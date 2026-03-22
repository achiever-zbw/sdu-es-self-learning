/**
 * 面向对象程序设计 03 数据的共享与保护 02 静态变量
 * 1.在函数 fn1() 中定义一个静态变量 n，fn1() 中对 n 的值加 1，
 * 在主函数中，调用 fn1() 10 次，显示 n 的值。
 */

# include <iostream>
using namespace std ;

void fn1() {
    // 定义静态变量
    static int n = 0 ; 
    n += 1 ; 
    cout << "fn1() 调用时 n = " << n << endl;
}

int main()
{
    for(int i = 1 ; i <= 10 ; i ++  ){
        fn1() ; 
    }
    return 0 ; 
}