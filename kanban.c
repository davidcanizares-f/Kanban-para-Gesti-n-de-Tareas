/*
 * kanban.c
 * Implementación de todas las funciones para el tablero Kanban.
 * Incluye registro, visualización, búsqueda, actualización de estado
 * y estadísticas de las tareas.
 */

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "kanban.h"

void etiquetaInicial() {
    printf("\n===============================\n");
    printf("- KANBAN PARA GESTION DE TAREAS -\n");
    printf("===============================\n");
}

int menuPrincipal(int *ptrOpcion) {
    printf("\n==============================\n");
    printf("<<<<<< MENU DE ACCIONES >>>>>");
    printf("\n==============================\n");
    printf("[1]: Registrar nueva tarea.\n");
    printf("[2]: Mostrar tablero Kanban.\n");
    printf("[3]: Buscar tarea.\n");
    printf("[4]: Cambiar estado de una tarea.\n");
    printf("[5]: Eliminar tarea.\n");
    printf("[6]: Mostrar estadisticas.\n");
    printf("[7]: Salir.\n");
    printf("-----------------------------------\n");
    printf("Escoja una opcion: ");

    /* Repite la solicitud mientras la entrada sea inválida o fuera de rango */
    while (scanf("%d", ptrOpcion) != 1 || *ptrOpcion > 7 || *ptrOpcion < 1) {
        printf("[ERROR]: DATO INVALIDO O FUERA DE RANGO. INGRESE NUEVAMENTE.\n");
        while (getchar() != '\n');
        printf("\n==============================\n");
        printf("<<<<<< MENU DE ACCIONES >>>>>");
        printf("\n==============================\n");
        printf("[1]: Registrar nueva tarea.\n");
        printf("[2]: Mostrar tablero Kanban.\n");
        printf("[3]: Buscar tarea.\n");
        printf("[4]: Cambiar estado de una tarea.\n");
        printf("[5]: Eliminar tarea.\n");
        printf("[6]: Mostrar estadisticas.\n");
        printf("[7]: Salir.\n");
        printf("-----------------------------------\n");
        printf("Escoja una opcion: ");
    }
    return *ptrOpcion;
}

void registrarTarea(struct tarea tareas[], int *ptrNumTareas) {
    int codigo;
    char titulo[100];
    char responsable[100];
    int opcionPrioridad, opcionEstado;
    bool duplicado;

    printf("\n<<< REGISTRO DE NUEVA TAREA >>>\n");
    printf("-------------------------------\n");

    /* ── Validación de Código ── */
    printf("> Codigo (entero positivo): ");
    while ((scanf("%d", &codigo) != 1) || codigo <= 0) {
        printf("[ERROR]: DATO INVALIDO O FUERA DE RANGO. INGRESE NUEVAMENTE.\n");
        while (getchar() != '\n'); 
        printf("> Codigo (entero positivo): ");
    }
    getchar(); /* Consume el '\n' residual */

    /* Validación de Código Duplicado */
    duplicado = true;
    while (duplicado) {
        duplicado = false;
        for (int i = 0; i < *ptrNumTareas; i++) {
            if (tareas[i].codigo == codigo) {
                duplicado = true;
                break;
            }
        }
        if (duplicado) {
            printf("\n[INVALIDO] Codigo ya registrado.\n");
            printf("> Codigo (entero positivo): ");
            while ((scanf("%d", &codigo) != 1) || codigo <= 0) {
                printf("\n[ERROR]: DATO INVALIDO O FUERA DE RANGO. INGRESE NUEVAMENTE.\n");
                while (getchar() != '\n');
                printf("> Codigo (entero positivo): ");
            }
            getchar();
        }
    }
    tareas[*ptrNumTareas].codigo = codigo;

    /* ── Título ── */
    printf("> Titulo de la tarea: ");
    fgets(titulo, 100, stdin);
    titulo[strcspn(titulo, "\n")] = '\0';
    strcpy(tareas[*ptrNumTareas].titulo, titulo);

    /* ── Responsable ── */
    printf("> Nombre del responsable: ");
    fgets(responsable, 100, stdin);
    responsable[strcspn(responsable, "\n")] = '\0';
    strcpy(tareas[*ptrNumTareas].responsable, responsable);

    /* ── Prioridad ── */
    printf("> Prioridad: \n");
    printf("    [1]: Alta\n");
    printf("    [2]: Media\n");
    printf("    [3]: Baja\n");
    printf("    Escoja: ");
    while ((scanf("%d", &opcionPrioridad) != 1) || opcionPrioridad < 1 || opcionPrioridad > 3) {
        printf("[ERROR]: DATO INVALIDO O FUERA DE RANGO. INGRESE NUEVAMENTE.\n");
        while (getchar() != '\n');
        printf("> Prioridad: ");
    }
    getchar();
    if (opcionPrioridad == 1) strcpy(tareas[*ptrNumTareas].prioridad, "Alta");
    else if (opcionPrioridad == 2) strcpy(tareas[*ptrNumTareas].prioridad, "Media");
    else strcpy(tareas[*ptrNumTareas].prioridad, "Baja");

    /* ── Estado ── */
    printf("> Estado Actual: \n");
    printf("    [1]: Pendiente\n");
    printf("    [2]: En Progreso\n");
    printf("    [3]: Finalizada\n");
    printf("    Escoja: ");
    while ((scanf("%d", &opcionEstado) != 1) || opcionEstado < 1 || opcionEstado > 3) {
        printf("[ERROR]: DATO INVALIDO O FUERA DE RANGO. INGRESE NUEVAMENTE.\n");
        while (getchar() != '\n');
        printf("> Estado Actual: ");
    }
    getchar();
    if (opcionEstado == 1) strcpy(tareas[*ptrNumTareas].estado, "Pendiente");
    else if (opcionEstado == 2) strcpy(tareas[*ptrNumTareas].estado, "En Progreso");
    else strcpy(tareas[*ptrNumTareas].estado, "Finalizada");

    (*ptrNumTareas)++; /* Incrementa el total de tareas */
    printf("\n<<< TAREA REGISTRADA EXITOSAMENTE >>>\n");
}

