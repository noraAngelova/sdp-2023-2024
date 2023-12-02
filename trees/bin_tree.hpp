#ifndef BINARY_TREE_HPP
#define BINARY_TREE_HPP
#include <cstring>
#include <cassert>

// Елемент в двоично дърво
template <typename T>
struct BinTreeNode {
    T data;
    BinTreeNode* left, * right;

    BinTreeNode(const T& value, BinTreeNode* leftNode, BinTreeNode* rightNode) 
        : data(value), left(leftNode), right(rightNode) {}
    BinTreeNode() {}
};

template <typename T>
class BinTree;

// Абстракция на позиция в двоично дърво
template <typename T>
class BinTreePosition {
    // Представяме позицията като указател към елемент. 
    BinTreeNode<T>* ptr;
    friend class BinTree<T>;
public:
    BinTreePosition(BinTreeNode<T>* nodePtr = nullptr) : ptr(nodePtr) {}

    // Проверка за валидност
    // Мeтодът проверява и двата адреса
    bool valid() const {
        return ptr != nullptr;
    }

    // Предвижваме се към корена на лявото поддърво.
    // Методът връща НОВА позиция
    BinTreePosition<T> left() const {
        if (!valid()) {
            throw std::runtime_error("Опит за преместване от невалидна позиция!");
        }
        return BinTreePosition<T>(ptr->left);
    }

    // Предвижваме се към корена на дясното поддърво.
    // Методът връща НОВА позиция
    BinTreePosition<T> right() const {
        if (!valid()) {
            throw std::runtime_error("Опит за преместване от невалидна позиция!");
        }
        return BinTreePosition<T>(ptr->right);
    }

    // Извличане на стойността на елементът, на който сме се позиционирали
    T const& get() const {
        if (!valid()) {
            throw std::runtime_error("Опит за данни от невалидна позиция!");
        }
        return ptr->data;
    }
    T& get() {
        if (!valid()) {
            throw std::runtime_error("Опит за данни от невалидна позиция!");
        }
        return ptr->data;
    }

    // Синтактична захар

    // Предефиниране на bool оператор, за да може да използваме позициите като булеви стойности
    // pos <-> pos.valid();
    operator bool() const {
        return valid();
    }

    // Предвижване към корена на дясното поддърво
    // ++pos
    BinTreePosition<T>& operator++() {
        return (*this = right());
    }

    // Предвижване към корена на дясното поддърво, с отложено оценяване
    // pos++
    BinTreePosition<T> operator++(int) {
        BinTreePosition<T> currentPos = *this;
        ++(*this);
        return currentPos;
    }

    // Предвижване към корена на лявото поддърво
    // --pos
    BinTreePosition<T>& operator--() {
        return (*this = left());
    }

    // Предвижване към корена на лявото поддърво, с отложено оценяване
    // pos--
    BinTreePosition<T> operator--(int) {
        BinTreePosition<T> currentPos = *this;
        --(*this);
        return currentPos;
    }

    // Извличане на стойност с *
    // *pos = 3;
    T& operator*() {
        return get();
    }

    // Сравнение на позиции
    bool operator==(BinTreePosition<T> const& pos) const {
        return valid() && pos.valid() && ptr == pos.ptr;
    }

    bool operator!=(BinTreePosition<T> const& pos) const {
        return !(*this == pos);
    }

    // Връщане на корена на лявото поддърво, по стойност
    BinTreePosition<T> operator-() const {
        return left();
    }
    // Връщане на корена на дясното поддърво, по стойност
    BinTreePosition<T> operator+() const {
        return right();
    }
};


// Абстракция на позиция в двоично дърво
template <typename T>
class BinTreeMutablePosition {
    // Осигуряваме достъп до вътрешното представяне на дървото
    friend class BinTree<T>;

