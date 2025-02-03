#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "lista.h"
#include "juegodetronos.h"
#include "abb.h"
#define MAX 50

//Función que añade elementos a las listas para aumentar la modularidad del programa
void procesarListas(TLISTA * l, char *tipo){
    char resp[MAX];
    do{
        printf("    %s (fin para parar):", tipo);
        scanf(" %[^\n]",resp);
        printf("\n");
        if(strcmp(resp,"fin")!=0){
            TIPOELEMENTOLISTA padre;
            strncpy(padre.name,resp,MAX);
            insertarElementoLista(l,primeroLista(*l),padre);
        }
        else break;

    }while(1);


}

//Funcion que insertar un Personaje en el árbol
void anhadirPersonaje(TABB *arbol){
    TIPOELEMENTOABB nodo;
    char nombre[MAX];
    char casa[MAX];
    unsigned int royal;

    crearLista(&nodo.padres);
    crearLista(&nodo.hermanos);
    crearLista(&nodo.asesinados);

    printf("Nombre:");
    scanf(" %[^\n]", nombre);
    strncpy(nodo.nombre,nombre,MAX);
    printf("\n");

    printf("    House (si es desconocido pon ?): ");
    scanf(" %[^\n]", casa);
    strncpy(nodo.casa,casa,MAX);
    printf("\n");

    printf("    Royal: ");
    scanf("%u", &royal);
    nodo.royal=royal;
    printf("\n");

    procesarListas(&nodo.padres, "Padres");
    procesarListas(&nodo.hermanos, "Hermanos");
    procesarListas(&nodo.asesinados, "Asesinados");


    insertarElementoAbb(arbol,nodo);
}


//Función que imprime las listas
void imprimirLista(TLISTA lista){
    TPOSICION actual;
    TPOSICION final=finLista(lista);
    TIPOELEMENTOLISTA e;

    for(actual=primeroLista(lista); actual!=final; actual=siguienteLista(lista,actual)){
        recuperarElementoLista(lista, actual, &e);
        printf(" %s,",e.name);
    }
}

//Funcion que imprime al personaje (llama a la funcion imprimirLista)
void _imprimirPersonaje(TIPOELEMENTOABB e){
    printf("%s\n", e.nombre);
    printf("    Casa: %s\n", e.casa);
    if(e.royal==1) printf("    Royal: Si");
    if(!esListaVacia(e.padres)){
        printf("\n    Padres: ");
        imprimirLista(e.padres);
    }
    if(!esListaVacia(e.hermanos)){
        printf("\n    Hermanos: ");
        imprimirLista(e.hermanos);
    }
    if(!esListaVacia(e.asesinados)){
        printf("\n    Asesinados: ");
        imprimirLista(e.asesinados);
    }

    printf("\n");
    printf("\n");

}

//Funcion que recorre el árbol inorden listando a los personajes
void listadoPersonajes(TABB arbol){
    TIPOELEMENTOABB e;
    if(!esAbbVacio(arbol)){
        listadoPersonajes(izqAbb(arbol));
        leerElementoAbb(arbol,&e);
        _imprimirPersonaje(e);
        listadoPersonajes(derAbb(arbol));
    }
}


//Función que imrpime las sublistas en el archivo
void imprimirListaArchivo(TLISTA lista, FILE *archivo) {

        TPOSICION actual = primeroLista(lista);
        TPOSICION final = finLista(lista);
        TIPOELEMENTOLISTA e;

        while (actual != final) {
            recuperarElementoLista(lista, actual, &e);
            actual = siguienteLista(lista, actual);
            if (actual != final) {
                fprintf(archivo, "%s,", e.name); // Imprimir con comas entre elementos
            } else {
                fprintf(archivo, "%s|", e.name); // El último elemento seguido de '|'
            }
        }

}

