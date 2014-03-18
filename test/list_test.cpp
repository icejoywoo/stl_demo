#include <cstdio>
#include <iostream>
#include <list>

#include "gtest/gtest.h"

class ListTest : public testing::Test {
public:
    virtual void SetUp() {
        char a = 'a';
        for (size_t i = 0; i < 26; ++i) {
            m_list.push_back(a + i);
        }
    }

    virtual void TearDown() {
        m_list.clear();
    }

    std::list<char> m_list;
};

TEST_F(ListTest, BasicInit) {
    std::list<char> letters(m_list.begin(), m_list.end());
    char a = 'a';
    for (std::list<char>::iterator it = letters.begin();
            it != letters.end(); ++it) {
        EXPECT_EQ(a++, *it);
    }
    EXPECT_EQ(26, m_list.size());
    printf("max_size: %lu\n", m_list.max_size());
}

TEST_F(ListTest, IterateElements) {
    // iterator
    char a = 'a';
    for (std::list<char>::iterator it = m_list.begin();
            it != m_list.end(); ++it) {
        EXPECT_EQ(a++, *it);
        printf("%c", *it);
    }
    printf("\n");

    a = 'a';
    for (std::list<char>::const_iterator it = m_list.cbegin();
            it != m_list.cend(); ++it) {
        EXPECT_EQ(a++, *it);
    }
}
