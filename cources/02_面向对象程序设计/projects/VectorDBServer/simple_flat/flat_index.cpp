# include <iostream>
# include <vector>
# include <unordered_map>
# include "flat_index.h"
# include "distance_utils.h"
# include "heap_utils.h"

// 插入 n 个向量，
void FlatIndex::add_with_ids(int n , const float* vectors , const int64_t* ids) {
    // 存储 n 个向量数据
    for(int i = 0 ; i < n ; i ++ ) {
        for(int j = 0 ; j < dim ; j ++ ) {
            // 每个向量 dim 维度，有 dim 个数
            data_all.push_back(vectors[i * dim + j]) ; 
        }
        ids_.push_back(ids[i]) ; // 存储自定义 id
        nums_data ++ ; // 向量总数 + 1
    }
}

// 返回与待查询向量最近邻 k 个向量的信息
void FlatIndex::search(int nums_query , const float* querys , int k , float* distances ,int64_t* labels) const {
    DistCalculator calculator ; // 距离计算器
    for(int i = 0 ; i < nums_query ; i ++ ) {
        HeapIndex heap_index(k , const_cast<FlatIndex*>(this) , &calculator)  ; 
        // 获取当前要查询的向量
        const float* query = querys + i * dim ;  
        // push 进堆
        heap_index.push(query) ; 
        // 获取结果
        std::vector<HeapIndex::HeapNode> top_k = heap_index.getTopKVector() ; 

        // 把结果写进答案里
        for(int j = 0 ; j < k ; j ++ ) {
            distances[i * k + j] = top_k[j].distance ; 
            labels[i * k + j] = ids_[top_k[j].index] ; 
        }
    }
}