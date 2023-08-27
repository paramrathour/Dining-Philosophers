#include<pthread.h>

typedef struct semaphore {
    int counter;
    pthread_mutex_t lock;
    pthread_cond_t signal;
} sem;

void sem_init(sem *, int);
void sem_up(sem *);
void sem_down(sem *);