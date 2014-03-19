#include <cstdio>
#include <queue>
#include <algorithm>

#include "gtest/gtest.h"

class QueueTest : public testing::Test {
public:
    virtual void SetUp() {
        for (size_t i = 0; i < 10; ++i) {
            m_queue.push(i);
        }
    }

    virtual void TearDown() {
    }

    // queue is a container adapter, default use deque
    std::queue<int> m_queue;
};

TEST_F(QueueTest, PopElements) {
    EXPECT_EQ(10, m_queue.size());
    int a = 0;
    while (!m_queue.empty()) {
        EXPECT_EQ(a++, m_queue.front());
        m_queue.pop();
    }
}
