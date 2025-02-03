#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h> //Librería para las funciones de red
#include <inttypes.h>





struct in_addr miip; //Struct tipo direccion IP en formato binario ej 0xC8806EC1

int main( int argc, char ** argv){
    //inter_pton, cambia formato de texto(193.110.128.200) a binario (0xC8806EC1)
    if (inet_pton ( AF_INET , "193.110.128.200" , ( void * ) &miip ) != 1) {
        //AF_INET (IPv4), char*src (cadena de texto), void* destino (struct)
        fprintf ( stderr , "Formato de direccion incorrecto " ) ;
        exit ( EXIT_FAILURE ) ;
    }

    //el formato uint8_t es como un array de 4 bytes diferentes, 
    //y lo igualo al campo del struct que contiene la direccion
    uint8_t* bytes = &miip.s_addr;
    for (int i = 0; i < 4; i++){
        printf(" %X", bytes[i]);
    }

    printf("\n");


    //asigno el formato binario al campo del address
    miip.s_addr = 0xC8806EC1;
    //la direccion en formato tiene que tener una longitud maxima definida por INET_ADDRSTRLEN
    char miiptext [INET_ADDRSTRLEN ] ;
    //inet_ntop, cambia formato binario a texto
    if ( inet_ntop ( AF_INET , (const void * ) &miip , miiptext , INET_ADDRSTRLEN) != NULL) {
        //AF_INET(IPv4), void *src, char* dest(cadena de caracteres vacia), entero que indica el tamaño de bytes del destino
        printf ( " %s \n" , miiptext ) ; 
    }
}
