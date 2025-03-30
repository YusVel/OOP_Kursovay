#define DEBUG_MODE 0
#include <QWidget>

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
        ~ITERATOR(){if(DEBUG_MODE){qDebug()<<"Деструктор ~ITERATOR() : "<<this;}}
        T* getRowPointer(){return this->iter; }
        VECTOR<T>::ITERATOR& operator=(ITERATOR other);
        VECTOR<T>::ITERATOR& operator++();
        VECTOR<T>::ITERATOR& operator--();
        bool operator>(ITERATOR other);
        bool operator<(ITERATOR other);
        bool operator>=(ITERATOR other);
        bool operator<=(ITERATOR other);
        bool operator==(ITERATOR other);
        bool operator!=(ITERATOR other);
        VECTOR<T>::ITERATOR operator-(const unsigned long offset);
        VECTOR<T>::ITERATOR operator+(const unsigned long offset);
        VECTOR<T>::ITERATOR& operator-=(const unsigned long offset);
        VECTOR<T>::ITERATOR& operator+=(const unsigned long offset);
        T&operator*();
    };


public:
    VECTOR();
    VECTOR(const unsigned long capacity_);
    VECTOR(VECTOR &other);
    ~VECTOR();
    unsigned long getSize();
    unsigned long getCapacity();
    void push_back(const T &item);
    void pop_back();
    void erase(const unsigned long index);
    void insert(const unsigned long index, const T&item);
    VECTOR<T>::ITERATOR begin();
    VECTOR<T>::ITERATOR end();
    void sort_increase(int parametr=-1);//todo
    void sort_decrease(int parametr=-1);//todo
    T&operator[]( const long index);

private:
    void relocate(const unsigned long newSize);
    bool makeMaxParentBySwap(T&parent, T&leftChild, T&rightChild);
    void makeHeap(int &lastParentIndex);
};
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////


template<typename T>
VECTOR<T>::VECTOR():capacity(10),size(0){
    if (DEBUG_MODE) {
        qDebug() << "Конструктор по умолчанию: " << this;
    }
    arr = new T[capacity];
}

template<typename T>
VECTOR<T>::VECTOR(const unsigned long capacity_):capacity(capacity_+5),size(0){\
        if (DEBUG_MODE) {
        qDebug() << "Конструктор VECTOR(const unsigned long capacity_): " << this;
    }
    arr = new T[capacity];
}


