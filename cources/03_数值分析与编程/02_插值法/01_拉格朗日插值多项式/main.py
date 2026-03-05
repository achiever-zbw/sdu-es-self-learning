"""
数值分析与编程 02 插值法 01 拉格朗日插值多项式

本实验构造简单的场景来构造插值多项式 Ln(x) 函数，来模拟拉格朗日插值

场景：测量气温变化

_______________________________________
时间        8          12           16
温度        18         24           22
_______________________________________

求上午10点的气温是多少
"""

import sympy as sp

# 构造 x y 序列
x = [8 , 12 , 16]
y = [18 , 24 , 22]

X = sp.symbols("X")
n = len(x)

# 1. 构造插值基函数 l_i(x)
def lix( k ) :
    l_i_x = 1 
    for i in range(n) : 
        if i != k :
            l_i_x *= ((X - x[i]) / (x[k] - x[i]))
    return l_i_x

# 2. 计算 Ln(x)
def Lnx() : 
    L_n_x = 0 
    for i in range(n) : 
        L_n_x += (lix(i) * y[i])

    return L_n_x

if __name__ == '__main__' : 
    L_n_x = Lnx()
    print(f"拉格朗日插值多项式为 : {L_n_x}")
    # 带入 10 点
    ans = L_n_x.subs(X , 10)
    print(f"10 点的气温模拟为 : {ans}")