void mostrarTablero(struct tarea tareas[], int *ptrNumTareas) {
    char estados[3][20] = {"Pendiente", "En Progreso", "Finalizada"};
    char etiquetas[3][20] = {"PENDIENTES", "EN PROGRESO", "FINALIZADAS"};
    bool hayTareas;

    printf("\n");
    for (int e = 0; e < 3; e++) {
        printf("=================================%s=================================\n", etiquetas[e]);
        hayTareas = false;
        
        for (int i = 0; i < *ptrNumTareas; i++) {
            if (strcmp(tareas[i].estado, estados[e]) == 0) {
                printf("[%d] %s\n (> Responsable: %s | > Prioridad: %s)\n", tareas[i].codigo, tareas[i].titulo, tareas[i].responsable, tareas[i].prioridad);
                hayTareas = true;
            }
        }
        
        if (!hayTareas) {
            printf("   (No hay tareas en este estado)\n");
        }
        printf("\n");
    }
}

int buscarTarea(struct tarea tareas[], int *ptrNumTareas) {
    char responsableBuscado[100];
    bool encontrado = false;
    int indiceEncontrado = -1;
    int opcionBusqueda;
    int codigoBuscado;

    if (*ptrNumTareas == 0) {
        printf("\n[INFO] No hay tareas registradas en el sistema.\n");
        return -1;
    }

    do {
        printf("\n========== BUSQUEDA DE TAREA ==========\n");
        printf("[1]: Busqueda por Codigo.\n");
        printf("[2]: Busqueda por Responsable.\n");
        printf("[3]: Salir.\n");
        printf("--------------------------------\n");
        printf("Escoja: ");

        while (scanf("%d", &opcionBusqueda) != 1 || opcionBusqueda > 3 || opcionBusqueda < 1) {
            printf("[ERROR]: DATO INVALIDO O FUERA DE RANGO. INGRESE NUEVAMENTE.\n");
            while (getchar() != '\n');
            printf("Escoja: ");
        }
        getchar();

        switch (opcionBusqueda) {
            case 1: /* Por Código */
                printf("Ingrese el Codigo de la tarea: ");
                while (scanf("%d", &codigoBuscado) != 1 || codigoBuscado <= 0) {
                    printf("[ERROR]: DATO INVALIDO O FUERA DE RANGO. INGRESE NUEVAMENTE.\n");
                    while (getchar() != '\n');
                    printf("Ingrese el Codigo de la tarea: ");
                }
                getchar();
                
                for (int i = 0; i < *ptrNumTareas; i++) {
                    if (tareas[i].codigo == codigoBuscado && !encontrado) {
                        encontrado = true;
                        indiceEncontrado = i;
                    }
                }
                break;

            case 2: /* Por Responsable */
                printf("Ingrese el nombre del Responsable: ");
                fgets(responsableBuscado, 100, stdin);
                responsableBuscado[strcspn(responsableBuscado, "\n")] = '\0';
                
                for (int i = 0; i < *ptrNumTareas; i++) {
                    if (strcmp(tareas[i].responsable, responsableBuscado) == 0 && !encontrado) {
                        encontrado = true;
                        indiceEncontrado = i;
                    }
                }
                break;

            case 3: /* Salir */
                return -1;
        }

        if (encontrado) {
            printf("\n>>>> TAREA ENCONTRADA <<<<\n");
            printf("---------------------------------\n");
            printf("> Codigo: %d\n", tareas[indiceEncontrado].codigo);
            printf("> Titulo: %s\n", tareas[indiceEncontrado].titulo);
            printf("> Responsable: %s\n", tareas[indiceEncontrado].responsable);
            printf("> Prioridad: %s\n", tareas[indiceEncontrado].prioridad);
            printf("> Estado: %s\n", tareas[indiceEncontrado].estado);
            printf("---------------------------------\n");
        } else {
            printf("\n>>>> TAREA NO ENCONTRADA <<<<\n");
        }

    } while (opcionBusqueda != 3 && !encontrado);

    return indiceEncontrado;
}

