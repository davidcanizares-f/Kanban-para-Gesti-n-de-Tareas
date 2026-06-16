/*
 =============== UNIVERSIDAD DE LAS AMÉRICAS ===============
        FACULTAD DE INGENIERÍA Y CIENCIAS APLICADAS
                INGENIERÍA DE SOFTWARE
                    PROGRAMACIÓN I
Autores:
    -David Cañizares
    -Sebastián Orbe
    -Jean Pierre Rosas
    -Derek Yépez

=========== KANBAN PARA GESTIÓN DE TAREAS =============


*/


//Inclusión de librerías.
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "kanban.h"
#include "kanban.c"

/*
 * main
 * Punto de entrada del programa.
 * Administra el arreglo de tareas usando el menú principal en bucle
 * hasta que el usuario decida salir.
 */
int main() {
    /* ── Variable para controlar el número de tareas registradas ── */
    int numeroTareas = 0;
    int *ptrNumTareas;
    ptrNumTareas = &numeroTareas;    

    /* ── Variable para la opción elegida en el menú principal ── */
    int opcionMenuPrincipal = 0;
    int *ptrOpcionMenuPrincipal;
    ptrOpcionMenuPrincipal = &opcionMenuPrincipal;

    /* ── Arreglo principal que no usa variables globales ── */
    struct tarea tareas[100]; 
    
    /* ── Encabezado del programa ── */
    etiquetaInicial();

    /* ── Bucle principal del menú ── */
    do {
        opcionMenuPrincipal = menuPrincipal(ptrOpcionMenuPrincipal);
        
        switch (opcionMenuPrincipal) {
            case 1: /* Registrar tarea */
                if (*ptrNumTareas >= 100) {
                    printf("\n[ERROR] Se ha alcanzado el límite máximo de tareas (100).\n");
                } else {
                    registrarTarea(tareas, ptrNumTareas);
                }
                break;
            case 2: /* Mostrar tablero Kanban */
                mostrarTablero(tareas, ptrNumTareas);
                break;
            case 3: /* Buscar tarea */
                buscarTarea(tareas, ptrNumTareas);
                break;
            case 4: /* Cambiar estado de una tarea */
                cambiarEstado(tareas, ptrNumTareas);
                break;
            case 5: /* Eliminar tarea */
                eliminarTarea(tareas, ptrNumTareas);
                break;
            case 6: /* Estadísticas */
                mostrarEstadisticas(tareas, ptrNumTareas);
                break;
            case 7: /* Salir del programa */
                printf("\n======================\n");
                printf("  SALISTE DEL PROGRAMA\n");
                printf("=========================\n");
                break;
        }

    } while (opcionMenuPrincipal != 7); 
    
    return 0;
}