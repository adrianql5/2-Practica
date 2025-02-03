#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "abin.h"
#include "pilaOperandos.h"
#include "pilaOperadores.h"


//Devuelve la prioridad del operador dentro de la pila.
//Prioridad('(')=0
int prioridadDentro(char op) {
    int prior;
    switch (op) {
        case '^': prior = 3;
            break;
        case '*': case '/': prior = 2;
            break;
        case '+': case '-': prior = 1;
            break;
        case '(': prior = 0; //nunca va a entrar en la pila, provoca vaciado
            break;
    }
    return prior;
}

//Devuelve la prioridad del operador fuera de la pila.
//Prioridad('(')=4
int prioridadFuera(char op) {
    int prior;
    switch (op) {
        case '^': prior = 3;
            break;
        case '*': case '/': prior = 2;
            break;
        case '+': case '-': prior = 1;
            break;
        case '(': prior = 4; //para que SIEMPRE entre en la pila
            break;
    }
    return prior;
}

//Devuelve 1 si c es un operador: +, -, /, *, ^, ()
unsigned esOperador(char c) {
    unsigned ope;
    switch (c) {
        case '^': case '*': case '/': case '+': case '-': case '(':
            ope = 1;
            break;
        default:
            ope = 0;
    }
    return ope;
}

//Devuelve 1 si c es un operando: mayúsculas y minúsculas
//completar para caracteres 0 a 9
unsigned esOperando(char c) {
    if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122) || (  c>= 48 && c <= 57 ) )
        return 1;
    else
        return 0;
}

//Función que construye un subárbol a partir de ambas pilas y facilita la modularidad del programa
abin construirSubarbol(pilaOperandos * operandos, pilaOperadores * operadores){
    abin aux; 
    crear(&aux); //creo mi árbol auxiliar
    insizq(&aux, topeOperadores(*operadores)); //inserto el tope de la pila de operadores
    popOperadores(operadores); //lo desapilo porque ya ha sido usado

    if(!esVaciaPilaOperandos(*operandos)){
        insArbolder(&aux, topeOperandos(*operandos));//inserto a la derecha el tope de la pila de operandos
        popOperandos(operandos);//elimino el operando de mi pila
    }
    else{
        //Esto lo hago por si el usuario introduce una expresion no valida
        printf("Pila de operandos vacía.\n");
        destruirPilaOperadores(operadores);
        destruirPilaOperandos(operandos);
        return 0;
    }

    if(!esVaciaPilaOperandos(*operandos)){ 
        //Sigo el mismo proceso que anteriormente para construir el árbol
        insArbolizq(&aux, topeOperandos(*operandos));
        popOperandos(operandos);
    }
    else{
        printf("Pila de operandos vacía.\n");
        destruirPilaOperadores(operadores);
        destruirPilaOperandos(operandos);
        return 0;
    }
    pushOperandos(operandos,aux); //meto este arbol en mi pila de operandos
    return aux; //devuelvo el arbol

}

//Recibe una cadena de caracteres y devuelve el arbol de expresion
//DEBES ESCRIBIR ESTA FUNCIÓN
abin arbolExpresion(char *expr_infija) {
    pilaOperandos operandos;
    pilaOperadores operadores;
    crearPilaOperandos(&operandos); //inicializo mis variables
    crearPilaOperadores(&operadores);

    abin arbol;
    abin aux;

    crear(&arbol);

    int i;

    for (i = 0; i < strlen(expr_infija); i++) {
        //En cada iteracion del bucle se analiza un caracter de la string que pasa el usuario
        if (esOperando(expr_infija[i])) {
            //Si es operando lo inserto en un árbol aux y meto este arbol en la pila de operandos
            crear(&aux);
            insizq(&aux, expr_infija[i]);
            pushOperandos(&operandos, aux);
        } else if (esOperador(expr_infija[i])) {
            //En caso de ser un operador distinto de ')' mientras que la pila de operadores y no se rompa la condición de las prioridades llamara a la funcion que contruye subárboles
            while (!esVaciaPilaOperadores(operadores) && (prioridadFuera(expr_infija[i]) <= prioridadDentro(topeOperadores(operadores)))) {

                aux=construirSubarbol(&operandos, &operadores);
                if(aux==NULL) return 0;
            }
            //meto en la pila de operadores el caracter
            pushOperadores(&operadores, expr_infija[i]);

        } else if (expr_infija[i] == ')') {
            //En caso de que sea ')', las pila de operadores no sea vacía y el tope sea distinto de '('
            while (!esVaciaPilaOperadores(operadores) && topeOperadores(operadores) != '(') {
                //construyo un nuevo subarbol
                aux=construirSubarbol(&operandos, &operadores);
                if (aux==NULL) return 0;
            }
            if (!esVaciaPilaOperadores(operadores)) {
                //en caso de que la pila no quede vacía hago un pop de '('
                popOperadores(&operadores);
            }

        }
    }
    
    //Si ha acabado todo el proceso anterior y la pila de operadores no ha sido vaciada contruyo nuevamente otro subarbol
    while (!esVaciaPilaOperadores(operadores)) {
        aux=construirSubarbol(&operandos, &operadores);
        if (aux==NULL) return 0;
    }

    //Finalmente libero la correspondiente memoria y devuelvo el arbol
    destruirPilaOperadores(&operadores);
    arbol = topeOperandos(operandos);
    destruirPilaOperandos(&operandos);
    return arbol;
}
 
    
    


