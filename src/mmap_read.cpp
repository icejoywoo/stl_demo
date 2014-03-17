/**
 * @author: icejoywoo
 * @date: 2014.3.10
 * @brief: mmap read shared memory
 */
#include <sys/mman.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char name[4];
    int age;
} person;

int main(int argc, char** argv) {
    if (argc != 2) {
        perror("usage: mmap_read <mmap file>");
        return 1;
    }
    int fd;
    person* p_list;
    fd = open(argv[1], O_CREAT|O_RDWR, 0777);
    p_list = (person*) mmap(NULL, sizeof(person)*10, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    close(fd);
    for (int i = 0; i < 10; ++i) {
        printf("name: %s, age: %d\n", (*(p_list+i)).name, (*(p_list+i)).age);
    }
    munmap(p_list, sizeof(person)*10);
    return 0;
}
