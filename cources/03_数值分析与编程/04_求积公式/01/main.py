"""
数值分析与编程 04 求积公式 01 


确定下列求积公式中的待定参数，使其代数精度尽量高，并指明所构造出的求积公式所具有的代数精度

求积公式：
∫(-h to h) f(x) dx ≈ A_-1 * f(-h) + A_0 * f(0) + A_1 * f(h)

其中，A_-1, A_0, A_1 是待定参数

我们需要确定 A_-1, A_0, A_1 的值，使得求积公式具有尽量高的代数精度

代数精度是指：
当 f(x) 为多项式时, 求积公式精确成立的最大次数
"""

import sympy as sp
import numpy as np
import matplotlib.pyplot as plt

def composite_trapezoidal(f , a , b , n):
    """
    复合梯形公式
    f: 被积函数
    a: 积分下限
    b: 积分上限
    n: 分割数
    return: 积分值
    """
    h = (b - a) / n     # 计算步长
    x = np.linspace(a , b , n + 1)
    sum = 0     
    # 公式 : h/2 * (f(a) + 2 * sum(f(x[i])) + f(b))
    sum += f(a) + f(b)
    for i in range(1 , n):
        sum += 2 * f(x[i])
    return sum * h / 2

# 定义符号变量
h = sp.Symbol('h' , positive=True)
A_neg1 , A_0 , A_1 = sp.symbols('A_neg1 , A_0 , A_1')

def left(k):
    """ 左端点积分公式 """
    x = sp.Symbol('x')
    if k == 0:
        return 2 * h
    return sp.integrate(x**k , (x , -h , h))

def right(k):
    """ 右端点积分公式 """
    x = sp.Symbol('x')
    if k == 0:
        return A_neg1 + A_0 + A_1
    return A_neg1 * (-h)**k + A_0 * 0**k + A_1 * h**k


if __name__ == '__main__':
    eqs = []
    for k in range(3):
        eq = sp.Eq(left(k) , right(k))
        eqs.append(eq)

    solutions = sp.solve(eqs , [A_neg1 , A_0 , A_1])
    print("求解得到的参数为 : ")
    print(solutions)

    for var , value in solutions.items():
        # 优雅的输出一下
        print(f"{var} = {sp.simplify(value)}")\

    A_neg1_val = solutions[A_neg1]
    A_0_val = solutions[A_0]
    A_1_val = solutions[A_1]

    print("\n检验更高次幂的精确性：")
    max_degree = 0
    for k in range(3, 10):
        L = left(k)
        R = right(k)
        R_subs = R.subs({A_neg1: A_neg1_val, A_0: A_0_val, A_1: A_1_val})
        diff = sp.simplify(L - R_subs)
        if diff == 0:
            print(f"k = {k}: 精确成立")
            max_degree = k
        else:
            print(f"k = {k}: 不成立，误差为 {diff}")
            break
    
    print(f"检验得到，最终代数精度为 ： {max_degree}")