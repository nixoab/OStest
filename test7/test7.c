#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>
#include <assert.h>

int a[2];
sem_t read, compute;

void thread1(void) {
    assert(sem_wait(&read) == 0);
    printf("This is thread1.\n");
    FILE* file = NULL;
    file = fopen("data1.txt", "r");
    fscanf(file, "%d", &a[0]);
    printf("data1 = %d\n", a[0]);
    fclose(file);
    assert(sem_post(&read) == 0);
    //assert(sem_post(&compute) == 0);
}

void thread2(void) {
    assert(sem_wait(&read) == 0);
    printf("This is thread2.\n");
    FILE* file = NULL;
    file = fopen("data2.txt", "r");
    fscanf(file, "%d", &a[1]);
    printf("data2 = %d\n", a[1]);
    fclose(file);
    assert(sem_post(&read) == 0);
    assert(sem_post(&compute) == 0);
}

void thread3(void) {
    assert(sem_wait(&compute) == 0);
    printf("This is thread3.\n");
    printf("%d + %d = %d\n", a[0], a[1], a[0] + a[1]);
    assert(sem_post(&compute) == 0);
}

void thread4(void) {
    assert(sem_wait(&compute) == 0);
    printf("This is thread4.\n");
    printf("%d * %d = %d\n", a[0], a[1], a[0] * a[1]);
    assert(sem_post(&compute) == 0);
}

int main(void) {
    pthread_t id1, id2, id3, id4;
    int ret1, ret2, ret3, ret4;
    assert(sem_init(&read, 0, 1) == 0);
    assert(sem_init(&compute, 0, 0) == 0);
    assert(pthread_create(&id1, NULL, (void*)thread1, NULL) == 0);
    assert(pthread_create(&id2, NULL, (void*)thread2, NULL) == 0);
    assert(pthread_create(&id3, NULL, (void*)thread3, NULL) == 0);
    assert(pthread_create(&id4, NULL, (void*)thread4, NULL) == 0);
    pthread_join(id1, NULL);
    pthread_join(id2, NULL);
    pthread_join(id3, NULL);
    pthread_join(id4, NULL);
    return 0;
}