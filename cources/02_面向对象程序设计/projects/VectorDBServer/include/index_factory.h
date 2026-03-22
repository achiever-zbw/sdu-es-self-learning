# pragma once
# include "distance_utils.h"
# include "flat_index.h"
# include "heap_utils.h"
# include "simple_index.h"
# include <map>

/**
 * 索引工厂类，用于初始化和获取不同类型的索引
 * 支持的索引类型：
 * - FLAT：扁平索引
 * 支持的距离类型：
 * - L2：欧氏距离
 */
class IndexFactory {
public :
    // 索引类型枚举
    enum struct IndexType {
        FLAT , // 目前仅支持扁平索引类型
        UNKNOWN , 
    } ; 

    // 距离类型枚举
    enum struct MetricType {
        L2 , 
        UNKNOWN , 
    } ; 

    // 初始化一个索引   
    void init(IndexType index_type , int dim , MetricType metric_type = MetricType::L2) ;  

    // 获取索引
    void* getIndex(IndexType index_type) const ;

private :
    // 索引类型到索引指针的映射,后期根据索引l类型获取索引指针
    std::map<IndexType , void*> index_map ;
}; 

// 获取全局的索引工厂
IndexFactory* getGlobalIndexFactory() ; 