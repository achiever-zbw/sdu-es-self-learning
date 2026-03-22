# pragma once
# include <vector>
# include <iostream>
# include <cmath>
# include <queue>
# include <vector>
# include "distance_utils.h"
# include "flat_index.h"

/**
 * 大顶堆，维护 Top-K 最小距离
 * 用于检索时，维护 Top-K 个最小距离的向量索引
 */
class HeapIndex {
public : 
    struct HeapNode {
            float distance ;  // 距离值
            int index ; // 逻辑索引
            // 实现大顶堆
            bool operator<(const HeapIndex::HeapNode& h) const {
                return distance < h.distance ; 
            }
        } ; 

    HeapIndex(int k, FlatIndex* index, DistCalculator* calculator) : k_(k), flat_index(index), dist_calculator(calculator) {} 

    // 插入堆操作
    void push(const float* query) ; 
    
    // 获取 Top-K 向量
    std::vector<HeapNode> getTopKVector() ; 
private :
    
    std::priority_queue<HeapNode> heap_ ;  // 大顶堆
    int k_ ; // 保留 k 个最小值
    FlatIndex* flat_index ; 
    DistCalculator* dist_calculator ;  // 距离计算器
} ; 