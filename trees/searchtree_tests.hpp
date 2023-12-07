#ifndef __BSTREE_TESTS_HPP
#define __BSTREE_TESTS_HPP

#include "doctest.h"
#include "search_tree.hpp"

using BSIntTree = BSTree<int>;

TEST_CASE("Включване и търсене на елементи") {
    BSIntTree bst;

    REQUIRE(bst.insert(5));
    REQUIRE(bst.insert(3));
    REQUIRE(bst.insert(7));
    REQUIRE(bst.insert(6));
    REQUIRE(bst.insert(2));

    // не можем да включваме същия елемент повторно
    REQUIRE(!bst.insert(3));

    SUBCASE("Търсене") {
        for (int x : {2, 3, 5, 6, 7})
            CHECK_EQ(*bst.search(x), x);

        CHECK(!bst.search(1));
    }

    SUBCASE("Изтриване на несъществуващ елемент") {
        CHECK(!bst.remove(10));
    }

    SUBCASE("Изтриване на корена") {
        CHECK(bst.remove(5));
        CHECK(!bst.search(5));
      
        for (int x : {2, 3, 6, 7})
            CHECK_EQ(*bst.search(x), x);

        std::ostringstream os;
        bst.printTree(os);
        CHECK_EQ(os.str(), "(6(3(2()())())(7()()))");
    }

    SUBCASE("Order") {
        std::ostringstream os;
        bst.printTree(os);
        CHECK_EQ(os.str(), "(5(3(2()())())(7(6()())()))");
    }
}

#endif
