/**
 * 面向对象程序设计 05 类的继承与多态
 * 定义一个基类 BaseClass，从它派生出类 DerivedClass，
 * BaseClass 有成员函数 fn1()、fn2()，DerivedClass 也有成员函数 fn1()、fn2()，
 * 在主函数中声明一个 DerivedClass 的对象，
 * 分别用 DerivedClass 的对象以及 BaseClass 和 DerivedClass 的指针来调用 fn1()、fn2()，
 * 观察运行结果。
 */

#include <iostream>
using namespace std ;

class BaseClass {
public : 
    BaseClass() {} 
    ~BaseClass() {}
    void fn1() {
        cout << "BaseClass 的 fn1 函数执行" << endl ; 
    }

    void fn2() {
        cout << "BaseClass 的 fn2 函数执行" << endl ; 
    }
private : 

} ; 


class DerivedClass : public BaseClass {
public :
    DerivedClass() {} 
    ~DerivedClass() {}
    void fn1() {
        cout << "DerivedClass 的 fn1 函数执行" << endl ; 
    }

    void fn2() {
        cout << "DerivedClass 的 fn2 函数执行" << endl ; 
    }
private :

} ; 


int main() {
    DerivedClass derivedObj;
    
    cout << "使用DerivedClass对象调用" << endl;
    derivedObj.fn1();  // 调用DerivedClass的fn1
    derivedObj.fn2();  // 调用DerivedClass的fn2
    
    cout << "\n使用BaseClass指针调用" << endl;
    BaseClass* basePtr = &derivedObj;
    basePtr->fn1();    // 调用BaseClass的fn1
    basePtr->fn2();    // 调用BaseClass的fn2
    
    cout << "\n使用DerivedClass指针调用" << endl;
    DerivedClass* derivedPtr = &derivedObj;
    derivedPtr->fn1(); // 调用DerivedClass的fn1
    derivedPtr->fn2(); // 调用DerivedClass的fn2
    
    return 0;
}