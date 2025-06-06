#include <mysql.h>
#include "open62541.h"
#include "nlohmann/json.hpp"
#include <iostream>
#include <fstream>
#include <thread>
#include <mutex>
#include <deque>
#include <atomic>
// 添加共享变量
std::atomic<uint32_t> executeCounter{0};
std::mutex counterMutex;


void writeOpcUaUint32(UA_Client *client, std::atomic<uint32_t> &counter, bool &done) {
    uint32_t lastValue = 0; // 初始化上一次的值为 0
    uint32_t heartbeat = 0; // 心跳变量
    uint32_t oldHeartbeat = 0; // 心跳变量
    while (!done) {
        // 正确获取状态
        UA_SecureChannelState channelState;
        UA_SessionState sessionState;
        UA_StatusCode connectStatus;
        UA_Client_getState(client, &channelState, &sessionState, &connectStatus);
        if (connectStatus != UA_STATUSCODE_GOOD || sessionState != UA_SESSIONSTATE_ACTIVATED) {
            std::cerr << "OPC UA session not active, waiting to reconnect..." << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            continue;
        }

        uint32_t currentValue = counter.load();
        if (currentValue != lastValue) { // 检查是否有新值
            UA_Variant value;
            UA_Variant_init(&value);
            UA_Variant_setScalarCopy(&value, &currentValue, &UA_TYPES[UA_TYPES_UINT32]);
            
            UA_StatusCode status = UA_Client_writeValueAttribute(client,
                UA_NODEID_STRING(6, "::AsGlobalPV:gMySQLInserter.ExternalCom.Counter[0]"),
                &value);
                
            if (status == UA_STATUSCODE_GOOD) {
                std::cout << "Written return value to OPC UA: " << currentValue << std::endl;
                lastValue = currentValue; // 更新上一次的值
            } else {
                std::cerr << "Failed to write Counter: " << UA_StatusCode_name(status) << std::endl;    
            }
            UA_Variant_clear(&value);
        }

        // HeartBeat变量自增并写入
        heartbeat++;
        if ((heartbeat - oldHeartbeat) > 10) { // 控制写入频率
            UA_Variant hbValue;
            UA_Variant_init(&hbValue);
            UA_Variant_setScalarCopy(&hbValue, &heartbeat, &UA_TYPES[UA_TYPES_UINT32]);
            UA_StatusCode hbStatus = UA_Client_writeValueAttribute(client,
                UA_NODEID_STRING(6, "::AsGlobalPV:gMySQLInserter.ExternalCom.HeartBeat[0]"),
                &hbValue);
            if (hbStatus != UA_STATUSCODE_GOOD) {
                std::cerr << "Failed to write HeartBeat: " << UA_StatusCode_name(hbStatus) << std::endl;
            }
            UA_Variant_clear(&hbValue);

            oldHeartbeat = heartbeat;
        }


        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void readOpcUaString(UA_Client *client, std::atomic<uint32_t> &counter, std::deque<std::string> &cmdQueue, std::mutex &mtx, bool &done) {
    UA_Variant value;
    std::string lastCmd; // Store the last command read
    while (!done) {
        // 正确获取状态
        UA_SecureChannelState channelState;
        UA_SessionState sessionState;
        UA_StatusCode connectStatus;
        UA_Client_getState(client, &channelState, &sessionState, &connectStatus);
        if (connectStatus != UA_STATUSCODE_GOOD || sessionState != UA_SESSIONSTATE_ACTIVATED) {
            std::cerr << "OPC UA session not active, waiting to reconnect..." << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            continue;
        }
        UA_Variant_init(&value);
        UA_StatusCode status = UA_Client_readValueAttribute(client, UA_NODEID_STRING(6, "::AsGlobalPV:gMySQLInserter.ExternalCom.StrCmd[0]"), &value);
        if (status == UA_STATUSCODE_GOOD && UA_Variant_hasScalarType(&value, &UA_TYPES[UA_TYPES_STRING])) {
            std::string newCmd((char *)((UA_String *)value.data)->data, ((UA_String *)value.data)->length);
            if (newCmd != lastCmd) { // Only add if the command is different
                std::lock_guard<std::mutex> lock(mtx);
                if (!newCmd.empty()) {
                    if (cmdQueue.size() >= 100) {
                        // 超过最大容量，丢弃最旧指令
                        std::cout << "Deque is max! The oldest cmd is lost!" << std::endl;
                        cmdQueue.pop_front();
                    }
                    cmdQueue.push_back(newCmd);
                    std::cout << "Read OPC UA String: " << newCmd << std::endl;
                    // 压入队列后，增加计数器
                    uint32_t current = counter.load();
                    counter.store(current + 1);                 
                }
                lastCmd = newCmd; // Update the last command
            }
        } else {
            std::cerr << "Failed to read value: " << UA_StatusCode_name(status) << std::endl;
        }
        UA_Variant_clear(&value);
        std::this_thread::sleep_for(std::chrono::milliseconds(200)); // Sleep for 200ms
    }
}

void executeSqlString(std::deque<std::string> &cmdQueue, std::mutex &mtx, bool &done, MYSQL *conn) {
    while (!done)
    {
        std::string sqlCommand;
        {
            std::lock_guard<std::mutex> lock(mtx);
            if (!cmdQueue.empty()) {
                sqlCommand = cmdQueue.front();
                cmdQueue.pop_front();
            }
        }
        if (!sqlCommand.empty()) {
            std::cout << "Executing SQL Command: " << sqlCommand << std::endl;
            if (mysql_query(conn, sqlCommand.c_str())) {
                std::cerr << "SQL execution failed: " << mysql_error(conn) << std::endl;
            } else {
                std::cout << "SQL executed successfully." << std::endl;
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

int main() {
    /***************************读取配置信息**********************************/
    // 打开并读取 JSON 文件
    std::ifstream inFile("cfg.json");
    if (!inFile) {
        std::cerr << "缺少配置文件 cfg.json" << std::endl;
        return 1;
    }

    nlohmann::json j;
    inFile >> j;

    // 打印整个 JSON 内容
    std::cout << j.dump(4) << std::endl;
    // 从 JSON 读取 MySQL 配置并做错误判断
    if (!j.contains("mysql") || !j["mysql"].contains("host") || !j["mysql"].contains("user") ||
        !j["mysql"].contains("password") || !j["mysql"].contains("database")) {
        std::cerr << "配置文件缺少 mysql 配置信息" << std::endl;
        return 1;
    }
    std::string mysql_host = j["mysql"]["host"];
    std::string mysql_user = j["mysql"]["user"];
    std::string mysql_password = j["mysql"]["password"];
    std::string mysql_database = j["mysql"]["database"];
    if (mysql_host.empty() || mysql_user.empty() || mysql_database.empty()) {
        std::cerr << "mysql配置信息不能为空 "<< std::endl;
        return 1;
    }
    // 从 JSON 读取 OPC UA 配置并做错误判断
    if (!j.contains("opcua") || !j["opcua"].contains("url")) {
        std::cerr << "配置文件缺少 opcua 配置信息" << std::endl;
        return 1;
    }
    std::string opcua_url = j["opcua"]["url"];
    if (opcua_url.empty()) {
        std::cerr << "opcua url 不能为空" << std::endl;
        return 1;
    }

    /***************************MySQL连接**********************************/
    // MySQL 连接信息
    const char *server = mysql_host.c_str();
    const char *user = mysql_user.c_str();
    const char *password = mysql_password.c_str();
    const char *database = mysql_database.c_str();

    MYSQL *conn = mysql_init(nullptr);
    if (conn == nullptr) {
        std::cerr << "mysql_init() failed\n";
        return EXIT_FAILURE;
    }
    if (mysql_real_connect(conn, server, user, password, database, 0, nullptr, 0) == nullptr) {
        std::cerr << "mysql_real_connect() failed: " << mysql_error(conn) << std::endl;
        mysql_close(conn);
        return EXIT_FAILURE;
    }
    std::cout << "Connected to MySQL database!" << std::endl;

    /******************************OPCUA连接**********************************/
    // Create a client instance
    UA_Client *client = UA_Client_new();
    UA_ClientConfig_setDefault(UA_Client_getConfig(client));

    // Connect to the OPC UA server
    UA_StatusCode status = UA_Client_connect(client, opcua_url.c_str());

    if (status != UA_STATUSCODE_GOOD) {
        std::cerr << "Failed to connect to server: " << UA_StatusCode_name(status) << std::endl;
        // UA_Client_delete(client);
        // return EXIT_FAILURE;
    }else {
        std::cout << "Connected to OPC UA server!" << std::endl;    
    }

    // Shared resources
    std::deque<std::string> cmdQueue;
    std::mutex mtx;
    bool done = false;
    executeCounter.store(0);

    // Start threads
    std::thread readerThread(readOpcUaString, client, std::ref(executeCounter) ,std::ref(cmdQueue), std::ref(mtx), std::ref(done));
    std::thread executorThread(executeSqlString, std::ref(cmdQueue), std::ref(mtx), std::ref(done), conn);
    std::thread writerThread(writeOpcUaUint32, client, std::ref(executeCounter), std::ref(done));

    // 线程检测输入
    std::thread inputThread([&done]() {
        std::cin.get();
        done = true;
    });

    // 程序一直运行，直到用户按下回车
    std::cout << "程序正在运行，按回车键退出..." << std::endl;

    UA_SecureChannelState channelState;
    UA_SessionState sessionState;
    UA_StatusCode connectStatus;

    while (!done) {
        // 在这里添加你的主循环逻辑
        UA_Client_getState(client, &channelState, &sessionState, &connectStatus);
        if (connectStatus != UA_STATUSCODE_GOOD || sessionState != UA_SESSIONSTATE_ACTIVATED) {
            done = false;
            std::cerr << "OPC UA session not active, waiting to reconnect..." << std::endl;
            status = UA_Client_connect(client, opcua_url.c_str());
            std::cerr << "Failed to connect to server: " << UA_StatusCode_name(status) << std::endl;
            
            if (status!= UA_STATUSCODE_GOOD) {
                std::cerr << "Failed to connect to server: " << UA_StatusCode_name(status) << std::endl;
            }else {
                std::cout << "Connected to OPC UA server!" << std::endl;
            }
            std::this_thread::sleep_for(std::chrono::seconds(1));
            continue;
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    // 等待队列中的指令执行完毕
    while (!cmdQueue.empty()) {
        done = false; // 继续执行
        std::cout << "Waiting for all commands to be executed..." << std::endl;
        std::lock_guard<std::mutex> lock(mtx);
        std::cout << "Remaining commands in queue: " << cmdQueue.size() << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    done = true; // 设置 done 为 true，结束所有线程

    // Join threads
    readerThread.join();
    executorThread.join();
    writerThread.join();
    inputThread.join();

    // Clean up
    UA_Client_disconnect(client);
    UA_Client_delete(client);

    // 线程结束后关闭数据库连接
    mysql_close(conn);

    return EXIT_SUCCESS;
}
