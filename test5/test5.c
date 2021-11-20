#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

static void	sig_usr(int);	/* one handler for both signals */
int pid;

int main(void) {
    while ((pid = fork()) == -1);
    if (pid == 0) {
        signal(SIGINT, sig_usr);
        signal(SIGUSR1, sig_usr);
    }
    else {
        signal(SIGINT, sig_usr);
        signal(SIGUSR2, sig_usr);
    }
    for (; ; )
        pause();
}

static void
sig_usr(int signo)		/* argument is signal number */
{
    printf("received signal %d\npid = %d\n", signo, pid);
}