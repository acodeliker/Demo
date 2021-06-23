#ifndef _HEAD_HPP_
#define _HEAD_HPP_

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

//////////////////////////////////////////////////////////////////////////////////////////
//
// 你一定要熟悉 C++11/14/17 常用的语言特性
//
///////////////////////////////////////////////////////////////
/** 参考：https://www.cnblogs.com/DswCnblog/p/6565024.html
 **  
 ** • Uniform Initialization： initializer-list since C++11
**/
// test1: C++11中Initializer-list适用性被放大，可以作用于任何类型对象的初始化
class Foo1
{
public:
    Foo1(int) {}

private:
    Foo1(const Foo1 &){};
};

// detailed usage
// 对于non-aggregate-type来说，能不能使用initializer-list初始化呢？看下面的讨论：
// test2:首先存在用户自定义的构造函数的情况:（编译器唯独不会报错的情况）
struct Foo2
{
    int x;
    int y;
    Foo2(int x, int y) // 对于有用户自定义构造函数的类,使用initializer-list对其成员初始化后变量值是一个随机值,也就是说会产生意想不到的结果，需要特别注意
    {
        std::cout << "Foo2 construction1" << std::endl;
    }
    /* Foo2(int x, int y) : x(0), y(0)              // 构造函数带有初始化列表的时候优先级高，因而用initializer-list对类的成员初始化无效
    {
        std::cout << "Foo2 construction2";
    } */
};

// test3:类包含有私有的或者受保护的非静态数据成员的情况:
struct Foo3
{
    int x;
    int y;
    //Foo(int, int, double){}
protected:
    double z; // [VS2013]error C2440: 'initializing' : cannot convert from 'initializer-list' to 'Foo'
};
struct Foo3_1
{
    int x;
    int y;

protected:
    static double z; // ok
};


//test4:类含有基类或者虚函数的情况：
struct Foo4
{
    int x;
    int y;
    virtual void func(){};
};
struct base
{
};
struct Foo4_1 : base
{
    int x;
    int y;
};

// test5:类中有{}或者=直接初始化的非静态数据成员的情况:
struct Foo5
{
    int x;
    int y = 5;
};

// 将前4种情况合并在一个non-aggregate-type Class中：
// 就是对于聚合类型的判别条件做一个总结，凡是不满足以下要求的其中一条的话，该类型就是个non-aggregate-type
struct Foo : public base //不能有基类
{
private:
    double z;     //不能有private的普通成员（言下之意就是非聚类了）
    static int k; //ok，但必须在类外用int Foo::k = 0的方式初始化
public:
    Foo(int x, int y, double z) : x(x), y(y), z(z) //不能有构造函数！
    {
        std::cout << "Foo(int x, int y, double z)" << std::endl;
    }

    Foo(const Foo &foo) //不能有构造函数！
    {
        this->x = foo.x;
        this->y = foo.y;
        this->z = foo.z;

        std::cout << "Foo(const Foo& foo)" << std::endl;
    }

    int x;
    int y;              //不能通过int y=0;或int y{0}来"就地初始化"
    virtual void F(){}; //不能有虚函数！
};
/////////////////////////////////////////////////////////////////////////////////





/////////////////////////////////////////////////////////////////////////////////







/////////////////////////////////////////////////////////////////////////////////

#endif