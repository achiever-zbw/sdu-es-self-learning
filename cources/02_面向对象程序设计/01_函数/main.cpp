/**
 * 面向对象程序设计 01 函数
 * 1、定义一个计算阶乘的函数并在 main() 中调用使用；
 * 2、定义一个内联函数实现两个数的最大值比较并测试；
 * 3、编写一个带有缺省形参值的函数，输出学生信息（如姓名、年龄、性别）；
 * 4、编写函数重载实现两个整数相加、两个浮点数相加和两个字符串相加；
 * 5、使用 C++ 系统函数 sqrt 和 pow 计算给定数的平方根和幂。

 */


# include <iostream>
# include <cmath>
# include <string>
# define ll long long
# define db double
using namespace std ;

ll factorial(ll n) {
    // 定义阶乘的递归函数
    if(n == 1 || n == 0) return 1;
    return n * factorial(n - 1);
}

inline db maxNum(db a, db b) {
    return a > b ? a : b;
}

void showInfo(string name = "张三", int age = 18, string gender = "男")  {
    cout << "姓名: " << name << endl;
    cout << "年龄: " << age << endl;
    cout << "性别: " << gender << endl;
}

// 定义整数相加方法
int add(int a , int b) {
    return a + b ; 
}

// 定义浮点数相加方法
db add(db a , db b) {
    return a + b ; 
}

// 定义字符串相加方法
string add(string a , string b) {
    // 字符串相加，返回两个字符串的拼接
    return a + b ; 
}


int main()
{
    // test1 
    ll n = 5 ; 
    cout << "5! = " << factorial(n) << endl;

    // test2
    db a = 3.5 , b = 4.5 ; 
    cout << "max(3.5, 4.5) = " << maxNum(a, b) << endl;

    // test3
    showInfo(); // 缺少形参，使用默认值
    showInfo("李四", 20, "女"); // 有形参，使用形参

    // test4
    cout << "1 + 2 = " << add(1, 2) << endl;
    cout << "1.5 + 2.5 = " << add(1.5, 2.5) << endl;
    cout << "hello + world = " << add("hello", "world") << endl;

    // test5
    db x = 2.5 ; 
    cout << "sqrt(2.5) = " << sqrt(x) << endl;
    cout << "pow(2.5, 2) = " << pow(x, 2) << endl;
}