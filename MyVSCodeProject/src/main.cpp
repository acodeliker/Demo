#include "Head.hpp"

using namespace std;

int main()
{

    double r = 2.0;
    cout << "Hello VScode !!" << endl;

    Circle c1(r);
    c1.getArea();


    //test1
    Foo1 a1(123);  //调用Foo(int)构造函数初始化
    Foo1 a2 = 123; //error Foo的拷贝构造函数声明为私有的，该处的初始化方式是隐式调用Foo(int)构造函数生成一个临时的匿名对象，再调用拷贝构造函数完成初始化

    Foo1 a3 = {123}; //列表初始化
    Foo1 a4{123};    //列表初始化


    //test2
    Foo2 foo{123, 321};
    cout << foo.x << " " << foo.y;
    return 0;

    getchar();
    return 0;
}