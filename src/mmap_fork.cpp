#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void) {
    size_t length = 1024 * 1024;
    off_t offset = 0;
    int prot = (PROT_READ| PROT_WRITE);
    int flags = MAP_SHARED;
    int fd = -1;
    pid_t pid;

    /*
     * Create file we are using for mmap. The file must be
     * size of memory we wish to map.
     */
    fd = open("./jim.mymemory", O_RDWR| O_CREAT, S_IRUSR| S_IWUSR );
    if (fd == 0) {
        int myerr = errno;
        printf("ERROR: open failed (errno %d %s)\n", myerr, strerror(myerr));
        return EXIT_FAILURE;
    }
    if (lseek(fd, length - 1, SEEK_SET) == -1) {
        int myerr = errno;
        printf("ERROR: lseek failed (errno %d %s)\n", myerr, strerror(myerr));
        return EXIT_FAILURE;
    }
    write(fd, "", 1);

    /*
     * Fork a child process to write to shared memory.
     * In the parent we simply wait for value to be written.
     */
    if ((pid = fork()) == 0) {
        /*Child process*/
        void * addr = 0;
        addr = mmap(NULL, length, prot, flags, fd, offset);
        if (addr == 0) {
            int myerr = errno;
            printf("ERROR (child): mmap failed (errno %d %s)\n", myerr,
                    strerror(myerr));
        }

        /*Write to memory*/
        printf("INFO (child): start write\n");
        *((int *) addr) = 0xcafebabe;
        printf("INFO (child): done write\n");

        /*
         * Call sync or parent will not see update until munmap is called.
         * Try commenting the below line out for fun.
         */
        msync(addr,sizeof(int),MS_SYNC|MS_INVALIDATE);

        /*Sleep to demonstrate msync*/
        printf("INFO (child): sleep start\n");
        sleep(5);/*Note: sleep seems to cause msync. Kinda interesting!*/
        printf("INFO (child): sleep done\n");

        if (munmap(addr, length) == -1) {
            int myerr = errno;
            printf("ERROR (child): munmap failed (errno %d %s)\n", myerr,
                    strerror(myerr));
        }
    } else {
        /*Parent process*/
        void * addr = 0;
        unsigned int readval = 0;
        addr = mmap(NULL, length, prot, flags, fd, offset);
        if (addr == 0) {
            int myerr = errno;
            printf("ERROR (parent): mmap failed (errno %d %s)\n", myerr,
                    strerror(myerr));
        }

        printf("INFO (parent): start read\n");
        while (readval != 0xcafebabe) {
            readval = *((int *) addr);
        }
        printf("INFO (parent): read value: %u, 0x%X\n", readval, readval);
        printf("INFO (parent): done read\n");

        if (munmap(addr, length) == -1) {
            int myerr = errno;
            printf("ERROR (parent): munmap failed (errno %d %s)\n", myerr,
                    strerror(myerr));
        }

        // wait child process
        int status;
        waitpid(pid, &status, 0);
    }

    if (close(fd) == -1) {
        int myerr = errno;
        printf("ERROR: close failed (errno %d %s)\n", myerr, strerror(myerr));
    }
    unlink ("./jim.mymemory");
    return EXIT_SUCCESS;
}
