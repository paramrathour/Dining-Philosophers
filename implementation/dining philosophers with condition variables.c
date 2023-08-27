#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<string.h>
#include<signal.h>
#include<errno.h>
#include<wait.h>
#include<unistd.h>
#include<pthread.h>

const int MAX_N = 100;
pthread_cond_t c[MAX_N];
enum state {Eating, Thinking};
enum state x[MAX_N];
pthread_mutex_t lock;

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
    pthread_mutex_lock(lock);
    printf("Philosopher %d is picking up forks\n", thinker);
    while (x[right(thinker)] == Eating || x[left(thinker)] == Eating) {
        pthread_cond_wait(c[i], lock);
    }
    x[thinker] = Eating;
    pthread_mutex_unlock(lock);
}

void put_down_forks(int thinker) {
    pthread_mutex_lock(lock);
    printf("Philosopher %d is putting down forks\n", thinker);
    x[thinker] = Thinking;
    if (x[right(right(thinker))] == Thinking) {
        pthread_cond_signal(c[right(thinker)]);
    }
    if (x[left(left(thinker))] == Thinking) {
        pthread_cond_signal(c[left(thinker)]);
    }
    pthread_mutex_unlock(lock);
}

int main() {
    int i, N = 10, schedule[N];
    pthread_t thread_id[N];
    for (i = 0; i < N; i++) {
        x[i] = Thinking;
    }
    for (i = 0; i < N; i++) {
        schedule[i] = i;
        pthread_create(&thread_id[i], NULL, philosopher_behaviour, (void *)&schedule[i]);
    }
    for (i = 0; i < N; i++) {
        pthread_join(thread_id[i], NULL);
    }
}