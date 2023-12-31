#ifndef __TREE_HPP
#define __TREE_HPP

#include <iostream>
#include "linked_list.hpp"

template <typename T>
class Tree {
private:
    T data;
    LinkedList<Tree> trees;
public:
    // конструктор за листо
    Tree(T const& _data = T()) : data(_data) {}

    // добавяне на поддърво
    void addSubtree(Tree const& t) {
        trees.insertLast(t);
    }

    Tree& operator<<(Tree const& t) {
        addSubtree(t);
        return *this;
    }

    T const& root() const { 
        return data; 
    }


    T& root() {
        return data;
    }

    LinkedList<Tree> const& subtrees() const { 
        return trees; 
    }

    void print(std::ostream& os = std::cout) const {
        os << '(' << root();
        for (Tree const& subtree : subtrees()) {
            os << ' ';
            subtree.print(os);
        }
        os << ')';
    }

    unsigned depth() const {
        unsigned maxDepth = 0;
        for (Tree const& subtree : subtrees()) {
            maxDepth = std::max(maxDepth, subtree.depth());
        }
        return 1 + maxDepth;
    }

    unsigned breadth() const {
        unsigned maxBreadth = 0;
        unsigned nChildren = 0;
        for (Tree const& subtree : subtrees()) {
            maxBreadth = std::max(maxBreadth, subtree.breadth());
            nChildren++;
        }
        return std::max(nChildren, maxBreadth);
    }

};
#endif
