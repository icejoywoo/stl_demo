#include <cstdio>
#include <deque>

#include "gtest/gtest.h"

class DequeTest : public testing::Test {
public:
    virtual void SetUp() {
        for (int i = 0; i < 100; ++i) {
            m_deque.push_back(i);
        }
    }

    virtual void TearDown() {
        m_deque.clear();
    }

    std::deque<int> m_deque;
};

TEST_F(DequeTest, IterateElementsFromBack) {
    int a = 0;
    for (size_t i = 0; i < m_deque.size(); ++i) {
        EXPECT_EQ(a++, m_deque[i]);
    }
    a = 99;
    while (!m_deque.empty()) {
        EXPECT_EQ(a--, m_deque.back());
        m_deque.pop_back();
    }
}

TEST_F(DequeTest, IterateElementsFromFront) {
    int a = 0;
    while (!m_deque.empty()) {
        EXPECT_EQ(a++, m_deque.front());
        m_deque.pop_front();
    }
}

TEST_F(DequeTest, EraseElements) {
    EXPECT_EQ(100, m_deque.size());
    for (std::deque<int>::iterator it = m_deque.begin();
            it != m_deque.end();) {
        if (*it < 10) {
            it = m_deque.erase(it);
        } else {
            ++it;
        }
    }
    EXPECT_EQ(90, m_deque.size());
}

TEST_F(DequeTest, InsertElements) {
    int a = 11;
    bool flag = true;
    for (std::deque<int>::iterator it = m_deque.begin();
            it != m_deque.end();) {
        if (flag && *it > a) {
            flag = false;
            it = m_deque.insert(it, a);
        } else {
            ++it;
        }
    }

    EXPECT_EQ(a, m_deque[11]);
    EXPECT_EQ(a, m_deque[12]);
}
