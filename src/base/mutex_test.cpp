#include <pthread.h>
#include <stdio.h>

#include "mutex.h"

using namespace icejoywoo::base;

int global = 0;
MutexLock mutex;

void* test_function(void* arg) {
    (void) arg; // unused
    for (int i = 0; i < 20; ++i) {
        {
            MutexLockGuard guard(mutex);
            ++global;
            printf("global: %d\n", global);
        }
    }
    return NULL;
}

int main() {
    pthread_t thread;
    if (pthread_create(&thread, NULL, test_function, NULL)) {
        fprintf(stderr, "pthread join error.\n");
        return -1;
    }
    for (int i = 0; i < 20; ++i) {
        {
            MutexLockGuard guard(mutex);
            ++global;
            printf("global: %d\n", global);
        }
    }
    if (pthread_join(thread, NULL)) {
        fprintf(stderr, "pthread join error.\n");
        return -1;
    }
    printf("global: %d\n", global);
    return 0;
}
