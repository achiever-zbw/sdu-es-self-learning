#pragma once
#include "spdlog/spdlog.h"

// 全局的日志管理器，允许在任何地方使用
extern std::shared_ptr<spdlog::logger> GlobalLogger;

// 初始化全局日志管理器
void init_global_logger();

// 设置全局日志级别
void set_log_level(spdlog::level::level_enum log_level);