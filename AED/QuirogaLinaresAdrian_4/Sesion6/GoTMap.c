#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafo.h"
#include "GoTMap.h"

//Funcion que dependiendo del tipo de transporte devuelve la velocidad de este
float calcularVelocidad(grafo g, char tipo, char * transporte){
    if(strcmp(transporte,"dragon")==0){
        return 80;
    }

    else if(strcmp(transporte,"caballo")==0){
        if(tipo=='t'){//si va por tierra
            return 5.5;
        }
        else{//si va en barco
            return 11.25;
        }
    }

    else {
        printf("Tipo Incorrecto\n");
        return 0;
    }
}

void primMST(grafo g) {
    int N = num_vertices(g);
    tipovertice *VECTOR = array_vertices(g);
    int Selected[N];
    int numArcos = 0;
    float tiempoTotal = 0;
    //Aplico el algoritmo de Prim
    for (int k = 0; k < N; k++) {
        Selected[k] = 0;
    }
    Selected[0] = 1;

    while (numArcos < N - 1) {
        float minimo = INFINITY;
        int vx = -1, vy = -1;

        // Busco el arco con el valor mínimo que conecta un vértice seleccionado y uno no seleccionado
        for (int i = 0; i < N; i++) {
            if (Selected[i]) { // Si el vértice i está en el conjunto Selected
                for (int j = 0; j < N; j++) {
                    // Compruebo que j no esté en Selected y que haya un arco
                    if (!Selected[j] && son_adyacentes(g, i, j)) {
                        float tiempo = distancia(g, i, j)/calcularVelocidad(g, tipoconexion(g,i,j),"caballo");
                        if (minimo > tiempo) { // Encontramos un arco de menor costo
                            minimo = tiempo;
                            vx = i;
                            vy = j;
                        }
                    }
                }
            }
        }

        if (vx != -1 && vy != -1) {
            Selected[vy] = 1;
            numArcos++;

            char tipo = tipoconexion(g, vx, vy);

            const char *conexStr;
            if (tipo == 't') {
                conexStr = "-->"; // Tipo de conexión 't'
            } else if (tipo == 's') {
                conexStr = "~~>"; // Tipo de conexión 's'
            } else {
                conexStr = "->";
            }

            printf(" %s %s %s         Tiempo: %.2f horas\n",
                   VECTOR[vx].ciudad,
                   conexStr,
                   VECTOR[vy].ciudad,
                   minimo);
            tiempoTotal += minimo;

        } else {
            printf("No se puede construir un árbol de expansión mínimo completo.\n");
            break;
        }
    }

    printf("Tiempo total del árbol de expansión de coste mínimo: %.2f horas\n", tiempoTotal);
}


//Funcion que construye la matriz de distancias y de la vertices previos
void construirMatrices(int N, grafo grafo, float matrizD[][N], int matrizP[][N], char * tipoBusqueda){
    char transporte[50];
    printf("Introduce el modo de transporte (dragon o caballo)\n");
    scanf("%s",transporte);

    int i, j;
    //Aplico el algoritmo de Floyd-Warshall
    for(i=0; i<N; i++){
        for(j=0; j<N; j++){
            if(i==j){
                matrizD[i][j]=0;
                matrizP[i][j]=0;
            }
            else if(distancia(grafo, i,j)!=0){
                if(strcmp(tipoBusqueda,"corta")==0){
                    matrizD[i][j]=distancia(grafo, i,j);
                }
                else{
                    matrizD[i][j]=distancia(grafo,i,j)/calcularVelocidad(grafo,tipoconexion(grafo, i, j),transporte);
                }

                matrizP[i][j]=i;

            }
            else{
                matrizD[i][j]=INFINITY;
                matrizP[i][j]=0;
            }
        }
    }

}


