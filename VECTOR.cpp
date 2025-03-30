#include "VECTOR.h"
#include "CAR.h"


/*
template<>
class VECTOR<CAR>
{
private:
    CAR *arr{nullptr};
    unsigned long size;
    unsigned long capacity;

    class ITERATOR{
    private:
        CAR *iter;
        VECTOR<CAR> *pointerVECTOR;
    public:
        ITERATOR();
        ITERATOR(ITERATOR &other);
        ITERATOR(CAR *iter_,VECTOR<CAR> *pointerVECTOR_);
        ~ITERATOR(){if(DEBUG_MODE){qDebug()<<"Деструктор ~ITERATOR() : "<<this;}}
        VECTOR<CAR>::ITERATOR& operator=(ITERATOR other);
        VECTOR<CAR>::ITERATOR& operator++();
        VECTOR<CAR>::ITERATOR& operator--();
        bool operator>(ITERATOR other);
        bool operator<(ITERATOR other);
        bool operator>=(ITERATOR other);
        bool operator<=(ITERATOR other);
        bool operator==(ITERATOR other);
        bool operator!=(ITERATOR other);
        VECTOR<CAR>::ITERATOR operator-(const unsigned long offset);
        VECTOR<CAR>::ITERATOR operator+(const unsigned long offset);
        VECTOR<CAR>::ITERATOR& operator-=(const unsigned long offset);
        VECTOR<CAR>::ITERATOR& operator+=(const unsigned long offset);
        CAR&operator*();
    };

public:
    VECTOR();
    VECTOR(const unsigned long capacity_);
    VECTOR(VECTOR &other);
    ~VECTOR();
    void push_back(const CAR &item);
    void pop_back();
    void erase(const unsigned long index);
    void insert(const unsigned long index, const CAR&item);
    VECTOR<CAR>::ITERATOR begin();
    VECTOR<CAR>::ITERATOR end();
    void sort_increase(int parametr=-1);//todo
    void sort_decrease(int parametr=-1);//todo
private:
    void relocate(const unsigned long newSize);
};
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

VECTOR<CAR>::VECTOR():capacity(10),size(0){
    if (DEBUG_MODE) {
        qDebug() << "Конструктор по умолчанию: " << this;
    }
    arr = new CAR[capacity];
}

VECTOR<CAR>::VECTOR(const unsigned long capacity_):capacity(capacity_+5),size(0){\
        if (DEBUG_MODE) {
        qDebug() << "Конструктор VECTOR(const unsigned long capacity_): " << this;
    }
    arr = new CAR[capacity];
}



VECTOR<CAR>::VECTOR(VECTOR &other) {
    if(DEBUG_MODE){qDebug()<<"Конструктор копирования: "<<this;}
    if(this->capacity<other.size) {
        delete [](this->arr);
        arr = new CAR[this->capacity = (other.size+other.size/3)+5];
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

VECTOR<CAR>::~VECTOR()
{
    if(DEBUG_MODE){qDebug()<<"Деструктор ~VECTOR(): "<<this;}
    if(arr!=nullptr) {
        delete [] arr;
    }
}

void VECTOR<CAR>::push_back(const CAR &item)
{
    if(this->size<this->capacity){
        if(DEBUG_MODE){qDebug()<<"push_back(): "<<this;}
        arr[size++] = item;
    }else {
        if(DEBUG_MODE){qDebug()<<"Релокация после push_back(): "<<this;}
        CAR *temp = new CAR[this->capacity+=capacity/3+5];
        for(int i = 0; i<this->size;++i)
        {
            temp[i] = this->arr[i];
        }
        temp[(this->size)++] = item;
        delete [](this->arr);
        this->arr = temp;
    }

}

inline void VECTOR<CAR>::pop_back()
{
    if(this->size==0){
        throw "ERROR: pop_back(); VECTOR::size = 0";
    }
    --size;
}

void VECTOR<CAR>::erase(const unsigned long index)
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


void VECTOR<CAR>::insert(const unsigned long index,const CAR&item)
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

typename VECTOR<CAR>::ITERATOR VECTOR<CAR>::begin(){
    if(DEBUG_MODE){qDebug()<<"begin(): "<<this;}
    return VECTOR<CAR>::ITERATOR(this->arr,this);
}

typename VECTOR<CAR>::ITERATOR VECTOR<CAR>::end(){
    if(DEBUG_MODE){qDebug()<<"end(): "<<this;}
    return VECTOR<CAR>::ITERATOR((this->arr+this->size),this);
}

void VECTOR<CAR>::relocate(const unsigned long newSize)
{
    CAR *temp = new CAR[this->capacity = (newSize+newSize/3)];
    for(int i = 0;i<(this->size<newSize?this->size:newSize);++i)
    {
        temp[i] = (this->arr)[i];
    }
    delete [](this->arr);
    this->arr = temp;
    this->size = (this->size<newSize? this->size:newSize);
}


VECTOR<CAR>::ITERATOR::ITERATOR():iter(nullptr),pointerVECTOR(nullptr){
    if(DEBUG_MODE){qDebug()<<"Конструктор по умолчанию VECTOR<T>::ITERATOT"<<this;}
}


VECTOR<CAR>::ITERATOR::ITERATOR(ITERATOR &other){
    if(DEBUG_MODE){qDebug()<<"Конструктор копирования ITERATOR(ITERATOR &other)"<<this;}
    this->iter = other.iter;
    this->pointerVECTOR = other.pointerVECTOR;
}

typename VECTOR<T>::ITERATOR& VECTOR<CAR>::ITERATOR::operator++()
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


typename VECTOR<CAR>::ITERATOR &VECTOR<CAR>::ITERATOR::operator--()
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


typename VECTOR<CAR>::ITERATOR& VECTOR<CAR>::ITERATOR::operator=(ITERATOR other)
{
    if(DEBUG_MODE){qDebug()<<"Оператор присваивания VECTOR<T>ITERATOT";}
    this->iter = other.iter;
    this->pointerVECTOR = other.pointerVECTOR;
    return *this;
}

VECTOR<CAR>::ITERATOR::ITERATOR(CAR *iter_, VECTOR<CAR> *pointerVECTOR_)
{
    if(DEBUG_MODE){qDebug()<<"Конструктор ITERATOR(T *iter_, VECTOR<T> *pointerVECTOR_)"<<this;}
    this->iter = iter_;
    this->pointerVECTOR = pointerVECTOR_;
}

bool VECTOR<CAR>::ITERATOR::operator>(VECTOR<CAR>::ITERATOR other){
    if(this->pointerVECTOR!=other.pointerVECTOR){
        throw "ERROR: Сравниваемые итераторы принадлежат разным векторам!";
    }
    return (this->iter>other.iter);
}

bool VECTOR<CAR>::ITERATOR::operator<(VECTOR<CAR>::ITERATOR other){
    if(this->pointerVECTOR!=other.pointerVECTOR){
        throw "ERROR: Сравниваемые итераторы принадлежат разным векторам!";
    }
    return this->iter<other.iter;
}

bool VECTOR<CAR>::ITERATOR::operator<=(VECTOR<CAR>::ITERATOR other){
    if(this->pointerVECTOR!=other.pointerVECTOR){
        throw "ERROR: Сравниваемые итераторы принадлежат разным векторам!";
    }
    return this->iter<=other.iter;
}

bool VECTOR<CAR>::ITERATOR::operator>=(VECTOR<CAR>::ITERATOR other){
    if(this->pointerVECTOR!=other.pointerVECTOR){
        throw "ERROR: Сравниваемые итераторы принадлежат разным векторам!";
    }
    return this->iter>=other.iter;
}


typename VECTOR<CAR>::ITERATOR VECTOR<CAR>::ITERATOR::operator-(const unsigned long offset)
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
*/
