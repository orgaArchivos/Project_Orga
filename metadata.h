#ifndef METADATA_H
#define METADATA_H
#include <vector>
#include "campo.h"
#include <stdio.h>
#include <iostream>
#include <ctype.h>
#include <QString>
#include <QDebug>

using namespace std;


/* La clase METADATA es la que contiene la información de los bloques para dirigirme a la estructuta o MDTBloque de las tablas
 o sea a MDTBloque*/

class metaData
{
public:

   /***NO USAR MDTBLOQUE**/
    // int primermdtbloque;  //Cuál es el primer MDTBloque de las tablas
  //   int actualmdtbloque;  //Donde se está escribiendo la informacion de estructura de la tabla
   //  int primer_bloque;     //El primer bloque de metaData
    // int actual_bloque;     //El bloque actual donde se está escribienda la metaData de las tablas

     /*Los 4 campos anteriores deberían escribirse como encabezado del archivo, dejando como secuencial y de constante escritura,
     por cada una de ls tablas, la información esencial, su nombre y su direccion de su MDTBloque (dir a su estructura)*/
     int prox_libre;  //Guarda la siguiente posicion donde puedo escribir en este bloque
     char nom_tabla[30];       //El nombre de la tabla
     int pos_databloque;    //Entero que brinda la información de la posicion del bloque de DATA de la tabla
     int cant_campos;  //La cantidad dependerá de la tabla por lo tanto debo saber para ver cuantos bytes de tipo CAMPO leeré
    // vector <Campo> campos; //Un vector de tipo campo que contendrá todos los campos y sus especificaciones

     void imprimir();

     QString getNomTabla();

    metaData();
};

#endif // METADATA_H
