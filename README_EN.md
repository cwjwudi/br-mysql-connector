# BR Mysql Connector

## Project Overview

BR Mysql Connector is a solution for data exchange between B&R PLCs and MySQL databases. The project includes both PLC-side (Structured Text/C code) and PC-side (C++/Python) components, implementing data acquisition, SQL statement generation, queue caching, database writing, and more.

## Directory Structure

- `AS/`B&R Automation Studio project directory, containing all PLC-side logic, libraries, and configurations.
  - `Logical/`Main logic code, including SQL statement generation, writing, queue management, etc.
    - `MySQLInserter/`
      Main inserter logic, command generator, SQL statement generator, etc.
    - `Libraries/`
      Common and third-party libraries.
    - `MyLibraries/`
      Project custom libraries.
  - `Physical/`
    Hardware configuration files.
- `CPP/`PC-side C++ project, responsible for OPC UA communication, MySQL database operations, JSON configuration reading, etc.
  - `main.cpp`
    Main program, including database connection, SQL execution, configuration reading, etc.
  - `nlohmann`
    JSON configuration
  - `open62541`
    OPC UA communication
  - `Mysql`
    MySQL operations (not included in the project, please edit CMakeLists.txt according to your MySQL installation directory)
- `Python/`
  Python project for PC-side, with the same functionality as the C++ version
- `README.md`
  Project documentation.

## Main Features

- PLC Side
  - Automatic/timed data acquisition, SQL insert statement generation
  - Supports data caching and batch writing
  - Supports automatic table structure creation
  - Supports multi-task configuration
- PC Side
  - Reads JSON configuration file (C++ version)
  - Acquires data via OPC UA
  - Executes SQL statements to write to MySQL database
  - Log output and error handling

## Quick Start

### 1. PLC Side

- Open the `AS/` project in Automation Studio.
- Configure `gMySQLInserter.Config`, such as database name, table name, acquisition cycle, data mapping, etc. (see [`AS/Logical/MySQLInserter/Demo/Main.st`](AS/Logical/MySQLInserter/Demo/Main.st)).
- Download and run the program.

### 2. PC Side C++ Version

- Install MySQL and create sample databases.

  ```mysql
  CREATE DATABASE IF NOT EXISTS wn_8;
  CREATE DATABASE IF NOT EXISTS wn_9;
  ```
- Modify `CMakeList.txt` to include the MySQL header and library paths.
- Compile the program (or directly download the precompiled C++ program).

  ```bash
  cd CPP 
  mkdir build & cd build
  cmake ..
  make .
  ```
- Prepare the `cfg.json` configuration file, including database connection info, OPC UA configuration, etc. Place it in the same directory as the executable.
- Run the C++ program.

### 3. PC Side Python Version

* Install MySQL and create sample databases.

  ```mysql
  CREATE DATABASE IF NOT EXISTS wn_8;
  CREATE DATABASE IF NOT EXISTS wn_9;
  ```
* Install dependencies

  ```bash
  pip install mysql-connector-python
  pip install opcua
  ```
* Modify the `MYSQL` and `OPCUA` configurations in `SqlRepeater.py`, including database connection info, OPC UA configuration, etc.
* Run the Python program

## Dependencies

- B&R Automation Studio 4.12
- MySQL database
- C++11 or above compiler / Python 3.8 or above interpreter

## Contact

If you have any questions or suggestions, please contact the project maintainer.
