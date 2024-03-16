#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // Para sleep()

#define NUM_HILOS 5
#define NUM_ITERACIONES 2

// Estructura y funciones de semáforo
#include "semaforo.c"

// Estructura y funciones de monitor (adaptadas sin semáforo)
#include "monitor.c"

// Estructura y funciones de barrera
#include "barrera.c"

// Prototipos de las funciones de ejemplo
void* tarea_semaforo(void* arg);
void* tarea_monitor(void* arg);
void* tarea_barrera(void* arg);
void ejemplo_semaforo();
void ejemplo_monitor();
void ejemplo_barrera();

int contador = 0; // Variable compartida para semáforo y monitor
semaforo_t sem;
monitor_t mi_monitor;
barrera_t bar;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Uso: %s [semaforo|monitor|barrera]\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "semaforo") == 0) {
        ejemplo_semaforo();
    } else if (strcmp(argv[1], "monitor") == 0) {
        ejemplo_monitor();
    } else if (strcmp(argv[1], "barrera") == 0) {
        ejemplo_barrera();
    } else {
        printf("Opción no reconocida: %s\n", argv[1]);
        printf("Uso: %s [semaforo|monitor|barrera]\n", argv[0]);
        return 1;
    }

    return 0;
}

// Implementaciones de las funciones de ejemplo

// Semáforo
void ejemplo_semaforo() {
    pthread_t hilos[NUM_HILOS];
    semaforo_init(&sem, 1); // Inicializa el semáforo para permitir 1 hilo en la sección crítica

    for (int i = 0; i < NUM_HILOS; i++) {
        pthread_create(&hilos[i], NULL, tarea_semaforo, NULL);
    }

    for (int i = 0; i < NUM_HILOS; i++) {
        pthread_join(hilos[i], NULL);
    }

    printf("Ejemplo semáforo completado. Contador: %d\n", contador);
}

void* tarea_semaforo(void* arg) {
    for (int i = 0; i < NUM_ITERACIONES; i++) {
        semaforo_wait(&sem);
        contador++;
        printf("Semaforo - Hilo %ld incrementó el contador a %d\n", pthread_self(), contador);
        semaforo_signal(&sem);
    }
    return NULL;
}

// Monitor
void ejemplo_monitor() {
    pthread_t hilos[NUM_HILOS];
    monitor_init(&mi_monitor);

    for (int i = 0; i < NUM_HILOS; i++) {
        pthread_create(&hilos[i], NULL, tarea_monitor, NULL);
    }

    for (int i = 0; i < NUM_HILOS; i++) {
        pthread_join(hilos[i], NULL);
    }

    printf("Ejemplo monitor completado. Contador: %d\n", contador);
}

void* tarea_monitor(void* arg) {
    for (int i = 0; i < NUM_ITERACIONES; i++) {
        monitor_enter(&mi_monitor);
        contador++;
        printf("Monitor - Hilo %ld incrementó el contador a %d\n", pthread_self(), contador);
        monitor_exit(&mi_monitor);
    }
    return NULL;
}

// Barrera
void ejemplo_barrera() {
    pthread_t hilos[NUM_HILOS];
    barrera_init(&bar, NUM_HILOS); // Inicializa la barrera para NUM_HILOS hilos

    for (int i = 0; i < NUM_HILOS; i++) {
        pthread_create(&hilos[i], NULL, tarea_barrera, (void*)(size_t)i);
    }

    for (int i = 0; i < NUM_HILOS; i++) {
        pthread_join(hilos[i], NULL);
    }

    printf("Ejemplo barrera completado.\n");
}

void* tarea_barrera(void* arg) {
    int id = (int)(size_t)arg;
    printf("Barrera - Hilo %d llegó a la barrera.\n", id);
    barrera_wait(&bar);
    printf("Barrera - Hilo %d pasó la barrera.\n", id);
    return NULL;
}

