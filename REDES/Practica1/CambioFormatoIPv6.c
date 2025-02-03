#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h> //Librería para las funciones de red
#include <inttypes.h>




int main(int argc, char ** argv){
    struct in6_addr ipv6;
    int i=0;
    char ip6[]="1080:0:0:0:8:800:200C:417A";
    
    //funcion que cambia de texto a binario
    if ( inet_pton ( AF_INET6 , ip6, ( void * ) &ipv6 ) != 1) {
        fprintf ( stderr , "Formato de direccion incorrecto " ) ;
        exit( EXIT_FAILURE ) ;
    }
    //al ocupar el doble imprimo con un bucle
    for(i; i<16;i++){
        printf ( "%X" , ipv6.s6_addr[i]);
    }
    printf("\n”");

    //misma lógica que con IPv6
    char miiptext [INET6_ADDRSTRLEN ] ;
    if ( inet_ntop ( AF_INET6 , (const void * ) &ipv6 , miiptext , INET6_ADDRSTRLEN) != NULL) {
        printf ( "%s \n" , miiptext ) ; 
    }
     
}