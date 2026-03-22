#!/bin/bash

# 向量数据库 - 插入向量示例

SERVER_URL="http://localhost:8080/insert"

echo "向量数据库 - 插入向量示例"
echo "=================================================="

# 示例1: 插入向量
echo -e "\n示例1: 插入向量 [0.88]"
curl -X POST "${SERVER_URL}" \
  -H "Content-Type: application/json" \
  -d '{
    "vectors": [0.88],
    "id": 1,
    "indexType": "FLAT"
  }'

echo -e "\n\n---"

# 示例2: 插入向量 [0.99]
echo -e "\n示例2: 插入向量 [0.99]"
curl -X POST "${SERVER_URL}" \
  -H "Content-Type: application/json" \
  -d '{
    "vectors": [0.99],
    "id": 2,
    "indexType": "FLAT"
  }'

echo -e "\n\n---"

# 示例3: 插入向量 [1.01]
echo -e "\n示例3: 插入向量 [1.01]"
curl -X POST "${SERVER_URL}" \
  -H "Content-Type: application/json" \
  -d '{
    "vectors": [1.01],
    "id": 3,
    "indexType": "FLAT"
  }'

echo -e "\n\n---"

# 示例4: 插入高维向量 (128维)
echo -e "\n示例4: 插入高维向量 (128维)"
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
    \"id\": 1001,
    \"indexType\": \"FLAT\"
  }"

echo -e "\n\n---"

# 示例5: 插入相似向量组
echo -e "\n示例5: 插入相似向量组"

for i in {1..5}; do
  # 基础向量 + 小幅扰动
  BASE="[1.0, 2.0, 3.0]"
  if [ $i -gt 1 ]; then
    VARIATION=$(python3 -c "
import json
import random
base = [1.0, 2.0, 3.0]
for j in range(len(base)):
    base[j] += random.uniform(-0.1, 0.1)
base = [round(x, 4) for x in base]
print(json.dumps(base))
")
  else
    VARIATION="$BASE"
  fi

  curl -X POST "${SERVER_URL}" \
    -H "Content-Type: application/json" \
    -d "{
      \"vectors\": ${VARIATION},
      \"id\": $((2000 + i)),
      \"indexType\": \"FLAT\"
    }"

  echo -e "\n"
done

echo -e "\n插入示例完成！"