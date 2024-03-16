# Biblioteca-Sync

Fecha de creación: 15 de marzo de 2024

Última actualización: 15 de marzo de 2024

Este proyecto es una implementación en C usando pthreads. Se incluyen implementaciones de semáforos, monitores y barreras.

En mi_programa.c se define una cantidad de hilos a usar y una cantidad de iteraciones que debe hacer cada hilo. Luego, para las implementaciones de semáforos y monitores, se hace un bucle en el que N hilos aumentan el contador por N iteraciones. Para la parte de barrera, espera a que N hilos lleguen a la barrera, anuncia su llegada y luego anuncia cuando pasan la barrera

## Autores
Isaac Meléndez

Pablo Sandí 

Gerald Matarrita

## Compilación

Para compilar el programa, puedes usar el siguiente comando:

```
gcc -o mi_programa mi_programa.c -lpthread
```


## Ejecución

Para esta parte cada comando ejecuta un ejemplo de cada estrategia de sincronización ya sea semáforos, monitores o barreras segun se llame

Una vez compilado, puedes ejecutar el programa con alguno de los siguientes argumentos:

```
./mi_programa semaforo
./mi_programa monitor
./mi_programa barrera
```
