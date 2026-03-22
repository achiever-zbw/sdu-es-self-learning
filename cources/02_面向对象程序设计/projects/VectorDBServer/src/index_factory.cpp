# include "simple_index.h"
#include "index_factory.h"

/**
 * 这里 namespace 的用法是把创建的这个全局的索引工厂，限制在当前文件中，外部无法访问，但是可以通过 getGlobalIndexFactory() 函数获取到这个指针
 */
namespace {
    // 全局的索引工厂
    IndexFactory globalIndexFactory ; 
}

/**
 * 获取全局的索引工厂
 * @details 返回全局的索引工厂指针，用于初始化和获取索引
 * @return IndexFactory* 全局的索引工厂指针
 */
IndexFactory* getGlobalIndexFactory() {
    return &globalIndexFactory ; 
}

/**
 * 初始化索引
 * @details 根据索引类型，初始化不同的索引,并储存在 index_map 中，后续可以根据索引类型获取对应的索引
 * @param index_type 索引类型
 * @param dim 向量维度
 * @param metric_type 距离计算类型,默认 L2 距离
 */
void IndexFactory::init(IndexType index_type , int dim , MetricType metric_type) {
    switch (index_type) {
        case IndexFactory::IndexType::FLAT :  {
            // new 一个 FlatIndex 索引
            index_map[index_type] = new SimpleIndex(new FlatIndex(dim)) ; 
            break ; 
        }
        default  :
            break ; 
    }
}

/**
 * 获取索引
 * @details 根据索引类型，返回对应的索引指针
 * @param index_type 索引类型
 * @return void* 索引指针,如果索引不存在，返回 nullptr
 */
void* IndexFactory::getIndex (IndexType index_type) const {
    auto it = index_map.find(index_type) ; 
    if(it != index_map.end()) {
        return it->second ; 
    }
    // 找不到，返回空指针 nullptr
    return nullptr ; 
}