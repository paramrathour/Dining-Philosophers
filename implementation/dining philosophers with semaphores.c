#include"semaphore.h"
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

const int MAX_N = 100;
sem max;
sem forks[MAX_N];

int right(int thinker) {
    return thinker == 0 ? MAX_N - 1 : thinker - 1;
}

int left(int thinker) {
    return thinker == MAX_N - 1 ? 0 : thinker + 1;
}

void eat(int thinker) {
    printf("Philosopher %d is eating\n", thinker);
    sleep(10);
}

void think(int thinker) {
    sleep(1);
}

void * philosopher_behaviour(void * num) {
    int thinker = *(int *)num;
    think()
    pick_up_forks(thinker);
    eat(thinker);
    put_down_forks(thinker);
}

void pick_up_forks(int thinker) {
    printf("Philosopher %d is picking up forks\n", thinker);
    sem_down(&max);
    sem_down(&forks[right(thinker)]);
    sem_down(&forks[left(thinker)]);
}

void put_down_forks(int thinker) {
    printf("Philosopher %d is putting down forks\n", thinker);
    sem_down(&forks[left(thinker)]);
    sem_down(&forks[right(thinker)]);
    sem_up(&max);
}

int main() {
    int i, N = 10, schedule[N];
    pthread_t thread_id[N];
    sem_init(&max, N - 1);
    for (i = 0; i < N; i++) {
        sem_init(&forks[i], 1);
    }
    for (i = 0; i < N; i++) {
        schedule[i] = i;
        pthread_create(&thread_id[i], NULL, philosopher_behaviour, (void *)&schedule[i]);
    }
    for (i = 0; i < N; i++) {
        pthread_join(thread_id[i], NULL);
    }
}