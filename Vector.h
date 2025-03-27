#ifndef VECTOR_H
#define VECTOR_H

template <typename T>
struct Vec{
    T data;
    Vec* prev;
    Vec* next;
    Vec(T d,Vec* p=nullptr,Vec* ne=nullptr):data(d), prev(p),next(ne) {};
    ~Vec(){prev= nullptr; if(!next){delete (*next);}next=nullptr;}
    Vec* operator[](int n){if(n==0){return this;} if((!next)||(n<0)) throw -1; return(*this)[n-1];}
    void push(T d ){Vec* A = new Vec<T>(data,this,next);data=d;next = A;}
};//nie wiem jak zrobic templaty w roznych plikach wiec tu definiuje ale to male rzeczy


#endif // VECTOR_H