//Funcion que modifica las matrices construidas previamente para representar los caminos
void modificarMatrices(int N, float matrizD[][N], int matrizP[][N]) {
    int i, j, k;

    for (k = 0; k < N; k++) {
        for (i = 0; i < N; i++) {
            for (j = 0; j < N; j++) {
                if (matrizD[i][j] > matrizD[i][k] + matrizD[k][j]) {
                    matrizD[i][j] = matrizD[i][k] + matrizD[k][j];
                    matrizP[i][j] = matrizP[k][j];
                }
            }
        }
    }

}

//Funcion que imprime el camino
void imprimir_camino(int N, grafo G, int matrizP[][N], int origen, int destino) {
    tipovertice *vertices = array_vertices(G);

    if (origen != destino) {
        imprimir_camino(N, G, matrizP, origen, matrizP[origen][destino]);

        char tipo = tipoconexion(G, matrizP[origen][destino], destino);
        if (tipo == 't') {
            printf(" --> ");
        } else if (tipo == 's') {
            printf(" ~~> ");
        } else {
            printf(" -> ");
        }
    }

    printf("%s", vertices[destino].ciudad);
}

//Funcion que busca la ruta mas corta entre dos ciudades
void buscarRutaRapida(grafo grafo) {
    int N = num_vertices(grafo);
    float matrizD[N][N];
    int matrizP[N][N];

    tipovertice origen, destino;

    printf("Introduce ciudad origen: ");
    scanf(" %[^\n]", origen.ciudad);

    if (!existe_vertice(grafo, origen)) {
        printf("La ciudad %s no existe en el grafo\n", origen.ciudad);
        return;
    }

    printf("Introduce ciudad destino: ");
    scanf(" %[^\n]", destino.ciudad);

    if (!existe_vertice(grafo, destino)) {
        printf("La ciudad %s no existe en el grafo\n", destino.ciudad);
        return;
    }

    //obtengo las matrices de distancias y de vertices previos
    construirMatrices(N, grafo,matrizD,matrizP,"asdf");
    modificarMatrices(N, matrizD, matrizP);

    int idx_origen = posicion(grafo, origen);
    int idx_destino = posicion(grafo, destino);

    //Imprimo el camino
    printf("Camino más corto de %s a %s: ", origen.ciudad, destino.ciudad);
    imprimir_camino(N,grafo, matrizP, idx_origen, idx_destino);
    printf("\nTiempo total: %.2f\n", matrizD[idx_origen][idx_destino]);
}

//funcion que busca la ruta mas corta entre dos ciudades
void buscarRutaCorta(grafo grafo) {
    int N = num_vertices(grafo);
    float matrizD[N][N];
    int matrizP[N][N];

    tipovertice origen, destino;

    printf("Introduce ciudad origen: ");
    scanf(" %[^\n]", origen.ciudad);

    if (!existe_vertice(grafo, origen)) {
        printf("La ciudad %s no existe en el grafo\n", origen.ciudad);
        return;
    }

    printf("Introduce ciudad destino: ");
    scanf(" %[^\n]", destino.ciudad);

    if (!existe_vertice(grafo, destino)) {
        printf("La ciudad %s no existe en el grafo\n", destino.ciudad);
        return;
    }

    construirMatrices(N, grafo,matrizD,matrizP,"corta");
    modificarMatrices(N, matrizD, matrizP);

    int idx_origen = posicion(grafo, origen);
    int idx_destino = posicion(grafo, destino);

    printf("Camino más corto de %s a %s: ", origen.ciudad, destino.ciudad);
    imprimir_camino(N,grafo, matrizP, idx_origen, idx_destino);
    printf("\nDistancia total: %.2f\n", matrizD[idx_origen][idx_destino]);
}




