"""
数值分析与编程 01 数值计算的误差分析 01 验证相近数相减损失有效数字个数
a = 1 - cos(2°)

两个输出分别为： 
0.0006091729809042379
0.0006091729809042699

对于 cos(2°) ，与 1 相近，在计算 1 - cos(2°) 时，会损失有效数字个数
因此可以更换计算方式，1 - cos(2°) = 2 * sin(1°) ** 2 ，从而计算更加精确
"""

import math
import decimal


print("cos(2°) 的近似值为 : ", math.cos(math.radians(2)))

a = 1 - math.cos(math.radians(2))   # 得到计算机计算的近似值
print(a)

a = 2 * math.sin(math.radians(1)) ** 2
print(a)

