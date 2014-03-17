#include <sys/mman.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct {
    char name[4];
    int age;
} person;

int main(int argc, char** argv) {
    if (argc != 2) {
        perror("usage: mmap_write <mmap file>");
        return 1;
    }
    int fd;
    person* p_list;
    fd = open(argv[1], O_CREAT|O_RDWR|O_TRUNC, 0777);
    lseek(fd, sizeof(person) * 5 - 1, SEEK_SET);
    write(fd, "", 1);

    p_list = (person*) mmap(NULL, sizeof(person) * 10, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    close(fd);

    char name[2];
    //name[0] = 'a';
    //name[1] = '\0';
    snprintf(name, 2, "a");
    for (int i = 0; i < 10; ++i) {
        memcpy((*(p_list+i)).name, &name, sizeof(name));
        (*(p_list+i)).age = 20 + i;
        name[0]++;
    }
    printf("Initialization is over.\n");
    sleep(10);

    munmap(p_list, sizeof(person) * 10);
    printf("munmap.\n");
    return 0;
}
