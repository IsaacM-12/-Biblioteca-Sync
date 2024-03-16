#ifndef BARRERA_H
#define BARRERA_H
#include <pthread.h>

typedef struct {
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    int count;
    int total;
} barrera_t;

void barrera_init(barrera_t *b, int total);

void barrera_wait(barrera_t *b);

#endif // BARRERA_H
