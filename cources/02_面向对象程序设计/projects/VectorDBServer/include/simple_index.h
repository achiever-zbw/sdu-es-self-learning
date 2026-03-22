# pragma once
# include "distance_utils.h"
# include "flat_index.h"
# include "heap_utils.h"
# include <vector>

/**
 * 简易的索引类，目前仅支持 FLAT 索引类型
 * 提供插入向量和检索向量的功能
 */
class SimpleIndex {
public :
    SimpleIndex(FlatIndex* index) :  index(index) {}

    // 插入向量
    void insert_vectors(const std::vector<float>& data , uint64_t label) ;

    // 检索向量
    std::pair<std::vector<int64_t> , std::vector<float>> search_vectors(const std::vector<float>& query , int k) ; 
    
private :
    // 索引指针，指向 FLAT 索引
    FlatIndex* index ; 
} ; 