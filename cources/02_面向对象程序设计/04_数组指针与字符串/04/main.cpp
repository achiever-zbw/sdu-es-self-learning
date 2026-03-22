/**
 * 面向对象程序设计 04 数组、指针与字符串
 * 编写函数 void reverse(string &s)，用递归算法使字符串 s 倒序。
 */

# include <iostream>
# include <cstring>
using namespace std ;

void reverse(string &s) {
    if(s.size() == 1) return ; 
    char first = s[0] ; 
    s = s.substr(1) ; // 删除第一个字符
    reverse(s) ;       // 递归处理剩下的
    s += first ;      // 再把第一个字母加到后面
}

int main()
{
    string s = "Hello world" ; 
    reverse(s) ; 
    cout << "字符串反转后为 : " << s << endl ;

    return 0 ; 
}