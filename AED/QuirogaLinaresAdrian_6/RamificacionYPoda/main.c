#include <stdio.h>
#include "RamificacionYPoda.h"

int main() {

    //Hay que modificar el N en lista.h
    /*
    int B[N][N]= {
        {11, 17, 8},
        {9, 7, 6},
        {13, 15, 16}
    };
    */

    int B[N][N] = {
        {11, 17, 8, 16, 20, 14},
        {9, 7, 6, 12, 15, 18},
        {13, 15, 16, 12, 16, 18},
        {21, 24, 28, 17, 26, 20},
        {10, 14, 12, 11, 15, 13},
        {12, 20, 19, 13, 22, 17}
    };


    NODO s;

    asignacionTrivial(B, &s) ;


    asignacionPrecisa(B, &s);

    return 0;
}
