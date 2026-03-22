# include "distance_utils.h"
# include <iostream>
# include <cmath>
# include <vector>

/**
 * 计算两个向量的 L2 距离，用于进行 Top-K 搜索
 * @param vec1 第一个向量地址
 * @param vec2 第二个向量地址
 * @param dim 维度
 */
float DistCalculator::dist_l2(const float* vec1 , const float* vec2 , int dim) {
    float dist = 0.0 ; 

    for(int i = 0 ; i < dim ; i ++ ) {
        float diff = vec1[i] - vec2[i] ; 
        dist += diff * diff ; 
    }

    return dist ; 
}