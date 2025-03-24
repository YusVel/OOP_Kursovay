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
        VECTOR<T>::ITERATOR& operator++();
        VECTOR<T>::ITERATOR& operator--();
    };

public:
    VECTOR();
    VECTOR(VECTOR &other);
    ~VECTOR();
    void push_back(const T &item);
};

#endif // VECTOR_H
