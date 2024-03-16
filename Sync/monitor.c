#include "monitor.h"
#include <pthread.h>
#include <stdio.h>

// Inicializa el monitor
void monitor_init(monitor_t *m) {
    pthread_mutex_init(&m->mutex, NULL);
    pthread_cond_init(&m->cond, NULL);
}

// Entra a la sección crítica del monitor
void monitor_enter(monitor_t *m) {
    pthread_mutex_lock(&m->mutex);
}

// Sale de la sección crítica del monitor
void monitor_exit(monitor_t *m) {
    pthread_mutex_unlock(&m->mutex);
}

// Espera a que se cumpla una condición dentro del monitor
void monitor_wait(monitor_t *m) {
    pthread_cond_wait(&m->cond, &m->mutex);
}

// Señaliza a un hilo que espera que la condición se ha cumplido
void monitor_signal(monitor_t *m) {
    pthread_cond_signal(&m->cond);
}

// Señaliza a todos los hilos que esperan que la condición se ha cumplido
void monitor_broadcast(monitor_t *m) {
    pthread_cond_broadcast(&m->cond);
}