//Funcion que imprime a un personaje en el archivo
void imprimirPersonajeArchivo(TIPOELEMENTOABB nodo, FILE *archivo) {
    fprintf(archivo, "%s|", nodo.nombre);
    fprintf(archivo, "%s|", nodo.casa);
    fprintf(archivo, "%u|", nodo.royal);

    if (!esListaVacia(nodo.padres)) {
        imprimirListaArchivo(nodo.padres, archivo);
    } else {
        fprintf(archivo, "-|"); // Si no hay padres, imprime '-'
    }

    if (!esListaVacia(nodo.hermanos)) {
        imprimirListaArchivo(nodo.hermanos, archivo);
    } else {
        fprintf(archivo, "-|"); // Si no hay hermanos, imprime '-'
    }

    if (!esListaVacia(nodo.asesinados)) {
        imprimirListaArchivo(nodo.asesinados, archivo);
    } else {
        fprintf(archivo, "-|"); // Si no hay asesinados, imprime '-'
    }

    fprintf(archivo, "\n");
}




//Función que imprime inorden a los personajes del archivo
void listadoPersonajesArchivo(TABB arbol, FILE * archivo) {
    TIPOELEMENTOABB e;
    if (!esAbbVacio(arbol)) {
        listadoPersonajesArchivo(izqAbb(arbol), archivo);
        leerElementoAbb(arbol, &e);
        imprimirPersonajeArchivo(e, archivo);
        listadoPersonajesArchivo(derAbb(arbol), archivo);
    }
}





//Funcion que elimina a un personaje concreto
void eliminarPersonaje(TABB *arbol){

    char nombre[50];

    printf("Introduce el nombre del personaje a eliminar:");
    scanf(" %[^\n]", nombre);

    TIPOELEMENTOABB e;

    strncpy(e.nombre,nombre,MAX);

    if(esMiembroAbb(*arbol,e)){
        buscarNodoAbb(*arbol,nombre,&e);

        suprimirElementoAbb(arbol, e);
        printf("El personaje %s, ha sido eliminado con éxito\n", nombre);
    }
    else{
        printf("El personaje que deseas eliminar no ha sido registrado en la base de datos.\n");
    }

}



void _strip_line(char *linea) {
    linea[strcspn(linea, "\r\n")] = 0;
}


//funcion que cargar las listas del archivo al arbol al inciar el programa
void cargarlistas(char *str, TLISTA *lista) {
    if (str == NULL || lista == NULL) return;

    char *inicio = str;
    char *final = str;

    TIPOELEMENTOLISTA e;

    while (*final != '\0') {

        if (*final == ',') {
            *final = '\0';
            strcpy(e.name, inicio);
            insertarElementoLista(lista, primeroLista(*lista), e);
            inicio = final + 1;
        }
        final++;
    }

    if (*inicio != '\0') {
        TIPOELEMENTOLISTA e;
        strcpy(e.name, inicio);
        insertarElementoLista(lista, primeroLista(*lista), e);
    }
}

//carga todo el archivo en el arbol, llama cargar listas
void cargarArchivo(TABB *arbol, int argc, char **argv) {

    if (strcmp(argv[1], "-f") != 0) {
        perror("Introduce una opción de formato válido.");
        exit(EXIT_FAILURE);
    }

    FILE *archivo = fopen(argv[2], "r");
    if (!archivo) {
        perror("Error al abrir el archivo.");
        exit(EXIT_FAILURE);
    }

    TIPOELEMENTOABB nodo;

    char linea[1000];
    while (fgets(linea, sizeof(linea), archivo)) {
        crearLista(&nodo.padres);
        crearLista(&nodo.hermanos);
        crearLista(&nodo.asesinados);
        _strip_line(linea);

        char *nombre = strtok(linea, "|");
        if (nombre) strcpy(nodo.nombre, nombre);

        char *casa = strtok(NULL, "|");
        if (casa) strcpy(nodo.casa, casa);

        char *royal = strtok(NULL, "|");
        if (royal) nodo.royal = atoi(royal);

        char *padres = strtok(NULL, "|");
        if(strcmp(padres, "-")!=0) cargarlistas(padres, &nodo.padres);

        char *hermanos = strtok(NULL, "|");
        if(strcmp(hermanos,"-")!=0)  cargarlistas(hermanos, &nodo.hermanos);

        char *asesinados = strtok(NULL, "|");

        if(strcmp(asesinados, "-")!=0) cargarlistas(asesinados, &nodo.asesinados);


        insertarElementoAbb(arbol, nodo);
    }


    fclose(archivo);
}

