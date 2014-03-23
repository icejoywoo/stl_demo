#include <cstdio>
#include <stack>
#include <string>

#include "gtest/gtest.h"

class StackTest : public testing::Test {
public:
    virtual void SetUp() {
    }

    virtual void TearDown() {
    }

    std::stack<int> m_stack;
};
