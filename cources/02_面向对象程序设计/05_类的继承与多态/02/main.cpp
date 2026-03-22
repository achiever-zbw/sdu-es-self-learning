/**
 * 面向对象程序设计 05 类的继承与多态
 * 定义一个 Document 类，有数据成员 name，
 * 从 Document 派生出 Book 类，增加数据成员 pageCount。
 */

#include <iostream>
using namespace std ;

 class Document {

    public :
        Document(string _name) : name(_name) {} ;
        // 获取名字
        string getName() {
            return name ; 
        }
    
    private :
        string name ;
    } ; 
    
    //  Book 继承 Document
    class Book : public Document {
    public : 
        Book(string _name , int pages = 0) : Document(_name) , pageCount(pages) {}
        int getPage() {
            return pageCount ; 
        }
    private :
        // 新增数据成员
        int pageCount ; 
    } ; 

int main()
{
    Book book("面向对象程序设计" , 150) ; 
    cout << "书名 : " << book.getName() << endl ; 
    cout << "页数 : " << book.getPage() << endl ; 

    return 0 ;
}
