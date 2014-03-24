#include <cstdio>
#include <stack>
#include <string>

#include "gtest/gtest.h"

class StackTest : public testing::Test {
public:
    virtual void SetUp() {
        for (int i = 0; i < 100; ++i) {
            m_stack.push(i);
        }
    }

    virtual void TearDown() {
    }

    std::stack<int> m_stack;
};

TEST_F(StackTest, IterateElements) {
    EXPECT_EQ(100, m_stack.size());

    int a = 99;
    while (!m_stack.empty()) {
        EXPECT_EQ(a--, m_stack.top());
        m_stack.pop();
    }
}

