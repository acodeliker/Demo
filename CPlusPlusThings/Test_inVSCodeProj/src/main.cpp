
#include "Circle.hpp"
#include "Features.hpp"

#include <iostream>
using namespace std;

/**
 *  created on 2021.8.1
 *  @ref:https://cloud.tencent.com/developer/article/1099957
 * 
 *  智能指针
 **/

// 背景： 防止某种资源遗失的常见办法就是捕捉所有异常，例如：
class classA
{
public:
    classA(int n) : num(n)
    {
    }

private:
    int num;
};

void f()
{
    classA *ptr = new classA(1); // create an object explicitly
    try
    {
        // perform some operations
    }
    catch (...)
    {
        delete ptr; //-clean up
        throw;      //-rethrow the exception
    }

    /*
    	为了更容易（同时也更安全的管理）的使用动态内存，

        新的标准库（C++11）提供了两种智能指针（smart pointer）类类型来管理动态对象。它负责自动释放所指向的对象。
    */

    // 举个例子：shared_ptr 提供swap()成员函数,用来交换两个相同类型的对象,比如:
    //shared_ptr<classA> p1(new classA(1));
    //shared_ptr<classA> p2(new classA(2));
    shared_ptr<int> p1(new int(1));
    shared_ptr<int> p2(new int(2));
    p1.swap(p2);         //交换后 p1=2,p2=1
    cout << *p1 << endl; //打印 2
    cout << *p2 << endl; //打印 1
    delete ptr;          // clean up(destory the object explicitly)

    // 再举个例子： shared_ptr 也提供use_count()成员函数,可以用来查看引用计数个数,比如:
    shared_ptr<int> sp1(new int(30)); //计数+1
    cout << sp1.use_count() << endl;  //打印计数:1
    cout << sp1.unique() << endl;     //打印:1
    shared_ptr<int> sp2(sp1);         //计数+1
    cout << sp1.use_count() << endl;  //打印:2
    cout << sp1.unique() << endl;     //由于sp1指针对象被sp2引用,打印:0
    sp1.reset();                      //将sp1指针对象地址设为NULL,计数-1
    cout << sp1.get() << endl;        //sp1指针对象地址为NULL,打印:0
    cout << sp2.use_count() << endl;  //打印:1
    cout << sp2.unique() << endl;     //由于sp1释放,仅剩下sp2指向30所在的地址,所以打印:1
}

/////////////////////////////////////////////////////
/** 
*   created on 2021.7.31
*   @ref:https://www.jianshu.com/p/16b015be4a48
*
*   结构化绑定
**/

int main4()
{
    int a[2] = {1, 2};
    auto [x, y] = a;
    auto &[xr, yr] = a; //
    std::cout << x << " " << y << std::endl;
    xr = 5;
    std::cout << a[0] << " " << a[1] << std::endl;
    return 0;
}

/* 分析下这段代码例子：
    int a[2] = { 1, 2 };
        我们给一个有两个元素的数组赋值。
    
    auto [x, y] = a;
        将这个数组的两个元素的值分别赋值给x，y。
    
    auto& [xr, yr] = a;
        xr为a[0]的引用，yr为a[1]的引用。
			
    其中，auto [x, y] = a; auto& [xr, yr] = a;
    就是我们这次要讲的结构化绑定（structured binding）
    
    上面的例子改一下，一个比较完整的结构化绑定的表达式应该为
        [[maybe_unused]] const auto& [xr, yr] = a;


*/

////////////////////////////////////////////////////
/** 
*   created on 2021.7.25
*   @ref:https://developer.aliyun.com/article/584964
*
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

#include <future>

int main3()
{
    // 这里开启两个线程
    /* thread t1(run, 1); // 第二个参数表示函数run里的参数（实参到形参的过程）
    thread t2(run, 2);
    t1.join();
    t2.join(); */
    // 很明显t1t2执行顺序会相互影响（线程加塞）

    /**************************/
    // a.

    /**************************/
    // b.
    void run3();
    vector<thread> threads;
    for (int i = 0; i < 20; i++)
    {
        threads.emplace_back(run3);
    }
    for (auto &t : threads)
    {
        t.join();
    }
    /* 
        try_to_lock在构造完成后，会使用owns_lock()检查是否实际持有这把锁，它一定持有该mutex，但未必持有这把锁。
        本例中，如果持有锁打印“*”号，不持有则打印“x”号。那么启动50个线程运行时，大多数情况下都持有锁，但是也存在打印“x”号的情况。
    */

    /**************************/
    // c.
    void runa();
    void runb();
    thread t3(runa);
    thread t4(runb);
    t3.join();
    t4.join();

    /**************************/

    // 质数判定服务
    // 11首先将判定服务置于一独立线程中，
    // 22然后利用request方法将一个整数传入质数判定服务，返回一个future，即判断结果是否为质数
    // 33在主线程中打印。44最后需要退出程序，即发送0至request中，具体如下所示。
    void prime_service();
    thread t(prime_service); // 11

    int n0 = 13524415;
    int n1 = 12343533;

    future<bool> request(int);
    future<bool> r0 = request(n0);
    future<bool> r1 = request(n1);

    // 33
    cout << n0 << ":" << boolalpha << r0.get() << endl;
    cout << n0 << ":" << boolalpha << r0.get() << endl;

    // 44
    request(0);
    t.join();

    return 0;
}
#include <vector>

