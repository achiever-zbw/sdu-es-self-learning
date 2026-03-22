# pragma once
# include <iostream>
# include <vector>
# include <unordered_map>

/**
 * 自己手搓的扁平索引类，支持插入和搜索向量
 * 支持的距离类型：
 * - L2：欧氏距离
 */
class FlatIndex {
public :    
    // 构造函数
    FlatIndex(int dim_) : dim(dim_) , nums_data(0) {}

    // 插入 n 个向量数据，带 id，用户自定义
    void add_with_ids(int n , const float* vectors , const int64_t* ids) ; 

    // 搜索 k 个最近邻
    void search(int nums_query , const float* querys , int k , float* distances ,int64_t* labels) const ;  

    // 获取维度
    int getDim() const {
        return dim ; 
    }

    // 获取向量总数
    int getNumsData() const {
        return nums_data ; 
    }

    // 获取所有向量数据
    const std::vector<float>& getAllVectors() const {
        return data_all ; 
    }

private :
    int dim ;       // 维度
    int nums_data ; // 存储的向量总数
    std::vector<float> data_all ; // 存储的所有向量数据
    std::unordered_map<int64_t , int> id_mp ; // 自定义id -> 向量 id 的映射
    std::vector<int64_t> ids_ ; // 存储每个向量的自定义 id
} ; 