template<typename T>
VECTOR<T>::VECTOR(VECTOR &other) {
    if(DEBUG_MODE){qDebug()<<"Конструктор копирования: "<<this;}
    if(this->capacity<other.size) {
        delete [](this->arr);
        arr = new T[this->capacity = (other.size+other.size/3)+5];
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
    if(DEBUG_MODE){qDebug()<<"Деструктор ~VECTOR(): "<<this;}
    if(arr!=nullptr) {
        delete [] arr;
    }
}

template<typename T>
inline unsigned long VECTOR<T>::getSize(){
    return this->size;
}

template<typename T>
inline unsigned long VECTOR<T>::getCapacity(){
    return this->capacity;
}

template<typename T>
void VECTOR<T>::push_back(const T &item)
{
    if(this->size<this->capacity){
        if(DEBUG_MODE){qDebug()<<"push_back(): "<<this;}
        arr[size++] = item;
    }else {
        if(DEBUG_MODE){qDebug()<<"Релокация после push_back(): "<<this;}
        T *temp = new T[this->capacity+=capacity/3+5];
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
inline void VECTOR<T>::pop_back()
{
    if(this->size==0){
        throw "ERROR: pop_back(); VECTOR::size = 0";
    }
    --size;
}

template<typename T>
void VECTOR<T>::erase(const unsigned long index)
{
    if(DEBUG_MODE){qDebug()<<"erase(): "<<this;}
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
    if(DEBUG_MODE){qDebug()<<"insert(): "<<this;}
    auto iterator = this->begin();
    iterator+=index;
    if(this->size<this->capacity)
    {
         ++(this->size);
        for(auto i = this->end();i>iterator;--i)
        {
            *i = *(i-1);
        }
        *iterator=item;
    }else {
        this->relocate(this->capacity+=this->capacity/3+5);
        iterator = this->begin();
        iterator+=index;
        ++(this->size);
        for(auto i = this->end();i>iterator;--i)
        {
            *i = *(i-1);
        }
        *iterator=item;
    }

}

template<typename T>
typename VECTOR<T>::ITERATOR VECTOR<T>::begin(){
    if(DEBUG_MODE){qDebug()<<"begin(): "<<this;}
    return VECTOR<T>::ITERATOR(this->arr,this);
}

template<typename T>
typename VECTOR<T>::ITERATOR VECTOR<T>::end(){
    if(DEBUG_MODE){qDebug()<<"end(): "<<this;}
    return VECTOR<T>::ITERATOR((this->arr+this->size),this);
}

template<typename T>
inline void VECTOR<T>::sort_increase(int parametr)
{
    int lastParentIndex;
    if((size-1)%2==0){lastParentIndex=(size-1-2)/2;}
    else{lastParentIndex=(size-1-1)/2;}
    makeHeap(lastParentIndex);
/*
    long sortindexes = 1;
    while(this->size-sortindexes>0)
    {
        makeMaxParentBySwap(this->arr[size-sortindexes],this->arr[1],this->arr[1]);
        while()
        {
            //todo;
        }
    }
*/

}

template<typename T>
void VECTOR<T>::relocate(const unsigned long newSize)
{
    T *temp = new T[this->capacity = (newSize+newSize/3)];
    for(int i = 0;i<(this->size<newSize?this->size:newSize);++i)
    {
        temp[i] = (this->arr)[i];
    }
    delete [](this->arr);
    this->arr = temp;
    this->size = (this->size<newSize? this->size:newSize);
}

template<typename T>
inline  bool VECTOR<T>::makeMaxParentBySwap(T &parent, T &leftChild, T &rightChild){
    T max =(parent>leftChild?(parent>rightChild?parent:rightChild):(leftChild>rightChild?leftChild:rightChild));
    if(max==leftChild)
    {
        leftChild=parent;
        parent = max;
        return true;
    }
    else if(max==rightChild)
    {
        rightChild=parent;
        parent = max;
        return true;
    }
    return false;
}

template<typename T>
inline void VECTOR<T>::makeHeap(int &lastParentIndex)
{
    long index = lastParentIndex;
    if((size-1)%2==0)
    {
        while(index>=0)
        {
            makeMaxParentBySwap(this->arr[index],arr[index*2+1],arr[index*2+2]);
            --index;
        }
    }
    else
    {
        if(index==lastParentIndex){
            makeMaxParentBySwap(this->arr[index],arr[index*2+1],arr[index*2+1]);
            --index;
        }
        while(index>=0)
        {
            makeMaxParentBySwap(this->arr[index],arr[index*2+1],arr[index*2+2]);
            --index;
        }
    }
}

template<typename T>
inline T &VECTOR<T>::operator[](const long index)
{
    return (this->arr[index]);
}

template<typename T>
VECTOR<T>::ITERATOR::ITERATOR():iter(nullptr),pointerVECTOR(nullptr){
    if(DEBUG_MODE){qDebug()<<"Конструктор по умолчанию VECTOR<T>::ITERATOT"<<this;}
}

template<typename T>
VECTOR<T>::ITERATOR::ITERATOR(ITERATOR &other){
    if(DEBUG_MODE){qDebug()<<"Конструктор копирования ITERATOR(ITERATOR &other)"<<this;}
    this->iter = other.iter;
    this->pointerVECTOR = other.pointerVECTOR;
}

template<typename T>
typename VECTOR<T>::ITERATOR& VECTOR<T>::ITERATOR::operator++()
{
    if(DEBUG_MODE){qDebug()<<"Инкримент VECTOR<T>::ITERATOR& VECTOR<T>::ITERATOR::operator++() ";}
    if(this->iter==nullptr) {
        if(DEBUG_MODE){qDebug()<<"Segmentation fault. VECTOR<T>::ITERATOR указывает на NULL.";}
        throw "Segmentation fault. VECTOR<T>::ITERATOR указывает на NULL.";
    } else if(this->iter>=this->pointerVECTOR->end().iter){
        if(DEBUG_MODE){qDebug()<<"Segmentation fault. VECTOR<T>::ITERATOR указывает на несуществующий элемент массива, Iterator>=&(arr[size]).";}
        throw "Segmentation fault. VECTOR<T>::ITERATOR указывает на несуществующий элемент массива, Iterator>=&(arr[size]).";
    }else if(this->iter<(this->pointerVECTOR)->arr){
        if(DEBUG_MODE){qDebug()<<"Segmentation fault. VECTOR<T>::ITERATOR указывает на несуществующий элемент массива.Iterator<arr";}
        throw "Segmentation fault. VECTOR<T>::ITERATOR указывает на несуществующий элемент массива.Iterator<arr";
    }
    this->iter+=1;
    return *this;
}

template<typename T>
typename VECTOR<T>::ITERATOR &VECTOR<T>::ITERATOR::operator--()
{
    if(DEBUG_MODE){qDebug()<<"Декримент VECTOR<T>::ITERATOR& VECTOR<T>::ITERATOR::operator--()";}
    if(this->iter==nullptr) {
        if(DEBUG_MODE){qDebug()<<"Segmentation fault. VECTOR<T>::ITERATOR указывает на NULL.";}
        throw "Segmentation fault. VECTOR<T>::ITERATOR указывает на NULL.";
    } else if(this->iter>this->pointerVECTOR->end().iter){
        if(DEBUG_MODE){qDebug()<<"Segmentation fault. VECTOR<T>::ITERATOR указывает на несуществующий элемент массива, Iterator>=&(arr[size]).";}
        throw "Segmentation fault. VECTOR<T>::ITERATOR указывает на несуществующий элемент массива, Iterator>&(arr[size]).";
    }else if(this->iter<=(this->pointerVECTOR)->arr){
        if(DEBUG_MODE){qDebug()<<"Segmentation fault. VECTOR<T>::ITERATOR указывает на несуществующий элемент массива.Iterator<arr";}
        throw "Segmentation fault. VECTOR<T>::ITERATOR указывает на несуществующий элемент массива.Iterator<=arr";
    }
    this->iter-=1;
    return *this;
}


template<typename T>
typename VECTOR<T>::ITERATOR& VECTOR<T>::ITERATOR::operator=(ITERATOR other)
{
    if(DEBUG_MODE){qDebug()<<"Оператор присваивания VECTOR<T>ITERATOT";}
    this->iter = other.iter;
    this->pointerVECTOR = other.pointerVECTOR;
    return *this;
}

template<typename T>
VECTOR<T>::ITERATOR::ITERATOR(T *iter_, VECTOR<T> *pointerVECTOR_)
{
     if(DEBUG_MODE){qDebug()<<"Конструктор ITERATOR(T *iter_, VECTOR<T> *pointerVECTOR_)"<<this;}
    this->iter = iter_;
    this->pointerVECTOR = pointerVECTOR_;
}

template<typename T>
bool VECTOR<T>::ITERATOR::operator>(VECTOR<T>::ITERATOR other){
    if(this->pointerVECTOR!=other.pointerVECTOR){
        throw "ERROR: Сравниваемые итераторы принадлежат разным векторам!";
    }
    return (this->iter>other.iter);
}

template<typename T>
bool VECTOR<T>::ITERATOR::operator<(VECTOR<T>::ITERATOR other){
    if(this->pointerVECTOR!=other.pointerVECTOR){
        throw "ERROR: Сравниваемые итераторы принадлежат разным векторам!";
    }
    return this->iter<other.iter;
}
template<typename T>
bool VECTOR<T>::ITERATOR::operator<=(VECTOR<T>::ITERATOR other){
    if(this->pointerVECTOR!=other.pointerVECTOR){
        throw "ERROR: Сравниваемые итераторы принадлежат разным векторам!";
    }
    return this->iter<=other.iter;
}

template<typename T>
bool VECTOR<T>::ITERATOR::operator>=(VECTOR<T>::ITERATOR other){
    if(this->pointerVECTOR!=other.pointerVECTOR){
        throw "ERROR: Сравниваемые итераторы принадлежат разным векторам!";
    }
    return this->iter>=other.iter;
}

template<typename T>
typename VECTOR<T>::ITERATOR VECTOR<T>::ITERATOR::operator-(const unsigned long offset)
{
    if(DEBUG_MODE){qDebug()<<"Перегрузка оператора ITERATOR::operator-(offset)";}
    if(this->iter==nullptr) {
        if(DEBUG_MODE){qDebug()<<"Segmentation fault. VECTOR<T>::ITERATOR указывает на NULL.";}
        throw "Segmentation fault. VECTOR<T>::ITERATOR указывает на NULL.";
    } else if(this->iter-offset>this->pointerVECTOR->end().iter){
        if(DEBUG_MODE){qDebug()<<"Segmentation fault. VECTOR<T>::ITERATOR указывает на несуществующий элемент массива, Iterator>=&(arr[size]).";}
        throw "Segmentation fault. VECTOR<T>::ITERATOR указывает на несуществующий элемент массива, Iterator-offset>&(arr[size]).";
    }else if(this->iter-offset<(this->pointerVECTOR)->begin().iter){
        if(DEBUG_MODE){qDebug()<<"Segmentation fault. VECTOR<T>::ITERATOR указывает на несуществующий элемент массива.Iterator<arr";}
        throw "Segmentation fault. VECTOR<T>::ITERATOR указывает на несуществующий элемент массива.Iterator-offset<arr";
    }
    auto temp = *this;
    temp.iter -=offset;
    return temp;
}

template<typename T>
typename VECTOR<T>::ITERATOR VECTOR<T>::ITERATOR::operator+(const unsigned long offset)
{
    if(DEBUG_MODE){qDebug()<<"Декримент VECTOR<T>::ITERATOR& VECTOR<T>::ITERATOR::operator+(offset)";}
    if(this->iter==nullptr) {
        if(DEBUG_MODE){qDebug()<<"Segmentation fault. VECTOR<T>::ITERATOR указывает на NULL.";}
        throw "Segmentation fault. VECTOR<T>::ITERATOR указывает на NULL.";
    } else if(this->iter+offset>=this->pointerVECTOR->end().iter){
        if(DEBUG_MODE){qDebug()<<"Segmentation fault. VECTOR<T>::ITERATOR указывает на несуществующий элемент массива, Iterator>=&(arr[size]).";}
        throw "Segmentation fault. VECTOR<T>::ITERATOR указывает на несуществующий элемент массива, Iterator+offset=>&(arr[size]).";
    }else if(this->iter+offset<(this->pointerVECTOR)->arr){
        if(DEBUG_MODE){qDebug()<<"Segmentation fault. VECTOR<T>::ITERATOR указывает на несуществующий элемент массива.Iterator<arr";}
        throw "Segmentation fault. VECTOR<T>::ITERATOR указывает на несуществующий элемент массива.Iterator+offset<=arr";
    }
    auto temp = *this;
    temp.iter +=offset;
    return temp;
}

template<typename T>
T &VECTOR<T>::ITERATOR::operator*()
{
    if(this->iter==nullptr){
        throw "ERROR:operator*() Попытка разыменовать nullpoiter.\n";
    }else if(this->iter>this->pointerVECTOR->begin().iter+(this->pointerVECTOR->size)){
        throw "ERROR:operator*() Segmentation fault.";
    }
    return *(this->iter);
}

template<typename T>
typename VECTOR<T>::ITERATOR &VECTOR<T>::ITERATOR::operator-=(const unsigned long offset)
{
    if(DEBUG_MODE){qDebug()<<"Перегрузка оператора ITERATOR::operator-=(offset)";}
    if(this->iter==nullptr) {
        if(DEBUG_MODE){qDebug()<<"Segmentation fault. VECTOR<T>::ITERATOR указывает на NULL.";}
        throw "Segmentation fault. VECTOR<T>::ITERATOR указывает на NULL.";
    } else if(this->iter-offset>this->pointerVECTOR->end().iter){
        if(DEBUG_MODE){qDebug()<<"Segmentation fault. VECTOR<T>::ITERATOR указывает на несуществующий элемент массива, Iterator>=&(arr[size]).";}
        throw "Segmentation fault. VECTOR<T>::ITERATOR указывает на несуществующий элемент массива, Iterator-offset>&(arr[size]).";
    }else if(this->iter-offset<(this->pointerVECTOR)->begin().iter){
        if(DEBUG_MODE){qDebug()<<"Segmentation fault. VECTOR<T>::ITERATOR указывает на несуществующий элемент массива.Iterator<arr";}
        throw "Segmentation fault. VECTOR<T>::ITERATOR указывает на несуществующий элемент массива.Iterator-offset<arr";
    }
    this->iter-=offset;
    return *this;
}

template<typename T>
typename VECTOR<T>::ITERATOR &VECTOR<T>::ITERATOR::operator+=(const unsigned long offset)
{
    if(DEBUG_MODE){qDebug()<<"Декримент VECTOR<T>::ITERATOR& VECTOR<T>::ITERATOR::operator+=(offset)";}
    if(this->iter==nullptr) {
        if(DEBUG_MODE){qDebug()<<"Segmentation fault. VECTOR<T>::ITERATOR указывает на NULL.";}
        throw "Segmentation fault. VECTOR<T>::ITERATOR указывает на NULL.";
    } else if(this->iter+offset>=this->pointerVECTOR->end().iter){
        if(DEBUG_MODE){qDebug()<<"Segmentation fault. VECTOR<T>::ITERATOR указывает на несуществующий элемент массива, Iterator>=&(arr[size]).";}
        throw "Segmentation fault. VECTOR<T>::ITERATOR указывает на несуществующий элемент массива, Iterator+offset=>&(arr[size]).";
    }else if(this->iter+offset<(this->pointerVECTOR)->arr){
        if(DEBUG_MODE){qDebug()<<"Segmentation fault. VECTOR<T>::ITERATOR указывает на несуществующий элемент массива.Iterator<arr";}
        throw "Segmentation fault. VECTOR<T>::ITERATOR указывает на несуществующий элемент массива.Iterator+offset<=arr";
    }
    this->iter+=offset;
    return *this;
}

template<typename T>
bool VECTOR<T>::ITERATOR::operator==(ITERATOR other){
    if(this->pointerVECTOR!=other.pointerVECTOR){
        throw "ERROR: Сравниваемые итераторы принадлежат разным векторам!\n";
    }
    return this->iter==other.iter;
}

template<typename T>
bool VECTOR<T>::ITERATOR::operator!=(ITERATOR other){
    if(this->pointerVECTOR!=other.pointerVECTOR){
        throw "ERROR: Сравниваемые итераторы принадлежат разным векторам!\n";
    }
    return this->iter!=other.iter;
}

#endif // VECTOR_H
