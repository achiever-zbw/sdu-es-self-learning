/**
 * 面向对象程序设计 04 数组、指针与字符串
 * 编写一个函数，统计一条英文句子中字母的个数，在主程序中实现输入输出。
 */

#include <iostream>
#include <string>

using namespace std;

/// 统计字符串中英文字母（A–Z / a–z）的个数
int countLetters(const string &s) {
    int cnt = 0;
    for (char x : s) {
        if ((x >= 'a' && x <= 'z') || (x >= 'A' && x <= 'Z')) {
            cnt++;
        }
    }
    return cnt;
}

int main() {
    string s;
    cout << "请输入一个英文句子 : " << endl;
    getline(cin, s);

    int cnt = countLetters(s);
    cout << "英文句子中字母的个数为 : " << cnt << " 个" << endl;

    return 0;
}
