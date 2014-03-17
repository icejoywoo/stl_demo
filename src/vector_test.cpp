#include <vector>
#include <string>

#include "gtest/gtest.h"

TEST(VectorTest, BasicInit) {
    std::vector<int> int_vector;
    for (int i = 0; i < 100; ++i) {
        int_vector.push_back(i);
    }

    EXPECT_EQ(int_vector.size(), 100);
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
