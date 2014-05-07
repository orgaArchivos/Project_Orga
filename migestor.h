#ifndef MIGESTOR_H
#define MIGESTOR_H
#include <stdio.h>
#include <iostream>
#include <ctype.h>

using namespace std;


class miGestor
{
public:
    void crearArchivo(FILE *ARCHIVO, char * byteArray);
    void abrirArchivo(FILE *ARCHIVO, char * byteArray);
    void leerMaterBloque(FILE *ARCHIVO, char * byteArray);
    void escribirMasterBloque(FILE *ARCHIVO, char * byteArray);
    void leermetaData(FILE *ARCHIVO, char * byteArray);
    void escribirmetaData(FILE *ARCHIVO, char * byteArray);
    void leerMDTBloque(FILE *ARCHIVO, char * byteArray);
    void escribirMDTBloque(FILE *ARCHIVO, char * byteArray);
    void leerdataBloque(FILE *ARCHIVO, char * byteArray);
    void escribirdataBloque(FILE *ARCHIVO, char * byteArray);

    miGestor();
};

#endif // MIGESTOR_H
