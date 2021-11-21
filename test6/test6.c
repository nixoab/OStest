/* example.c*/
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

void myThread1(void* argv) {
    int thread1 = *(int*)argv;
    printf("This is myThread1, int = %d.\n", thread1);
}

void myThread2(void* argv) {
    char thread2 = *(char*)argv;
    printf("This is myThread2, char = %c.\n", thread2);
}

int main(void) {
    pthread_t id1, id2;
    int ret1, ret2;
    int thread1 = 1;
    char thread2 = 'a';
    ret1 = pthread_create(&id1, NULL, (void*)myThread1, (void*)&thread1);
    if (ret1 != 0) {
        printf("Create myThread1 error!\n");
        exit(1);
    }
    ret2 = pthread_create(&id2, NULL, (void*)myThread2, (void*)&thread2);
    if (ret2 != 0) {
        printf("Create myThread2 error!\n");
        exit(1);
    }
    pthread_join(id1, NULL);
    pthread_join(id2, NULL);
    return (0);
}