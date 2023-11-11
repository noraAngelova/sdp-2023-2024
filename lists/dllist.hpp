#ifndef _DLLIST_HPP
#define _DLLIST_HPP
#include<iostream>

template <typename T>
struct DoubleLinkedListElement {
    T data;
    DoubleLinkedListElement<T> *next, *prev;
    DoubleLinkedListElement(T _data, DoubleLinkedListElement<T>* _next = nullptr, DoubleLinkedListElement<T>* _prev = nullptr) :
        data(_data), next(_next), prev(_prev) 
    {}
};

// Декларация на свързан списък с две връзки
template <typename T>
class DoubleLinkedList;

// Итератор за свързан списък с две връзки
template <typename T>
class DoubleLinkedListIterator {
    // Осигураване на достъп до елементите на свързан списък
    friend class DoubleLinkedList<T>;

    // Съкращение, което ще се използва за тип елементите, които ще обхождаме
    using DLLE = DoubleLinkedListElement<T>;

    // Тип итератор
    using I = DoubleLinkedListIterator<T>;

    // Указател към елемент на свързания списък, който ще се използва за абстракция на позиция
    DLLE *ptr;
public:
    // Конструктор за итератор - абстракция на позиция в свързан списък с две връзки
    DoubleLinkedListIterator(DLLE* p = nullptr) : ptr(p) {}

    // Проверка за валидност на итератора/позицията.
    bool valid() const { 
        return ptr != nullptr; 
    }

    // Преместване към следваща елемент. Връща се новата позиция (итератор)
    I next() const {
        if (!valid())
            return *this;

        return I(ptr->next);
    }

    I prev() const {
        if (!valid())
            return *this;

        return I(ptr->prev);
    }

    // ! Не се прави валидация. Предоставен е метод за проверка на валидност
    T const& getConst() const {
        return ptr->data;
    }
    T& get() const {
        return ptr->data;
    }

    // Синтактична захар
    // Начин на използване: it <-> it.valid();
    operator bool() const { 
        return valid(); 
    }

    // Начин на използване: ++it
    I& operator++() {
        return (*this = next());
    }

    // Начин на използване: it++
    I operator++(int) {
        I save = *this;
        ++(*this); // Променя позицията, която се намира в *this
        return save;
    }

    // Начин на използване: --it
    I& operator--() {
        return (*this = prev());
    }

    // Начин на използване: it--
    I operator--(int) {
        I save = *this;
        --(*this);
        return save;
    }

    // Начин на използване: *it = 3;
    T& operator*() {
        return get();
    }

    // Начин на използване: T data = *it;
    T const & operator*() const {
        return getConst();
    }

    bool operator==(I const& it) const {
        return ptr == it.ptr;
    }
    bool operator!=(I const& it) const {
        return !(*this == it);
    }

    bool operator<=(I const& it) const {
        return ptr <= it.ptr;
    }

    I& operator+=(unsigned n) {
        for (unsigned i = 0; i < n; i++) {
            ++(*this);
        }
        return *this;
    }

    I& operator-=(unsigned n) {
        for (unsigned i = 0; i < n; i++) {
            --(*this);
        }
        return *this;
    }
};

// Реализация на свързан списък с две връзки
template <typename T>
class DoubleLinkedList {
    using DLLE = DoubleLinkedListElement<T>;
    DLLE *front, *back;

    void erase();
public:
    using I = DoubleLinkedListIterator<T>;
    using Type = T;

    DoubleLinkedList() : front(nullptr), back(nullptr) {}

    DoubleLinkedList(DoubleLinkedList const& ll) : front(nullptr), back(nullptr) {
        append(ll);
    }

    DoubleLinkedList& operator=(DoubleLinkedList const& ll) {
        if (this != &ll) {
            erase();
            append(ll);
        }
        return *this;
    }

    ~DoubleLinkedList() { 
        erase(); 
    }

    // Move семантики
    DoubleLinkedList(DoubleLinkedList<T>&& ll) {
        front = ll.front;
        back = ll.back;
        ll.front = ll.back = nullptr;
    }

    DoubleLinkedList<T>& operator=(DoubleLinkedList<T>&& ll) {
        if (this != &ll) {
            erase();
            front = ll.front;
            back = ll.back;
            ll.front = ll.back = nullptr;
        }

        return *this;
    }

    bool empty() const {
        return front == nullptr && back == nullptr;
    }

    // Базови методи на класа
    bool insertBefore(I const& it, T const& x);
    bool insertAfter(I const& it, T const& x);

    bool deleteBefore(I const& it, T& x);
    bool deleteAt(I & it, T& x);
    bool deleteAfter(I const& it, T& x);

    // Допълнителни методи
    bool deleteBefore(I const& it) {
        T tmp;
        return deleteBefore(it, tmp);
    }

    bool deleteAt(I & it) {
        T tmp;
        return deleteAt(it, tmp);
    }

    bool deleteAfter(I const& it) {
        T tmp;
        return deleteAfter(it, tmp);
    }

