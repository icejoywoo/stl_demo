#include <cstdio>
#include <iostream>
#include <set>
#include <string>

#include "gtest/gtest.h"

class SetTest : public testing::Test {
public:
    virtual void SetUp() {
        char temp[1024];
        for (int i = 0; i < 100; ++i) {
            snprintf(temp, sizeof(temp), "test_str_%d", i);
            std::pair<std::set<std::string>::iterator, bool> ret =
                m_set.insert(temp);
            if (!ret.second) {
                fprintf(stderr, "SetUp error");
            }
        }
    }

    virtual void TearDown() {
        m_set.clear();
    }

    std::set<std::string> m_set;
};

TEST_F(SetTest, InsertExistedElement) {
    // The pair::second element in the pair is set to true
    // if a new element was inserted or false if an equivalent
    // element already existed
    std::pair<std::set<std::string>::iterator, bool> ret = m_set.insert("test_str_0");
    EXPECT_FALSE(ret.second);
}

TEST_F(SetTest, FindElement) {
    EXPECT_EQ(0, m_set.count("test_str_100"));
    EXPECT_EQ(1, m_set.count("test_str_0"));

    std::set<std::string>::iterator it = m_set.find("test_str_0");
    EXPECT_NE(m_set.end(), it);
    EXPECT_STREQ("test_str_0", (*it).c_str());
}

