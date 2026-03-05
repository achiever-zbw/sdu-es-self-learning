"""
数值分析与编程 01 数值计算的误差分析 02 关于秦九韶算法对计算的优化

举例运算 : 5x^3 + 4x^2 + 3x + 2 秦九韶算法可节省运算时间

实验结果 ：
顺序计算的时间 :  0.7972075000016048
秦九韶优化后的时间 :  0.6297237080016203

在程序实际运行过程中，实际的机器指令如下 (以 ax*2 + bx + c 举例)
1. 将 x 取至运算器
2. 乘以 x 的到x^2 存于运算器
3. 再乘以 a 得到 ax^2 , 存于运算器
4. ax^2  送到存储器中
5. 取 b 到运算器
6. 乘以 x 得到 bx 存于运算器
7. 将 ax^2 从存储器中取出与 bx 相加，得到 ax^2 + bx ，存于运算器中
8. 取 c 与 ax^2 + bx 相加得到结果存于运算器

一共是 8 个步骤，若改为 (ax + b) * x + c 一共需要 5 步

在做实验时，尽可能将函数写的复杂些，并且设置的执行次数多一些，才能显著看到秦九韶算法的优势

"""

import timeit

def calculate_base(x : int) :
    """ 计算 5x^3 + 4x^2 + 3x + 2 """
    return 5 * x * x * x + 4 * x * x + 3 * x + 2

def calculate_better(x : int) :
    return x * (x * (5 * x + 4) + 3) + 2

# 分别计算基础计算和秦九韶算法的运行时间，这里为了体现的更加明显，计算 10000000 次
base_time = timeit.timeit(lambda : calculate_base(5), number=10000000)
better_time = timeit.timeit(lambda : calculate_better(5), number=10000000)

print("顺序计算的时间 : " , base_time)
print("秦九韶优化后的时间 : " , better_time)

