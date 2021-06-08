//
// Created by light on 19-11-3.
//

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

/* 
int main() {
    int i;
    int j();        // 0
    int *p;
    int *q();       // nullptr

//    int x1{5.0};    //  error:narrowing conversion
    // 编译器调用initializer_list私有构造之前,编译器准备好array(array头)与len,传递给该构造,并没有内含这个array,
    // 指针指向array,copy只是浅copy.即不开辟新的array address
    // 如今所有容器都接受任意数量的值  insert()或assign() max() min()

    cout<<max({1,2,3})<<endl;   // algorithm里面的max/min
    return 0;
} */


// 下面一个例子可以帮助我们更好的理解如何使用initializer_list
// referring to https://www.cnblogs.com/lysuns/p/4278589.html

template <class T>
struct S
{
    vector<T> v;
    S(initializer_list<T> l) : v(l)
    {
        cout << "constructed with a " << l.size() << "-elements lists" << endl;
    }
    void append(std::initializer_list<T> l)
    {
        v.insert(v.end(), l.begin(), l.end());
    }
    pair<const T *, size_t> c_arr() const
    {
        return {&v[0], v.size()};
    }
};

template <typename T>
void templated_fn(T arg)
{
    for (auto a : arg)
        cout << a << " ";
    cout << endl;
}

int main()
{
    //automatically construct a initializer_list object and copy it
    S<int> s = {1, 2, 3, 4, 5}; 
    
    //list-initialization in function call
    s.append({6, 7, 8});
    
    // tmp_T----> pair<const int*, size_t>
    cout << "The vector size is now " << s.c_arr().second << " ints:" << endl;
    for (auto n : s.v)
        cout << ' ' << n;
    cout << endl;
    cout << "range-for over brace-init-list: " << endl;
    for (auto x : {-1, -2, 03}) //// the rule for auto makes this ranged for work
        cout << x << " ";
    cout << endl;

    auto al = {10, 11, 12}; //special rule for auto
    cout << "The list bound to auto has size() = " << al.size() << endl;
    //templated_fn({1, 2, 3});   //compiler error! "{1, 2, 3}" is not an expressionit has no type, and so T cannot be duduced.

    templated_fn<initializer_list<int>>({7, 8, 9}); //ok
    templated_fn<vector<int>>({3, 5, 7});           //also ok

    return 0;
}
