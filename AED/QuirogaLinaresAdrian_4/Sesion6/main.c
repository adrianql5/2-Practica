#include <complex.h>
#include <stdio.h>
#include <stdlib.h>
#include "GoTMap.h"
#include "grafo.h"

#define MAXVERTICES 100

int main(int argc, char** argv) {
    grafo mapa;
    char opcion;

    crear_grafo(&mapa);

    cargarArchivo(&mapa, argc, argv);

    do {
        printf("\n\na. Agregar nueva ubicación\n");
        printf("b. Eliminar ubicación\n");
        printf("c. Crear conexión\n");
        printf("d. Eliminar conexión\n");
        printf("i. Imprimir mapa\n");
        printf("l. Ruta más corta\n");
        printf("r. Ruta más rápida\n");
        printf("m. Mínima Infraestructura\n");
        printf("s. Salir\n");

        printf("Opción: ");
        scanf(" %c", &opcion);

        switch (opcion) {
            case 'a': case 'A':
                agregar_ubicacion(&mapa);
                break;
            case 'b': case 'B':
                eliminar_ubicacion(&mapa);
                break;
            case 'c': case 'C':
                agregar_conexion(&mapa);
                break;
            case 'd': case 'D':
                eliminar_conexion(&mapa);
                break;
            case 'i': case 'I':
                imprimir_mapa(mapa);
                break;
            case 's': case 'S':
                opcion = 's';
                escribirArchivo(mapa, argc, argv);
                break;

            case 'l': case 'L':
                buscarRutaCorta(mapa);
                break;

            case 'r': case 'R':
                buscarRutaRapida(mapa);
                break;

            case 'm': case 'M':
                primMST(mapa);
                break;

            default:
                printf("Opción equivocada\n");
        }
    } while (opcion != 's');

    borrar_grafo(&mapa);

    return (EXIT_SUCCESS);
}

