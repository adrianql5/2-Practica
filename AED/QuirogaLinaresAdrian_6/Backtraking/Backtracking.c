#include <stdio.h>
#include "Backtracking.h"

// Variables globales
int nodosVisitados = 0;
int pasosCriterio = 0;
int pasosGenerar = 0;
int pasosSolucion = 0;
int pasosMasHermanos = 0;
int pasosRetroceder = 0;

// Verifica el criterio con/sin "usada"
int Criterio(int nivel, int s[], int usarUsadas, int usada[]) {
    //Si se usa el vector de usadas.
    if (usarUsadas) {
        pasosCriterio++;
        return (s[nivel] < n && usada[s[nivel]] == 1);
    } else {
        for (int i = 0; i < nivel; i++) {
            pasosCriterio++;
            if (s[nivel] == s[i]) return 0;
        }
        return 1;
    }
}

// Verifica si la solución es válida
int Solucion(int nivel, int s[], int usarUsadas, int usada[]) {
    pasosSolucion++;
    return (nivel == n - 1 && Criterio(nivel, s, usarUsadas, usada));
}

// Generar el siguiente nodo sin usar el vector de usadas
void GenerarSinUsadas(int *nivel, int s[], int *bact, int B[][n]) {
    pasosGenerar++;
    s[*nivel] = s[*nivel] + 1;
    if (s[*nivel] == 0) {
        *bact = *bact + B[*nivel][s[*nivel]];
    } else {
        *bact = *bact + B[*nivel][s[*nivel]] - B[*nivel][s[*nivel] - 1];
    }

    for(int i=0; i< (*nivel); i++){
        if(s[*nivel]==s[i]) return;
    }
    nodosVisitados++;//si cumple el criterio se cuenta como nodo visitado
}

// Generar el siguiente nodo usando el vector de usadas
void GenerarConUsadas(int *nivel, int s[], int *bact, int B[][n], int usada[n]) {
    pasosGenerar++;
    if (s[*nivel] != -1) {
        usada[s[*nivel]]--;
    }
    s[*nivel] = s[*nivel] + 1;
    if (s[*nivel] < n) {
        usada[s[*nivel]]++;
    }
    if (s[*nivel] == 0) {
        *bact = *bact + B[*nivel][s[*nivel]];
    } else {
        *bact = *bact + B[*nivel][s[*nivel]] - B[*nivel][s[*nivel] - 1];
    }

    for(int i = 0; i < (*nivel); i++){
        if(s[*nivel] == s[i]) return;
    }
    nodosVisitados++;//si cumple el criterio se cuenta como nodo visitado
}

// Resetea los contadores de pasos
void resetContadores() {
    nodosVisitados = 0;
    pasosCriterio = 0;
    pasosGenerar = 0;
    pasosSolucion = 0;
    pasosMasHermanos = 0;
    pasosRetroceder = 0;
}

// Verifica si hay más hermanos
int masHermanos(int nivel, int s[]) {
    pasosMasHermanos++;
    return s[nivel] < n - 1;
}

// Retrocede en el árbol de decisiones
void Retroceder(int *nivel, int s[], int *bact, int B[][n], int usada[n], int usarUsadas) {
    pasosRetroceder++;
    //si usamos el vector de usadas
    ///recalculamos el beneficio y el nivel
    if (usarUsadas){
        *bact = *bact - B[*nivel][s[*nivel]];
        usada[s[*nivel]]--;
    }
    else{
        *bact = *bact - B[*nivel][s[*nivel]];
    }
    s[*nivel] = -1;
    *nivel = * nivel - 1;
}

// Imprime la solución encontrada
void imprimirSolucion(int voa, int soa[], int usarUsadas) {

    if(usarUsadas) printf("Usando usadas\n");
    else printf("Sin usar usadas\n");

    printf("Tamaño del problema: %d\n", n);
    printf("Mejor beneficio: %d\n", voa);
    printf("Mejor solución: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", soa[i] + 1);
    }
    printf("\n");

    printf("\n--- Estadísticas ---\n");
    printf("Nº nodos visitados: %d\n", nodosVisitados);
    printf("Nº pasos Criterio: %d\n", pasosCriterio);
    printf("Nº pasos Generar: %d\n", pasosGenerar);
    printf("Nº pasos Solución: %d\n", pasosSolucion);
    printf("Nº pasos masHermanos: %d\n", pasosMasHermanos);
    printf("Nº pasos Retroceder: %d\n", pasosRetroceder);
    printf("\n");
}

// Algoritmo de Backtracking
void Backtracking(int sInicial[], int B[][n], int usarUsadas) {
    int nivel = 0;
    int s[n];
    for (int i = 0; i < n; i++) s[i] = sInicial[i];

    nodosVisitados ++;

    int usada[n];

    //en caso de querer usar el vector de usadas
    if(usarUsadas) for (int i = 0; i < n; i++) usada[i] = 0;

    int voa = -1;
    int soa[n];
    for (int i = 0; i < n; i++) soa[i] = -1;

    int bact = 0;

    while (nivel != -1) {
        if (usarUsadas) {//gereramos con el vector de usadas
            GenerarConUsadas(&nivel, s, &bact, B, usada);
        } else {
            GenerarSinUsadas(&nivel, s, &bact, B);
        }
        //comprobamos si es solución
        if (Solucion(nivel, s, usarUsadas, usada) && (bact > voa)) {
            voa = bact;
            for (int i = 0; i < n; i++) soa[i] = s[i];
        }
        //comprobamos si se cumple el criterio
        if (Criterio(nivel, s, usarUsadas, usada) && (nivel < n - 1)) {
            nivel++;
        }
        //si no hay más hermanos retrocedemos
        while (!masHermanos(nivel, s) && (nivel >= 0)) {
            Retroceder(&nivel, s, &bact, B, usada, usarUsadas);
        }

    }

    imprimirSolucion(voa, soa,usarUsadas);

    resetContadores();
}
