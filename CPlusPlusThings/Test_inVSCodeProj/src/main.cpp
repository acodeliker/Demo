
#include "Circle.hpp"
#include "Features.hpp"

#include <iostream>
using namespace std;

/**
*	C++线程和基础同步原语
*   Thread
**/

//   C++11中怎样开启一个线程呢？以下是一段代码示例：
#include <thread>
// 模拟线程
void run(int n)
{
    for (int i = 0; i < 5; ++i)
    {
        cout << "thread" << n << '\n';
    }
}
int main()
{
    thread t1(run, 1);
    thread t2(run, 2);
    t1.join();
    t2.join();
}

// 改进
// a.加入mutex
#include <mutex>

mutex m;

void run1(int n)
{
    for (int i = 0; i < 5; ++i)
    {
        m.lock();
        cout << "thread" << n << '\n';
        m.unlock();
    }
}

// b.上面存在异常安全问题，在抛出异常时需要注意一些收尾操作。这也是RAII的设计目标之一，标准库提供了一种RAII锁形式，即lock_guard
// 或者unique_lock基本用法和lock_guard一致，在构造函数和析构函数中进行锁操作，不同的地方在于它提供了非常多构造函数。
void run2(int n)
{
    for (int i = 0; i < 5; ++i)
    {
        lock_guard<mutex> lo(m);
//        unique_lock<mutex> lo(m); // call constructor::unique_lock(mutex_type&), 持有mutex并上锁
        cout << "thread" << n << '\n';
    }
}
// 如果该mutex是timed_mutex，可以持有该mutex并尝试上锁一段时间，或者尝试上锁到某个时间点。具体使用方法如下：
void run3() {
    unique_lock<mutex> ulck(m, try_to_lock);
    cout << (ulck.owns_lock() ? '*' : 'x');
}
#include <vector>

// c.条件变量是线程间的通知机制。将通过以下示例进行讲解：

#include <condition_variable>

mutex mtx;
condition_variable cv;

void runa() {
    unique_lock<mutex> ul(mtx);
    cout << "Waiting" << endl;  
    cv.wait(ul)

}

int main3()
{

    // 改进b.
    vector<thread> threads;
    for(int i = 0; i < 20; i ++ ) {
        threads.emplace_back(run3);
    }
    for (auto& t: threads) {
        t.join();
    }
    /* 
        try_to_lock在构造完成后，会使用owns_lock()检查是否实际持有这把锁，它一定持有该mutex，但未必持有这把锁。
        本例中，如果持有锁打印“*”号，不持有则打印“x”号。那么启动50个线程运行时，大多数情况下都持有锁，但是也存在打印“x”号的情况。
    */





    return 0;
}

////////////////////////////////////////////////////////////

/*
	使用auto的时候，编译器根据上下文情况，确定auto变量的真正类型
*/

#include <utility>
#include <type_traits>

template <class T, class U>
auto add(T t, U u)
{
    return t + u;
} // 返回类型是 operator+(T, U) 的类型

// 在其所调用的函数返回引用的情况下
// 函数调用的完美转发必须用 decltype(auto)
template <class F, class... Args>
decltype(auto) PerfectForward(F fun, Args &&...args)
{
    return fun(forward<Args>(args)...);
}

template <auto n>                          // C++17 auto 形参声明
auto f() -> pair<decltype(n), decltype(n)> // auto 不能从花括号(Initializer-list)推导
{
    return {n, n};
}

int main2()
{
    auto a = 1 + 2;       // a 的类型是 int
    auto b = add(1, 1.2); // b 的类型是 double
    static_assert(is_same_v<decltype(a), int>);
    static_assert(is_same_v<decltype(b), double>);

    auto c0 = a;             // c0 的类型是 int，保有 a 的副本
    decltype(auto) c1 = a;   // c1 的类型是 int，保有 a 的副本
    decltype(auto) c2 = (a); // c2 的类型是 int&，它是 a 的别名
    cout << "通过 c2 修改前，a = " << a << '\n';
    ++c2;
    cout << "通过 c2 修改后，a = " << a << '\n';

    auto [v, w] = f<0>(); // 结构化绑定声明

    auto d = {1, 2}; // OK：d 的类型是 std::initializer_list<int>
    auto n = {5};    // OK：n 的类型是 std::initializer_list<int>
                     //  auto e{1, 2};    // C++17 起错误，之前是 std::initializer_list<int>
    auto m{5};       // OK：DR N3922 起 m 的类型是 int，之前是 initializer_list<int>
                     //  decltype(auto) z = { 1, 2 } // 错误：{1, 2} 不是表达式

    // auto 常用于无名类型，例如 lambda 表达式的类型
    auto lambda = [](int x)
    { return x + 3; };

    //  auto int x; // 于 C++98 合法，C++11 起错误
    //  auto x;     // 于 C 合法，于 C++ 错误
}


double Foo3_1::z = 1.0;
int main1()
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

    Foo1 a4{123}; //列表初始化   生成initializer_list<int>，然后分解元素后，由于列表中有两个元素，所以将其传给Foo1(int, int)

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

    /**
     * created in 2021.7.21
     * @ref: https://www.jianshu.com/p/6ecfd541ec04
     */

    using F = int(int *, int);
    //    F  f1(int);    //错误： 不能是函数类型
    using PF = int (*)(int *, int);
    //    PF  f1(int);    // 返回值是个函数指针

    //////////////////////////////////////////////////////////////////////

    getchar();
    return 0;
}