    // Представяме позицията като указател към (указател към елемент). 
    // Позволява да променяме адреса при предаване на позиция (като параметър на функция, по стойност) 
    BinTreeNode<T>** ptr;

public:
    BinTreeMutablePosition() : ptr(nullptr) {}
    BinTreeMutablePosition(BinTreeNode<T>*& node) : ptr(&node) {}

    // Проверка за валидност
    // Мeтодът проверява и двата адреса
    bool valid() const {
        return ptr != nullptr && *ptr != nullptr;
    }

    // Предвижваме се към корена на лявото поддърво.
    // Методът връща НОВА позиция
    BinTreeMutablePosition<T> left() const {
        if (!valid()) {
            throw std::runtime_error("Опит за преместване от невалидна позиция!");
        }
        return BinTreeMutablePosition<T>((*ptr)->left);
    }

    // Предвижваме се към корена на дясното поддърво.
    // Методът връща НОВА позиция
    BinTreeMutablePosition<T> right() const {
        if (!valid()) {
            throw std::runtime_error("Опит за преместване от невалидна позиция!");
        }
        return BinTreeMutablePosition<T>((*ptr)->right);
    }

    // Извличане на стойността на елементът, на който сме се позиционирали
    T const& get() const {
        if (!valid()) {
            throw std::runtime_error("Опит за данни от невалидна позиция!");
        }
        return (*ptr)->data;
    }
    T& get() {
        if (!valid()) {
            throw std::runtime_error("Опит за данни от невалидна позиция!");
        }
        return (*ptr)->data;
    }

    // Синтактична захар

    // Предефиниране на bool оператор, за да може да използваме позициите като булеви стойности
    // pos <-> pos.valid();
    operator bool() const {
        return valid();
    }

    // Предвижване към корена на дясното поддърво
    // ++pos
    BinTreeMutablePosition<T>& operator++() {
        return (*this = right());
    }

    // Предвижване към корена на дясното поддърво, с отложено оценяване
    // pos++
    BinTreeMutablePosition<T> operator++(int) {
        BinTreeMutablePosition<T> currentPos = *this;
        ++(*this);
        return currentPos;
    }

    // Връщане на корена на дясното поддърво, по стойност
    BinTreeMutablePosition<T> operator+() const {
        return right();
    }

    // Предвижване към корена на лявото поддърво
    // --pos
    BinTreeMutablePosition<T>& operator--() {
        return (*this = left());
    }

    // Предвижване към корена на лявото поддърво, с отложено оценяване
    // pos--
    BinTreeMutablePosition<T> operator--(int) {
        BinTreeMutablePosition<T> currentPos = *this;
        --(*this);
        return currentPos;
    }

    // Връщане на корена на лявото поддърво, по стойност
    BinTreeMutablePosition<T> operator-() const {
        return left();
    }

    // Извличане на стойност с *
    // *pos = 3;
    T& operator*() {
        return get();
    }
};


// Двоично дърво
template <typename T>
class BinTree {
private:
    // Представяме дървото чрез указател към корена
    BinTreeNode<T>* root;

    void printTreeHelp(std::ostream&, BinTreePosition<T> pos);

    // Изтриване на дървото от тази позиция надолу
    void erase(BinTreePosition<T> pos);
    // Копиране на дървото от тази позиция надолу
    BinTreePosition<T> copy(BinTreePosition<T> pos);

public:
    BinTree();
    BinTree(const T&);
    BinTree(T const& root, BinTree&& left, BinTree&& right);

    // O(n) по памет и време
    BinTree(BinTree& other) : root(nullptr) {
        copy(other.rootPos());
    }

    // O(1) по памет и време
    // Работи се с rvalue
    BinTree(BinTree&& other) : root(nullptr) {
        assignFrom(rootMutablePos(), other.rootMutablePos());
    }

    BinTree& operator=(BinTree& other) {
        if (this != &other) {
            erase(rootPos());
            copy(other.rootPos());
        }
        return *this;
    }