//Verifica si un personaje esta en la lista

int estaEnLista(char *str, TLISTA lista) {
    TPOSICION actual;
    TPOSICION final = finLista(lista);

    for (actual = primeroLista(lista); actual != final; actual = siguienteLista(lista, actual)) {
        TIPOELEMENTOLISTA e;
        recuperarElementoLista(lista, actual, &e);
        if (strcmp(e.name, str) == 0) {
            return 1;
        }
    }

    return 0;
}


//funcion que en dependiendo del tipo de llamada hace una accion u otra,
//pero principalmente se encarga de reocorrer el arbol inorden buscando personajes
void BuscarPersonajes(TABB arbol, char *str, char *tipo,int * contador) {
    TIPOELEMENTOABB e;

    if (!esAbbVacio(arbol)) {
        BuscarPersonajes(izqAbb(arbol), str, tipo,contador);
        leerElementoAbb(arbol, &e);

        //Caso asesinos, imprime los asesinos que tiene un personaje
        if (strcmp(tipo, "asesinos") == 0) {
            if (estaEnLista(str, e.asesinados) == 1) {
                printf("%s, ", e.nombre);
                (*contador)++;
            }
        }

        //Caso hijos, imprime lo hijos que tiene un personaje
        else if (strcmp(tipo, "hijos") == 0) {
            if (estaEnLista(str, e.padres) == 1) {
                printf("%s, ", e.nombre);
                (*contador)++;
            }
        }

        //Caso killer, cuenta la longitud de la lista de asesinos con mayor longitud
        else if(strcmp(tipo,"killer")==0){
            int kills = longitudLista(e.asesinados);
            if (kills > *contador) {
                (*contador) = kills;
            }
        }

        //Caso printkillers, imprime a los personajes que son killers
        else if(strcmp(tipo,"printkillers")==0){
            if(longitudLista(e.asesinados)==(*contador)){
                    printf("%s, ", e.nombre);
            }
        }

        BuscarPersonajes(derAbb(arbol), str, tipo,contador);
    }
}


//funcion que busca a los asesinos de un personaje
void buscarAsesinos(TABB arbol) {
    char nombre[50];
    printf("Introduce el nombre del personaje asesinado: ");
    scanf(" %[^\n]", nombre);
    printf("\n");

    int contador=0;
    printf("    Asesinos: ");
    BuscarPersonajes(arbol, nombre, "asesinos",&contador);

    //En caso de que no encuentre ningun asesino
    if (contador == 0) {
        printf("El nombre introducido no tiene asesinos o no existe.\n");

    }
}

//Funcion que imprime los hijos de un personaje
void buscarHijos(TABB arbol) {
    char nombre[50];
    printf("Introduce el nombre del personaje del que quieras saber sus hijos: ");
    scanf(" %[^\n]", nombre);
    printf("\n");

    int contador=0;
    printf("    Hijos: ");
    BuscarPersonajes(arbol, nombre, "hijos", &contador);

    //En caso de que no tenga hijos
    if (contador == 0) {
        printf("El nombre introducido no tiene hijos o no existe.\n");
    }
}

//Funcion que imprime a los killers del arbol
void buscarKiller(TABB arbol){
    int maxKills=-1;
    //Primero miro cual es el numero maximo de kills
    BuscarPersonajes(arbol,NULL,"killer",&maxKills);
    if(maxKills==0){
        printf("No hay ningún killer\n");
    }
    //si hay imprimo a los que lo cumplen
    else{
        printf("    Los killers con %d asesinatos son: ", maxKills);
        BuscarPersonajes(arbol, NULL, "printkillers", &maxKills);
    }
}

//funcion que clona una lista en otra para aumentar la modularidad del codigo
void clonarListas(TLISTA L1, TLISTA * L2){
    if(!esListaVacia(L1)){
        TPOSICION actual;
        TPOSICION final=finLista(L1);
        TIPOELEMENTOLISTA e;
        for(actual=primeroLista(L1); actual!=final; actual=siguienteLista(L1, actual)){
            recuperarElementoLista(L1, actual, &e);
            insertarElementoLista(L2, primeroLista(*L2), e);
        }
    }

}

