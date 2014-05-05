#ifndef METADATA_H
#define METADATA_H

#include <stdio.h>
#include <iostream>
#include <ctype.h>

using namespace std;


/* La clase METADATA es la que contiene la información de los bloques para dirigirme a la estructuta o MDTBloque de las tablas
 o sea a MDTBloque*/

class metaData
{
public:
     int primermdtbloque;  //Cuál es el primer MDTBloque de las tablas
     int actualmdtbloque;  //Donde se está escribiendo la informacion de estructura de la tabla
     int primerbloque;     //El primer bloque de metaData
     int actualbloque;     //El bloque actual donde se está escribienda la metaData de las tablas

     /*Los 4 campos anteriores deberían escribirse como encabezado del archivo, dejando como secuencial y de constante escritura,
     por cada una de ls tablas, la información esencial, su nombre y su direccion de su MDTBloque (dir a su estructura)*/

     char nom_tabla[30];       //El nombre de la tabla
     int pos_mdtbloque;    //Entero que brinda la información de la posicion del MDTBloque de la tabla

    metaData();
};

#endif // METADATA_H
