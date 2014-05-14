#ifndef METACAMPOS_H
#define METACAMPOS_H
#include <vector>
#include "campo.h"
#include <stdio.h>
#include <iostream>
#include <ctype.h>
#include <QString>
#include <QDebug>

using namespace std;


//Esta clase fue creada solo para devolver en un solo objeto la metadata y los campos, su vector en este caso

class metaCampos
{
public:
    //por cada una de ls tablas, la información esencial, su nombre y su direccion de su MDTBloque (dir a su estructura)*/
  //  int prox_libre;  //Guarda la siguiente posicion donde puedo escribir en este bloque
    char nom_tabla[30];       //El nombre de la tabla
    int pos_databloque;    //Entero que brinda la información de la posicion del bloque de DATA de la tabla
    int cant_campos;  //La cantidad dependerá de la tabla por lo tanto debo saber para ver cuantos bytes de tipo CAMPO leeré
    vector <Campo> campos; //Un vector de tipo campo que contendrá todos los campos y sus especificaciones

    void imprimir();

    metaCampos();
};

#endif // METACAMPOS_H
