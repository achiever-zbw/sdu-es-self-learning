# include "heap_utils.h"
# include <vector>
# include "distance_utils.h"
# include "flat_index.h"

/**
 * 遍历所有向量，计算与 query 的距离，维护 Top-K 最小距离
 * @details 利用大顶堆，元素不满 k 个时直接插入，满 k 个时，只有当当前距离小于堆顶距离时，才插入
 * @param query 查询向量
 */
void HeapIndex::push(const float* query) {
    for (int i = 0 ; i < flat_index->getNumsData() ; i ++ ) {
        float distance = dist_calculator->dist_l2(query , flat_index->getAllVectors().data() + i * flat_index->getDim() , flat_index->getDim()) ; 
        if(heap_.size() < k_) {
            // 不满 k 个直接插入
            heap_.push({distance , i}) ; 
        } else {
            if(distance < heap_.top().distance) {
                // 比堆顶要小，就插入
                heap_.pop() ; heap_.push({distance , i}) ; 
            }
        }
    }
}

// 获取 Top-K 向量  
std::vector<HeapIndex::HeapNode> HeapIndex::getTopKVector() {
    std::vector<HeapNode> top_k(k_) ;
    while(!heap_.empty()) {
        top_k[-- k_] = heap_.top() ; heap_.pop() ; 
    } 

    return top_k ; 
}