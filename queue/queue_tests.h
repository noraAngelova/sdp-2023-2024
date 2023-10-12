TEST_CASE("Default constructor creates empty queue") {
    TestQueue q;
    CHECK(q.empty());
}

TEST_CASE("pushing an element creates a non-empty queue") {
    TestQueue q;
    q.push(42);
    CHECK(!q.empty());
}

TEST_CASE("pushing elements after the first one does not change head of queue") {
    TestQueue q;
    const int N = 10;
    for (int i = 0; i < N; i++) {
        q.push(i);
    }
    CHECK_EQ(q.head(), 0);
}

TEST_CASE("poping the first element removes only it and does not change the others") {
    TestQueue q;
    const int N = 10;
    for (int i = 0; i < N; i++)
        q.push(i);
    CHECK_EQ(q.head(), 0);
    q.pop();
    for (int i = 1; i < N; i++) {
        CHECK(!q.empty());
        CHECK_EQ(q.head(), i);
        q.pop();
    }
    CHECK(q.empty());
}

TEST_CASE("Multiple pops after pushs should work") {
    TestQueue q;
    const int N = 150;
    const int THE_ANSWER = 42;
    for (int i = 0; i < N; i++) {
        q.push(THE_ANSWER);
        CHECK_EQ(q.head(), THE_ANSWER);
        q.pop();
    }
    CHECK(q.empty());
}

