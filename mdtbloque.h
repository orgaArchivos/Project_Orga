#ifndef MDTBLOQUE_H
#define MDTBLOQUE_H
#include "campo.h"
#include <stdio.h>
#include <iostream>
#include <ctype.h>

using namespace std;


/*La clase MDTBloque es la que contiene la información de toda la estructura de la tabla, como los campos, sus longitudes
aquí se estará escribiendo cada campo, la estructura, de cada una de las tablas de la base de datos.*/

class MDTBloque
{
public:
    int actualdatabloque;    //Donde se está escribiendo los datos la tabla en este momento
    int primerdatabloque;    //Cuál es el primer bloque de datos de la tabla
    int midatabloque;        //Donde está ubicada mi información, dirección a mi información
    char nom_tabla[30];      //Un vector de tipo campo que contendrá todos los campos y sus especificaciones
    vector <Campo> campos;
    MDTBloque();
};

#endif // MDTBLOQUE_H
