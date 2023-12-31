#include "doctest.h"
#include <sstream>
#include "tree.hpp"

using IntTree = Tree<int>;

TEST_CASE("Извеждане на примерно дърво на две нива") {
    IntTree t =
        IntTree(1)      // създава дърво с единствен връх (листо 1 )
        << IntTree(2)   // създава листо 2 и го добавя като наследник на 1
        << IntTree(9)   // създава листо 9 и го добавя като наследник на 1 
        << IntTree(10); // създава листо 9 и го добавя като наследник на 1

    std::ostringstream os;
    t.print(os);
    CHECK_EQ(os.str(), "(1 (2) (9) (10))");
}

TEST_CASE("Промяна на корена") {
    IntTree t =
        IntTree(1)
        << IntTree(2)
        << IntTree(9)
        << IntTree(10);

    t.root() = 5;
    std::ostringstream os;
    t.print(os);
    CHECK_EQ(os.str(), "(5 (2) (9) (10))");
}

TEST_CASE("Работа с примерно дърво на четири нива") {
    IntTree t =
        IntTree(1)
        << (IntTree(2)
            << IntTree(3)
            << (IntTree(4)
                << IntTree(5)
                << IntTree(6))
            << IntTree(7)
            << IntTree(8))
        << IntTree(9)
        << IntTree(10);

    SUBCASE("Извеждане") {
        std::ostringstream os;
        t.print(os);
        CHECK_EQ(os.str(), "(1 (2 (3) (4 (5) (6)) (7) (8)) (9) (10))");
    }

    SUBCASE("Дълбочина") {
        CHECK_EQ(t.depth(), 4);
    }

    SUBCASE("Ширина") {
        CHECK_EQ(t.breadth(), 4);
    }

}
