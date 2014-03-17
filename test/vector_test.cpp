#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

#include "gtest/gtest.h"

TEST(VectorTest, BasicInit) {
    std::vector<int> int_vector;
    for (int i = 0; i < 100; ++i) {
        int_vector.push_back(i);
    }

    EXPECT_EQ(int_vector.size(), 100);
    printf("max_size: %lu\n", int_vector.max_size());
    std::cout << "max_size: " << int_vector.max_size() << std::endl;
}

TEST(VectorTest, IterateElements) {
    std::vector<int> int_vector;
    for (int i = 0; i < 100; ++i) {
        int_vector.push_back(i);
    }

    int a = 0;
    for (std::vector<int>::iterator it = int_vector.begin();
            it != int_vector.end(); ++it) {
        EXPECT_EQ((*it), a++);
    }
}
