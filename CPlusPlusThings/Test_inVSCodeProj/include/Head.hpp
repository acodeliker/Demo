#ifndef _HEAD_
#define _HEAD_

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string>

const double Pi = 3.14159;

//
class Circle
{
public:
    Circle(double r);
    void getArea();

private:
    double radium;
};

// https://www.cnblogs.com/DswCnblog/p/6565024.html
// initializer-list since C++11
// test1:
class Foo1
{
public:
    Foo1(int) {}

private:
    Foo1(const Foo1 &);
};

// detailed usage
// test2:首先存在用户自定义的构造函数的情况:
struct Foo2
{
    int x;
    int y;
    Foo2(int, int) : x(0), y(0)
    {
        std::cout << "Foo2 construction";
    }
};

// test3:类包含有私有的或者受保护的非静态数据成员的情况:
struct Foo3
{
    int x;
    int y;
    //Foo(int, int, double){}
protected:
    double z;                       // error C2440: 'initializing' : cannot convert from 'initializer-list' to 'Foo'
    //static double _z;              // ok
};

// 快速幂template
/* 
    (k)_10 ---> (k)_2 == jnjn-1....j2j1j0

    m^(k) == m^(2^0 * j0) * m^(2^1 * j1)  ...  * m^(2^n * jn)
 */
template <typename T>
inline T qmi(T m, int k, int p)
{
    T res = 1 % p, t = m;
    while (k)
    {
        if (k & 1)
        {
            res = res * t * 1ll % p;
        }
        t = t * t * 1ll % p;
        k >>= 1;
    }
    return res;
}

#endif