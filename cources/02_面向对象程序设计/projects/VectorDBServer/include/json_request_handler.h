# pragma once
# include <iostream>
# include <rapidjson/document.h>
# include <rapidjson/writer.h>
# include <rapidjson/stringbuffer.h>

/**
 * JSON 格式请求体处理类
 * 负责解析 JSON 格式的请求体，提取索引类型、向量、K 值等参数
 * 分为 insert 和 search 两种请求
 */
class JsonRequestHandler {
public : 
    // 处理 insert 的请求
    std::pair<std::vector<float> , uint64_t> handleInsertRequest(const httplib::Request& req) ;

    // 处理 search 的请求
    std::pair<std::vector<float> , int> handleSearchRequest(const httplib::Request& req) ; 
    
private :
} ; 

// 获取全局的 JSON 请求体处理器
JsonRequestHandler* getGlobalJsonRequestHandler() ; 