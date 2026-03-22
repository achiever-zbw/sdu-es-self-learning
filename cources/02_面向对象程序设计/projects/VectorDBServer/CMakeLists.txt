cmake_minimum_required(VERSION 3.10)
# 项目名称 ———— VectorDBServer
project(VectorDBServer)

# 设置 C++ 标准 C++ 17 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 添加编译选项
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pthread -O3 -march=native")

# 检查AVX支持（仅x86架构）
if(CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64|AMD64")
    include(CheckCXXSourceRuns)
    set(CMAKE_REQUIRED_FLAGS "-mavx2")
    check_cxx_source_runs("
#include <immintrin.h>
int main() {
    __m256d a = _mm256_set_pd(1.0, 2.0, 3.0, 4.0);
    __m256d b = _mm256_set_pd(5.0, 6.0, 7.0, 8.0);
    __m256d c = _mm256_add_pd(a, b);
    return 0;
}
" HAVE_AVX2)
    if(HAVE_AVX2)
        add_definitions(-DHAVE_AVX2)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mavx2 -DHAVE_AVX2")
    endif()
endif()

# 包含头文件目录
include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/simple_flat)
include_directories(${CMAKE_SOURCE_DIR}/spdlog)
include_directories(${CMAKE_SOURCE_DIR}/rapidjson)

# 收集 simple_flat 目录下的所有源文件
file(GLOB SIMPLE_FLAT_SOURCES
    ${CMAKE_SOURCE_DIR}/simple_flat/*.cpp
)

# 源文件
set(MAIN_SOURCES
    src/main.cpp
    src/http_server.cpp
    src/index_factory.cpp
    src/simple_index.cpp
    src/json_request_handler.cpp
    src/logger.cpp
)

# 创建主程序可执行文件
add_executable(vectorDB_server
    ${MAIN_SOURCES}
    ${SIMPLE_FLAT_SOURCES}
)

# 链接库
target_link_libraries(vectorDB_server m pthread)


