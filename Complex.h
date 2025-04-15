#ifndef COMPLEX_H
#define COMPLEX_H
const int N = 10;
const double PI = 3.1415926535897;
//float sin(float x);
//float cos(float x);

#include <iostream>
#include <cmath>

struct Complex{
    float rel=0;
    float img=0;
    Complex(float a=0, float b=0):rel(a) , img(b){};

    Complex Conjugate();
    Complex operator+(Complex other);
    void operator+=(Complex other);
    Complex operator-(Complex other);
    Complex operator*(Complex other);
    void operator*=(Complex other);
    Complex operator*(float other);
    Complex operator/(Complex other);
    Complex operator/(float other);
    friend std::ostream& operator<<(std::ostream& os, const Complex& z){
        os <<z.rel<<" +i "<<z.img <<"\t";
        return os;
    };
};
Complex ComplexExp(double theata);



#endif // COMPLEX_H
