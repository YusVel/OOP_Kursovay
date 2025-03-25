#ifndef VECTOR_H
#define VECTOR_H

template<typename T>
class VECTOR
{
private:
    T *arr{nullptr};
    unsigned long size;
    unsigned long capacity;

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
    };

public:
    VECTOR();
    VECTOR(const unsigned long capacity_);
    VECTOR(VECTOR &other);
    ~VECTOR();
    void push_back(const T &item);
    void pop_back();//todo
    void erase(const unsigned long index);
    void insert(const unsigned long index, const T&item);//todo
    VECTOR<T>::ITERATOR begin();
    VECTOR<T>::ITERATOR end();
private:
    void relocate(const unsigned long newSize);
};

#endif // VECTOR_H
