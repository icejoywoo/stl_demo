#include <iostream>
#include <string>

#include "Poco/String.h"

using Poco::trim;
using Poco::trimLeft;
using Poco::trimRight;
using Poco::trimRightInPlace;

int main(int argc, char* argv[]) {
    std::string hello("   Hello, World!\t   ");
    std::cout << hello << std::endl;

    std::string s1(trimLeft(hello));
    std::cout << s1 << std::endl;
    std::cout << trimRightInPlace(s1) << std::endl;
    std::cout << s1 << std::endl;

    std::string s2(trim(hello));
    std::cout << s2 << std::endl;

    return 0;
}
