#include <iostream>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>


volatile void *shared_malloc(int size) {
    void *ptr=mmap(0,size,
        PROT_READ+PROT_WRITE,
        MAP_SHARED,
        -1,0);
    return ptr;
}

class scoped_shared_lock {
    volatile int *lock;
public:
    scoped_shared_lock(volatile int *lock_) {
        lock=lock_;
    /* FAIL:
        while (*lock!=0) {} // wait for them to finish
        // when zero,   *lock=1; // we grab the lock
    */
    // Atomic version, using assembly
        __asm__(
            "4: movl $1,%%ecx\n"
            "xchg %%ecx,(%[ptr])\n"
            "test %%ecx,%%ecx\n"
            "jnz 4b\n"
        ::[ptr] "r" (lock): "ecx");
    }
    ~scoped_shared_lock() {
        *lock=0;
    }
};

int main(void)
{
    volatile int *lock=(volatile int *)shared_malloc(sizeof(int));
    *lock=0; /* starts unlocked */
    volatile int &local=*(volatile int *)shared_malloc(sizeof(int));
    local=17;

    int pid=fork();
    if (pid != 0) { /* I am parent */
        for (int i=0;i<100;i++) {
            scoped_shared_lock lk(lock);
            local++;
            std::cout<<"Parent's copy="<<local<<" (at "<<&local<<")\n";
            std::cout.flush();
        }
        int status=0;
        waitpid(pid,&status,0);
    } else {
        for (int i=0;i<100;i++) {
            scoped_shared_lock lk(lock);
            local++;
            std::cout<<"Child copy="<<local<<" (at "<<&local<<")\n";
            std::cout.flush();
        }
    }
    return local;
}
