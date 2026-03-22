# pragma once
# include <vector>
# include "flat_index.h"
# include <cmath>

/**
 * 距离计算器类，用于计算两个向量的距离
 */
class DistCalculator {
public :
    float dist_l2(const float* vec1 , const float* vec2 , int dim) ;

} ; 