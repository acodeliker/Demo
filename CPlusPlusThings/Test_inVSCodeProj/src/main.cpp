
#include "Head.hpp"
#include "Features.hpp"

using namespace std;

double Foo3_1::z = 1.0;
int main()
{
    cout << "Hello VScode !!" << endl;

    double r = 2.0;
    Circle c1(r);
    c1.getArea();

    /////////////////////////////////////////////////////////////////////
    //test1
    Foo1 a1(123); //调用Foo(int)构造函数初始化
    //Foo1 a2 = 123; //error Foo的拷贝构造函数声明为私有的，该处的初始化方式是隐式调用Foo(int)构造函数生成一个临时的匿名对象，再调用拷贝构造函数完成初始化

    Foo1 a3 = {123}; //列表初始化	生成initializer_list<int>，然后分解元素后，由于列表中只有1个元素，所以将其传给Foo1(int)

    Foo1 a4{123};    //列表初始化   生成initializer_list<int>，然后分解元素后，由于列表中有两个元素，所以将其传给Foo1(int, int)

    //test2
    Foo2 foo{123, 321};
    cout << foo.x << " " << foo.y << endl;

    //test3
    //Foo3 foo1{123,456,789.0};           // [g++]error: no matching function for call to ‘Foo3::Foo3(<brace-enclosed initializer list>)
    //cout << foo1.x << " " << foo1.y;
    Foo3_1 foo2{123, 456};

    cout << foo2.x << " " << foo2.y << endl;

    //test4
    //Foo4 foo3{123,456};                   // [g++]error: no matching function for call to ‘Foo4::Foo4(<brace-enclosed initializer list>)
    //cout << foo.x << " " << foo.y;

    //Foo4_1 foo4 {123,456};                // [g++]error: no matching function for call to ‘Foo4_1::Foo4_1(<brace-enclosed initializer list>)
    //cout << foo.x << " " << foo.y;

    //test5
    //Foo5 foo5{123,456};
    // cout << foo.x << " " << foo.y;

    Foo f1(1, 2, 3.0);    //直接调用构造函数初始化
    Foo f2{4, 5, 6.0};    //由于Foo是个非聚合类型，使用{}时会调用相应的构造函数来初始化。
    Foo f3 = {7, 8, 9.0}; //非聚合类型会调用构造函数来初始化

    cout << "a.x = " << f1.x << ", a.y = " << f1.y << endl;
    /*  
    output:
        Foo(int x, int y, double z)
        Foo(int x, int y, double z)
        Foo(int x, int y, double z)
        a.x = 1, a.y = 2
    */
    /////////////////////////////////////////////////////////////////////






    getchar();
    return 0;
}