    bool insertFirst(T const& x) {
        return insertBefore(begin(), x);
    }

    bool insertLast(T const& x) {
        return insertAfter(last(), x);
    }

    bool deleteFirst(T& x) {
        I beg = begin();
        return deleteAt(beg, x);
    }

    bool deleteLast(T& x) {
        I lt = last();
        return deleteAt(lt, x);
    }

    bool deleteFirst() {
        T tmp;
        return deleteFirst(tmp);
    }
 
    bool deleteLast() {
        T tmp;
        return deleteLast(tmp);
    }

    T const& getAt(I const& it) const {
        return it.getConst();
    }

    T& getAt(I const& it) {
        return it.get();
    }

    // Метод, който връща итератор към първия елемент
    I begin() const {
        return I(front);
    }
    // Метод, който връща итератор към края на списъка
    I end() const {
        return I();
    }
    // Метод, който връща итератор към последния елемент
    I last() const {
        return I(back);
    }

    // Залепва елементите на l в края на списъка
    void append(DoubleLinkedList const& l);

    // Присвоява си елементите на l като ги залепва в края на списъка
    void appendAssign(DoubleLinkedList& l);

    // Синтактична захар
    // Предефиниране на оператор += за добавяне на елемент към края на свързания списък
    DoubleLinkedList<T>& operator+=(T const& x) {
        insertLast(x);
        return *this;
    }

    bool isPalindrome() const {
        if (empty) {
            return false;
        }

        I fi = begin(), bi = last();
        while (fi != bi && fi.next() != bi && *fi == *bi) {
            ++fi;
            --bi;
        }
        return *fi == *bi;
    }
};


// O(1) по време и по памет
template <typename T>
bool DoubleLinkedList<T>::insertBefore(I const& it, T const& x) {
    if (empty()) {
        front = back = new DLLE{ x, nullptr, nullptr };
        return true;
    };

    if (!it) {
        return false;
    }

    // вмъкване преди първи елемент
    if (!it.prev()) {
        // добавяме преди началото на списъка
        it.ptr->prev = front = new DLLE{ x, it.ptr, nullptr };
        return true;
    }

    //// общ случай
    return insertAfter(it.prev(), x);
}

// O(1) по време и по памет
template <typename T>
bool DoubleLinkedList<T>::insertAfter(I const& it, T const& x) {
    // Проверка дали списъкът е празен 
    if (empty()) {
        front = back = new DLLE{ x, nullptr, nullptr };
        return true;
    }

    if (!it) {
        return false;
    }

    // Списъкът не е празен
    if (!it.next()) {
        // Добавяме след края на списъка {стойност, next, prev}
        it.ptr->next = back = new DLLE{ x, nullptr, it.ptr };
        return true;
    }

    DLLE* newElem = new DLLE{ x, it.ptr->next, it.ptr };
    it.ptr->next->prev = newElem;
    it.ptr->next = newElem;
    return true;
}

// O(1) по време и памет
template <typename T>
bool DoubleLinkedList<T>::deleteAt(I & it, T& x) {
    if (!it || empty()) {
        return false;
    }

    // Има ли предходен елемент
    if (it.prev()) {
        it.ptr->prev->next = it.ptr->next;
    }
    else {
        // изтриваме първия елемент, трябва да преместим front
        front = it.ptr->next;
    }

    // Има ли следващ елемент
    if (it.next()) {
        it.ptr->next->prev = it.ptr->prev;
    }
    else {
        // Изтриваме последния елемент, трябва да преместим back
        back = it.ptr->prev;
    }
    
    // Изтриването на последния елемент работи както се очаква
    x = it.ptr->data;
    delete it.ptr;

    // Зануляване на указателя в итератора за следващо използване
    it.ptr = nullptr;
    return true;
}

// O(1) по време и памет
template <typename T>
bool DoubleLinkedList<T>::deleteAfter(I const& it, T& x) {
    if (!it) {
        return false;
    }

    // Използване на временен итератор, който може да бъде занулен
    I next = it.next();
    
    return deleteAt(next, x);
}

// O(1) по време и памет
template <typename T>
bool DoubleLinkedList<T>::deleteBefore(I const& it, T& x) {
    if (!it) {
        return false;
    }
    
    // Използване на временен итератор, който може да бъде занулен
    I prev = it.prev();
    
    return deleteAt(prev, x);
}

template <typename T>
void DoubleLinkedList<T>::append(DoubleLinkedList const& l) {
    for (T const& x : l)
        insertLast(x);
}

template <typename T>
void DoubleLinkedList<T>::erase() {
    while (!empty())
        deleteFirst();
}

// O(1) по време и памет
template <typename T>
void DoubleLinkedList<T>::appendAssign(DoubleLinkedList& l) {
    if (back != nullptr)
        back->next = l.front;
    else
        front = l.front;

    if (l.front != nullptr)
        l.front->prev = back;

    if (l.back != nullptr)
        back = l.back;

    l.front = l.back = nullptr;
}

#endif