void cambiarEstado(struct tarea tareas[], int *ptrNumTareas) {
    int indice, opcionEstado;

    printf("\n============== CAMBIAR ESTADO DE TAREA ==============\n");
    indice = buscarTarea(tareas, ptrNumTareas);
    if (indice < 0) return;

    printf("----------------------------\n");
    printf("\nESTADO ACTUAL: %s\n", tareas[indice].estado);
    printf("-------------------------\n");
    printf("MOVER A:\n");
    printf("[1]: Pendiente\n");
    printf("[2]: En Progreso\n");
    printf("[3]: Finalizada\n");
    printf("[4]: Cancelar cambio\n");
    printf("-------------------------\n");
    printf("Escoja: ");

    while (scanf("%d", &opcionEstado) != 1 || opcionEstado < 1 || opcionEstado > 4) {
        printf("[ERROR]: DATO INVALIDO O FUERA DE RANGO. INGRESE NUEVAMENTE.\n");
        while (getchar() != '\n');
        printf("Escoja: ");
    }
    getchar();

    switch (opcionEstado) {
        case 1: strcpy(tareas[indice].estado, "Pendiente"); break;
        case 2: strcpy(tareas[indice].estado, "En Progreso"); break;
        case 3: strcpy(tareas[indice].estado, "Finalizada"); break;
        case 4: return; /* Cancela el cambio */
    }

    printf("<<<< ESTADO DE TAREA CAMBIADO A: '%s' >>>>\n", tareas[indice].estado);
}

void eliminarTarea(struct tarea tareas[], int *ptrNumTareas) {
    int indice;

    printf("\n============== ELIMINAR REGISTRO DE TAREA ============\n");
    indice = buscarTarea(tareas, ptrNumTareas);
    if (indice < 0) return;

    /* Desplaza los elementos posteriores una posición hacia la izquierda */
    for (int i = indice; i < (*ptrNumTareas) - 1; i++) {
        tareas[i] = tareas[i + 1];
    }

    (*ptrNumTareas)--; /* Reduce el contador */

    printf("\n<<< TAREA ELIMINADA CORRECTAMENTE >>>\n");
}

void mostrarEstadisticas(struct tarea tareas[], int *ptrNumTareas) {
    int pendientes = 0, enProgreso = 0, finalizadas = 0;
    float porcentaje = 0.0;

    printf("\n============== ESTADISTICAS DEL TABLERO ============\n");
    if (*ptrNumTareas == 0) {
        printf("No hay tareas registradas para calcular estadisticas.\n");
        return;
    }

    for (int i = 0; i < *ptrNumTareas; i++) {
        if (strcmp(tareas[i].estado, "Pendiente") == 0) pendientes++;
        else if (strcmp(tareas[i].estado, "En Progreso") == 0) enProgreso++;
        else if (strcmp(tareas[i].estado, "Finalizada") == 0) finalizadas++;
    }

    porcentaje = ((float)finalizadas / (*ptrNumTareas)) * 100.0;

    printf(" > Total de tareas registradas: %d\n", *ptrNumTareas);
    printf(" > Cantidad de tareas pendientes: %d\n", pendientes);
    printf(" > Cantidad en progreso: %d\n", enProgreso);
    printf(" > Cantidad finalizadas: %d\n", finalizadas);
    printf(" > Porcentaje de tareas completadas: %.2f%%\n", porcentaje);
    printf("====================================================\n");
}