/**
 * 面向对象程序设计 03 数据的共享与保护 03
 *  定义类 X、Y、Z，函数 h(X*)，满足：类 X 有私有成员 i，Y 的成员函数 g(X*) 是 X 的友元函数，
 * 实现对 X 的成员 i 加 1；类 Z 是类 X 的友元类，其成员函数 f(X*) 实现对 X 的成员 i 加 5；
 * 函数 h(X*) 是 X 的友元函数，实现对 X 的成员 i 加 10。
 * 在一个文件中定义和实现类，在另一个文件中实现 main() 函数。
 */

# include <iostream>
# include "a.h"

using namespace std ;

int main() 
{
    // 构造对象
    X x(0) ; 
    Y y ; 
    Z z ;

    x.showInfo() ; 

    y.g(&x) ; 
    x.showInfo() ; 

    z.f(&x) ; 
    x.showInfo() ; 

    h(&x) ; 
    x.showInfo() ;

    return 0 ; 
}
