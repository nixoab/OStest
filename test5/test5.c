#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

static void	sig_usr(int); //one handler for both signals
int pid;

int main(void) {
    while ((pid = fork()) == -1);
    if (pid == 0) {
        printf("child\n");
    }
    else {
        printf("father\n");
        signal(SIGINT, sig_usr);
    }
    for (; ; )
        pause();
}

static void sig_usr(int signo) { //argument is signal number
    printf("\nreceived signal %d, pid = %d\n", signo, pid);
    exit(1);
}
