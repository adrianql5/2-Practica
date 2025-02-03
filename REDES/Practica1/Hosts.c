#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h> // Librería para las funciones de red
#include <arpa/inet.h>  // Para inet_pton y inet_ntop
#include <inttypes.h>

struct in_addr miip;

int main(int argc, char const *argv[]){
    // Convierto la direccion en formato de texto a Binario y la guardo en miip
    if (inet_pton(AF_INET, "142.250.184.174", &miip) != 1) {
        perror("inet_pton failed");
        exit(EXIT_FAILURE);
    }

    //Direccion IP original en binario
    printf("Dirección IP en formato hexadecimal: %X\n", miip.s_addr);

    //Convierto la IP de formato de host a red
    uint32_t direccion_red = htonl(miip.s_addr);
    printf("Dirección IP en formato de red: %X\n", direccion_red);

    //Convierto la direccion IP binaria a formato de host
    uint32_t direccion_host = ntohl(direccion_red);
    printf("Dirección IP en formato de host: %X\n", direccion_host);

    return 0;
}
