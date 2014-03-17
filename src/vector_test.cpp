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
