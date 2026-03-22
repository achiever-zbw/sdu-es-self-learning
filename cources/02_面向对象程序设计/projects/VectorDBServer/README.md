# VectorDBServer--简易向量数据库项目

## 一、项目介绍

这是一个基于C++的向量搜索服务器，提供HTTP API接口进行向量的插入和搜索操作。

---

在近年来，我们逐渐进入到快速崛起的AI新时代，诸如Transformer、GPT、大模型、AI Agent等技术不断兴起，
而**向量**作为经典的数学概念，在这一领域尤为重要。通过深度学习模型，我们可以将众多格式的数据类型转化为以**向量**表示
的数据，由此，**向量数据**逐步成为AI技术落地人类社会的基础数据。
传统的数据库技术无法应对向量数据在高维度、高精度和大规模场景下带来的挑战，而向量数据库针对向量数据的特点进行了专门设计，
能够更好的存储、索引和查询向量数据。

---

本项目参考书籍《从零构建向量数据库》（罗云著），书籍里面用到的`Faiss库`(高效相似性搜索和密集向量聚类的库)，本项目中不再使用，我仿照着其核心功能——**计算距离**、**搜索TopK**手搓了简易版的`simple_flat库`(扁平索引库)，用于自己项目的初步构建。

<div align="center">
    <img src="pics/book.png" alt="参考书籍" width="400" height="500">
</div>

---

## 开发环境
- **操作系统**: macOS
- **编译器**: Apple clang version 14.0.0
- **构建工具**: CMake 3.24+, Make
- **编程语言**: C++17
- **第三方库**: spdlog, rapidjson, httplib (已包含在项目中)


## 二、项目架构

```
VectorDBServer/
├── CMakeLists.txt              # CMake构建配置文件
├── README.md                   # 项目介绍文档
├── src/                        # 源代码目录
│   ├── main.cpp                # 程序入口，初始化日志、索引工厂和HTTP服务器
│   ├── http_server.cpp         # HTTP服务器类实现，处理网络请求和响应
│   ├── index_factory.cpp       # 索引工厂类实现，管理不同类型的索引实例
│   ├── simple_index.cpp        # 简单索引包装类实现，提供统一的索引接口
│   ├── json_request_handler.cpp # JSON请求处理器实现，解析和处理HTTP请求体
│   └── logger.cpp              # 日志管理器实现，提供全局日志功能
│
├── include/                    # 头文件目录
│   ├── constants.h             # 常量定义（字段名、错误码等）
│   ├── httplib.h               # HTTP服务器库头文件(第三方)
│   ├── http_server.h           # HTTP服务器类头文件
│   ├── index_factory.h         # 索引工厂类头文件
│   ├── simple_index.h          # 简单索引包装类头文件
│   ├── json_request_handler.h  # JSON请求处理器头文件
│   └── logger.h                # 日志管理器头文件
│
├── simple_flat/                # 手搓扁平索引实现模块
│   ├── flat_index.h            # 扁平索引核心实现头文件，存储和检索向量
│   ├── flat_index.cpp          # 扁平索引核心实现
│   ├── distance_utils.h        # 距离计算工具类头文件（L2距离）
│   ├── distance_utils.cpp      # 距离计算工具类实现
│   ├── heap_utils.h            # 优先队列工具类头文件，用于Top-K搜索
│   └── heap_utils.cpp          # 优先队列工具类实现
│   
│
├── examples/                   # 示例代码目录
│   ├── curl/                   # curl测试脚本目录
│   │   ├── insert.sh           # 向量插入测试脚本
│   │   └── search.sh           # 向量搜索测试脚本
│   └── README.md               # 示例使用说明文档
│
├── 第三方库/
│   ├── spdlog/                 # C++日志库
│   └── rapidjson/              # 高性能JSON解析库
│
└── build/                      # CMake构建输出目录（运行make后生成）
```

---

## 三、架构说明

### 1. 程序入口 (main.cpp)
- 初始化全局日志记录器
- 创建并配置全局索引工厂
- 启动HTTP服务器监听8080端口

### 2. HTTP服务层 (http_server.h/cpp)
- 基于httplib库实现HTTP服务器
- 提供两个主要API端点：
  - 搜索接口 (`/search`)：查询最相似的k个向量
  - 插入接口 (`/insert`)：插入新向量
- 支持JSON格式的请求和响应
- 包含请求验证和错误处理机制

### 3. 索引管理层 (index_factory.h/cpp)
- 实现工厂模式，支持多种索引类型
- 当前支持FLAT（扁平）索引，预留扩展接口
- 管理索引实例的生命周期
- 支持L2距离度量

### 4. 向量索引实现 (simple_index.h/cpp + simple_flat/)
**SimpleIndex**: 扁平索引的包装类，提供简洁的API接口

**FlatIndex**: 扁平索引核心实现
- 存储向量数据和对应的ID映射
- 支持批量向量添加和Top-K搜索
- 基于线性搜索的精确最近邻算法

**DistCalculator**: 距离计算工具
- 实现L2欧氏距离计算

**HeapIndex**: Top-K搜索工具
- 使用大顶堆维护k个最近邻结果
- 优化搜索性能

### 5. 请求处理层 (json_request_handler.h/cpp)
- 解析HTTP请求中的JSON数据
- 提取向量数据和参数
- 验证请求格式的合法性

