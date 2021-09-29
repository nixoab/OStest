#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
char command[256];
char command1[256];
char command2[256];

int main() {
    int rtn; //子进程的返回数值
    int errorno;
    while (1) {
        //从终端读取要执行的命令
        printf(">");
        fgets(command, 256, stdin); //stdin为标准流(键盘输入)
        fgets(command1, 256, stdin);
        fgets(command2, 256, stdin);
        command[strlen(command) - 1] = 0;
        command1[strlen(command1) - 1] = 0;
        command2[strlen(command2) - 1] = 0;
        if (fork() == 0) {
            //子进程执行此命令
            errorno = execlp(command, command1, command2, NULL);
            //如果 exec 函数返回，表明没有正常执行命令，打印错误信息
            perror(command);
            exit(errorno);
        }
        else {
            //父进程， 等待子进程结束，并打印子进程的返回值
            wait(&rtn);
            printf(" child process return %d\n", rtn);
        }
    }
    return 0;
}


