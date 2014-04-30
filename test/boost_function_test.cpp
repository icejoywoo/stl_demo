#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>

#include "boost/bind.hpp"
#include "boost/function.hpp"
#include "boost/lambda/lambda.hpp"
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

    // c++ 11 lambda
    std::for_each(v.begin(), v.end(), [](int i) { std::cout << i << std::endl; });

    // boost::bind
    std::for_each(v.begin(), v.end(), boost::bind(add(), 10, _1));
    std::for_each(v.begin(), v.end(), boost::bind(add(), _1, 10));

    // boost::lambda
    std::for_each(v.begin(), v.end(), std::cout << boost::lambda::_1 << "\n"); // not std::endl
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

class World {
public:
    void Hello(std::ostream& os) {
        os << "Hello, World!" << std::endl;
    }
};

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

    boost::function<void (World*, std::ostream&)> function_in_class = &World::Hello;
    World w;
    function_in_class(&w, boost::ref(std::cout));
}

int divide_by(int x, int y) {
    return x / y;
}

size_t get_size(const std::string& s) {
    return s.size();
}

TEST_F(BoostFunctionTest, BoostExercise) {
    // http://zh.highscore.de/cpp/boost/, chapter 3
    std::cout << "Exercise 1" << std::endl;

    std::vector<int> numbers;
    numbers.push_back(10);
    numbers.push_back(20);
    numbers.push_back(30);

    std::transform(numbers.begin(), numbers.end(), numbers.begin(), boost::bind(divide_by, _1, 2));

    std::for_each(numbers.begin(), numbers.end(), [](int i) { std::cout << i << std::endl; });

    std::cout << "Exercise 2" << std::endl;

    std::vector<std::string> strings;
    strings.push_back("Boost");
    strings.push_back("C++");
    strings.push_back("Libraries");

    std::vector<size_t> sizes(strings.size(), 0);

    std::transform(strings.begin(), strings.end(), sizes.begin(), boost::bind(get_size, _1));
    std::for_each(sizes.begin(), sizes.end(), [](size_t i) { std::cout << i << std::endl; });

    std::cout << "Exercise 3" << std::endl;
    std::vector<boost::function<int (const char*)> > processors;
    processors.push_back(std::atoi);
    processors.push_back(std::strlen);

    std::for_each(processors.begin(), processors.end(), [](boost::function<int (const char*)> f) { std::cout << f("1.23") << std::endl; });
}

