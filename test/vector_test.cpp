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

class VectorTest : public testing::Test {
protected:
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

TEST_F(VectorTest, IterateElements) {
    int a = 0;
    // iterator or const_iterator
    for (std::vector<int>::iterator it = int_vector.begin();
            it != int_vector.end(); ++it) {
        EXPECT_EQ(a++, *it);
    }
    
    a = 0;
    for (int i = 0; i < 100; ++i) {
        EXPECT_EQ(a++, int_vector[i]);
    }
}

TEST_F(VectorTest, ReverseInterateElements) {
    int a = 99;
    // reverse_iterator or const_reverse_iterator
    for (std::vector<int>::reverse_iterator it = int_vector.rbegin();
            it != int_vector.rend(); ++it) {
        EXPECT_EQ(a--, *it);
    }
}

TEST_F(VectorTest, RemoveElement) {
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
