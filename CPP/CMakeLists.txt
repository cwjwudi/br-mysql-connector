include_directories(include "C:/Program Files/MySQL/MySQL Server 8.0/include")

file(GLOB SRC_FILES src/*)  # 获取 src 文件夹内的所有文件

link_directories("C:/Program Files/MySQL/MySQL Server 8.0/lib")

add_executable(demo2_mysql_opcua_json main.cpp ${SRC_FILES})

# 设置编译选项
target_link_libraries(demo2_mysql_opcua_json ws2_32 iphlpapi libmysql)