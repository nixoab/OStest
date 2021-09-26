#include <stdio.h>
#include <unistd.h>

int main() {
    int pid1, pid2;
    if (pid1 = fork() != 0) //子进程1创建成功
        printf("b\n");
    else if (pid2 = fork() != 0) //子进程2创建成功
        printf("c\n");
    else //父进程
        printf("a\n");
    return 0;
}
