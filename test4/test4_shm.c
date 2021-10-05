#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>

#define key 75
#define MSG_SIZE 1024

int main() {
    int client, server;
    int* addr;
    int shmid = shmget(key, MSG_SIZE, IPC_CREAT | 0666);
    if (shmid < 0) {
        perror("id error");
        exit(1);
    }
    addr = shmat(shmid, 0, 0);
    while ((server = fork()) == -1);
    if (server == 0) {
        //sleep(1);
        for (int i = 0; i < 10; i++) {
            sleep(1);
            printf("(Server)received %d\n", addr[i]);
        }
        shmdt(addr);
        shmctl(shmid, IPC_RMID, 0);
        exit(0);
    }
    else {
        while ((client = fork()) == -1);
        if (client == 0) {
            for (int i = 0; i < 10; i++) {
                addr[i] = 10 - i;
                printf("(Client)sent %d\n", addr[i]);
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