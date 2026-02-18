"""
计算思维 03 排序算法相关
1. 选择排序 -- 不稳定
2. 冒泡排序 -- 稳定
3. 插入排序 -- 稳定
"""

def select_sort(arr) -> list :
    """
    选择排序 ：每一轮在"未排序好的"序列中找到最小的，放到当前位置
    每一轮的结果： 排好一个最小的
    """
    n = len(arr)
    for i in range(0 , n) :
        index = i
        for j in range(i + 1 , n) :
            # 当前 i 是未排序好的第一个数
            if arr[j] < arr[index] :
                index = j   # 逐个更新最小值
        arr[i] , arr[index] = arr[index] , arr[i]
        # 每一轮输出一次结果方便观察
        print(arr)
    return arr

def bubble_sort_basic(arr) -> list :
    """
    冒泡排序 ：每一轮排好一个最大值，每一轮的过程中，不断的交换
    """
    n = len(arr)
    for i in range(0, n - 1) :
        for j in range(0 , n - 1 - i) :
            if arr[j] > arr[j + 1] :
                arr[j], arr[j + 1] = arr[j + 1], arr[j]     # 交换
        print(arr)

    return arr

def bubble_sort_better(arr) -> list :
    """
    优化的冒泡排序，如果其中一轮没有存在交换的情况，说明已经排序好，直接 break
    """
    n = len(arr)
    for i in range(0, n - 1) :
        check = True
        for j in range(0, n - 1 - i) :
            if arr[j] > arr[j + 1] :
                arr[j], arr[j + 1] = arr[j + 1], arr[j]
                check = False   # 发生了交换
        print(arr)
        if check : break
    return arr


def insert_sort(arr) -> list :
    """
    插入排序: 想象成 "摸扑克牌"，摸到一张牌，需要看看应该把他插入到哪里
    """
    n = len(arr)
    for i in range(1 , n) :
        end = i - 1
        tmp = arr[i]
        while end >= 0 :
            if tmp < arr[end] :     # 如果比前一个数字小，前一个数字就往后移动一个
                arr[end + 1] = arr[end]
                end -= 1
            else :
                break
        # 此时找到了正确的位置
        arr[end + 1] = tmp
        print(arr)
    return arr

def insert_sort_better(arr) -> list :
    """
    在插入排序的步骤中，涉及到在已经 "有序数组"中寻找合适位置的一个步骤
    在有序数组中找到某个位置 -- 经典的 "二分" 算法，所以可以把寻找的 O(n) 复杂度优化为 O(logn)
    """
    n = len(arr)
    for i in range(1 , n) :
        tmp = arr[i]
        # 每次从 0 ~ i - 1 找到合适的位置
        l = 0
        r = i - 1
        while l <= r :
            mid = (l + r) // 2
            if tmp < arr[mid] :
                r = mid - 1
            else :
                l = mid + 1
        first = i
        # 找到了位置，现在需要移动了
        while first > l :
            arr[first] = arr[first - 1]
            first -= 1
        # 把当前待插入元素放入最终位置
        arr[l] = tmp
        print(arr)
    return arr


if __name__ == '__main__':
    nums = [23 , 7 , 2 , 10 , 999 , 111, 21]
    sort_algorithms = {
        1 : {
            "name" : "选择排序" ,
            "func" : select_sort,
        } ,
        2 : {
            "name" : "冒泡排序 朴素版" ,
            "func" : bubble_sort_basic ,
        },
        3: {
            "name": "冒泡排序 优化版",
            "func": bubble_sort_better,
        } ,
        4: {
            "name": "插入排序 朴素版",
            "func": insert_sort,
        } ,
        5: {
            "name": "插入排序 优化版",
            "func": insert_sort_better,
        }
    }

    option = 3
    print(sort_algorithms[option]["name"])
    sort_algorithm = sort_algorithms[option]
    result = sort_algorithm["func"](list(nums))
    print("最终结果:", result)
