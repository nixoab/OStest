#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>

#define key 75
#define MSG_SIZE 1024

struct msgt {
    long msgtype;
    char msgtext[MSG_SIZE];
}msg;

int main() {
    int client, server;
    int msgid = msgget(key, IPC_CREAT | 0666);
    if (msgid < 0) {
        perror("id error");
        exit(1);
    }
    while ((server = fork()) == -1);
    if (server == 0) {
        do {
            int snd = msgrcv(msgid, &msg, MSG_SIZE, 0, 0);
            if (snd)
                printf("(Server)received %ld\n", msg.msgtype);
            else {
                perror("receive message error");
                exit(1);
            }
        } while (msg.msgtype != 1);
        msgctl(msgid, IPC_RMID, 0);
        exit(0);
    }
    else {
        while ((client = fork()) == -1);
        if (client == 0) {
            for (int i = 10; i > 0; i--) {
                msg.msgtype = i;
                int snd = msgsnd(msgid, &msg, MSG_SIZE, 0);
                if (snd == 0)
                    printf("(Client)sent %d\n", i);
                else {
                    perror("send message error");
                    exit(1);
                }
                sleep(1);
            }
            exit(0);
        }
        else {
            wait(0);
            wait(0);
            exit(0);
        }
    }
    return 0;
}