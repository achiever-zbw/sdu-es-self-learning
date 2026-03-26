"""
数值分析与编程 03 最小二乘法

实验数据如下：
----------------------------------
x_i  19     25     31     38     44
y_i  19.0   32.3   49.2   73.3   97.8
----------------------------------

试用最小二乘法拟合 y = a + bx^2 的经验公式

目标是找到 a 和 b 使得误差平方和 ∑(y_i - (a + bx_i^2))^2 最小
"""

import numpy as np  
import matplotlib.pyplot as plt

# 原始数据
x = np.array([19, 25, 31, 38, 44])
y = np.array([19.0, 32.3, 49.2, 73.3, 97.8])

# 计算所需统计量
n = len(x)
Sx = np.sum(x**2)       # Σ x_i^2
Sx2 = np.sum(x**4)      # Σ x_i^4
Sy = np.sum(y)          # Σ y_i
Sxy = np.sum((x**2) * y) # Σ x_i^2 y_i

# 解正规方程
denom = n * Sx2 - Sx * Sx

a = (Sy * Sx2 - Sx * Sxy) / denom
b = (n * Sxy - Sx * Sy) / denom

print("拟合结果为 : ")
print(f"a = {a:.6f}")
print(f"b = {b:.8f}")
print(f"经验公式: y = {a:.6f} + {b:.8f} * x²")

# 计算拟合值及误差平方和
y_fit = a + b * (x**2)
SSE = np.sum((y - y_fit)**2)
print(f"误差平方和 SSE = {SSE:.6f}")

plt.scatter(x, y, color='red', label='Original Data')
x_smooth = np.linspace(min(x), max(x), 200)
y_smooth = a + b * (x_smooth**2)
plt.plot(x_smooth, y_smooth, 'b-', label='Fitting Curve')
plt.xlabel('x')
plt.ylabel('y')
plt.legend()
plt.grid(True)
plt.title('Least Squares Fitting y = a + b x²')
plt.show()