#ifndef __BINTREE_TEST_HPP
#define __BINTREE_TEST_HPP

#include "doctest.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include "binary_tree.hpp"

using BIntTree = BinTree<int>;

TEST_CASE("Тестове за двоично дърво") {
    BIntTree t(1, 
        BIntTree(2, BIntTree(3), BIntTree(4)),
        BIntTree(5, BIntTree(), BIntTree(6))
    );

    SUBCASE("Извеждане") {
        std::ostringstream os;
        t.printTree(os);
        CHECK_EQ(os.str(), "(1(2(3()())(4()()))(5()(6()())))");
    }

    SUBCASE("Копиране") {
        BIntTree* t2 = new BIntTree(t);
        *t2->rootPos() = 10;
        delete t2;
        CHECK_EQ(*t.rootPos(), 1);
    }

    SUBCASE("Присвояване") {
        BIntTree* t2 = new BIntTree;
        *t2 = t;
        *t2->rootPos() = 10;
        delete t2;
        CHECK_EQ(*t.rootPos(), 1);
    }

    SUBCASE("Move assignment") {
        BIntTree t2 = std::move(t);
        std::ostringstream os;
        t2.printTree(os);
        CHECK_EQ(os.str(), "(1(2(3()())(4()()))(5()(6()())))");
    }
}

#endif
