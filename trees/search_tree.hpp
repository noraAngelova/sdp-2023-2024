#ifndef SEARCH_TREE_HPP
#define SEARCH_TREE_HPP
#include "binary_tree.hpp"

// Двоично наредено дърво / Двоично дърво за търсене
template <typename T>
class BSTree : public BinTree<T> {
public:
    // Търсене в двоично наредено дърво
    // Работи се с позиции в дървото
    // Връща позицията на намерения елемент ИЛИ неговата правилна позиция в дървото
    BinTreeMutablePosition<T> searchFromPos(BinTreeMutablePosition<T> pos, T const& x) {
        while (pos && *pos != x)
            if (x < *pos) {
                --pos;
            }
            else {
                ++pos;
            }
        // Или сме намерили търсения елемент или позицията е празна (мястото, където би бил елементът) 
        // !pos ще бъде false
        // ако *pos == x, ще се оцени до true
        return pos;
    }

    BinTreeMutablePosition<T> search(T const& x) {
        // Търсенето започва от корена
        return searchFromPos(BinTree<T>::rootMutablePos(), x);
    }

    // Вмъкване на елемент
    // Той трябва да се намира на точно определено място в дървото
    bool insert(T const& x) {
        // Търсим елемента в дървото
        BinTreeMutablePosition<T> pos = search(x);
        if (pos) {
            // Дървото не може да съдържа два елемента с една и също стойност
            // Добавянето е неуспешно
            return false;
        }

        // Намерили сме позицията, където елементът трябва да се добави
        // pos е позицията, където искаме да вмъкнем новия елемент
        BinTree<T> leaf = x;
        BinTree<T>::assignFrom(pos, leaf.rootMutablePos());
        return true;
    }

    // Премахване на елемент
    // Операцията трябва да запазва свойствата на двоично нареденото дърво
    bool remove(T const& x) {
        // Търсим елемента в дървото
        BinTreeMutablePosition<T> pos = search(x);
        if (!pos) {
            // Не може да се премахне елементът, той не е в дървото
            return false;
        }

        // Лявото поддърво е празно
        if (!-pos) {
            BinTree<T>::assignFrom(pos, +pos);
            return true;
        }

        // Дясното поддърво е празно
        if (!+pos) {
            BinTree<T>::assignFrom(pos, -pos);
            return true;
        }

        // Имаме ляво и дясно поддървета
        // Търси се най-левия възел в дясното поддърво
        // Търсенето започва от корена на дясното поддърво
        BinTreeMutablePosition<T> minRightTreePos = +pos;
        while (-minRightTreePos) --minRightTreePos;
        // !-minRightTreePos
        // Взима се стойността на minRightTreePos и се записва в корена
        *pos = *minRightTreePos;

        // Свежда се до случая, в който изтриваме възел, който няма ляво поддърво
        // Не може да има елемент в лявотоподдърво, той ще е по-малък от minRightTreePos
        BinTree<T>::assignFrom(minRightTreePos, +minRightTreePos);
        return true;
    }

    // Публичен метод за извеждане на елементи на дърво    
    void print(std::ostream& out) {
        BinTree<T>::printTree(out);
    }

};

#endif
