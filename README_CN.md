# BR Mysql Connector

## 项目简介

BR Mysql Connector 是一个用于在 B&R PLC 与 MySQL 数据库之间进行数据交互的解决方案。项目包含 PLC 端（Structured Text/C 代码）和 PC 端（C++/Python）两部分，实现了数据采集、SQL 语句生成、队列缓存、数据库写入等功能。

## 目录结构

- `AS/`B&R Automation Studio 工程目录，包含 PLC 端所有逻辑、库和配置。

  - `Logical/`主要逻辑代码，包括 SQL 语句生成、写入、队列管理等。
    - `MySQLInserter/`
      插入器主逻辑、命令生成器、SQL 语句生成器等。
    - `Libraries/`
      通用库和第三方库。
    - `MyLibraries/`
      项目自定义库。
  - `Physical/`
    硬件配置相关文件。
- `CPP/`PC 端 C++ 工程，负责 OPC UA 通信、MySQL 数据库操作、JSON 配置读取等。

  - `main.cpp`
    主程序，包含数据库连接、SQL 执行、配置读取等逻辑。
  - `nlohmann`
    json配置
  - `open62541`
    OPC UA 通信
  - `Mysql`
    Mysql操作（工程未包含，请根据自己安装的Mysql目录，编辑CMakeLists.txt）
- `Python/`PC端的Python工程，与C++版功能一致
- `README.md`
  项目说明文档。

## 主要功能

- PLC 端
  - 自动/定时采集数据，生成 SQL 插入语句
  - 支持数据缓存、批量写入
  - 支持表结构自动创建
  - 支持多任务配置
- PC 端
  - 读取 JSON 配置文件（C++版）
  - 通过 OPC UA 获取数据
  - 执行 SQL 语句写入 MySQL 数据库
  - 日志输出与错误处理

## 快速开始

### 1. PLC 端

- 在 Automation Studio 中打开 `AS/` 工程。
- 配置 `gMySQLInserter.Config`，如数据库名、表名、采集周期、数据映射等（详见 [`AS/Logical/MySQLInserter/Demo/Main.st`](AS/Logical/MySQLInserter/Demo/Main.st)）。
- 下载并运行程序。

### 2. PC 端C++版

- 安装 MySQL，并创建案例数据库。

  ```mysql
  CREATE DATABASE IF NOT EXISTS wn_8;
  CREATE DATABASE IF NOT EXISTS wn_9;
  ```
- 修改`CMakeList.txt`包含的MySQL头文件、库文件路径。
- 编译程序（也可以直接下载编译好的C++程序）。

  ```bash
  cd CPP 
  mkdir build & cd build
  cmake ..
  make .
  ```
- 准备 `cfg.json` 配置文件，包含数据库连接信息、Opuca配置等。与exe文件放置于同级目录。
- 执行C++程序。

### 3. PC端Python版

* 安装 MySQL，并创建案例数据库。

  ```mysql
  CREATE DATABASE IF NOT EXISTS wn_8;
  CREATE DATABASE IF NOT EXISTS wn_9;
  ```
* 安装依赖库

  ```bash
  pip install mysql-connector-python
  pip install opcua
  ```
* 修改`SqlRepeater.py`中的`MYSQL`和`OPCUA`配置，包含数据库连接信息、Opcua配置等。
* 执行Python程序

## 依赖

- B&R Automation Studio 4.12
- MySQL 数据库
- C++11 及以上编译器 / Python 3.8及以上解释器

## 联系方式

如有问题或建议，请联系项目维护者。
