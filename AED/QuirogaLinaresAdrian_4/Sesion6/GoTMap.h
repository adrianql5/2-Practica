#ifndef GOTMAP_H
#define GOTMAP_H
#define MAXVERTICES 100
#include "grafo.h"
#include <limits.h>
#define INFINITY INT_MAX


// FUNCIONES DEL PROGRAMA DE PRUEBA DEL MAPA
// Opción a del menú, agregar una nueva ubicación en el grafo
void agregar_ubicacion(grafo *grafo);

// Opción b del menú, eliminar una ubicación del grafo
void eliminar_ubicacion(grafo *grafo);

// Opción c del menú, crear una conexión entre dos ubicaciones
void agregar_conexion(grafo *grafo);

// Opción d del menú, eliminar una conexión entre dos ubicaciones
void eliminar_conexion(grafo *grafo);

// Opción i del menú, imprimir el grafo
void imprimir_mapa(grafo grafo);

// Funcion que carga los datos de un archivo en el grafo
void cargarArchivo(grafo * grafo, int argc, char ** argv);

// Funcion que guarda el estado del grafo en el archivo
void escribirArchivo(grafo grafo, int argc, char ** argv);

//Opcion l del menu, devuelve la ruta mas corta entre dos ciudades indicando si hay tramos por mar o tierra
void buscarRutaCorta(grafo grafo);

//Opcion r del menu, devuelve la ruta mas rapida entre dos ciudades teniendo en cuenta los diferntes medios de transporte
void buscarRutaRapida(grafo grafo);

//Opcion m del menu, que usa el algortimo de Prim para poder devolver la minima infraestructura de conexiones
void primMST(grafo g);

#endif /* GOTMAP_H */

