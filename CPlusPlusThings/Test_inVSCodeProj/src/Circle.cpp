#include "Head.hpp"

// initializer-list
Circle::Circle(double r):radium(r) {
    std::cout << "the first Circle has created!" << std::endl;
    //

};


void Circle::getArea() {
    std::cout << "=======================================" << std::endl;
    double res = 0.0;
    double ra = this->radium;
    res = ra * ra * Pi;
    std::cout << "The area of circle is " << res << std::endl;
    std::cout << "=======================================" << std::endl;

};