#ifndef MONITOR_H
#define MONITOR_H

#include <pthread.h>

typedef struct {
    pthread_mutex_t mutex;
    pthread_cond_t cond;
} monitor_t;

void monitor_init(monitor_t *m);
void monitor_enter(monitor_t *m);
void monitor_exit(monitor_t *m);
void monitor_wait(monitor_t *m);
void monitor_signal(monitor_t *m);
void monitor_broadcast(monitor_t *m);

#endif // MONITOR_H

