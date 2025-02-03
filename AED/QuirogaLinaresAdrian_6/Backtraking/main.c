#include <stdio.h>
#include "Backtracking.h"

int main() {

    //Hay que modificar el n en Backtracking.h

    int B[n][n]= {
        {11, 17, 8},
        {9, 7, 6},
        {13, 15, 16}
    };


    /*
    int B[n][n] = {
        {11, 17, 8, 16, 20, 14},
        {9, 7, 6, 12, 15, 18},
        {13, 15, 16, 12, 16, 18},
        {21, 24, 28, 17, 26, 20},
        {10, 14, 12, 11, 15, 13},
        {12, 20, 19, 13, 22, 17}
    };
    */


    int sInicial[n];
    for (int i = 0; i < n; i++) sInicial[i] = -1;

    //Backtracking sin usar el vector de usadas
    Backtracking(sInicial, B,0);

    //Backtracking usando el vector de usadas
    Backtracking(sInicial, B,1);

    return 0;
}
