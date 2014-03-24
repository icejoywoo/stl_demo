#include <cstdio>
#include <map>
#include <string>

#include "gtest/gtest.h"

class MapTest : public testing::Test {
public:
    virtual void SetUp() {
        char temp[1024];
        for (int i = 0; i < 100; ++i) {
            snprintf(temp, sizeof(temp), "test_%d", i);
            m_map[i] = std::string(temp);
        }
    }

    virtual void TearDown() {
        m_map.clear();
    }

    std::map<int, std::string> m_map;
};

TEST_F(MapTest, IterateElements) {
    char temp[1024];
    for (int i = 0; i < (int)m_map.size(); ++i) {
        snprintf(temp, sizeof(temp), "test_%d", i);
        EXPECT_STREQ(temp, m_map[i].c_str());
    }
    EXPECT_EQ(100, m_map.size());
}

TEST_F(MapTest, InsertElements) {
    std::map<int, int> id_mapping;
    id_mapping.insert(std::make_pair(1, 1));
    id_mapping.insert(std::make_pair(2, 2));
    id_mapping.insert(std::make_pair(3, 3));
    id_mapping.insert(std::make_pair(4, 4));
    for (std::map<int, int>::iterator it = id_mapping.begin();
            it != id_mapping.end();) {
        printf("%d: %d\n", it->first, it->second);
        if (it->first == 4) {
            std::pair<std::map<int, int>::iterator, bool> ret = id_mapping.insert(std::make_pair(5, 5));
            it = ret.first;
        } else {
            ++it;
        }
    }
}

TEST_F(MapTest, CustomKeyComparator) {
    std::map<int, int, std::greater<int> > int_map;
    typedef std::map<int, int, std::greater<int> >::iterator iterator_type;
    for (int i = 0; i < 10; ++i) {
        int_map.insert(std::make_pair(i, i));
    }

    int a = 9;
    for (iterator_type it = int_map.begin(); it != int_map.end(); ++it) {
        EXPECT_EQ(a, it->first);
        EXPECT_EQ(a, it->second);
        --a;
    }
}

TEST_F(MapTest, EraseElement) {
    m_map.erase(m_map.find(0));
    EXPECT_EQ(99, m_map.size());

    EXPECT_EQ(1, m_map.erase(1));
    EXPECT_EQ(98, m_map.size());
    m_map.erase(m_map.find(90), m_map.end());
    EXPECT_EQ(88, m_map.size());
    
    EXPECT_EQ(0, m_map.count(1));
    EXPECT_EQ(1, m_map.count(5));
}

TEST_F(MapTest, MultimapTest) {
    std::multimap<int, int> multimap;
    for (int i = 0; i < 10; ++i) {
        multimap.insert(std::make_pair(i, i));
        multimap.insert(std::make_pair(i, i));
    }

    EXPECT_EQ(2, multimap.erase(0));
    typedef std::multimap<int, int>::iterator iterator_type;
    for (iterator_type it = multimap.begin(); it != multimap.end();) {
        printf("%d: %d\n", it->first, it->second);
        multimap.erase(it++);
    }
    
}
