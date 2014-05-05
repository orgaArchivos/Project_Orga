#ifndef MASTERBLOQUE_H
#define MASTERBLOQUE_H
#include <stdio.h>
#include <iostream>
#include <ctype.h>

using namespace std;



/*El máster bloque es lo primero que se escribirá en el arvhivo de tipo .gbd, este encabezado contiene las direcciones principales
en el archivo, a espacio libres y a bloque de metadata*/


class masterBloque
{
public:
    int prox_libre;    //Este entero nos da el sigueinte espacio libre en el archivo para seguir escribiendo,
                       //puede ser tomado por cualquier tipo de bloque
    int primer_bloque;  //Dirección del primer bloque de METADATA
    int bloque_actual; //Dirección del bloque de METADATA actual (MDTBloque)
    char * toBytes;    //Función que devuelve el CHAR* de bytes para ser escrito en el archivo
    char * fromBytes;  //Usada para la lectura, hace lo inverso, convierte a Class los bytes

    masterBloque();
};

#endif // MASTERBLOQUE_H
