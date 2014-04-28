#include <string>
#include "Poco/Format.h" // for format
#include "Poco/NumberFormatter.h" // for NumberFormatter class
#include "Poco/String.h"

#include "gtest/gtest.h"

class PocoStringsTest : public testing::Test {
public:
    virtual void SetUp() {
    }

    virtual void TearDown() {
    }
private:

};

TEST_F(PocoStringsTest, StringTrim) {
    using Poco::trim;
    using Poco::trimInPlace;
    using Poco::trimLeft;
    using Poco::trimLeftInPlace;
    using Poco::trimRight;
    using Poco::trimRightInPlace;

    // trim left
    std::string left_string("   \t\nHello, World!\t\n  ");
    std::string trim_left_result = trimLeft(left_string);
    ASSERT_STREQ("Hello, World!\t\n  ", trim_left_result.c_str());
    // "in place" means that a function that directly modiﬁes the original string
    ASSERT_STREQ("Hello, World!\t\n  ", trimLeftInPlace(left_string).c_str());
    ASSERT_STREQ("Hello, World!\t\n  ", left_string.c_str());

    // trim right
    std::string right_string("   \t\nHello, World!\t\n  ");
    std::string trim_right_result = trimRight(right_string);
    ASSERT_STREQ("   \t\nHello, World!", trim_right_result.c_str());
    // in place
    ASSERT_STREQ("   \t\nHello, World!", trimRightInPlace(right_string).c_str());
    ASSERT_STREQ("   \t\nHello, World!", right_string.c_str());

    // trim
    std::string trim_string("   \t\nHello, World!\t\n  ");
    std::string trim_result = trim(trim_string);
    ASSERT_STREQ("Hello, World!", trim_result.c_str());
    // in place
    ASSERT_STREQ("Hello, World!", trimInPlace(trim_string).c_str());
    ASSERT_STREQ("Hello, World!", trim_string.c_str());
}

TEST_F(PocoStringsTest, StringCaseConversion) {
    using Poco::toUpper;
    using Poco::toUpperInPlace;
    using Poco::toLower;
    using Poco::toLowerInPlace;

    // upper
    std::string hello_to_upper("Hello, World!");
    std::string upper_result = toUpper(hello_to_upper);
    ASSERT_STREQ("HELLO, WORLD!", upper_result.c_str());
    // in place
    ASSERT_STREQ("HELLO, WORLD!", toUpperInPlace(hello_to_upper).c_str());
    ASSERT_STREQ("HELLO, WORLD!", hello_to_upper.c_str());

    // lower
    std::string hello_to_lower("Hello, World!");
    std::string lower_result = toLower(hello_to_lower);
    ASSERT_STREQ("hello, world!", lower_result.c_str());
    ASSERT_STREQ("hello, world!", toLowerInPlace(hello_to_lower).c_str());
    ASSERT_STREQ("hello, world!", hello_to_lower.c_str());
}

TEST_F(PocoStringsTest, StringCaseInsensitiveComparison) {
    using Poco::icompare;

    std::string str1("hello");
    std::string str2("HellO");
    std::string str3("world");
    ASSERT_EQ(0, icompare(str1, str2)); // for std::string
    ASSERT_EQ(-1, icompare(str1, str3)); // for std::string
    ASSERT_EQ(1, icompare(str3, str1)); // for std::string
    //ASSERT_EQ(0, icompare("world", "World")); // cannot for const char*
}

TEST_F(PocoStringsTest, StringTranslate) {
    using Poco::translate;
    using Poco::translateInPlace;

    std::string string_to_translate("eacdb1234");
    std::string translate_result = translate(string_to_translate, "abcde", "ABCDE");
    ASSERT_STREQ("EACDB1234", translate_result.c_str());
    // in place
    ASSERT_STREQ("EACDB1234", translateInPlace(string_to_translate, "abcde", "ABCDE").c_str());
    ASSERT_STREQ("EACDB1234", string_to_translate.c_str());
}

TEST_F(PocoStringsTest, StringReplace) {
    using Poco::replace;
    using Poco::replaceInPlace;

    std::string string_to_replace("abcaabbcc");
    ASSERT_TRUE(replace(string_to_replace, "aa", "") == "abcbbcc");
    ASSERT_TRUE(replaceInPlace(string_to_replace, "aa", "") == "abcbbcc");
}

TEST_F(PocoStringsTest, StringCat) {
    using Poco::cat;

    // append strings
    std::string s1("one");
    std::string s2("two");
    std::string s3("three");
    std::string s4("four");
    std::string s5("five");
    std::string s6("six");

    ASSERT_TRUE(cat(s1, s2) == "onetwo");
    ASSERT_TRUE(cat(s1, s2, s3) == "onetwothree");

    std::vector<std::string> vec;
    ASSERT_TRUE(cat(std::string(), vec.begin(), vec.end()) == "");
    ASSERT_TRUE(cat(std::string(","), vec.begin(), vec.end()) == "");
    vec.push_back(s1);
    ASSERT_TRUE(cat(std::string(), vec.begin(), vec.end()) == "one");
    ASSERT_TRUE(cat(std::string(","), vec.begin(), vec.end()) == "one");
    vec.push_back(s2);
    ASSERT_TRUE(cat(std::string(), vec.begin(), vec.end()) == "onetwo");
    ASSERT_TRUE(cat(std::string(","), vec.begin(), vec.end()) == "one,two");
    vec.push_back(s3);
    ASSERT_TRUE(cat(std::string(), vec.begin(), vec.end()) == "onetwothree");
    ASSERT_TRUE(cat(std::string(","), vec.begin(), vec.end()) == "one,two,three");
}

TEST_F(PocoStringsTest, NumberFormat) {
    using Poco::NumberFormatter;
    std::string str;
    ASSERT_TRUE(NumberFormatter::format(123) == "123");
    // for integer, param 2 is width
    ASSERT_TRUE(NumberFormatter::format(123, 5) == "  123");
    ASSERT_TRUE(NumberFormatter::format(-123, 5) == " -123");
    ASSERT_TRUE(NumberFormatter::format0(123, 5) == "00123");
    ASSERT_TRUE(NumberFormatter::format0(-123, 5) == "-0123");
    // for float, param 2 is precision, param 3 is width
    ASSERT_TRUE(NumberFormatter::format(1.5) == "1.5");
    ASSERT_TRUE(NumberFormatter::format(1.5, 2) == "1.50");
    ASSERT_TRUE(NumberFormatter::format(1.5234, 2) == "1.52");
    ASSERT_TRUE(NumberFormatter::format(1.5254, 2) == "1.53");
    // for pointer
    if (sizeof(void*) == 4) {
        std::cout << "32bit" << std::endl;
        ASSERT_TRUE(NumberFormatter::format((void*) 0x12345678) == "12345678");
    } else {
        std::cout << "64bit" << std::endl;
        ASSERT_TRUE(NumberFormatter::format((void*) 0x12345678) == "0000000012345678");
    }
}

TEST_F(PocoStringsTest, PrintfStyleFormat) {
}
