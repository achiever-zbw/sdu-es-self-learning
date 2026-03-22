/**
 * 面向对象程序设计 04 数组、指针与字符串
 * 1. 声明一个有 5 个元素的 int 型数组，在程序中提示用户输入元素值，最后再在屏幕上显示出来。
 * 2. 声明一个 int 型变量 a，一个 int 型指针 p，一个引用 r，通过 p 把 a 的值改为 10，
 * 通过 r 把 a 的值改为 5。
 */

# include <iostream>
using namespace std ;

int num[5] ; 


int main()
{
    // test1 
    cout << "请输入5个整数 : "  ; 
    for(int i = 0 ; i < 5 ; i ++ ) cin >> num[i] ; 

    cout << "您输入的数字为 : " ;
    for(int i = 0 ; i < 5 ; i ++ ) cout << num[i] << ' ' ; 

    // test2    
    int a = 0 ; 
    int  *p ; 
    int &r = a ; 
    // 把 a 的地址取出来给指针 p
    p = &a ; 
    *p = 10 ; 
    cout << "通过指针 p 修改后，a 的值为 : " << a << endl ; 

    r = 5 ; 
    cout << "通过引用 r 修改后，a 的值为 : " << a << endl ; 
}