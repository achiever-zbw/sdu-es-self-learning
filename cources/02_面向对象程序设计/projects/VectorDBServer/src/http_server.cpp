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

/**
 * 构造函数，包含 主机 和 端口
 * @param host 主机名或IP地址
 * @param port 端口号
 */
HttpServer::HttpServer(const std::string& host , int port) : host(host) , port(port){
    // 注册 search 路由
    server.Post("/search" , [this](const httplib::Request& req , httplib::Response& res) {
        searchHandler(req , res) ;
    }) ;
    // 注册 insert 路由
    server.Post("/insert" , [this](const httplib::Request& req , httplib::Response& res) {
        insertHandler(req , res) ;
    }) ; 
}

/**
 *启动启动启动！！！开始监听指定的主机和端口
 */
void HttpServer::start() {
    server.listen(host , port) ; 
}

/**
 * 检查 Json 请求是否为有效对象
 * @details 检查 Json 请求是否为有效对象，根据 check_type 检查 search 或 insert 请求是否合法
 * @param json_request Json 请求对象
 * @param check_type 检查类型，SEARCH 或 INSERT
 * @return true 请求合法 ， false 请求不合法
 */
bool HttpServer::isRequestValid(const rapidjson::Document& json_request, CheckType check_type) {
    switch (check_type) {
        // 查询操作,确保包含 vectors 和 k 参数, 可选 index_type 参数
        case CheckType::SEARCH:
            return json_request.HasMember(REQUEST_VECTORS) &&
                   json_request.HasMember(REQUEST_K) &&
                   (!json_request.HasMember(REQUEST_INDEX_TYPE) || json_request[REQUEST_INDEX_TYPE].IsString());
        // 插入操作,确保包含 vectors 和 id 参数, 可选 index_type 参数
        case CheckType::INSERT:
            return json_request.HasMember(REQUEST_VECTORS) &&
                   json_request.HasMember(REQUEST_ID) &&
                   (!json_request.HasMember(REQUEST_INDEX_TYPE) || json_request[REQUEST_INDEX_TYPE].IsString());
        default:
            return false;
    }
}

/**
 * 从 Json 请求中获取索引类型
 * @param json_request Json 请求对象
 * @return IndexFactory::IndexType 索引类型
 */
IndexFactory::IndexType HttpServer::getIndexTypeFromRequest(const rapidjson::Document& json_request) {
    // 检测 index_type 参数
    if(json_request.HasMember(REQUEST_INDEX_TYPE)) {
        std::string index_type_str = json_request[REQUEST_INDEX_TYPE].GetString() ;  // 先获取字符串
        if(index_type_str == "FLAT") {
            return IndexFactory::IndexType::FLAT ; 
        } 
    }
    return IndexFactory::IndexType::UNKNOWN ;
}

/**
 * insert 路由处理函数
 * @details 接收用户的 insert 请求，解析参数，调用索引工厂初始化索引 , 参数的形式为 
 * {
 *     "vectors": [0.1, 0.2, 0.3, ...],
 *     "id": 12345,
 *     "index_type": "FLAT"
 * }
 */
void HttpServer::insertHandler(const httplib::Request& req, httplib::Response& res) {
    GlobalLogger->debug("Received insert request") ; // "接受到插入请求" 

    // 把接收到的 Json 请求解析一下
    rapidjson::Document json_request ; 
    json_request.Parse(req.body.c_str()) ; 

    // 打印一下用户输入的请求参数
    GlobalLogger->info("Insert request parameters : {}" , req.body) ; 

    // 检查 Json 请求是否为有效对象
    if(!json_request.IsObject()) {
        GlobalLogger->error("Invalid JSON request") ; 
        res.status = 400 ; 
        setErrorJsonResponse(res , -1 , "Invalid JSON request") ; 
        return ; 
    }

    // 检查请求的合法性
    if(!isRequestValid(json_request , CheckType::INSERT)) {
        GlobalLogger->error("Missing vectors or id parameters in the request") ; 
        res.status = 400 ;
        setErrorJsonResponse(res , RESPONSE_RETCODE_ERROR, "Missing vectors or id parameters in the request") ; 
        return ; 
    }

    // 一切正常！！开始获取各种参数，插入 ！
    // 使用全局的 Json 请求处理对象处理 insert 请求
    std::pair<std::vector<float> , uint64_t> insert_params = getGlobalJsonRequestHandler()->handleInsertRequest(req) ; 
    std::vector<float> data = insert_params.first ; 
    uint64_t labels = insert_params.second ; 

    GlobalLogger->debug("Insert parameters : label = {}" , labels) ; 

    // 获取参数中的索引类型
    IndexFactory::IndexType index_type = getIndexTypeFromRequest(json_request) ; 
    // 如果索引类型为UNKNOWN，返回400错误
    if (index_type == IndexFactory::IndexType::UNKNOWN) {
        GlobalLogger->error("Invalid indexType parameter in the request");
        res.status = 400;
        setErrorJsonResponse(res, RESPONSE_RETCODE_ERROR, "Invalid indexType parameter in the request"); 
        return;
    }
    // 根据索引类型获取索引
    IndexFactory* globalIndexFactory = getGlobalIndexFactory() ;  // 先获取全局的索引工厂
    void* index = globalIndexFactory->getIndex(index_type) ; 

    switch(index_type) {
        case IndexFactory::IndexType::FLAT : {
            SimpleIndex* simple_index = static_cast<SimpleIndex*>(index) ; 
            // 调用自己实现的 insert 函数
            simple_index->insert_vectors(data, labels) ; 
            break ; 
        } case IndexFactory::IndexType::UNKNOWN :{
            GlobalLogger->error("Unknown index type") ; 
            res.status = 400 ;
            setErrorJsonResponse(res , RESPONSE_RETCODE_ERROR, "Unknown index type") ; 
            return ; 
        } default : break ; 
    }
    // 设置响应
    rapidjson::Document json_response;
    json_response.SetObject();
    rapidjson::Document::AllocatorType& allocator = json_response.GetAllocator();

    // 添加retCode到响应
    json_response.AddMember(RESPONSE_RETCODE, RESPONSE_RETCODE_SUCCESS, allocator);

    setJsonResponse(json_response, res);
}