### 6. 日志系统 (logger.h/cpp)
- 基于spdlog库的全局日志管理
- 支持不同日志级别配置
- 提供统一的日志接口

### 7. 常量定义 (constants.h)
- HTTP响应字段名定义
- 错误码和状态码定义
- 请求参数字段名定义

---

## 四、API接口

### 插入向量
- **URL**: `POST /insert`
- **请求体**: `{"vectors": [float], "id": int64, "indexType": "FLAT"}`
- **响应**: 成功/失败状态

### 搜索向量
- **URL**: `POST /search`
- **请求体**: `{"vectors": [float], "k": int, "indexType": "FLAT"}`
- **响应**: `{"retCode": 0, "vectors": [id], "distances": [float]}`


### 第三方库（项目已包含）
项目已经包含了所有必需的第三方库头文件，无需额外安装：
- **spdlog**: 高性能C++日志库（已包含在项目中）
- **RapidJSON**: 高性能JSON解析库（已包含在项目中）
- **httplib**: 轻量级HTTP服务器库（已包含在项目中）

---

## 五、项目运行
1、编译项目
```bash
mkdir build
cd build
cmake ..
make
```
2、运行项目
```bash
./vectorDB_server
```

3、测试项目
- 可以使用`examples/`目录下的示例代码进行测试，详细参考`examples/`目录下的README.md文件 

- 也可以使用curl等工具发送HTTP请求测试，如下
```bash
# 插入向量
curl -X POST http://localhost:8080/insert -H "Content-Type: application/json" -d '{"vectors": [0.88], "id": 1, "indexType": "FLAT"}'

curl -X POST http://localhost:8080/insert -H "Content-Type: application/json" -d '{"vectors": [0.99], "id": 2, "indexType": "FLAT"}'

curl -X POST http://localhost:8080/insert -H "Content-Type: application/json" -d '{"vectors": [1.01], "id": 3, "indexType": "FLAT"}'


# 搜索向量
curl -X POST http://localhost:8080/search -H "Content-Type: application/json" -d '{"vectors": [0.91], "k": 2, "indexType": "FLAT"}'

# 搜索向量成功响应
{"vectors":[1,2],"distances":[0.0009000018471851945,0.0063999975100159645],"retCode":0}

## 在这个例子中，搜索向量[0.91]的最近邻是向量1和向量2，它们的距离分别为0.0009和0.0064。
```

---

## 类设计思路与问题的解决

### 1. 索引层设计

在设计索引层时，我考虑到了未来可能需要支持不同类型的索引算法，所以采用了工厂模式来管理索引实例。这样做的好处是，当需要添加新的索引类型（比如HNSW）时，只需要扩展工厂类，而不需要修改现有代码。目前我只实现了FLAT（扁平）索引，但工厂模式为后续扩展留下了接口。

### 2. 向量存储与检索

我参考了Faiss库的核心功能，自己实现了一个简单的扁平索引库。主要包括三个核心类：

- **FlatIndex类**：负责存储向量数据，使用STL的vector来保证内存连续性，提高缓存命中率。同时用unordered_map来维护用户ID和内部索引的对应关系。

- **DistCalculator类**：专门负责计算两个向量之间的L2距离（欧氏距离），这是向量相似性搜索中最常用的距离度量。

- **HeapIndex类**：使用大顶堆来维护Top-K搜索结果，这样在搜索时只需要保留K个最优结果，不需要存储所有距离值，既节省内存又提高效率。

### 3. 接口封装

为了使用起来更方便，我设计了SimpleIndex类作为FlatIndex的包装类，隐藏了底层实现的细节，只提供两个简单的方法：insert_vectors和search_vectors。这样上层应用调用起来更加直观。

### 4. HTTP服务与请求处理

我使用httplib库实现了HTTP服务器，提供两个主要的API接口：
- POST /insert：用于插入向量
- POST /search：用于搜索相似向量

请求和响应都采用JSON格式，使用RapidJSON库来解析和处理JSON数据。在请求处理过程中，我还添加了参数验证和错误处理机制，确保系统的稳定性。

### 5. 遇到的问题和解决方法

在实现过程中，我遇到了几个主要问题：

**问题1：纯向量无标量的问题**
在当前项目中仅支持向量数据的操作，并未设计好过滤功能。在实际应用中，用户可能需要根据某些条件（如标签、时间等）来筛选向量。因此，我需要在索引层添加一个简单的标量字段来存储额外的信息。

**问题2：Top-K搜索结果的稳定性**
有时候多个向量与查询向量的距离完全相同，这会导致搜索结果不稳定。我通过在距离相同时按照ID大小进行排序来解决这个问题，确保结果的一致性。

**问题3：命名空间全局化**
全局JSON解析与全局索引工厂一开始并没有设计成全局的，而是在每个请求处理函数中进行实例化。这导致了在高并发场景下，每个请求都需要创建一个新的解析器和索引工厂，增加了系统的内存占用和初始化时间。

为了解决这个问题，我将JSON解析器和索引工厂设计成全局单例模式。这样，在系统启动时就会创建一个全局的解析器和索引工厂实例，后续所有请求都可以共享这两个实例，避免了重复创建和销毁的开销。

### 总结

通过这个项目，我实现了一个基本的向量搜索服务器。虽然功能相对简单，但涵盖了向量数据库的核心功能，包括向量存储、距离计算和Top-K搜索。这个项目不仅让我深入理解了向量数据库的原理，也提升了我在C++系统设计和性能优化方面的能力。