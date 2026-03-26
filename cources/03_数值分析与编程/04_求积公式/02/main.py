"""
数值分析与编程 04 求积公式 02


确定下列求积公式中的待定参数，使其代数精度尽量高，并指明所构造出的求积公式所具有的代数精度

求积公式：
∫(-1 to 1) f(x) dx ≈ [f(-1) + 2* f(x_1) + 3 * f(x_2)] / 3

其中，x_1, x_2 是待定参数

我们需要确定 x_1, x_2 的值，使得求积公式具有尽量高的代数精度
"""

import sympy as sp

# 定义符号变量
x1, x2 = sp.symbols('x1 x2')

def left(k):
    """ ∫_{-1}^{1} x^k dx """
    if k == 0:
        return 2
    x = sp.Symbol('x')
    return sp.integrate(x**k, (x, -1, 1))

def right(k):
    """ [f(-1) + 2f(x1) + 3f(x2)]/3 """
    if k == 0:
        return (1 + 2 + 3) / 3  # = 2
    else:
        return (1 * ((-1)**k) + 2 * (x1**k) + 3 * (x2**k)) / 3

# 建立方程：对 k = 0,1,2 要求精确成立
print("建立方程：")
eqs = []
for k in range(3):
    eq = sp.Eq(left(k), right(k))
    eqs.append(eq)
    print(f"k = {k}: {left(k)} = {right(k)}")

# 求解参数
print("\n求解参数...")
sol = sp.solve(eqs, (x1, x2))
print("解：")
for s in sol:
    print(f"x1 = {sp.simplify(s[0])}, x2 = {sp.simplify(s[1])}")

# 检验每个解
for idx, (x1_val, x2_val) in enumerate(sol):
    print(f"\n{'='*50}")
    print(f"检验解 {idx+1}: x1 = {x1_val}, x2 = {x2_val}")
    
    # 检验更高次幂
    max_degree = 2  # 至少为2
    for k in range(3, 8):
        L = left(k)
        R = right(k)
        # 代入解
        R_val = R.subs({x1: x1_val, x2: x2_val})
        diff = sp.simplify(L - R_val)
        
        if diff == 0:
            print(f"k = {k}: 精确成立")
            max_degree = k
        else:
            print(f"k = {k}: 不成立，误差 = {diff}")
            break
    
    print(f"代数精度 = {max_degree}")

# 数值验证
print("\n" + "="*50)
print("数值验证：")
x1_num = float(sol[0][0])
x2_num = float(sol[0][1])
print(f"x1 ≈ {x1_num:.6f}, x2 ≈ {x2_num:.6f}")

# 定义测试函数
def test_func(x):
    return x**4  # 4次多项式测试

def exact_int():
    return 2 / 5  # ∫_{-1}^{1} x^4 dx

def approx_int(f):
    return (f(-1) + 2*f(x1_num) + 3*f(x2_num)) / 3

print(f"精确积分值: {exact_int():.6f}")
print(f"求积公式近似: {approx_int(test_func):.6f}")
print(f"误差: {abs(approx_int(test_func) - exact_int()):.2e}")