/**
 * 处理用户的 search 请求，解析参数，调用索引工厂查询索引 , 参数的形式为
 * {
 *     "vectors": [0.1, 0.2, 0.3, ...],
 *     "k": 10
 * }
 */
void HttpServer::searchHandler(const httplib::Request& req, httplib::Response& res) {
    GlobalLogger->debug("Received search request") ; 

    // 解析 JSON 请求
    rapidjson::Document json_request ; 
    json_request.Parse(req.body.c_str()) ; 

    // 打印一下用户输入的请求参数
    GlobalLogger->info("Search request parameters : {}" , req.body) ; 

    // 检查 Json 请求是否为有效对象
    if(!json_request.IsObject()) {
        GlobalLogger->error("Invalid JSON request") ; 
        res.status = 400 ; 
        setErrorJsonResponse(res , RESPONSE_RETCODE_ERROR , "Invalid JSON request") ; 
        return ; 
    }

    // 检查请求的合法性
    if(!isRequestValid(json_request , CheckType::SEARCH)) {
        GlobalLogger->error("Missing vectors or k parameters in the request") ; 
        res.status = 400 ;
        setErrorJsonResponse(res , RESPONSE_RETCODE_ERROR, "Missing vectors or k parameters in the request") ; 
        return ; 
    }

    std::pair<std::vector<float> , int> search_params = getGlobalJsonRequestHandler()->handleSearchRequest(req) ; 
    std::vector<float> query = search_params.first ; 
    int k = search_params.second ; 

    GlobalLogger->debug("Query parameters : k = {}" , k) ; 

    // 获取参数中的索引类型
    IndexFactory::IndexType index_type = getIndexTypeFromRequest(json_request) ; 
    // 如果索引类型为UNKNOWN，返回400错误
    if (index_type == IndexFactory::IndexType::UNKNOWN) {
        GlobalLogger->error("Invalid indexType parameter in the request");
        res.status = 400;
        setErrorJsonResponse(res, RESPONSE_RETCODE_ERROR, "Invalid indexType parameter in the request"); 
        return;
    }
    // 根据索引类型获取索引
    IndexFactory* globalIndexFactory = getGlobalIndexFactory() ; 
    void* index = globalIndexFactory->getIndex(index_type) ; 

    std::pair<std::vector<int64_t> , std::vector<float>> results ; 
    switch(index_type) {
        case IndexFactory::IndexType::FLAT : {
            SimpleIndex* simple_index = static_cast<SimpleIndex*>(index) ; 
            results = simple_index->search_vectors(query , k) ;  // 执行搜索
            break ; 
        }
        case IndexFactory::IndexType::UNKNOWN : {
            GlobalLogger->error("Unknown index type") ; 
            res.status = 400 ;
            setErrorJsonResponse(res , RESPONSE_RETCODE_ERROR, "Unknown index type") ; 
            return ; 
        }
        default : break ; 
    }

    // 把结果转化为 JSON 输出出来
    rapidjson::Document json_response ; 
    json_response.SetObject()  ;      // 把 json_response 设为对象类型
    rapidjson::Document::AllocatorType& allocator = json_response.GetAllocator() ;     // 获取分配器

    // 检查是否有有效的搜索结果
    bool valid_results = false;
    rapidjson::Value vectors(rapidjson::kArrayType);        // 搜索结果的向量数组
    rapidjson::Value distances(rapidjson::kArrayType);      // 搜索结果的距离数组
    for (size_t i = 0; i < results.first.size(); ++i) {
        if (results.first[i] != -1) {
            valid_results = true;
            vectors.PushBack(results.first[i], allocator);
            distances.PushBack(results.second[i], allocator);
        }
    }

    if (valid_results) {
        json_response.AddMember(RESPONSE_VECTORS, vectors, allocator);
        json_response.AddMember(RESPONSE_DISTANCES, distances, allocator);
    }

    // 设置响应
    json_response.AddMember(RESPONSE_RETCODE, RESPONSE_RETCODE_SUCCESS, allocator); 
    setJsonResponse(json_response, res);
}

/**
 * 设置 JSON 响应体为错误信息
 * @param res HTTP 响应对象
 * @param error_code 错误码
 * @param errorMsg 错误信息
 */
void HttpServer::setErrorJsonResponse(httplib::Response& res, int error_code, const std::string& errorMsg) {
    rapidjson::Document json_response;
    json_response.SetObject();
    rapidjson::Document::AllocatorType& allocator = json_response.GetAllocator();
    json_response.AddMember("retCode", error_code, allocator);
    json_response.AddMember("errorMsg", rapidjson::StringRef(errorMsg.c_str()), allocator); // 使用宏定义
    setJsonResponse(json_response, res);
}

/**
 * 设置 JSON 响应体为成功信息
 * @param res HTTP 响应对象
 * @param json_response JSON 响应文档
 */
void HttpServer::setJsonResponse(const rapidjson::Document& json_response, httplib::Response& res) {
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    json_response.Accept(writer);
    res.set_content(buffer.GetString(), RESPONSE_CONTENT_TYPE_JSON); // 使用宏定义
}