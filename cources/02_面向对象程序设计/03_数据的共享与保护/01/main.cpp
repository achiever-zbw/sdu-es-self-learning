/**
 * 面向对象程序设计 03 数据的共享与保护 01 全局变量
 * 1、在一个文件中定义一个全局变量 n，主函数 main()，在另一个文件中定义函数 fn1()，在 main() 中对 n 赋值，
 * 再调用 fn1()，在 fn1() 中也对 n 赋值，显示 n 最后的值。

 在 main 中需要使用外部函数 fn1() , 在 a.cpp 中需要使用外部变量，需要声明
 最后，需要使用 " g++ main.cpp a.cpp -o main " 一起编译两个文件，不能只运行 main.cpp 一个文件，否则
 */

# include <iostream>
using namespace std ;

// 定义全局变量
int n ; 

// 声明外部函数
void fn1() ;

int main()
{   
    // 1. 在 main() 中对 n 赋值
    n = 10 ; 
    // 2. 调用 fn1()
    fn1();
    // 3. 显示 n 最后的值
    cout << "n 最后的值: " << n << endl;
}