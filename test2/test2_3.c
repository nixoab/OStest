#include <stdio.h>
#include <unistd.h>

#define MSG 30 //定义消息长度
char* MSG_1 = "Child 1 is sending a message!";
char* MSG_2 = "Child 2 is sending a message!";

int main() {
    char buffer[MSG];
    int p[2];
    pipe(p);
    int pid1, pid2;
    while (pid1 = fork() == -1); //创建子进程1
    if (pid1 == 0) {
        close(p[0]); //关闭读通道
        write(p[1], MSG_1, MSG); //写入MSG_1
    }
    else {
        while (pid2 = fork() == -1); //创建子进程2
        if (pid2 == 0) {
            close(p[0]); //关闭读通道
            write(p[1], MSG_2, MSG); //写入MSG_2
        }
        else { //父进程
            close(p[1]); //关闭写通道
            for (int i = 0; i < 2; i++) {
                read(p[0], buffer, MSG); //读取通道内信息存入buffer
                printf("%s\n", buffer);
            }
        }
    }
    return 0;
}
