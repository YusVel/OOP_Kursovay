#ifndef VECTOR_H
#define VECTOR_H
#include <QWidget>
#define DEBUG_MODE 1


template<typename T>
class VECTOR
{
private:
    T *arr{nullptr};
    unsigned long size;
    unsigned long capacity;
public:
    VECTOR():capacity(10),size(0){
        if(DEBUG_MODE){qDebug()<<"Конструктор по умолчанию: "<<this;}
        arr = new T[capacity];
    }
    VECTOR(const unsigned long capacity_):capacity(capacity_+10),size(0)
    {
        if(DEBUG_MODE){qDebug()<<"Конструктор VECTOR(const unsigned long capacity_);: "<<this;}
        arr = new T[capacity];
    }
    VECTOR(VECTOR &other);
    ~VECTOR()
    {
        if(DEBUG_MODE){qDebug()<<"Деструктор ~VECTOR(): "<<this;}
        if(arr!=nullptr) {
            delete [] arr;
        }
    }
    void push_back(const T &item);
    void pop_back();//todo
    void erase(const unsigned long index);
    void insert(const unsigned long index, const T&item);
    class ITERATOR{
    private:
        T *iter;
        VECTOR<T> *pointerVECTOR;
    public:
        ITERATOR();
        ITERATOR(ITERATOR &other);
        ITERATOR(T *iter_,VECTOR<T> *pointerVECTOR_);
        VECTOR<T>::ITERATOR operator=(ITERATOR &other);
        VECTOR<T>::ITERATOR& operator++();
        VECTOR<T>::ITERATOR& operator--();
        bool operator>(ITERATOR &other);
        bool operator<(ITERATOR &other);
        bool operator>=(ITERATOR &other);
        bool operator<=(ITERATOR &other);
        bool operator==(ITERATOR &other);
        bool operator!=(ITERATOR &other);
        VECTOR<T>::ITERATOR& operator-(const unsigned long offset);
        VECTOR<T>::ITERATOR& operator+(const unsigned long offset);
        VECTOR<T>::ITERATOR& operator-=(const unsigned long offset);
        VECTOR<T>::ITERATOR& operator+=(const unsigned long offset);
        T&operator*();
        ~ITERATOR(){if(DEBUG_MODE){qDebug()<<"Конструктор ITERATOR(T *iter_, VECTOR<T> *pointerVECTOR_)"<<this;}}
    };
    VECTOR<T>::ITERATOR begin();
    VECTOR<T>::ITERATOR end();
private:
    void relocate(const unsigned long newSize);
};

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
VECTOR<T>::ITERATOR::ITERATOR():iter(nullptr),pointerVECTOR(nullptr){
    if(DEBUG_MODE){qDebug()<<"Конструктор по умолчанию VECTOR<T>ITERATOT"<<this;}
}

template<typename T>
VECTOR<T>::ITERATOR::ITERATOR(ITERATOR &other){
    if(DEBUG_MODE){qDebug()<<"Конструктор копирования VECTOR<T>ITERATOT"<<this;}
    this->iter = other.iter;
    this->pointerVECTOR = other.pointerVECTOR;
}

template<typename T>
VECTOR<T>::ITERATOR::ITERATOR(T *iter_, VECTOR<T> *pointerVECTOR_)
{
    if(DEBUG_MODE){qDebug()<<"Конструктор ITERATOR(T *iter_, VECTOR<T> *pointerVECTOR_)"<<this;}
    this->iter = iter_;
    this->pointerVECTOR = pointerVECTOR_;
}
#endif // VECTOR_H
