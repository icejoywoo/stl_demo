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
