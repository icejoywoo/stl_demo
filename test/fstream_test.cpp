#include <iostream>
#include <fstream>
#include <string>

#include "gtest/gtest.h"

class FstreamTest : public testing::Test {
public:
    virtual void SetUp() {
    }
    virtual void TearDown() {
    }
};

TEST_F(FstreamTest, ReadFileLineByLine) {
    std::ifstream in("README.md");
    ASSERT_TRUE(in); // error checking
    // read line by line
    char temp[1024];
    while (in.getline(temp, sizeof(temp))) {
        printf("%s\n", temp);
    }
    
    // seek to beg, ATTENTION: clear first, then seekg
    in.clear();
    in.seekg(0, std::ios::beg);

    std::string line;
    while (std::getline(in, line)) {
        printf("%s\n", line.c_str());
    }

    in.close();
}

TEST_F(FstreamTest, ReadFileWordByWord) {
    std::ifstream in("README.md");
    std::string word;
    // 以空白字符为分割
    while (in >> word) {
        printf("%s\n", word.c_str());
    }
    in.close();
}

