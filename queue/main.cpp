#include <iostream>
#include "static_queue.hpp"
#include "linked_queue.hpp"

using TestQueue = StaticQueue<int>;
//using TestQueue = LinkedQueue<int>;

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "queue_tests.h"
