#include <stdio.h>
#include "abb.h"
#include "juegodetronos.h"


int main(int argc, char **argv) {
    char opcion;
    TABB arbol;


    crearAbb(&arbol);

    if(argc==3){
        cargarArchivo(&arbol, argc, argv);
        printf("Se van a cargar los datos del archivo %s", argv[2]);
    }

    do {
        printf("\nBienvenido a GOT\n");
        printf("   A/a) Añadir Personaje\n");
        printf("   L/l) Listado Personajes\n");
        printf("   E/e) Eliminar Personaje\n");
        printf("   B/b) Buscar Asesino\n");
        printf("   H/h) Buscar Hijo\n");
        printf("   K/k) Buscar Killer\n");
        printf("   M/m) Modificar Personaje\n");
        printf("   S/s) Salir\n");
        printf("Seleccione una opción: ");
        scanf(" %c", &opcion);

        switch (opcion) {
            case 'a': case 'A':
                anhadirPersonaje(&arbol);
                break;

            case 'l': case 'L':
                listadoPersonajes(arbol);
                break;

            case 'e': case 'E':

                eliminarPersonaje(&arbol);
                break;

            case 'b': case 'B':
                buscarAsesinos(arbol);
                break;

            case 'h': case 'H':

                buscarHijos(arbol);
                break;

            case 'k': case 'K':
                buscarKiller(arbol);
                break;

            case 'm': case 'M':
                modificarPersonaje(&arbol);
                break;

            case 's': case 'S':
                FILE* archivo;
                if(argc==3){
                    archivo= fopen(argv[2],"w");
                    listadoPersonajesArchivo(arbol,archivo);
                }
                else{
                    char str[50];
                    printf("Introduce el nombre del archivo donde desees guardar el árbol:");
                    scanf("%s",str);
                    archivo=fopen(str,"w");
                    listadoPersonajesArchivo(arbol, archivo);
                }
                fclose(archivo);
                destruirAbb(&arbol);
                printf("Saliendo del programa...\n");
                break;

            default:
                printf("Opción incorrecta.\n");
                break;
        }
    } while (opcion != 's' && opcion != 'S');
    printf("Gracias por usar GoT\n");
    return 0;
}
