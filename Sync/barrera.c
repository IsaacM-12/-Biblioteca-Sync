#include "barrera.h"
#include <pthread.h>

void barrera_init(barrera_t *b, int total) {
    pthread_mutex_init(&b->mutex, NULL);
    pthread_cond_init(&b->cond, NULL);
    b->count = 0;
    b->total = total;
}

void barrera_wait(barrera_t *b) {
    pthread_mutex_lock(&b->mutex);
    b->count++;
    if (b->count == b->total) {
        b->count = 0; // Reset para el próximo uso
        pthread_cond_broadcast(&b->cond);
    } else {
        while (pthread_cond_wait(&b->cond, &b->mutex) != 0);
    }
    pthread_mutex_unlock(&b->mutex);
}

