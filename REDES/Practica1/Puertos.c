#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h> //Librería para las funciones de red
#include <inttypes.h>


struct in_addr miip;

int main(int argc, char const *argv[]){
    uint16_t puerto= 0x1234;
    uint16_t puertoared = htons(puerto);
    uint16_t redapuerto = ntohs(puertoared);
    
    printf("%X \n", puerto);
    printf("%X \n", puertoared);
    printf("%X \n", redapuerto);

    
}