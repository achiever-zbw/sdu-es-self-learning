/**
 * 面向对象程序设计 05 类的继承与多态
 * 定义一个哺乳动物类 Mammal，再由此派生出狗类 Dog，定义一个 Dog 类的对象，
 * 观察基类与派生类的构造函数与析构函数的调用顺序。
 */

#include <iostream>
using namespace std ;

class Mammal {
    public :
        Mammal() {
            cout << "基类构造函数执行" << endl ; 
        }
        ~Mammal() {
            cout << "基类析构函数执行" << endl ; 
        }
    } ; 
    
    // 继承 Mammal
    class Dog : public Mammal {
    public :
        Dog() {
            cout << "派生类构造函数执行" << endl ; 
        } 
        ~Dog() {
            cout << "派生类析构函数执行" << endl ; 
        }
    } ; 

int main()
{
    Dog d ; 

    return 0 ; 
}
