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

TEST_F(SetTest, IterateElements) {
    for (std::set<std::string>::iterator it = m_set.begin();
            it != m_set.end(); ++it) {
        printf("%s\n", (*it).c_str()); // order by alphabet
    }
}

TEST_F(SetTest, IterateElementsLess) {
    std::set<int> int_set;
    for (int i = 0; i < 100; ++i) {
        int_set.insert(i);
    }
    int a = 0;
    for (std::set<int>::iterator it = int_set.begin();
            it != int_set.end(); ++it) {
        EXPECT_EQ(a++, *it);
    }
}

TEST_F(SetTest, IterateElementsGreater) {
    std::set<int, std::greater<int> > int_set;
    for (int i = 0; i < 100; ++i) {
        int_set.insert(i);
    }
    int a = 99;
    for (std::set<int>::iterator it = int_set.begin();
            it != int_set.end(); ++it) {
        EXPECT_EQ(a--, *it);
    }
}

TEST_F(SetTest, EraseElement) {
    EXPECT_EQ(0, m_set.erase("test_str_100"));
    EXPECT_EQ(1, m_set.erase("test_str_0"));
    EXPECT_EQ(99, m_set.size());

    // m_set.erase(m_set.find("test_str_200")); // raise a core dump
    m_set.erase(m_set.find("test_str_1"));
    EXPECT_EQ(98, m_set.size());

    std::set<std::string>::iterator begin = m_set.find("test_str_80");
    std::set<std::string>::iterator end = m_set.find("test_str_9");
    m_set.erase(begin, end);
    EXPECT_EQ(88, m_set.size());
}

TEST_F(SetTest, BoundTest) {
    std::set<std::string>::iterator lower = m_set.lower_bound("test_str_80");
    std::set<std::string>::iterator upper = m_set.upper_bound("test_str_89");
    int a = 80;
    for (std::set<std::string>::iterator it = lower; it != upper; ++it) {
        char temp[1024];
        snprintf(temp, sizeof(temp), "test_str_%d", a++);
        EXPECT_STREQ(temp, (*it).c_str());
    }
}

TEST_F(SetTest, EqualRangeTest) {
    std::pair<std::set<std::string>::const_iterator,std::set<std::string>::const_iterator> ret;
    ret = m_set.equal_range("test_str_0");
    EXPECT_STREQ("test_str_0", (*ret.first).c_str());
    EXPECT_STREQ("test_str_1", (*ret.second).c_str());
}

