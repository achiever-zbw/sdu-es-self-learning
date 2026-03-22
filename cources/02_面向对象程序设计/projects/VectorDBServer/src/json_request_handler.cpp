# include "http_server.h"
# include "simple_index.h"
# include "index_factory.h"
# include <iostream>
# include <rapidjson/document.h>
# include <rapidjson/writer.h>
# include <rapidjson/stringbuffer.h>
# include "logger.h"
#include "constants.h"
# include "json_request_handler.h"

namespace {
    // 全局的 Json 请求处理对象
    JsonRequestHandler global_json_request_handler ; 
}

JsonRequestHandler* getGlobalJsonRequestHandler() {
    return &global_json_request_handler ; 
}

/**
 * 从 JSON 请求中获取到插入的向量、id
 * @param request_body JSON 请求体字符串
 * @return 包含插入向量和id的 std::pair
 */
std::pair<std::vector<float> , uint64_t> JsonRequestHandler::handleInsertRequest(const httplib::Request& req) {
    // 把 req.body 解析为 JSON 文档
    rapidjson::Document json_request ; 
    json_request.Parse(req.body.c_str()) ; 

    std::vector<float> data ; 
    uint64_t labels = json_request[REQUEST_ID].GetUint64() ;
    for(const auto& d : json_request[REQUEST_VECTORS].GetArray()) {
        data.push_back(d.GetFloat()) ; 
    }

    return {data , labels} ;
}

/**
 * 从请求中获取要查询的向量和 k
 * @param request_body JSON 请求体字符串
 * @return 包含查询的向量和 k 组成的 pair
 */
std::pair<std::vector<float> , int > JsonRequestHandler::handleSearchRequest(const httplib::Request& req) {
    // 把 req.body 解析为 JSON 文档
    rapidjson::Document json_request ; 
    json_request.Parse(req.body.c_str()) ; 

    std::vector<float> query ; 
    for(const auto& q : json_request[REQUEST_VECTORS].GetArray()) {
        query.push_back(q.GetFloat()) ; 
    }

    int k = json_request[REQUEST_K].GetInt() ; 

    return {query , k} ; 
}