#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

/// refer: http://coolshell.cn/articles/7965.html
int main(void) {
    for (int i = 0; i < 2; ++i) {
        fork();
        // fork 会让子进程将缓冲区一并复制过去
        printf("-");
    }
    printf("\n");
    return 0;
}
