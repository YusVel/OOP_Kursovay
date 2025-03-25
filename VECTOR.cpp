#include "VECTOR.h"
#include <iostream>
#define DEBUG_MODE 1


template<typename T>
VECTOR<T>::VECTOR():capacity(10),size(0){
    if(DEBUG_MODE){std::cout<<"Конструктор по умолчанию: "<<this<<std::endl;}
    arr = new T[capacity];
}

template<typename T>
VECTOR<T>::VECTOR(const unsigned long capacity_):capacity(capacity_+10),size(0)
{
    arr = new T[capacity];
}


template<typename T>
VECTOR<T>::VECTOR(VECTOR &other) {
    if(DEBUG_MODE){std::cout<<"Конструктор копирования: "<<this<<std::endl;}
    if(this->capacity<other.size) {
        delete [](this->arr);
        arr = new T[this->capacity = (other.size+other.size/3)+10];
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
        T *temp = new T[this->capacity+=capacity/3+10];
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
void VECTOR<T>::erase(const unsigned long index)
{
     if(DEBUG_MODE){std::cout<<"erase(): "<<this<<std::endl;}
    auto iterator = this->begin();
    iterator+=index;
    for(;iterator<this->end()-1;++iterator)
    {
        *iterator = *(iterator+1);
    }
    --(this->size);
}

template<typename T>
void VECTOR<T>::insert(const unsigned long index,const T&item)
{
    if(DEBUG_MODE){std::cout<<"insert(): "<<this<<std::endl;}
    auto iterator = this->begin();
    iterator+=index;
    if(this->size<this->capacity)
    {
        for(auto i = this->end();i>iterator;--i)
        {
            *i = *(i-1);
        }
        ++(this->size);
        *iterator=item;
    }else {
        this->relocate(this->capacity+=this->capacity/3+10);
        for(auto i = this->end();i>iterator;--i)
        {
            *i = *(i-1);
        }
        ++(this->size);
        *iterator=item;
    }

}

template<typename T>
typename VECTOR<T>::ITERATOR VECTOR<T>::begin()
{
    return VECTOR<T>::ITERATOR(this->arr,this);
}

template<typename T>
typename VECTOR<T>::ITERATOR VECTOR<T>::end()
{
    return VECTOR<T>::ITERATOR((this->arr+this->size),this);
}

template<typename T>
void VECTOR<T>::relocate(const unsigned long newSize)
{
    T *temp = new T[this->capacity = (newSize+newSize/3+10)];
    for(int i = 0;i<(this->size<newSize?this->size:newSize);++i)
    {
        temp[i] = (this->arr)[i];
    }
    delete [](this->arr);
    this->arr = temp;
    this->size = (this->size<newSize?:newSize);
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
    } else if(this->iter>=this->pointerVECTOR->end()){
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
    if(DEBUG_MODE){std::cout<<"Декримент VECTOR<T>::ITERATOR& VECTOR<T>::ITERATOR::operator--()\n"<<std::endl;}
    if(this->iter==nullptr) {
        if(DEBUG_MODE){std::cout<<"Segmentation fault. VECTOR<T>::ITERATOR указывает на NULL.\n"<<std::endl;}
        throw "Segmentation fault. VECTOR<T>::ITERATOR указывает на NULL.\n";
    } else if(this->iter>this->pointerVECTOR->end()){
        if(DEBUG_MODE){std::cout<<"Segmentation fault. VECTOR<T>::ITERATOR указывает на несуществующий элемент массива, Iterator>=&(arr[size]).\n"<<std::endl;}
        throw "Segmentation fault. VECTOR<T>::ITERATOR указывает на несуществующий элемент массива, Iterator>&(arr[size]).\n";
    }else if(this->iter<=(this->pointerVECTOR)->arr){
        if(DEBUG_MODE){std::cout<<"Segmentation fault. VECTOR<T>::ITERATOR указывает на несуществующий элемент массива.Iterator<arr\n"<<std::endl;}
        throw "Segmentation fault. VECTOR<T>::ITERATOR указывает на несуществующий элемент массива.Iterator<=arr\n";
    }
    return --(this->iter);
}


template<typename T>
typename VECTOR<T>::ITERATOR VECTOR<T>::ITERATOR::operator=(ITERATOR &other)
{
    if(DEBUG_MODE){std::cout<<"Оператор присваивания VECTOR<T>ITERATOT"<<std::endl;}
    this->iter = other.iter;
    this->pointerVECTOR = other.pointerVECTOR;
    return *this;
}

template<typename T>
VECTOR<T>::ITERATOR::ITERATOR(T *iter_, VECTOR<T> *pointerVECTOR_)
{
    this->iter = iter_;
    this->pointerVECTOR = pointerVECTOR_;
}

template<typename T>
bool VECTOR<T>::ITERATOR::operator>(ITERATOR &other){
    if(this->pointerVECTOR!=other.pointerVECTOR){
        throw "ERROR: Сравниваемые итераторы принадлежат разным векторам!\n";
    }
    return this->iter>other.iter;
}

template<typename T>
bool VECTOR<T>::ITERATOR::operator<(ITERATOR &other){
    if(this->pointerVECTOR!=other.pointerVECTOR){
        throw "ERROR: Сравниваемые итераторы принадлежат разным векторам!\n";
    }
    return this->iter<other.iter;
}
template<typename T>
bool VECTOR<T>::ITERATOR::operator<=(ITERATOR &other){
    if(this->pointerVECTOR!=other.pointerVECTOR){
        throw "ERROR: Сравниваемые итераторы принадлежат разным векторам!\n";
    }
    return this->iter<=other.iter;
}

template<typename T>
bool VECTOR<T>::ITERATOR::operator>=(ITERATOR &other){
    if(this->pointerVECTOR!=other.pointerVECTOR){
        throw "ERROR: Сравниваемые итераторы принадлежат разным векторам!\n";
    }
    return this->iter>=other.iter;
}

template<typename T>
typename VECTOR<T>::ITERATOR &VECTOR<T>::ITERATOR::operator-(const unsigned long offset)
{
    if(DEBUG_MODE){std::cout<<"Декримент VECTOR<T>::ITERATOR& VECTOR<T>::ITERATOR::operator-(offset)\n"<<std::endl;}
    if(this->iter==nullptr) {
        if(DEBUG_MODE){std::cout<<"Segmentation fault. VECTOR<T>::ITERATOR указывает на NULL.\n"<<std::endl;}
        throw "Segmentation fault. VECTOR<T>::ITERATOR указывает на NULL.\n";
    } else if(this->iter-offset>this->pointerVECTOR->end()){
        if(DEBUG_MODE){std::cout<<"Segmentation fault. VECTOR<T>::ITERATOR указывает на несуществующий элемент массива, Iterator>=&(arr[size]).\n"<<std::endl;}
        throw "Segmentation fault. VECTOR<T>::ITERATOR указывает на несуществующий элемент массива, Iterator-offset>&(arr[size]).\n";
    }else if(this->iter-offset<(this->pointerVECTOR)->arr){
        if(DEBUG_MODE){std::cout<<"Segmentation fault. VECTOR<T>::ITERATOR указывает на несуществующий элемент массива.Iterator<arr\n"<<std::endl;}
        throw "Segmentation fault. VECTOR<T>::ITERATOR указывает на несуществующий элемент массива.Iterator-offset<arr\n";
    }
    return (this->iter-offset);
}

template<typename T>
typename VECTOR<T>::ITERATOR &VECTOR<T>::ITERATOR::operator+(const unsigned long offset)
{
    if(DEBUG_MODE){std::cout<<"Декримент VECTOR<T>::ITERATOR& VECTOR<T>::ITERATOR::operator+(offset)\n"<<std::endl;}
    if(this->iter==nullptr) {
        if(DEBUG_MODE){std::cout<<"Segmentation fault. VECTOR<T>::ITERATOR указывает на NULL.\n"<<std::endl;}
        throw "Segmentation fault. VECTOR<T>::ITERATOR указывает на NULL.\n";
    } else if(this->iter+offset>=this->pointerVECTOR->end()){
        if(DEBUG_MODE){std::cout<<"Segmentation fault. VECTOR<T>::ITERATOR указывает на несуществующий элемент массива, Iterator>=&(arr[size]).\n"<<std::endl;}
        throw "Segmentation fault. VECTOR<T>::ITERATOR указывает на несуществующий элемент массива, Iterator+offset=>&(arr[size]).\n";
    }else if(this->iter+offset<(this->pointerVECTOR)->arr){
        if(DEBUG_MODE){std::cout<<"Segmentation fault. VECTOR<T>::ITERATOR указывает на несуществующий элемент массива.Iterator<arr\n"<<std::endl;}
        throw "Segmentation fault. VECTOR<T>::ITERATOR указывает на несуществующий элемент массива.Iterator+offset<=arr\n";
    }
    return (this->iter+offset);
}

template<typename T>
T &VECTOR<T>::ITERATOR::operator*()
{
    if(this->iter==nullptr){
        throw "Попытка разыменовать nullpoiter.\n";
    }
    return *(this->iter);
}

template<typename T>
typename VECTOR<T>::ITERATOR &VECTOR<T>::ITERATOR::operator-=(const unsigned long offset)
{
    return operator-(offset);
}

template<typename T>
typename VECTOR<T>::ITERATOR &VECTOR<T>::ITERATOR::operator+=(const unsigned long offset)
{
    return operator+(offset);
}

template<typename T>
bool VECTOR<T>::ITERATOR::operator==(ITERATOR &other){
    if(this->pointerVECTOR!=other.pointerVECTOR){
        throw "ERROR: Сравниваемые итераторы принадлежат разным векторам!\n";
    }
    return this->iter==other.iter;
}

template<typename T>
bool VECTOR<T>::ITERATOR::operator!=(ITERATOR &other){
    if(this->pointerVECTOR!=other.pointerVECTOR){
        throw "ERROR: Сравниваемые итераторы принадлежат разным векторам!\n";
    }
    return this->iter!=other.iter;
}
