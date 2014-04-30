#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>

#include "boost/bind.hpp"
#include "boost/function.hpp"
#include "gtest/gtest.h"

class BoostFunctionTest : public testing::Test {
public:
    virtual void SetUp() {
    }
    virtual void TearDown() {
    }
private:
};

void print(int i) {
    std::cout << i << std::endl;
}

class add
  : public std::binary_function<int, int, void>
{
    public:
        void operator()(int i, int j) const {
            std::cout << i << ", " << j << std::endl;
            std::cout << i + j << std::endl;
        }
};

TEST_F(BoostFunctionTest, StdForEachUnaryFunctor) {
    std::vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    std::for_each(v.begin(), v.end(), print);

    // std::bind1st bind2nd
    std::for_each(v.begin(), v.end(), std::bind1st(add(), 10));
    std::for_each(v.begin(), v.end(), std::bind2nd(add(), 10));

    // boost::bind
    std::for_each(v.begin(), v.end(), boost::bind(add(), 10, _1));
    std::for_each(v.begin(), v.end(), boost::bind(add(), _1, 10));
}

bool compare(int i, int j) {
    return i > j;
}

TEST_F(BoostFunctionTest, BinaryFunctor) {
    std::vector<int> v;
    v.push_back(1);
    v.push_back(3);
    v.push_back(2);
    std::sort(v.begin(), v.end(), compare);
    std::for_each(v.begin(), v.end(), print);
    std::sort(v.begin(), v.end(), boost::bind(compare, _2, _1));
    std::for_each(v.begin(), v.end(), print);
}

TEST_F(BoostFunctionTest, BoostFunction) {
    boost::function<int (const char*)> f = std::atoi;
    ASSERT_EQ(1609, f("1609"));
    f = std::strlen;
    ASSERT_EQ(4, f("1609"));

    boost::function<void ()> empty_func;
    try {
        empty_func();
    } catch (boost::bad_function_call& e) {
        std::cerr << e.what() << std::endl;
    }
}

