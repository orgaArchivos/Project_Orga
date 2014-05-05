#ifndef MIGESTOR_H
#define MIGESTOR_H
#include <stdio.h>
#include <iostream>
#include <ctype.h>

using namespace std;


class miGestor
{
public:
    void crearArchivo();
    void abrirArchivo();
    void leerMaterBloque();
    void escribirMasterBloque();
    void leermetaData();
    void escribirmetaData();
    void leerMDTBloque();
    void escribirMDTBloque();
    void leerdataBloque();
    void escribirdataBloque();

    miGestor();
};

#endif // MIGESTOR_H
