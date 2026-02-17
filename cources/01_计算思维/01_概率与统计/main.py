"""
计算思维 01 概率与统计相关
1. 随机模拟（蒙特卡洛方法）: 模拟抛硬币实验
2. 概率分布: 二项分布的计算与应用
3. 组合数学: 排列与组合的计算
"""

import random
import matplotlib.pyplot as plt


# 模拟抛硬币实验
def coin_flip_simulation(n) :
    """
    模拟抛硬币实验
    :param n: 抛硬币的次数
    :return: 正面频率与反面频率
    """
    heads = 0   # 正面次数
    tails = 0   # 反面次数

    for i in range(n) :
        option = random.randint(0 , 1)
        if option == 0 :
            heads += 1
        else :
            tails += 1
    return heads / n , tails / n

def verify_law_of_large_numbers() :
    """
    验证大数定律，在试验次数增大的情况下，频率趋近于概率(0.5)
    """
    n = 50
    frequencies = []
    trials_list = []
    while n <= 50000 :
        freq_head , _ = coin_flip_simulation(n)    # 得到正面向上的频率
        frequencies.append(freq_head)
        trials_list.append(n)
        n += 50

    # 绘制频率变化曲线
    plt.figure(figsize=(10, 6))
    plt.plot(trials_list, frequencies, label='正面频率')
    plt.axhline(y = 0.5, color = 'r', linestyle = '--', label = '理论概率 (0.5)')
    plt.title('抛硬币实验：频率随次数的变化（验证大数定律）')
    plt.xlabel('实验次数')
    plt.ylabel('正面频率')
    plt.legend()
    plt.grid(True)
    plt.show()

# 二项分布

# 对于二项分布，首先要完成组合数学公式
def factorial(n) :
    """阶乘，递归实现"""
    if n == 1 or n == 0 :
        return 1
    return n * factorial(n - 1)

def combination(n , m):
    """ C(n m ) = n! / (m! * (n - m)! )"""
    return factorial(n) / (factorial(m) * factorial(n - m))

def binomial_distribution_demo(k_):
    """
    二项分布实例
    假设连续投掷一枚硬币 60 次，计算恰好 k 次正面的概率
    """
    n_trails = 60
    p = 0.5
    ans = combination(n_trails, k_) * (p ** k_) * ((1 - p) ** (n_trails - k_))

    # 绘制二项分布视图
    x_values = list(range(1 , 61))  # 60 个样本点
    pmf_values = [combination(n_trails , x) * (p**x) * ((1 - p)**(n_trails - x)) for x in x_values]
    plt.figure(figsize=(10, 4))
    plt.stem(x_values, pmf_values)
    plt.title("Binomial distribution")
    plt.show()
    return ans


if __name__ == '__main__':
    # 1. 运行抛硬币
    verify_law_of_large_numbers()
    # 2. 二项分布
    k = 30
    print(f"模拟60次抛硬币，恰好 {k} 次正面向上的概率为 : {binomial_distribution_demo(k)}")