// 改进（添加基础同步原语），如
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
void run3()
{
    unique_lock<mutex> ulck(m, try_to_lock);
    cout << (ulck.owns_lock() ? '*' : 'x');
}

// c.条件变量是线程间的通知机制。将通过以下示例进行讲解：

#include <condition_variable>

mutex mtx;
condition_variable cv;

void runa()
{
    unique_lock<mutex> ul(mtx);
    cout << "Waiting" << endl;
    cv.wait(ul);
    cout << "Wake up" << endl;
}

void runb()
{
    {
        lock_guard<mutex> ul(mtx);
        cout << "Notify" << endl;
    }
    cv.notify_one();
}

// d. Semaphore
// Condition variable的一个用法是实现信号量。信号量（semaphore）是一种同步机制，但在C++11中并没有原生提供该机制，那么就需要自己去实现。

/*******************************************************************/
// 高级同步原语：future (构造方式：async/packaged_task/promise

// 有时某项工作很早就可以开始做（前置条件都已完备），而等待这件工作结果的任务在非常靠后的位置，这时候就需要async。
// 换言之，如果可以尽早开始做一件事，就让其在后台运行即可，或快或慢都可以，只需在需要结果的时候运行完成就好。例如：

int FinalAns()
{
    cout << __func__ << " is running" << endl;

    this_thread::sleep_for(chrono::seconds(1));

    cout << "the ans is ready." << endl;
    return 42;
}

int main3()
{
    future<int> lazyAns = async(launch::async, FinalAns);
    this_thread::sleep_for(chrono::microseconds(100));
    cout << __func__ << " is running." << endl;
    cout << lazyAns.get() << endl;

    return 0;
}

/*******************************************************************/
// 质数判定服务

#include <deque>
deque<tuple<promise<bool>, int>> reqs;
condition_variable cv1;

#include <math.h>
bool is_prime(int n)
{
    if (n == 1)
        return false;
    bool sign = true;
    for (int i = 2; i <= sqrt(n); i++) //是<=,不要忘记等号
    {
        if (n % i == 0)
        {
            sign = false;
            break;
        }
    }
    return sign;
}
void prime_service()
{
    while (1)
    {
        /* code */
        unique_lock<mutex> lck(mtx);
        for (; reqs.empty();)
        {
            cv1.wait(lck);
        }
        promise<bool> res;
        int n = 0;

        tie(res, n) = move(reqs.front());
        reqs.pop_front();
        if (n == 0)
            break;
        res.set_value(is_prime(n));
    }
}

future<bool> request(int x)
{
    promise<bool> pm;
    future<bool> res = pm.get_future();
    {
        lock_guard<mutex> lck(mtx);
        reqs.emplace_back(move(pm), x);
    }

    cv.notify_one();

    return res;
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
    auto m{5}; // OK：DR N3922 起 m 的类型是 int，之前是 initializer_list<int>
    //  decltype(auto) z = { 1, 2 } // 错误：{1, 2} 不是表达式

    // auto 常用于无名类型，例如 lambda 表达式的类型
    auto lambda = [](int x)
    { return x + 3; };

    //  auto int x; // 于 C++98 合法，C++11 起错误
    //  auto x;     // 于 C 合法，于 C++ 错误

    return 0;
}

///////////////////////////////////////////////////////////////////////

double Foo3_1::z = 1.0;
int main1()
{
    cout << "Hello VScode !!" << endl;

    double r = 2.0;
    Circle c1(r);
    c1.getArea();

    /************************************************************************************************/
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
    /************************************************************************************************/

    /**
     * created in 2021.7.21
     * @ref: https://www.jianshu.com/p/6ecfd541ec04
     */

    using F = int(int *, int);
    //    F  f1(int);    //错误： 不能是函数类型
    using PF = int (*)(int *, int);
    //    PF  f1(int);    // 返回值是个函数指针

    /************************************************************************************************/

    getchar();
    return 0;
}