//funcion que permite modificar a un personaje
void modificarPersonaje(TABB *arbol) {
    char nombre[50];
    char opcion;
    char str[50];
    TIPOELEMENTOABB e,aux;
    int control =1;//Esto lo pongo por si el usuario modifica el nombre y después modifica la lista, para evitar segfaults

    printf("Introduce el nombre del personaje del que quieras modificar los atributos: ");
    scanf(" %[^\n]", nombre);
    printf("\n");

    strcpy(e.nombre, nombre);

    //Compruebo que sea un miembro del arbol
    if (esMiembroAbb(*arbol, e)) {
        printf("Menú para Modificar al Personaje\n");
        //recupero el nodo del arbol

        do {
            buscarNodoAbb(*arbol, nombre, &e);

            printf("\nElige una opción:\n");
            printf("1. Modificar el nombre del Personaje\n");
            printf("2. Modificar la Casa del Personaje\n");
            printf("3. Modificar si es Royal\n");
            printf("4. Modificar los Padres del Personaje\n");
            printf("5. Modificar los Hermanos del Personaje\n");
            printf("6. Modificar los Asesinados por el Personaje\n");
            printf("S. Salir\n");

            printf("Opción: ");
            scanf(" %c", &opcion);

            switch(opcion) {
                case '1':
                    //clono todos los elementos en un nodo auxliar
                    strcpy(aux.casa, e.casa);
                    aux.royal = e.royal;

                    crearLista(&aux.padres);
                    crearLista(&aux.hermanos);
                    crearLista(&aux.asesinados);

                    clonarListas(e.padres, &aux.padres);
                    clonarListas(e.hermanos, &aux.hermanos);
                    clonarListas(e.asesinados, &aux.asesinados);
                    //suprimo el elemento, solo elimino e inserto el elemento en caso de que se modifique el nombre
                    suprimirElementoAbb(arbol, e);

                    printf("Introduce el nuevo nombre: ");
                    scanf(" %[^\n]", str);
                    strcpy(aux.nombre, str);

                    //añado el nodo auxliar
                    insertarElementoAbb(arbol, aux);
                    control=0;
                    break;

                case '2':
                    printf("Introduce la nueva Casa: ");
                    scanf(" %[^\n]", str);
                    strcpy(e.casa, str);
                    break;

                case '3':
                    printf("Introduce 1 para Royal, 0 para no Royal: ");
                    scanf(" %d", &e.royal);
                    break;

                case '4':
                    printf("Introduce los nuevos Padres: ");
                    if(control){
                        destruirLista(&e.padres);
                        crearLista(&e.padres);
                        procesarListas(&e.padres, "Padres");
                    }

                    else{
                        destruirLista(&aux.padres);
                        crearLista(&aux.padres);
                        procesarListas(&aux.padres, "Padres");
                    }
                    break;

                case '5':
                    printf("Introduce los nuevos Hermanos:\n");
                    if(control){
                        destruirLista(&e.hermanos);
                        crearLista(&e.hermanos);
                        procesarListas(&e.hermanos, "Hermanos");
                    }
                    else{
                        destruirLista(&aux.hermanos);
                        crearLista(&aux.hermanos);
                        procesarListas(&aux.hermanos, "Hermanos");
                    }
                    break;

                case '6':
                    printf("Introduce los nuevos Asesinados:\n");
                    if(control){
                        destruirLista(&e.asesinados);
                        crearLista(&e.asesinados);
                        procesarListas(&e.asesinados,"Asesinados");
                    }
                    else{
                        destruirLista(&aux.asesinados);
                        crearLista(&aux.asesinados);
                        procesarListas(&aux.asesinados, "Asesinados");
                    }

                    break;


                default:
                    printf("Opción no válida, intenta de nuevo.\n");
            }

        } while (opcion != 'S' && opcion != 's');
    } else {
        printf("El personaje introducido no existe.\n");
    }
}







