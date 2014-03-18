#include <algorithm>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

#include "gtest/gtest.h"

class VectorTestEnvironment : public testing::Environment {
public:
    virtual void SetUp() {
    }

    virtual void TearDown() {
    }
};

// class VectorTest : public testing::Test {
class VectorTest : public testing::TestWithParam<int> {
public:
    // before first case
    static void SetUpTestCase() {
    }

    // after last case
    static void TearDownTestCase() {
    }

    virtual void SetUp() {
        for (int i = 0; i < 100; ++i) {
            int_vector.push_back(i);
        }
    }
    
    virtual void TearDown() {
        int_vector.clear();
    }

    std::vector<int> int_vector;
};

TEST_F(VectorTest, BasicInit) {
    std::vector<int> vec;
    // watch the changes when insert elements
    for (int i = 0; i < 100; ++i) {
        vec.push_back(i);
        printf("capacity: %lu\n", vec.capacity()); // 2^n
        printf("size: %lu\n", vec.size());
    }

    EXPECT_EQ(100, vec.size());
    printf("max_size: %lu\n", vec.max_size());
    printf("capacity: %lu\n", vec.capacity()); // 128
    printf("size: %lu\n", vec.size());
}

TEST_F(VectorTest, ReserveSize) {
    printf("before capacity: %lu\n", int_vector.capacity()); // 128
    int_vector.reserve(1000);
    EXPECT_EQ(1000, int_vector.capacity());
    printf("after capacity: %lu\n", int_vector.capacity()); // 1024
}

TEST_F(VectorTest, Resize) {
    // resize n (n < vec.size)
    int_vector.resize(10); // 0-9
    EXPECT_EQ(10, int_vector.size());
    int a = 0;
    for (size_t i = 0; i < int_vector.size(); ++i) {
        EXPECT_EQ(a++, int_vector[i]);
    }
    // n > vec.size
    int_vector.resize(20); // 0-9 and 10 zero
    a = 0;
    for (size_t i = 0; i < 10; ++i) {
        EXPECT_EQ(a++, int_vector[i]);
    }
    for (size_t i = 10; i < int_vector.size(); ++i) {
        EXPECT_EQ(0, int_vector[i]);
    }
}

TEST_F(VectorTest, ClearVector) {
    int_vector.clear();
    EXPECT_EQ(0, int_vector.size());
    EXPECT_EQ(128, int_vector.capacity());

    {
        std::vector<int> temp;
        int_vector.swap(temp);
    }
    EXPECT_EQ(0, int_vector.size());
    EXPECT_EQ(0, int_vector.capacity());
}

TEST_F(VectorTest, IterateElements) {
    int a = 0;
    // iterator which can remove element
    for (std::vector<int>::iterator it = int_vector.begin();
            it != int_vector.end(); ++it) {
        EXPECT_EQ(a++, *it);
    }

    // const_iterator just for read-only
    a = 0;
    for (std::vector<int>::const_iterator it = int_vector.cbegin();
            it != int_vector.cend(); ++it) {
        EXPECT_EQ(a++, *it);
    }
    
    // using operator [] or at function
    a = 0;
    for (size_t i = 0; i < int_vector.size(); ++i) {
        EXPECT_EQ(a, int_vector[i]);
        EXPECT_EQ(a, int_vector.at(i));
        ++a;
    }
}

TEST_F(VectorTest, ReverseInterateElements) {
    int a = 99;
    // reverse_iterator 
    for (std::vector<int>::reverse_iterator it = int_vector.rbegin();
            it != int_vector.rend(); ++it) {
        EXPECT_EQ(a--, *it);
    }

    // const_reverse_iterator
    a = 99;
    for (std::vector<int>::const_reverse_iterator it = int_vector.crbegin();
            it != int_vector.crend(); ++it) {
        EXPECT_EQ(a--, *it);
    }
}

TEST_F(VectorTest, RemoveElement) {
    // ATTENTION: 遍历过程中删除元素, 需要注意iterator的处理
    for (std::vector<int>::iterator it = int_vector.begin();
            it != int_vector.end();) {
        if (*it >= 10) {
            it = int_vector.erase(it);
        } else {
            ++it;
        }
    }
    EXPECT_EQ(10, int_vector.size());
}

TEST_P(VectorTest, FindElementInVector) {
    int n = GetParam();
    EXPECT_EQ(n, *std::find(int_vector.begin(), int_vector.end(), n));
}

// parametered case
INSTANTIATE_TEST_CASE_P(VectorFindTest, VectorTest, testing::Values(0, 1, 2, 3, 5, 9, 10, 99));
INSTANTIATE_TEST_CASE_P(VectorFindAllTest, VectorTest, testing::Range(0, 10, 1));

TEST_F(VectorTest, PopBackElement) {
    EXPECT_EQ(0, int_vector.front()); // visit first element

    int sum = 0;
    int a = 99;
    while (!int_vector.empty()) {
        EXPECT_EQ(a--, int_vector.back());
        sum += int_vector.back(); // visit last element
        int_vector.pop_back(); // remove last element
    }

    EXPECT_EQ(4950, sum);
    EXPECT_EQ(0, int_vector.size());
}

