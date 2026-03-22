/**
 * 面向对象程序设计 03 数据的共享与保护 04
 * 定义 Boat 与 Car 两个类，二者都有 weight 属性，
 * 定义二者的一个友元函数 getTotalWeight()，计算二者的重量和。
 */

#include <iostream>
using namespace std;

// 前向声明
class Boat;
class Car;


double getTotalWeight(const Boat& b, const Car& c);

// Boat 类定义
class Boat {
private:
    double weight;

public:
    Boat(double w = 0) : weight(w) {}

    double getWeight() const { return weight; }

    friend double getTotalWeight(const Boat& b, const Car& c);
};

// Car 类定义
class Car {
private:
    double weight;

public:
    Car(double w = 0) : weight(w) {}

    double getWeight() const { return weight; }

    friend double getTotalWeight(const Boat& b, const Car& c);
};

// 友元函数实现
double getTotalWeight(const Boat& b, const Car& c) {
    return b.weight + c.weight;
}

int main() {
    Boat b(1200.5);  // 船重
    Car c(850.3);    // 车重

    cout << "Boat 的重量: " << b.getWeight() << endl;
    cout << "Car  的重量: " << c.getWeight() << endl;
    cout << "总重量 = " << getTotalWeight(b, c) << endl;

    return 0;
}
