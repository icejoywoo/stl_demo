#include <iostream>
#include <vector>

#include "boost/smart_ptr.hpp"
#include "boost/tuple/tuple.hpp"
#include "boost/tuple/tuple_comparison.hpp"
#include "boost/tuple/tuple_io.hpp"
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

TEST_F(BoostSmartPtr, TupleTest) {
    {
        typedef boost::tuple<std::string, std::string> person;
        person p("Boris", "Schaeling");
        std::cout << p << std::endl; // need tuple_io.hpp
        std::cout << p.get<0>() << std::endl;
        std::cout << p.get<1>() << std::endl;
        p.get<0>() = "Modified Boris";
        std::cout << p << std::endl;

        std::cout << boost::make_tuple("Boris", "Schaeling", 43) << std::endl;
    }
    
    {
        typedef boost::tuple<std::string, std::string, int> person; 
        person p1 = boost::make_tuple("Boris", "Schaeling", 43); 
        person p2 = boost::make_tuple("Boris", "Becker", 43); 
        std::cout << (p1 != p2) << std::endl; 
    }

    {
        typedef boost::tuple<std::string&, std::string&, int&> person; 

        std::string firstname = "Boris"; 
        std::string surname = "Schaeling"; 
        int shoesize = 43; 
        // boost::tie is a reference tuple
        person p = boost::tie(firstname, surname, shoesize); // same meaming with the setence belows
        // person p = boost::make_tuple(boost::ref(firstname), boost::ref(surname), boost::ref(shoesize)); 
        surname = "Becker"; 
        std::cout << p << std::endl; 
    }
}

