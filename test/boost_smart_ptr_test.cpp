#include <iostream>
#include <vector>

#include "boost/smart_ptr.hpp"
#include "gtest/gtest.h"

class BoostSmartPtr : public testing::Test {
public:
    virtual void SetUp() {
    }
    virtual void TearDown() {
    }
private:
};

TEST_F(BoostSmartPtr, SharedPtrVector) {
    using std::vector;
    typedef vector<boost::shared_ptr<int> >::iterator iterator;

    vector<boost::shared_ptr<int> > v;
    v.push_back(boost::shared_ptr<int>(new int(3)));
    v.push_back(boost::shared_ptr<int>(new int(4)));

    for (iterator it = v.begin(); it != v.end(); ++it) {
        std::cout << *(*it) << std::endl;
        it->reset(new int(1));
    }

    for (iterator it = v.begin(); it != v.end(); ++it) {
        std::cout << *(*it) << std::endl;
    }
}
