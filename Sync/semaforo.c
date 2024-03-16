#include "semaforo.h"
#include <pthread.h>

void semaforo_init(semaforo_t *s, int value) {
    pthread_mutex_init(&s->mutex, NULL);
    pthread_cond_init(&s->cond, NULL);
    s->count = value;
}

void semaforo_wait(semaforo_t *s) {
    pthread_mutex_lock(&s->mutex);
    while (s->count <= 0) {
        pthread_cond_wait(&s->cond, &s->mutex);
    }
    s->count--;
    pthread_mutex_unlock(&s->mutex);
}

void semaforo_signal(semaforo_t *s) {
    pthread_mutex_lock(&s->mutex);
    s->count++;
    pthread_cond_signal(&s->cond);
    pthread_mutex_unlock(&s->mutex);
}