    // Работи се с rvalue
    BinTree& operator=(BinTree&& other) {
        if (this != &other) {
            assignFrom(rootMutablePos(), other.rootMutablePos());
        }
        return *this;
    }

    // Деструктор
    ~BinTree() {
        // Изтриване на дървото от тази позиция
        erase(rootPos());
    }

    BinTreePosition<T> rootPos() {
        return BinTreePosition<T>(root);
    }

    BinTreeMutablePosition<T> rootMutablePos() {
        return BinTreeMutablePosition<T>(root);
    }

    // Проверка дали дървото е празно
    bool empty() const {
        return root == nullptr;
    }

    // Добавяне на елемент по подаден път
    BinTree<T>& addElement(const char*, const T&);

    // Извеждане на дървото ЛКД
    void printTree(std::ostream&);

    void assignFrom(BinTreeMutablePosition<T> base, BinTreeMutablePosition<T> other) {
        // Запомня се наличното от from
        BinTreeNode<T>* save = *base.ptr;
        // Променя се с наличното в other
        *base.ptr = *other.ptr;
        // Нулираме указателя, за да избегнем подeлянето на памет
        *other.ptr = nullptr;
        // Изтрива се старото съдържание на from
        erase(BinTreePosition<T>(save));
    }
};

template <typename T>
BinTree<T>::BinTree() : root(nullptr) {}

template <typename T>
BinTree<T>::BinTree(const T& x) {
    root = new BinTreeNode<T>(x, nullptr, nullptr);
}

template <typename T>
BinTree<T>::BinTree(T const& _root, BinTree&& left, BinTree&& right) {
    root = new BinTreeNode<T>(_root, left.root, right.root);
    left.root = right.root = nullptr;
}

template <typename T>
BinTree<T>& BinTree<T>::addElement(const char* trace, const T& x) {
    if (strlen(trace) == 0) {
        assert(root == nullptr);
        root = new BinTreeNode<T>(x, nullptr, nullptr);
        return *this;
    }

    assert(root != nullptr);
    BinTreeNode<T>* current = root;
    unsigned int traceLength = strlen(trace);

    for (int i = 0; i < traceLength - 1; i++) {
        assert(trace[i] == 'L' || trace[i] == 'R');
        if (trace[i] == 'L') {
            current = current->left;
        }
        else {
            current = current->right;
        }
        assert(current != nullptr);
    }
    // current е родителя на новия елемент
    assert(trace[traceLength - 1] == 'L' || trace[traceLength - 1] == 'R');
    if (trace[traceLength - 1] == 'L') {
        assert(current->left == nullptr);
        current->left = new BinTreeNode<T>(x, nullptr, nullptr);
    }
    else {
        assert(current->right == nullptr);
        current->right = new BinTreeNode<T>(x, nullptr, nullptr);
    }

    return *this;
}

template <typename T>
void BinTree<T>::printTree(std::ostream& out) {
    printTreeHelp(out, rootPos());
}

template <typename T>
void BinTree<T>::printTreeHelp(std::ostream& out, BinTreePosition<T> pos) {
    if (!pos) {
        out << "()";
        return;
    }

    out << "(";
    out << *pos;
    printTreeHelp(out, -pos);
    printTreeHelp(out, +pos);
    out << ")";
}

template <typename T>
void BinTree<T>::erase(BinTreePosition<T> pos) {
    if (pos) {
        erase(-pos);
        erase(+pos);
        delete pos.ptr;
    }
}

template <typename T>
BinTreePosition<T> BinTree<T>::copy(BinTreePosition<T> pos) {
    if (pos) {
        // Дървото НЕ е празно
        BinTreeNode<T>* left = -pos ? copy(-pos).ptr : nullptr;
        BinTreeNode<T>* right = +pos ? copy(+pos).ptr : nullptr;

        root = new BinTreeNode<T>(*pos, left, right);
    }
    return rootPos();
}
//
#endif
