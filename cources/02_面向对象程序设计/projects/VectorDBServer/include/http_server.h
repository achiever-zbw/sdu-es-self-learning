# pragma once
# include <rapidjson/document.h>
# include "httplib.h"
# include "index_factory.h"
# include "simple_index.h"

/**
 * 向量插入与搜索服务器的 HTTP 接口类
 * 处理 JSON 格式的请求响应
 */
class HttpServer {
public :
    enum struct CheckType {
        SEARCH ,     // 查询操作
        INSERT ,     // 插入操作
    } ;

    // 构造函数，包含 主机 和 端口
    HttpServer(const std::string& host , int port) ;

    // 启动 ！！！
    void start() ;

private :
    void searchHandler(const httplib::Request& req, httplib::Response& res) ;
    void insertHandler(const httplib::Request& req , httplib::Response& res) ;
    void setJsonResponse(const rapidjson::Document& json_response , httplib::Response& res) ;
    void setErrorJsonResponse(httplib::Response& res , int error_code , const std::string& errorMsg) ;
    bool isRequestValid(const rapidjson::Document& json_request, CheckType check_type);

    // 从请求体中提取索引类型
    IndexFactory::IndexType getIndexTypeFromRequest(const rapidjson::Document& json_request) ;

    httplib::Server server ;
    std::string host ; // 主机
    int port ; // 接口
} ; 