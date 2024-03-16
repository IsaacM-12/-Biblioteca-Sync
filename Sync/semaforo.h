#ifndef SEMAFORO_H
#define SEMAFORO_H
#include <pthread.h>

typedef struct {
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    int count;
} semaforo_t;

void semaforo_init(semaforo_t *s, int value);

void semaforo_wait(semaforo_t *s);

void semaforo_signal(semaforo_t *s);

#endif // SEMAFORO_H
