#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#include "mutex.h"

using namespace icejoywoo::base;

int global = 0;
MutexLock mutex;

void* test_function(void* arg) {
    int id = *((int*) arg);
    for (int i = 0; i < 20; ++i) {
        {
            MutexLockGuard guard(mutex);
            ++global;
            printf("global in thread %d: %d\n", id, global);
            usleep(100);
        }
    }
    return NULL;
}

int main() {
    pthread_t thread[20];
    for (int i = 0; i < 20; ++i) {
        if (pthread_create(&thread[i], NULL, test_function, (void*)&i)) {
            fprintf(stderr, "pthread join error.\n");
            return -1;
        }
    }

    for (int i = 0; i < 20; ++i) {
        {
            MutexLockGuard guard(mutex);
            ++global;
            printf("global in main: %d\n", global);
            usleep(500);
        }
    }

    for (int i = 0; i < 20; ++i) {
        if (pthread_join(thread[i], NULL)) {
            fprintf(stderr, "pthread join error.\n");
            return -1;
        }
    }
    printf("global: %d\n", global);
    return 0;
}
