#include <cstdio>
#include <queue>
#include <algorithm>

#include "gtest/gtest.h"

/// FIFO
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

TEST_F(QueueTest, EmptyQueue) {
    std::queue<std::string> empty_queue;
    // std::cout << empty_queue.front() << std::endl; // call front() will core when queue is empty
    EXPECT_EQ(0, empty_queue.size());
}

TEST_F(QueueTest, PriorityQueueMaxHeap) {
    // template <class T, class Container = vector<T>,
    // class Compare = less<typename Container::value_type> > class priority_queue
    std::priority_queue<int> max_heap; // like max heap, there is max value on top
    for (int i = 0; i < 100; ++i) {
        max_heap.push(i);
    }

    int a = 99;
    while (!max_heap.empty()) {
        EXPECT_EQ(a--, max_heap.top());
        max_heap.pop();
    }
}

TEST_F(QueueTest, PriorityQueueMinHeap) {
    std::priority_queue<int, std::deque<int>, std::greater<int> > min_heap; // like min heap
    for (int i = 0; i < 100; ++i) {
        min_heap.push(i);
    }
    int a = 0;
    while (!min_heap.empty()) {
        EXPECT_EQ(a++, min_heap.top());
        min_heap.pop();
    }
}
