#include "mutex.h"

using namespace icejoywoo::base;

int main() {
    MutexLock lock;
    MutexLockGuard guard(lock);
    return 0;
}
