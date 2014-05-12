#ifndef CAMPO_H
#define CAMPO_H
#include <iostream>
#include <QString>
using namespace std;

#include <QDebug>

class Campo
{
public:
    char nombre[30];
    int longitud;
    int tipo;        // Para el tipo usaremos 1 para indicar ENTERO y el 0 para indicar STRING
    int indice;      // Para el ÍDICE usaremos 1 para indicar NO y el 0 para indicar NO

    void imprimir();
    Campo(QString nombre, int longitud, int tipo, int indice);
    Campo();
};

#endif // CAMPO_H
