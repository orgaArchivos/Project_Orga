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
    list <metadata>
    DATABloque();
};

#endif // DATABLOQUE_H
