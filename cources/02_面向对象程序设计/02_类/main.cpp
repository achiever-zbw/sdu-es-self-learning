/**
 * 面向对象程序设计 02 类
 * 1、定义一个 Book 类，编写构造函数和析构函数并在 main() 中创建与销毁对象。
 * 2、定义 Student 类并组合 Book 类，使用前向引用解决依赖问题并在 main() 中演示借书。
 * 3、定义 struct Person 和 union Data，用 sizeof 比较结构体与联合体的内存占用。
 * 4、定义 enum Weekday 并编写函数输出一周七天的名称。

对于虚构函数，在这个文件中由于把所有的功能要求放在了一个文件，所以会出现最后执行完“输出一周七天”后，
会诡异的输出“析构函数执行 , 销毁《西游记》”。这是因为虚构函数在 main() 函数执行完毕后，会自动调用。
 */

#include <iostream>
#include <string>
using namespace std;

// 前向声明
class Book;

class Student {
private:
    string name;
    Book* borrowBook; // 借的书

public:
    Student() {}
    Student(string _name) : name(_name), borrowBook(nullptr) {}

    void borrow(Book* _book); 
};

// Book 类完整定义
class Book {
private:
    string bookName;

public:
    Book(string _bookName) : bookName(_bookName) {
        cout << "构造函数执行 , 创建《" << bookName << "》" << endl;
    }
    ~Book() {
        cout << "析构函数执行 , 销毁《" << bookName << "》" << endl;
    }

    string getBookName() {
        return bookName ; 
    }
};

// 现在 Book 已经完整定义，可以调用其方法
void Student::borrow(Book* _book) {
    borrowBook = _book;
    cout << name << " 借阅了 《" << _book->getBookName() << "》 这本书" << endl;
}

struct Person {
    char name[20] ;    
    int age ;          
    char gender[10] ;  
}; 

union Data {
    int index ; 
    double dex ; 
    char str[20] ; 
} ; 

enum Weekday { Monday, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday };

void printWeekday(Weekday day) {
    switch (day) {
        case Monday: cout << "今天是星期一" << endl; break;
        case Tuesday: cout << "今天是星期二" << endl; break;
        case Wednesday: cout << "今天是星期三" << endl; break;
        case Thursday: cout << "今天是星期四" << endl; break;
        case Friday: cout << "今天是星期五" << endl; break;
        case Saturday: cout << "今天是星期六" << endl; break;
        case Sunday: cout << "今天是星期日" << endl; break;
    }
}   

int main() {
    // test1 创建 Book 与 Student 对象并借书
    Book book1("西游记");
    Student stu1("张三");
    stu1.borrow(&book1);

    // test2 比较结构体与联合体的内存占用
    Person p = {
        "zhang" , 20 , "Male"
    } ; 

    Data d ; 
    cout << "结构体 Person 的大小 : " << sizeof(Person) << " 字节" << endl ; 
    cout << "联合体 Data 的大小: " << sizeof(Data) << " 字节" << endl;

    // test3 输出一周七天
    for (int i = Monday; i <= Sunday; i++) {
        printWeekday(Weekday(i));
    }
    
    return 0;
}
