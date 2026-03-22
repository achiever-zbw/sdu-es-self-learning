#!/bin/bash

# 向量数据库 - 搜索向量示例

SERVER_URL="http://localhost:8080/search"

echo "向量数据库 - 搜索向量示例"
echo "=================================================="

# 示例1: 搜索向量
echo -e "\n示例1: 搜索向量 [0.91]"
curl -X POST "${SERVER_URL}" \
  -H "Content-Type: application/json" \
  -d '{
    "vectors": [0.91],
    "k": 2,
    "indexType": "FLAT"
  }'

echo -e "\n\n---"

# 示例2: 搜索相似向量
echo -e "\n示例2: 搜索相似向量 [1.0, 2.0, 3.0]"
curl -X POST "${SERVER_URL}" \
  -H "Content-Type: application/json" \
  -d '{
    "vectors": [1.0, 2.0, 3.0],
    "k": 5,
    "indexType": "FLAT"
  }'

echo -e "\n\n---"

# 示例3: 搜索不同向量
echo -e "\n示例3: 搜索不同向量 [0.5, 1.5, 2.5]"
curl -X POST "${SERVER_URL}" \
  -H "Content-Type: application/json" \
  -d '{
    "vectors": [0.5, 1.5, 2.5],
    "k": 3,
    "indexType": "FLAT"
  }'

echo -e "\n\n---"

# 示例4: 搜索高维向量
echo -e "\n示例4: 搜索高维向量 (128维)"
VECTOR128=$(python3 -c "
import json
import random
vectors = [round(random.random(), 4) for _ in range(128)]
print(json.dumps(vectors))
")

curl -X POST "${SERVER_URL}" \
  -H "Content-Type: application/json" \
  -d "{
    \"vectors\": ${VECTOR128},
    \"k\": 10,
    \"indexType\": \"FLAT\"
  }"

echo -e "\n\n---"

# 示例5: 搜索并返回更多结果
echo -e "\n示例5: 搜索并返回更多结果 [1.05, 2.05, 3.05]"
curl -X POST "${SERVER_URL}" \
  -H "Content-Type: application/json" \
  -d '{
    "vectors": [1.05, 2.05, 3.05],
    "k": 10,
    "indexType": "FLAT"
  }'

echo -e "\n\n---"

