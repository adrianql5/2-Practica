## Direcciones IP
En Internet, cada dispositivo se identifica mediante una dirección *IP*.

- **IPv4** está formada por 4 bytes (32 bits) separados por puntos (`.`), por ejemplo, `192.168.0.1`.
- **IPv6** está formada por 16 bytes (128 bits) separados por dos puntos (`:`), por ejemplo, `2001:0db8:85a3:0000:0000:8a2e:0370:7334`.

No todas las **IPv4** tienen una **IPv6** asociada. IPv4 y IPv6 son sistemas de direccionamiento diferentes. Sin embargo, existen mecanismos de transición, como las direcciones IPv4-mapeadas en IPv6, que permiten la coexistencia.

Las direcciones IPv4 son limitadas, por lo que para paliar esta restricción, se emplean direcciones privadas y la técnica de **NAT** (Network Address Translation), que permite la traducción de direcciones privadas a públicas. Otra solución es la migración a **IPv6**, que ofrece un rango de direcciones muchísimo mayor.

## Problema Big-Endian vs Little-Endian
En Internet, siempre se usa el formato **Big-Endian** para transmitir los datos a través de la red. Sin embargo, las máquinas pueden estar codificadas en **Little-Endian** o **Big-Endian**, dependiendo de su arquitectura. 

Este proceso de convertir de formato de **host** a **red** (y viceversa) lo realizan todas las máquinas. Cuando los datos se envían a través de la red, se convierten al formato Big-Endian para asegurar compatibilidad entre diferentes sistemas. Al llegar al destino, el host los reconvierte a su formato nativo.

## Nombres de host
Una forma alternativa de identificar a un dispositivo en Internet es mediante un nombre de **host**. Por ejemplo, al ejecutar el comando:
```bash
dig +short www.youtube.es
```
Obtendremos una lista de las diferentes direcciones IP asociadas. Cada una de estas direcciones IP puede tener un nombre de host asociado. Para comprobarlo, podemos usar:
```bash
dig +short -x IP
```
donde *IP* es una de las direcciones devueltas por el comando anterior.

Si ejecutamos:
```bash
dig +short AAAA www.youtube.es
```
obtendremos las direcciones IPv6 asociadas a ese nombre de host.

La razón de tener varias **IP** para un mismo dominio es asegurar fiabilidad y balanceo de carga. Los servidores con el mismo nombre de host suelen ser espejos que contienen el mismo contenido. Cada vez que se resuelve un nombre de dominio, se devuelve una **IP** de un conjunto para distribuir las solicitudes entre varios servidores.

Tener un **nombre oficial** y **varios alias** permite identificar diferentes servidores bajo un mismo nombre público, pero gestionarlos con nombres distintos en una red interna.

## Puertos 
Una vez que la transmisión llega al ordenador destino, es necesario dirigir los datos a la aplicación (*servicio*) correcta. Cada aplicación se identifica mediante un número de puerto. Al igual que ocurre con las direcciones IP, los puertos también se transmiten en **Big-Endian** cuando viajan por la red. Por ello, las máquinas realizan una conversión similar para interpretar correctamente los números de puerto.


## Servicio de Nombres de Dominio (DNS)

### Nombres de equipos:
- Los **nombres de host** identifican a los ordenadores en Internet y son más fáciles de recordar que una dirección IP.
- Un nombre de dominio puede estar asociado a varias direcciones IP (para balanceo de carga y redundancia).
- Un ordenador puede tener varios nombres de dominio (alias o subdominios).

El sistema **DNS** (Domain Name System) permite la **traducción de un nombre de dominio a una dirección IP** y viceversa.

### Para obtener los servidores DNS de un dominio y sus direcciones IP:

```bash
dig +short NS usc.es           # Obtener los servidores DNS de 'usc.es'
dig +short A ns1.usc.es         # Obtener la dirección IPv4 del servidor 'ns1.usc.es'
dig +short AAAA ns1.usc.es      # Obtener la dirección IPv6 del servidor 'ns1.usc.es' (si existe)


Para obtner los de un correo electrónico. 
```bash
dig +short MX google.com
```


