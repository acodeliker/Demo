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






/////////////////////////////////////////////////////////////////////////////////

#endif