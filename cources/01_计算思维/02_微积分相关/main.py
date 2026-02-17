"""
计算思维 02 微积分相关
1. Sympy 库的使用
2. 微分计算：一阶导数与二阶导数
3. 积分计算：不定积分与定积分的实现
4. 方程求解：求解代数方程
"""
import sympy as sp
import matplotlib.pyplot as plt

# 微分求导运算
def basic_diff_demo() :
    """
    演示简单的求导运算，定义函数与符号
    :return:
    """
    # 1. 定义符号变量
    x = sp.Symbol('x')
    # 2. 定义函数表达式 f(x) = x^3 + 2x^2 + 5
    func = x**3 + 2*x**2 + 5
    print(f"原函数为 : y = {func}")
    # 3. 求一阶导数
    first_diff = sp.diff(func, x , 1)
    print(f"一阶导数 : y' = {first_diff}")

    # 4. 求二阶导数
    second_diff = sp.diff(func, x , 2)
    print(f"二阶导数 : y'' = {second_diff}")

    # 5. 带入数值运算
    x0 = 2
    value = first_diff.subs(x, x0)
    print(f"在 x = {x0} 处的一阶导数值为 : {value}")

# 积分运算，定积分与不定积分
def basic_integrate_demo() :
    """
    演示简单的积分运算
    :return:
    """
    x = sp.Symbol('x')
    # 构造简单的方程 f(x) = x^2
    func = x**2
    print(f"原函数为 : y = {func}")
    indefinite_integrate = sp.integrate(func, x)   # 不定积分，对 x 进行积分
    print(f"不定积分为 : {indefinite_integrate} + C")  # 记得 + C

    # 定积分，integrate(函数, (变量， 下限 ， 上限))
    lower_limit = 0
    upper_limit = 3
    definite_integrate = sp.integrate(func, (x, lower_limit, upper_limit))
    print(f"在区间 [{lower_limit} ~ {upper_limit}] 之间，定积分为 : {definite_integrate}")

# 方程求解
def equation_solve() :
    """
    演示简单的方程求解
    :return:
    """
    x = sp.Symbol('x')
    # 1. 一元二次方程  x^2 + 5x + 6 = 0
    func1 = x**2 + 5*x + 6
    answer1 = sp.solve(func1, x)
    print(f"求解方程 : {func1} = 0 , 答案为 : {answer1}")

    # 2. 求解带有参数的方程， ax^2 + bx + c = 0
    a, b, c = sp.symbols('a, b, c')
    func2 = a*x**2 + b*x + c
    answer2 = sp.solve(func2, x)    # 关于 x 求解
    print(f"求解方程 : {func2} = 0 , 答案为 : {answer2}")

# limit 极限的应用
def limit_demo() :
    """
    演示 Limit 极限的运算 # 求数列极限 (1+1/n)**n n-->oo
    :return:
    """
    import numpy as np
    n = sp.Symbol('n')
    func = (1 + 1 / n) ** n
    limit_ans = sp.limit(func, n , 'oo') # n 趋近于 +OO
    print("%s 数列的极限值为 %s" % (str(func), str(limit_ans)))  # 注意是以字符串形式表达的

    # 可视化展示
    n = np.arange(1 , 100 , 1)  # 设置 n 个取样点，1~100, 间距为 1
    # 注意，这里的 n 和上面的 n 是不同的，上面的 n 是符号变量，下面的 n 是数组, 这也就是不能直接用上面 func 的原因
    func = (1 + 1 / n) ** n
    plt.figure(figsize=(10, 5))
    plt.title('y = (1+1/n)**n')
    plt.scatter(n, func)  # 散点图
    plt.axis('on')
    plt.axhline(float(np.e), color='red', linestyle='--', label='y=e')
    plt.show()



if __name__ == "__main__":
    print("=== 微积分相关教学示例 ===")
    basic_diff_demo()
    print()
    basic_integrate_demo()
    print()
    equation_solve()
    print()
    limit_demo()
