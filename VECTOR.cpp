#include "VECTOR.h"
#include <iostream>
#define DEBUG_MODE 1


template<typename T>
VECTOR<T>::VECTOR():capacity(10),size(0){
    if(DEBUG_MODE){std::cout<<"Конструктор по умолчанию: "<<this<<std::endl;}
    arr = new T[capacity];
}

template<typename T>
VECTOR<T>::VECTOR(VECTOR &other) {
    if(DEBUG_MODE){std::cout<<"Конструктор копирования: "<<this<<std::endl;}
    if(this->capacity<other.size) {
        delete [](this->arr);
        arr = new T[this->capacity = (other.size+other.size/3)];
        this->size = other.size;
        for(int i=0;i<this->size;++i)
        {
            this->arr[i] = other.arr[i];
        }
    } else {
        for(int i=0;i<other.size;++i)
        {
            this->arr[i] = other.arr[i];
        }
    }
}

template<typename T>
VECTOR<T>::~VECTOR()
{
    if(DEBUG_MODE){std::cout<<"Деструктор: "<<this<<std::endl;;}
    if(arr!=nullptr) {
        delete [] arr;
    }
}

template<typename T>
void VECTOR<T>::push_back(const T &item)
{
    if(this->size<this->capacity){
         if(DEBUG_MODE){std::cout<<"push_back(): "<<this<<std::endl;;}
        arr[size++] = item;
    }else {
         if(DEBUG_MODE){std::cout<<"Релокация после push_back(): "<<this<<std::endl;}
        T *temp = new T[this->capacity+=capacity/3];
        for(int i = 0; i<this->size;++i)
        {
            temp[i] = this->arr[i];
        }
        temp[(this->size)++] = item;
        delete [](this->arr);
        this->arr = temp;
    }

}

template<typename T>
VECTOR<T>::ITERATOR::ITERATOR():iter(nullptr),pointerVECTOR(nullptr){
    if(DEBUG_MODE){std::cout<<"Конструктор по умолчанию VECTOR<T>ITERATOT"<<this<<std::endl;}
}

template<typename T>
VECTOR<T>::ITERATOR::ITERATOR(ITERATOR &other){
    if(DEBUG_MODE){std::cout<<"Конструктор копирования VECTOR<T>ITERATOT"<<this<<std::endl;}
    this->iter = other.iter;
    this->pointerVECTOR = other.pointerVECTOR;
}

template<typename T>
typename VECTOR<T>::ITERATOR& VECTOR<T>::ITERATOR::operator++()
{
    if(DEBUG_MODE){std::cout<<"Инкримент VECTOR<T>::ITERATOR& VECTOR<T>::ITERATOR::operator++() "<<std::endl;}
    if(this->iter==nullptr) {
        if(DEBUG_MODE){std::cout<<"Segmentation fault. VECTOR<T>::ITERATOR указывает на NULL.\n"<<std::endl;}
        throw "Segmentation fault. VECTOR<T>::ITERATOR указывает на NULL.\n";
    } else if(this->iter>=&((this->pointerVECTOR)->arr[this->pointerVECTOR->size])){
        if(DEBUG_MODE){std::cout<<"Segmentation fault. VECTOR<T>::ITERATOR указывает на несуществующий элемент массива, Iterator>=&(arr[size]).\n"<<std::endl;}
        throw "Segmentation fault. VECTOR<T>::ITERATOR указывает на несуществующий элемент массива, Iterator>=&(arr[size]).\n";
    }else if(this->iter<(this->pointerVECTOR)->arr){
        if(DEBUG_MODE){std::cout<<"Segmentation fault. VECTOR<T>::ITERATOR указывает на несуществующий элемент массива.Iterator<arr\n"<<std::endl;}
        throw "Segmentation fault. VECTOR<T>::ITERATOR указывает на несуществующий элемент массива.Iterator<arr\n";
    }
    return ++(this->iter);
}

template<typename T>
typename VECTOR<T>::ITERATOR &VECTOR<T>::ITERATOR::operator--()
{
    if(DEBUG_MODE){std::cout<<"Декримент VECTOR<T>::ITERATOR& VECTOR<T>::ITERATOR::operator++()\n"<<std::endl;}
    if(this->iter==nullptr) {
        if(DEBUG_MODE){std::cout<<"Segmentation fault. VECTOR<T>::ITERATOR указывает на NULL.\n"<<std::endl;}
        throw "Segmentation fault. VECTOR<T>::ITERATOR указывает на NULL.\n";
    } else if(this->iter>&((this->pointerVECTOR)->arr[this->pointerVECTOR->size])){
        if(DEBUG_MODE){std::cout<<"Segmentation fault. VECTOR<T>::ITERATOR указывает на несуществующий элемент массива, Iterator>=&(arr[size]).\n"<<std::endl;}
        throw "Segmentation fault. VECTOR<T>::ITERATOR указывает на несуществующий элемент массива, Iterator>&(arr[size]).\n";
    }else if(this->iter<=(this->pointerVECTOR)->arr){
        if(DEBUG_MODE){std::cout<<"Segmentation fault. VECTOR<T>::ITERATOR указывает на несуществующий элемент массива.Iterator<arr\n"<<std::endl;}
        throw "Segmentation fault. VECTOR<T>::ITERATOR указывает на несуществующий элемент массива.Iterator<=arr\n";
    }
    return --(this->iter);
}
