#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "gtest/gtest.h"

class SstreamTest : public testing::Test {
public:
    virtual void SetUp() {
    }

    virtual void TearDown() {
    }
};

TEST_F(SstreamTest, SplitWords) {
    const char* input = "This is a word";
    std::stringstream stream;
    stream << input;
    std::string temp;
    std::vector<std::string> result;
    while (stream >> temp) {
        result.push_back(temp);
    }

    for (std::vector<std::string>::iterator it = result.begin();
            it != result.end(); ++it) {
        printf("%s\n", it->c_str());
    }

    std::vector<std::string> expected;
    expected.push_back("This");
    expected.push_back("is");
    expected.push_back("a");
    expected.push_back("word");
    EXPECT_EQ(expected, result);
    printf("%d\n", expected == result);
}

TEST_F(SstreamTest, IntConvertToString) {
    int number = 12345;
    std::stringstream stream;
    std::string temp;
    stream << number;
    stream >> temp;
    EXPECT_STREQ("12345", temp.c_str());
    stream.clear();
}

TEST_F(SstreamTest, StringConvertToInt) {
    std::string str("12345");
    std::stringstream stream;
    int number;
    stream << str;
    stream >> number;
    EXPECT_EQ(12345, number);
    stream.clear();
}
