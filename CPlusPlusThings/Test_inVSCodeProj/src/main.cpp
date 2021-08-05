
#include "Circle.hpp"
#include "Features.hpp"

#include <iostream>
using namespace std;

/**
 *  created on 2021.8.5
 *  @ref: http://c.biancheng.net/view/7759.html
 * 
 *  for-each based on range
 **/


/*
    C++ 11 标准中，除了可以沿用前面介绍的用法外，还为 for 循环添加了一种全新的语法格式，如下所示：
        for (declaration : expression){
            //循环体
        }

    其中，两个参数各自的含义如下：
    declaration：表示此处要定义一个变量，该变量的类型为要遍历序列中存储元素的类型。
        需要注意的是，C++ 11 标准中，declaration参数处定义的变量类型可以用 auto 关键字表示，该关键字可以使编译器自行推导该变量的数据类型。
    expression：表示要遍历的序列，常见的可以为事先定义好的普通数组或者容器，还可以是用 {} 大括号初始化的序列。

    可以看到，同 C++ 98/03 中 for 循环的语法格式相比较，此格式并没有明确限定 for 循环的遍历范围，这是它们最大的区别，即旧格式的 for 循环可以指定循环的范围，
    而 C++11 标准增加的 for 循环，只会逐个遍历 expression 参数处指定序列中的每个元素。

*/

// 下面程序演示了如何用 C++ 11 标准中的 for 循环遍历实例一定义的 arc 数组和 myvector 容器：

#include <iostream>
#include <vector>
using namespace std;
int main() {
    char arc[] = "http://c.biancheng.net/cplus/11/";
    //for循环遍历普通数组
    for (char ch : arc) {
        cout << ch;
    }
    cout << '!' << endl;
    vector<char>myvector(arc, arc + 23);
    //for循环遍历 vector 容器
    for (auto ch : myvector) {
        cout << ch;
    }
    cout << '!';
    return 0;
}
/*
    这里有以下 2 点需要说明：
    1) 程序中在遍历 myvector 容器时，定义了 auto 类型的 ch 变量，当编译器编译程序时，会通过 myvector 容器中存储的元素类型自动推导出 ch 为 char 类型。
        注意，这里的 ch 不是迭代器类型，而表示的是 myvector 容器中存储的每个元素。

    2) 仔细观察程序的输出结果，其中第一行输出的字符串和 "!" 之间还输出有一个空格，
    这是因为新格式的 for 循环在遍历字符串序列时，不只是遍历到最后一个字符，还会遍历位于该字符串末尾的 '\0'（字符串的结束标志）。
        之所以第二行输出的字符串和 "!" 之间没有空格，是因为 myvector 容器中没有存储 '\0'。

*/

// 另外值得一提的是，在使用新语法格式的 for 循环遍历某个序列时，如果需要遍历的同时修改序列中元素的值，实现方案是在 declaration 参数处定义引用形式的变量。举个例子：
#include <iostream>
#include <vector>
using namespace std;
int main8() {
    char arc[] = "abcde";
    vector<char>myvector(arc, arc + 5);
    //for循环遍历并修改容器中各个字符的值
    for (auto &ch : myvector) {
        ch++;
    }
    //for循环遍历输出容器中各个字符
    for (auto ch : myvector) {
        cout << ch;
    }
    return 0;
}
// 此程序中先后使用了 2 个新语法格式的 for 循环，其中前者用于修改 myvector 容器中各个元素的值，后者用于输出修改后的 myvector 容器中的各个元素。

/* *declaration 参数既可以定义普通形式的变量，也可以定义引用形式的变量，应该如何选择呢？
    其实很简单，如果需要在遍历序列的过程中修改器内部元素的值，就必须定义引用形式的变量；
    反之，建议定义const &（常引用）形式的变量（避免了底层复制变量的过程，效率更高），也可以定义普通变量。
*/

/**
 *  created on 2021.8.4
 *  @ref: https://www.jianshu.com/p/f191e88dcc80
 * 
 *  std::function/bind
 **/

/* std::function 是一个可调用对象包装器，是一个类模板，可以容纳除了类成员函数指针之外的所有可调用对象，它可以用统一的方式处理函数、函数对象、函数指针，并允许保存和延迟它们的执行。
    定义格式：std::function<函数类型>。
    std::function可以取代函数指针的作用，因为它可以延迟函数的执行，特别适合作为回调函数使用。它比普通函数指针更加的灵活和便利。
*/

/*
    std::bind
    可将std::bind函数看作一个通用的函数适配器，它接受一个可调用对象，生成一个新的可调用对象来“适应”原对象的参数列表。
    std::bind将可调用对象与其参数一起进行绑定，绑定后的结果可以使用std::function保存。std::bind主要有以下两个作用：
        将可调用对象和其参数绑定成一个防函数；  
        只绑定部分参数，减少可调用对象传入的参数。
*/

// std::bind绑定普通函数
double my_divide(double x, double y) { return x / y; }
auto fn_half = std::bind(my_divide, _1, 2);
std::cout << fn_half(10) << '\n'; // 5
//bind的第一个参数是函数名，普通函数做实参时，会隐式转换成函数指针。因此std::bind (my_divide,_1,2)等价于std::bind (&my_divide,_1,2)；_1表示占位符，位于<functional>中，std::placeholders::_1；

