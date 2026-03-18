"""
数值分析与编程 02 插值法 02 牛顿插值多项式
本试验构造简单场景模拟牛顿插值多项式 Pn(x)

x      0.2    0.4    0.6    0.8    1.0
f(x)   0.98   0.92   0.81   0.64   0.38

试用 4 次牛顿插值多项式对数据进行插值，并画出图像
"""

import sympy as sp
import matplotlib.pyplot as plt
import numpy as np

# 构建 x y 序列
x = [0.2, 0.4, 0.6, 0.8, 1.0]
y = [0.98 , 0.92, 0.81, 0.64, 0.38]

# 定义符号变量
X = sp.symbols("X")

# 构建差商表
def diff_table(x, y):
    """
    table[i , j] = f[xj , xj+1 , ... , xj+i] 第 i 阶差商
    """
    n = len(x)
    # 初始化 table 为 n * n 大小
    table = [[0 for _ in range(n)] for _ in range(n)]

    # 先填充第一列
    for j in range(n):
        table[0][j] = y[j]

    for i in range(1, n):
        for j in range(n - i):
            # 通过递推实现
            # f[xj , xj+1 , ... , xj+i] = (f[xj+1 , xj+2 , ... , xj+i] - f[xj , xj+1 , ... , xj+i-1]) / (x[j+i] - x[j])
            table[i][j] = (table[i-1][j+1] - table[i-1][j]) / (x[j+i] - x[j])
    return table

# 使用递推构建牛顿插值多项式 Pn(x)
def newton_interpolation(n , table) :
    """
    Pn(x) = Pn -1(x) + f[x0 , x1 , ... , xn] * (x - x0) * (x - x1) * ... * (x - xn - 1)
    可以发现有明显的递推性质
    """
    if n == 0 :
        return table[0][0]
    else :
        num = 1
        for i in range(0 , n) :
            num *= (X - x[i])
        return newton_interpolation(n - 1 , table) + table[n][0] * num

if __name__ == '__main__' :

    # 先构建差商表
    table = diff_table(x, y)

    P_n_x = newton_interpolation(4 , table)
    print(f"4 次牛顿插值多项式为 : {P_n_x}")
    # 带入 0.5 点
    ans = P_n_x.subs(X , 0.5)
    print(f"0.5 点的插值结果为 : {ans}")

    # 画出图像
    f = sp.lambdify(X , P_n_x , 'numpy')
    x_values = np.linspace(0.2 , 1.0 , 100)
    y_values = f(x_values)
    plt.plot(x_values , y_values)
    plt.scatter(x , y)
    plt.show()