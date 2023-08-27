#include"semaphore.h"
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<string.h>
#include<signal.h>
#include<errno.h>
#include<wait.h>

void sem_init(sem *s, int value) {
    s -> counter = value;
    if (pthread_cond_init(&s -> signal, NULL) != 0) {
        perror("pthread_cond_init() error");
        exit(1);
    }
    if (pthread_mutex_init(&s -> lock, NULL) != 0) {
        perror("pthread_mutex_init() error");
        exit(1);
    }
}

void sem_down(sem *s) {
    pthread_mutex_lock(&s -> lock);
    s -> counter--;
    if (s -> counter < 0)
        pthread_cond_wait(&s -> signal, &s -> lock);
    pthread_mutex_unlock(&s -> lock);
}

void sem_up(sem *s) {
    pthread_mutex_lock(&s -> lock);
    s -> counter++;
    pthread_cond_signal(&s -> signal);
    pthread_mutex_unlock(&s -> lock);
}