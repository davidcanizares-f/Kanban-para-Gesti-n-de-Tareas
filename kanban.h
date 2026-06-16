/*
 * kanban.h
 * Archivo de cabecera que define las estructuras de datos y declara
 * los prototipos de todas las funciones del programa Kanban.
 */

#ifndef KANBAN_H
#define KANBAN_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

/*
 * Estructura tarea
 * Almacena los atributos principales de una actividad en el tablero.
 */
struct tarea {
    int codigo;
    char titulo[100];
    char responsable[100];
    char prioridad[20]; /* Alta, Media, Baja */
    char estado[20];    /* Pendiente, En Progreso, Finalizada */
};

/* ─── Prototipos de funciones ─── */

/* Muestra el encabezado inicial del programa */
void etiquetaInicial();
/* Despliega el menú principal y retorna la opción elegida */
int menuPrincipal(int *ptrOpcion);
/* Permite registrar una nueva tarea validando que el código no se repita */
void registrarTarea(struct tarea tareas[], int *ptrNumTareas);
/* Muestra las tareas agrupadas por estado (Pendientes, En Progreso, Finalizadas) */
void mostrarTablero(struct tarea tareas[], int *ptrNumTareas);
/* Permite buscar una tarea por Código o Responsable, retorna el índice o -1 */
int buscarTarea(struct tarea tareas[], int *ptrNumTareas);
/* Permite cambiar el estado actual de una tarea en el tablero */
void cambiarEstado(struct tarea tareas[], int *ptrNumTareas);
/* Elimina una tarea y reacomoda el arreglo */
void eliminarTarea(struct tarea tareas[], int *ptrNumTareas);
/* Muestra los conteos totales, por estado y el porcentaje de avance */
void mostrarEstadisticas(struct tarea tareas[], int *ptrNumTareas);

#endif /* KANBAN_H */