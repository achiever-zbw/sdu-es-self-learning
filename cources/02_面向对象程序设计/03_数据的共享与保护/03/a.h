# ifndef CLASS_H
# define CLASS_H

# include <iostream>
# include <iomanip>
# include <cstring>

using namespace std ;

// 类的定义
class X ;

class Y {
public :
    void g(X* p) ;
} ; 

class Z {
public : 
    void f(X* p) ;
} ; 

class X {
private :
    int i ; 
public : 
    // 构造函数
    X(int _i = 0) : i(_i) {} ; 
    // 友元：Y::g、h 为友元函数；Z 为友元类（Z 的成员可访问 X 的私有成员）
    friend void Y::g(X* p) ;
    friend class Z ;
    friend void h(X* p) ;

    void showInfo() ;
} ; 

// 函数声明
void h(X* p) {
    // 实现对 X 的成员 i 加 10
    p->i += 10 ; 
}

// 类的实现
void Z::f(X* p) {
    // 实现对 X 的成员 i 加 5
    p->i += 5 ; 
}

void Y::g(X* p) {
    // 实现对 X 的成员 i 加 1
    p->i ++ ;
}

void X::showInfo() {
    cout << "X 中的 i 值为 : " << i << endl ; 
}

# endif