// Función para asignar la región a una ciudad dada
void asignarRegion(char *ciudad, tipovertice *vertice) {
    FILE *archivo = fopen("regiones.txt", "r+");//abro mi base de datos que contiene una asociacion entre ciudades y regiones
    if (!archivo) {
        printf("Error al abrir el archivo de regiones.\n");
        return;
    }

    char linea[100];
    int encontrada = 0;

    // Lo cada línea del archivo para buscar la ciudad
    while (fgets(linea, sizeof(linea), archivo)) {
        char ciudadArchivo[50], region[50];

        if (sscanf(linea, "%49[^|]|%49[^|]|", ciudadArchivo, region) == 2) {
            if (strcmp(ciudadArchivo, ciudad) == 0) {
                strcpy(vertice->region, region);
                encontrada = 1;
                break;
            }
        }
    }

    // Si la ciudad no se encontró, le pido al usuario la región
    if (!encontrada) {
        char region[50];
        printf("La ciudad '%s' no está registrada. Introduzca su región: ", ciudad);
        scanf(" %[^\n]", region);
        fseek(archivo, 0, SEEK_END);
        //actualizo mi base de datos con la nueva ciudad y su region
        fprintf(archivo, "%s|%s|\n", ciudad, region);

        strcpy(vertice->region, region);
    }

    fclose(archivo);
}


//funcion que carga las rutas de un archivo al grafo
void cargarArchivo(grafo *grafo, int argc, char **argv) {
    if (argc < 2) {
        printf("No se ha introducido ningún archivo\n");

    }
    else{
        tipovertice origen, destino;

        FILE *archivo = fopen(argv[1], "r");
        if (!archivo) {
            printf("Error al abrir el archivo\n");
            return;
        }

        char linea[1000];
        while (fgets(linea, sizeof(linea), archivo)) {
            char *origenar = strtok(linea, "|");
            if (origenar) strcpy(origen.ciudad, origenar);
            //asigno la region, ahorrandole al usuario introducir todo el rato la region
            asignarRegion(origenar, &origen);

            // Verificar si el vértice ya existe antes de insertarlo
            if (!existe_vertice(*grafo, origen)) {
                insertar_vertice(grafo, origen);
            }

            char *destinoar = strtok(NULL, "|");
            if (destinoar) strcpy(destino.ciudad, destinoar);
            asignarRegion(destinoar, &destino);//asigno la region

            // Verificar si el vértice ya existe antes de insertarlo
            if (!existe_vertice(*grafo, destino)) {
                insertar_vertice(grafo, destino);
            }

            char *distancia = strtok(NULL, "|");
            float dist = distancia ? atof(distancia) : 0.0;

            char *tipo = strtok(NULL, "|");
            char tipot = tipo ? tipo[0] : '\0';

            if (!son_adyacentes(*grafo, posicion(*grafo, origen), posicion(*grafo, destino))) {
                crear_arco(grafo, posicion(*grafo, origen), posicion(*grafo, destino), dist, tipot);
            }
        }

        fclose(archivo);
    }
}


//funcion que guarda en el archivo el grafo
void escribirArchivo(grafo grafo, int argc, char ** argv){

    FILE *archivo;
    if(argc<2){
        printf("Introduce el nombre del archivo donde guardar el árbol: ");
        char str[50];
        scanf(" %[^\n]",str);
        archivo= fopen(str, "w");
    }
    else{
        archivo =fopen(argv[1],"w");
    }

    tipovertice *VECTOR;
    int N;

    N = num_vertices(grafo);
    VECTOR = array_vertices(grafo);

    int i, j;
    //Para que no se imprima las rutas duplicadas, solo imprimo la mitad
    for (i = 0; i < N; i++) {
        for (j = 0; j < i; j++)
            if (son_adyacentes(grafo, i, j))
                fprintf(archivo,"%s|%s|%f|%c|\n", VECTOR[i].ciudad,VECTOR[j].ciudad,distancia(grafo,i,j),tipoconexion(grafo,i,j));
    }
}


// FUNCIONES DEL PROGRAMA DE PRUEBA DE GRAFOS

