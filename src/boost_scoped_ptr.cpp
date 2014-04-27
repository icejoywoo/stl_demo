#include <cstdio>
#include <unistd.h>

#include "boost/scoped_ptr.hpp"

class Foo {
public:
    explicit Foo() {
        id = counter++;
        printf("Contructing Foo %d object...\n", id);
    }

    ~Foo() {
        printf("Destroying Foo %d object...\n", id);
    }
private:
    int id;
    static int counter;
};

int Foo::counter = 0;

int main() {
    // 利用析构函数来释放指针，不能转移所有权(ownership)
    boost::scoped_ptr<int> i(new int());
    *i = 3;
    printf("%d\n", *i);
    *i.get() = 2;
    printf("%d\n", *i);

    i.reset(new int(5));
    printf("%d\n", *i);

    try {
        // 离开作用域会自动被销毁
        boost::scoped_ptr<Foo> f(new Foo);
        f.reset(new Foo);
        throw "Test Exception";
    } catch (...) {
        fprintf(stderr, "Exception caught.\n");
    }
    usleep(1000000);

    printf("end of the main.\n");

    return 0;
}
