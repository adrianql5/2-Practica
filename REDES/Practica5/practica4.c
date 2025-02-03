#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>

/*
 *
 * Adrián Quiroga Linares
 * Clara Yuemí Rodríguez Rodríguez
 *
 */

typedef struct {
    struct in_addr ip;       /* Dirección IP de la ruta */
    int longitudPrefijo;     /* Longitud del prefijo de la ruta */
    int nInterfaz;           /* Número de interfaz de salida */
} Ruta;

int evaluarPrefijoLargo (struct in_addr ip, const char *filename) {
    Ruta entrada;
    uint32_t mask;
    char ipArchivo[INET_ADDRSTRLEN + 3];
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error al abrir el archivo de tabla de reenvío");
        return -1;
    }

    /* Inicializamos la mejor ruta con un prefijo no válido */
    Ruta mejorRuta = {.ip.s_addr = 0, .longitudPrefijo = -1, .nInterfaz = -1};

    char line[100];

    while (fgets(line, sizeof(line), file)) {
        /* Extraemos IP, longitud de prefijo y número de interfaz de salida de la línea */
        if (sscanf(line, "%15[^/]/%d,%d", ipArchivo, &entrada.longitudPrefijo, &entrada.nInterfaz) < 3) {
            fprintf(stderr, "Formato incorrecto en la línea: %s", line);
            fclose(file);
            exit(EXIT_FAILURE);
        }

        /* Convertimos la IP de la tabla en formato texto a formato binario */
        if (inet_net_pton(AF_INET, ipArchivo, &entrada.ip, sizeof(entrada.ip)) < 0) {
            fprintf(stderr, "Formato de dirección incorrecto: %s\n", ipArchivo);
            fclose(file);
            exit(EXIT_FAILURE);
        }

        /*
         * Calculamos la máscara a partir de la longitud del prefijo.
         * Primero, usamos `~0U` para crear un entero de 32 bits con todos los bits en 1.
         * Luego, desplazamos estos bits a la izquierda por (32 - entrada.longitudPrefijo) para
         * dejar en 1 solo los primeros `entrada.longitudPrefijo` bits, creando así la máscara.
         * Finalmente, usamos `htonl` para convertir este valor al orden de bytes de red.
         */
        mask = htonl(~0U << (32 - entrada.longitudPrefijo));
        /*
         * Realizamos una operación AND entre la IP de entrada y la máscara.
         * Luego comparamos el resultado con la IP de la ruta en la tabla ANDeada con la máscara.
         * Si coinciden, significa que la IP de entrada coincide con el prefijo de la ruta.
         */
        if ((ip.s_addr & mask) == entrada.ip.s_addr) {

            /*
             * Si la entrada actual tiene un prefijo más largo que el mejor encontrado hasta ahora,
             * actualizamos `mejorRuta` con esta entrada.
             */
            if (entrada.longitudPrefijo > mejorRuta.longitudPrefijo) {
                mejorRuta = entrada;
            }
        }
    }


    /*
     * Si la IP indicada no se corresponde con ninguna interfaz de salida,
     * se asigna la última de la tabla (asumiendo que la última entrada del
     * archivo es la interfaz de salida por defecto)
     */
    if (mejorRuta.longitudPrefijo < 0) {
        mejorRuta = entrada;
    }

    fclose(file);

    printf("Interfaz de salida: %d\n", mejorRuta.nInterfaz);
    printf("Bits del prefijo correspondiente: %d\n", mejorRuta.longitudPrefijo);

    return mejorRuta.nInterfaz;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Uso: %s <archivo_tabla_reenvio> <direccion_IP>\n", argv[0]);
        return EXIT_FAILURE;
    }

    struct in_addr ip;
    if (!(inet_pton(AF_INET, argv[2], &ip))) {
        fprintf(stderr, "Dirección IP de entrada (%s) no válida.\n", argv[2]);
        return EXIT_FAILURE;
    }

    evaluarPrefijoLargo(ip, argv[1]);

    return EXIT_SUCCESS;
}