// std::bind绑定一个成员函数
struct Foo
{
    void print_sum(int n1, int n2)
    {
        std::cout << n1 + n2 << '\n';
    }
    int data = 10;
};
int main7()
{
    Foo foo;
    auto f = std::bind(&Foo::print_sum, &foo, 95, std::placeholders::_1);
    f(5); // 100
}
// bind绑定类成员函数时，第一个参数表示对象的成员函数的指针，第二个参数表示对象的地址。
// 必须显示的指定&Foo::print_sum，因为编译器不会将对象的成员函数隐式转换成函数指针，所以必须在Foo::print_sum前添加&；
// 使用对象成员函数的指针时，必须要知道该指针属于哪个对象，因此第二个参数为对象的地址 &foo；

// 绑定一个引用参数
// 默认情况下，bind的那些不是占位符的参数被拷贝到bind返回的可调用对象中。但是，与lambda类似，有时对有些绑定的参数希望以引用的方式传递，或是要绑定参数的类型无法拷贝。

#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>
#include <sstream>
using namespace std::placeholders;
using namespace std;

ostream &print(ostream &os, const string &s, char c)
{
    os << s << c;
    return os;
}

int main6()
{
    vector<string> words{"helo", "world", "this", "is", "C++11"};
    ostringstream os;
    char c = ' ';
    for_each(words.begin(), words.end(),
             [&os, c](const string &s)
             { os << s << c; });
    cout << os.str() << endl;

    ostringstream os1;
    // ostream不能拷贝，若希望传递给bind一个对象，
    // 而不拷贝它，就必须使用标准库提供的ref函数
    for_each(words.begin(), words.end(),
             bind(print, ref(os1), _1, c));
    cout << os1.str() << endl;
}

/**
 * created on 2021.8.2
 * @ref:
 * 
 * RAII机制
 **/

//	i. 在使用多线程时，经常会涉及到共享数据的问题：
template <class... _Mutexes>
class lock_guard
{ // class with destructor that unlocks mutexes
public:
    explicit lock_guard(_Mutexes &..._Mtxes)
        : _MyMutexes(_Mtxes...)
    { // construct and lock
        _STD lock(_Mtxes...);
    }

    lock_guard(_Mutexes &..._Mtxes, adopt_lock_t)
        : _MyMutexes(_Mtxes...)
    { // construct but don't lock
    }

    ~lock_guard() _NOEXCEPT
    { // unlock all
        _For_each_tuple_element(
            _MyMutexes,
            [](auto &_Mutex) _NOEXCEPT
            { _Mutex.unlock(); });
    }

    lock_guard(const lock_guard &) = delete;
    lock_guard &operator=(const lock_guard &) = delete;

private:
    tuple<_Mutexes &...> _MyMutexes;
};

/*  C++中通过实例化std::mutex创建互斥量，通过调用成员函数lock()进行上锁，unlock()进行解锁。
	不过这意味着必须记住在每个函数出口都要去调用unlock()，也包括异常的情况，这非常麻烦，而且不易管理。
	C++标准库为互斥量提供了一个RAII语法的模板类std::lock_guard，其会在构造函数的时候提供已锁的互斥量，并在析构的时候进行解锁，从而保证了一个已锁的互斥量总是会被正确的解锁。
    上面的代码正是<mutex>>头文件中的源码，其中还使用到很多C++11的特性
*/

// ii. 下面说一个具有实际意义的例子：
#include <iostream>
#include <windows.h>
#include <process.h>
using namespace std;
CRITICAL_SECTION cs;
int gGlobal = 0;
class MyLock
{
public:
    MyLock()
    {
        EnterCriticalSection(&cs);
    }
    ~MyLock()
    {
        LeaveCriticalSection(&cs);
    }

private:
    MyLock(const MyLock &);
    MyLock operator=(const MyLock &);
};
void DoComplex(MyLock &lock) // 非常感谢益可达犀利的review 2014.04.13
{
}
unsigned int __stdcall ThreadFun(PVOID pv)
{
    MyLock lock;
    int *para = (int *)pv;
    // I need the lock to do some complex thing
    DoComplex(lock);
    for (int i = 0; i < 10; ++i)
    {
        ++gGlobal;
        cout << "Thread " << *para << endl;
        cout << gGlobal << endl;
    }
    return 0;
}
int main5()
{
    InitializeCriticalSection(&cs);
    int thread1, thread2;
    thread1 = 1;
    thread2 = 2;
    HANDLE handle[2];
    handle[0] = (HANDLE)_beginthreadex(NULL, 0, ThreadFun, (void *)&thread1, 0, NULL);
    handle[1] = (HANDLE)_beginthreadex(NULL, 0, ThreadFun, (void *)&thread2, 0, NULL);
    WaitForMultipleObjects(2, handle, TRUE, INFINITE);
    return 0;
}
/*	这个例子可以说是实际项目的一个模型，
	当多个进程访问临界变量时，为了不出现错误的情况，需要对临界变量进行加锁；上面的例子就是使用的Windows的临界区域实现的加锁。			
	但是，在使用CRITICAL_SECTION时，EnterCriticalSection和LeaveCriticalSection必须成对使用，很多时候，经常会忘了调用LeaveCriticalSection，此时就会发生死锁的现象。
    当我将对CRITICAL_SECTION的访问封装到MyLock类中时，之后，我只需要定义一个MyLock变量，而不必手动的去显示调用LeaveCriticalSection函数。
*/

/////////////////////////////////////////////////////////
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
