/**
 * 面向对象程序设计 04 数组、指针与字符串
 * 编写一个矩阵转置的函数，矩阵的行数和列数在程序中由用户输入。
 */

# include <iostream>
# include <vector>
using namespace std ;

int n , m ; 

vector<vector<int>> transpose(vector<vector<int>>& init) {
    int hang = m , lie = n ; 
    // 构造行列大小反转的二维矩阵
    vector<vector<int>> res(hang , vector<int>(lie)) ; 

    for(int i = 0 ; i < n ; i ++ ) {
        for(int j = 0 ; j < m ; j ++ ) {
            res[j][i] = init[i][j] ; // 赋值
        }
    }
    return res ; 
}   

int main()
{
    cout << "请输入矩阵的行数 : " ; cin >> n ; 
    cout << "请输入矩阵的列数 : " ; cin >> m ; 

    // 初始化二维矩阵
    vector<vector<int>> init(n , vector<int>(m)) ; 
    cout << "请输入矩阵 : " << endl ; 

    for(int i = 0 ; i < n ; i ++ ) {
        for(int j = 0 ; j < m ; j ++ ) {
            cin >> init[i][j] ; 
        }
    }

    auto res = transpose(init) ; 

    cout << "矩阵转置后为 : " << endl ; 
    for(int i = 0 ; i < m ; i ++ ) {
        for(int j = 0 ; j < n ; j ++ ) {
            cout << res[i][j] << ' ' ; 
        }
        cout << endl ; 
    }
    
    return 0 ; 
}