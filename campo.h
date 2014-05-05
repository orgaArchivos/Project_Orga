#ifndef CAMPO_H
#define CAMPO_H

class Campo
{
public:
    char nombre[20];
    int longitud;
    int tipo;        // Para el tipo usaremos 1 para indicar ENTERO y el 0 para indicar STRING
    int indice;      // Para el ÍDICE usaremos 1 para indicar NO y el 0 para indicar NO
    Campo();
};

#endif // CAMPO_H
