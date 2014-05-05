#ifndef DATABLOQUE_H
#define DATABLOQUE_H
#include <stdio.h>
#include <iostream>
#include <ctype.h>

using namespace std;

/*Esta clase se encarga de gestionar los datos, registros de cada una de las tablas*/

class DATABloque
{
public:
    int sig_direccion;  //Me dice donde está el próximo registro de la tabla
    int cont;
   // list <metadata>
    //Crear una estructura, tipo vector de acuerdo al tipo de campos que tiene la tabla  que llama al DATABloque

    DATABloque();
};

#endif // DATABLOQUE_H
