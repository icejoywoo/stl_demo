#include <bitset>
#include <cstdio>
#include <string>

#include "gtest/gtest.h"

class BitsetTest : public testing::Test {
public:
    virtual void SetUp() {
        m_bitset.reset();
    }

    virtual void TearDown() {
    }

    std::bitset<16> m_bitset;
};

TEST_F(BitsetTest, SetTest) {
    m_bitset.set(); // set all bits to one
    EXPECT_STREQ("1111111111111111", m_bitset.to_string().c_str());
    m_bitset.set(2, 0); // set val as the value for the bit in the pos
    EXPECT_STREQ("1111111111111011", m_bitset.to_string().c_str());
    m_bitset.set(2); // set val as one for the bit in the pos
    EXPECT_STREQ("1111111111111111", m_bitset.to_string().c_str());
}

TEST_F(BitsetTest, TransformationTest) {
    EXPECT_EQ(0x0000u, m_bitset.to_ulong());
    EXPECT_EQ(0x0000ll, m_bitset.to_ullong());
    EXPECT_STREQ("0000000000000000", m_bitset.to_string().c_str());
    m_bitset.set(); // set all bits to one
    EXPECT_EQ(0xFFFFu, m_bitset.to_ulong());
    EXPECT_EQ(0xFFFFll, m_bitset.to_ullong());
    EXPECT_STREQ("1111111111111111", m_bitset.to_string().c_str());
    m_bitset.set(3, 0); // set val as the value for the bit in the pos
    EXPECT_EQ(0xFFF7u, m_bitset.to_ulong());
    EXPECT_EQ(0xFFF7ll, m_bitset.to_ullong());
    EXPECT_STREQ("1111111111110111", m_bitset.to_string().c_str());
}

TEST_F(BitsetTest, FlipTest) {
    m_bitset.flip(); // Flips all bits in the bitset.
    EXPECT_STREQ("1111111111111111", m_bitset.to_string().c_str());
    m_bitset.flip(2); // Flip the bit at the position pos
    EXPECT_STREQ("1111111111111011", m_bitset.to_string().c_str());
}

TEST_F(BitsetTest, IteratorBits) {
    std::bitset<8> mybitset(std::string("10101010"));
    char a = 0;
    for (size_t i = 0; i < mybitset.size(); ++i) {
        EXPECT_EQ(a, mybitset[i]);
        a = !a;
    }
}

TEST_F(BitsetTest, TestBit) {
    std::bitset<8> mybitset(std::string("10101010"));
    for (size_t i = 0; i < mybitset.size(); i += 2) {
        EXPECT_EQ(false, mybitset.test(i));
        EXPECT_EQ(true, mybitset.test(i+1));
    }
}

TEST_F(BitsetTest, AnyAntCountTest) {
    std::bitset<8> mybitset(std::string("00000000"));
    EXPECT_EQ(false, mybitset.any());
    int a = 1;
    for (size_t i = 0; i < mybitset.size(); ++i) {
        mybitset.set(i);
        EXPECT_EQ(true, mybitset.any());
        EXPECT_EQ(a++, mybitset.count());
    }

}

