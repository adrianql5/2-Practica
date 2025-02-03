#ifndef FUNCIONESARBOLES_H
#define FUNCIONESARBOLES_H

//Función que calcula la altura del árbol A
// @param A Arbol binario
int AlturaArbol(abin A);

//Función que calcula el número de nodos de un árbol A
// @param A Arbol binario
int NumeroNodos(abin A);

//Función que suma los elementos de un árbol A
// @param A Arbol binario
int SumaElementos(abin A);


//Función que busca en el arbol el nodo que contiene la letra A y almacena su posicion en aux
/*
@param A arbol binario
@param inf información del nodo
@param aux puntero a la rama
*/
void buscar(abin A, tipoelem inf, abin *aux);

#endif /* FUNCIONESARBOLES_H */
