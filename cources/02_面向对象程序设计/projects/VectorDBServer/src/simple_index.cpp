# include "simple_index.h"
# include <vector>
# include <iostream>

// SimpleIndex::SimpleIndex(FlatIndex* index) :  index(index) {}

/**
 * 接受一个向量，目前仅接受一个，以及对应的label ， 强制类型转换为 index 接受的形式
 *          调用 FlatIndex 对象的 add_with_ids 实现向量的插入
 * @param data 插入的向量
 * @param label 自定义的标签
 */
void SimpleIndex::insert_vectors(const std::vector<float>& data , uint64_t label) {
    int64_t ids = static_cast<int64_t>(label) ; 

    index->add_with_ids(1 , data.data() , &ids) ; 
}

/**
 * 接受一个向量，目前仅接受一个，以及对应的label ， 强制类型转换为 index 接受的形式
 *          调用 FlatIndex 对象的 add_with_ids 实现向量的插入
 * @param query 查询的向量
 * @param k 返回的最近邻数量
 * @return std::pair<std::vector<int64_t> , std::vector<float>> 最近邻的 id 以及距离
 */
std::pair<std::vector<int64_t> , std::vector<float>> SimpleIndex::search_vectors(const std::vector<float>& query , int k) {
    int dim = index->getDim() ; // 获取维度
    int num_querys = query.size() / dim ; // 查询的向量中包含多少向量
    std::vector<int64_t> ids(num_querys * k) ; 
    std::vector<float> distances(num_querys * k) ; 

    index->search(num_querys , query.data() , k , distances.data() , ids.data()) ; 

    return {ids , distances} ; 
}
