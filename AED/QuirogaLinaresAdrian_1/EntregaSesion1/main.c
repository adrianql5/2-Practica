#include <stdlib.h>
#include <stdio.h>

#include "abin.h"
#include "recorridos.h"
#include "funcionesArboles.h"

int main(int agrc, char ** argv){
    //defino mis variables
    abin Raiz, aux;
    int altura;
    int nNodos;
    char letra;

    //Creo y añado los elementos del Árbol
    crear(&Raiz);

    insder(&Raiz,'A');
    insder(&Raiz,'C');
    insizq(&Raiz,'B');

    aux=izq(Raiz);
    insizq(&aux,'D');
    insder(&aux,'E');

    aux=der(Raiz);
    insizq(&aux,'F');
    insder(&aux,'G');

    aux=izq(izq(Raiz));
    insizq(&aux,'H');
    insder(&aux,'I');

    aux=der(der(Raiz));
    insizq(&aux,'J');

    printf("Arbol creado\n");

    //Imprimo la altura y el recorrido inorden no recursivo
    altura = AlturaArbol(Raiz);
    printf("Altura del arbol: %d \n", altura);

    printf("Recorrido en inorden no recursivo (usa pilas): ");
    inordenNR(Raiz);
    printf("\n");

    //Le pregunto al usuario a partir de que nodo desea eliminar el subárbol
    aux= NULL;
    printf("Introduce la letra del nodo a partir del que quieres eleminar el subárbol: \n");
    scanf("%c",&letra);
    buscar(Raiz,letra,&aux);
    
    //Esto lo hago por si se da la situación de que no encuentre dicho nodo
    if(aux==NULL) printf("La letra introducida no está en el árbol\n");
    else {
        supizq(&aux);
        printf("Subárbol de %c eliminado \n",letra);
    }

    //Recorrido Postorden, altura y número de nodos
    printf("Recorrido PostOrden (IDR): ");
    postorden(Raiz);
    printf("\n");

    altura = AlturaArbol(Raiz);
    printf("Altura del arbol: %d\n", altura);

    nNodos = NumeroNodos(Raiz);
    printf("Numero de nodos: %d\n",nNodos);


    //Libero la memoria
    destruir(&Raiz);

    return 0;


}