// Opción a del menú, introducir una ubicación en el grafo
void agregar_ubicacion(grafo * grafo) {
    tipovertice nueva_ubicacion;
    printf("Introduce ciudad: ");
    scanf(" %[^\n]", nueva_ubicacion.ciudad);
    asignarRegion(nueva_ubicacion.ciudad, &nueva_ubicacion);//asigno la region

    if (existe_vertice(*grafo, nueva_ubicacion))
        printf("Esa ciudad ya está en el grafo\n");
    else
        insertar_vertice(grafo, nueva_ubicacion);
}

// Opción b del menú, eliminar una ubicación del grafo
void eliminar_ubicacion(grafo *grafo) {
    tipovertice ubicacion_a_eliminar;
    printf("Introduce ciudad: ");
    scanf(" %[^\n]", ubicacion_a_eliminar.ciudad);//asigno la region

    if (existe_vertice(*grafo, ubicacion_a_eliminar))
        borrar_vertice(grafo, ubicacion_a_eliminar);
    else
        printf("Esa ciudad no existe en el grafo\n");
}

// Opción c del menú, crear una conexión entre dos ubicaciones
void agregar_conexion(grafo *grafo) {
    tipovertice origen, destino;

    printf("Nueva conexión ciudad1-->ciudad2\n");

    printf("Introduce ciudad origen: ");
    scanf(" %[^\n]", origen.ciudad);


    if (!existe_vertice(*grafo, origen)) {
        printf("La ciudad %s no existe en el grafo\n", origen.ciudad);
        return;
    }

    printf("Introduce ciudad destino: ");
    scanf(" %[^\n]", destino.ciudad);


    if (!existe_vertice(*grafo, destino)) {
        printf("La ciudad %s no existe en el grafo\n", destino.ciudad);
        return;
    }

    float distancia;
    printf("Introduce la distancia: ");
    scanf("%f",&distancia);

    char modo;
    printf("Introduce el modo del viaje: ");
    scanf(" %c",&modo);

    if (!son_adyacentes(*grafo, posicion(*grafo, origen), posicion(*grafo, destino)))
        crear_arco(grafo, posicion(*grafo, origen), posicion(*grafo, destino),distancia,modo);
}

// Opción d del menú, eliminar una conexión entre dos ubicaciones
void eliminar_conexion(grafo *grafo) {
    tipovertice origen, destino;

    printf("Eliminar conexión ciudad1-->ciudad2\n");

    printf("Introduce ciudad origen: ");
    scanf(" %[^\n]", origen.ciudad);

    if (!existe_vertice(*grafo, origen)) {
        printf("La ciudad %s no existe en el grafo\n", origen.ciudad);
        return;
    }

    printf("Introduce ciudad destino: ");
    scanf(" %[^\n]", destino.ciudad);

    if (!existe_vertice(*grafo, destino)) {
        printf("La ciudad %s no existe en el grafo\n", destino.ciudad);
        return;
    }

    if (son_adyacentes(*grafo, posicion(*grafo, origen), posicion(*grafo, destino)))
        borrar_arco(grafo, posicion(*grafo, origen), posicion(*grafo, destino));
}

// Opción i del menú, imprimir el grafo
// Función que imprime el grafo utilizando num_vertices para saber cuántas ubicaciones tiene
// y array_vertices para recuperar el vector de ubicaciones y recorrerlo
void imprimir_mapa(grafo grafo) {
    tipovertice *VECTOR; // Para almacenar el vector de ubicaciones del grafo
    int N; // número de ubicaciones del grafo

    // Para recorrerla, simplemente vamos a recorrer la matriz de adyacencia
    N = num_vertices(grafo);
    VECTOR = array_vertices(grafo);

    int i, j;
    printf("El grafo actual es:\n");
    for (i = 0; i < N; i++) {
        // Imprimo la ubicación
        printf("Ciudad: %s, Región: %s\n", VECTOR[i].ciudad, VECTOR[i].region);
        // Chequeo sus conexiones
        for (j = 0; j < N; j++)
            if (son_adyacentes(grafo, i, j))
                printf("\t%s-->%s\n", VECTOR[i].ciudad, VECTOR[j].ciudad);
    }
}



