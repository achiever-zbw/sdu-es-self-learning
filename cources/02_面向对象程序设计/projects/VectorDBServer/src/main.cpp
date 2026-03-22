#include "http_server.h"
#include "index_factory.h"
#include "logger.h"

int main() {
    // 初始化全局日志记录器
    init_global_logger();
    set_log_level(spdlog::level::debug); // 设置日志级别为debug

    GlobalLogger->info("Global logger initialized");

    // 初始化全局IndexFactory实例
    int dim = 1; // 向量维度

    // 初始化索引
    IndexFactory* globalIndexFactory = getGlobalIndexFactory();      // 获取全局索引工厂
    globalIndexFactory->init(IndexFactory::IndexType::FLAT, dim);    // 初始化一个索引
    GlobalLogger->info("Global IndexFactory initialized");

    // 创建并启动HTTP服务器
    HttpServer server("localhost", 8080);      // 设置好主机和端口
    GlobalLogger->info("HttpServer created");
    server.start();   // 启动服务！！！

    return 0;
}