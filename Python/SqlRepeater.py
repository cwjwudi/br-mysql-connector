import threading
import queue
import time
import mysql.connector
from opcua import Client
from opcua.ua import uatypes
from opcua.common.subscription import SubHandler
from opcua.ua import Variant, VariantType
from opcua import ua
from datetime import datetime


# ===== 配置部分 =====
OPCUA_SERVER_URL = "opc.tcp://192.168.0.200:4840"
OPCUA_READ_NODE_ID = "ns=6;s=::sql_writer:rec_data.InsertCmd"
OPCUA_WRITE_NODE_ID = "ns=6;s=::AsGlobalPV:gSqlExtSts"

MYSQL_CONFIG = {
    "host": "localhost",
    "user": "root",
    "password": "123456",
    "database": "wn_9"
}

DISP_NUMBER = 30  # 显示的字符数

# ===== 全局资源 =====
data_queue = queue.Queue(maxsize=100)  # 线程安全队列，限制大小防止内存溢出
stop_event = threading.Event()  # 停止事件通知
heartbeat = 0
response_server = False


class OpcUaReadThread(threading.Thread):
    def __init__(self):
        super(OpcUaReadThread, self).__init__()
        self.working = True
        self.node_id = OPCUA_READ_NODE_ID
        self.last_data = None

    def __del__(self):
        self.working = False
        stop_event.wait(1)

    def connectStop(self):
        # self.working = False  ##经过测试，此处开就无法断线重连
        # self.quit()
        print("OpcUaReadGoToStop")

    # 处理要做的业务逻辑
    def run(self):
        global response_server
        while self.working == True:
            try:
                client = Client(OPCUA_SERVER_URL)
                client.connect()
                root = client.get_root_node()

                tmp1 = client.get_node(self.node_id)

                while True:
                    #######################  要采集的变量在这里进行编写     ############################################
                    # 通过外部引用的GlobalData.py建立线程之间的数据联系
                    data = tmp1.get_value()
                    if data != self.last_data: # 数据变化，执行写入
                        data_queue.put_nowait(data)
                        self.last_data = data
                        response_server = True
                    #######################  要采集的变量在这里进行编写     ############################################

                    stop_event.wait(0.2)

            except Exception as e:
                with open('database_err.txt', 'a') as file:
                    txtr = "Cannot establish the connection, I'm over"
                    current_time = datetime.now()
                    file.write(f"\n{current_time}")
                    file.write(f"：{e}")
                    file.write(f"----{txtr}")
                print("Cannot establish the connection, I'm over")
                stop_event.wait(1)


class OpcUaWriteThread(threading.Thread):
    def __init__(self):
        super(OpcUaWriteThread, self).__init__()
        self.working = True

    def __del__(self):
        self.working = False
        self.stop()
        self.wait()

    def stop(self):
        self.working = False

    # 处理要做的业务逻辑
    def run(self):
        global heartbeat, response_server
        while  self.working:
            try:
                client = Client(OPCUA_SERVER_URL)
                client.connect()
                root = client.get_root_node()
                tmpWrite1 = client.get_node(OPCUA_WRITE_NODE_ID) # Write为全局变量名
                #####################          要赋值的变量在这里进行操作           #######################
                while True:
                    if response_server == True:
                        response_server = False
                        heartbeat = heartbeat + 1

                        data_send = ua.DataValue()
                        data_send.Value = ua.Variant(heartbeat, ua.VariantType.UInt32)

                        tmpWrite1.set_value(data_send)
                    stop_event.wait(0.2)

            except Exception as e:
                print(e)
            finally:
                try:
                    client.disconnect()

                except Exception as e:
                    with open('database_err.txt', 'a') as file:
                        txtw = "OpcUaWrite Cannot Over"
                        current_time = datetime.now()
                        file.write(f"\n{current_time}")
                        file.write(f"：{e}")
                        file.write(f"----{txtw}")
                    print(e)
                    print("OpcUaWrite Cannot Over")

# ===== 数据库工作线程 =====
class DbWorker(threading.Thread):
    def __init__(self):
        super().__init__()
        self.conn = mysql.connector.connect(**MYSQL_CONFIG)
        self._init_database()

    def _init_database(self):
        """初始化数据库表结构"""
        with self.conn.cursor() as cursor:
            cursor.execute("""
                CREATE TABLE IF NOT EXISTS opcua_data_log (
                    id INT AUTO_INCREMENT PRIMARY KEY,
                    data_string TEXT NOT NULL,
                    timestamp TIMESTAMP DEFAULT CURRENT_TIMESTAMP
                )
            """)
            self.conn.commit()

    def _safe_insert(self, data):
        """安全执行插入操作"""
        try:
            with self.conn.cursor() as cursor:
                cursor.execute(
                    data
                )
                self.conn.commit()
                value = extract_values_suffix(data, DISP_NUMBER)
                print(f"插入成功: {value}")
        except mysql.connector.Error as e:
            with open('database_err.txt', 'a') as file:
                current_time = datetime.now()
                file.write(f"\n{current_time}")
                file.write(f"：{e}")
            print(f"数据库错误: {e}")
            self.conn.rollback()

    def run(self):
        while not stop_event.is_set():
            try:
                data = data_queue.get(timeout=1)  # 阻塞最多1秒
                self._safe_insert(data)
                data_queue.task_done()
            except queue.Empty:
                continue
        self.conn.close()


def extract_values_suffix(s, n):
    """
    查找字符串中所有'VALUES'后面的n个字符，并将它们拼接起来返回。
    如果未找到'VALUES'或后面不足n个字符，则跳过该部分。
    """
    result = []
    idx = s.find('VALUES')
    while idx != -1:
        start = idx + len('VALUES')
        if start + n <= len(s):
            result.append(s[start:start+n])
        idx = s.find('VALUES', start)
    return ''.join(result)


# ===== 主程序 =====
if __name__ == "__main__":
    try:
        # 启动线程
        opcua_reader_thread = OpcUaReadThread()
        opcua_writer_thread = OpcUaWriteThread()
        db_thread = DbWorker()

        opcua_reader_thread.start()
        opcua_writer_thread.start()
        db_thread.start()

        # 主线程监控
        while True:
            opcua_reader_thread.join()
            opcua_writer_thread.join()
            db_thread.join()

    except KeyboardInterrupt:
        print("\n接收到停止信号...")
        stop_event.set()

        # 等待线程结束
        opcua_reader_thread.join()
        opcua_writer_thread.join()
        db_thread.join()
        
        print("清理剩余队列数据:")
        while not data_queue.empty():
            data = data_queue.get()
            DbWorker()._safe_insert(data)  # 临时实例处理残留数据
            data_queue.task_done()
