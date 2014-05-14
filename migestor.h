#ifndef MIGESTOR_H
#define MIGESTOR_H
#include <stdio.h>
#include <iostream>
#include <ctype.h>
#include "masterbloque.h"
#include "metadata.h"
#include "metacampos.h"
#include "databloque.h"
#include <stdio.h>
#include <iostream>
#include <ctype.h>
#include <QComboBox>
#include <qdebug.h>
#include <QMainWindow>
#include <QDialog>
#include <QFileDialog>
#include <QString>
#include <QMessageBox>
#include <QInputDialog>
#include <QLineEdit>
#include <QStandardItemModel>
#include <qpointer.h>

using namespace std;


class miGestor
{
public:
    bool crearArchivo(QString path);
    bool abrirArchivo(QString path);
    bool cerrarArchivo();
    masterBloque  leerMasterBloque(masterBloque master);
    void escribirMasterBloque(masterBloque master);
    vector <metaCampos> leermetaData();
    int getProxMetadata();
    int getProxData();
    void escribirmetaData(metaData metadata);
    void escribirCampo(Campo campo);
    void leerCampo(Campo campo);
    char* leerdataBloque();
    void escribirdataBloque(const char *dato,int largo);
    void formarArray(char *bytearray, string info, int pos, int largo);
    long int posPuntero();
    void ByteArrayToMetadata(char * byteArray, int &byteArrayLen, int pos, metaData &readStruct, Campo &temp);

    FILE *archivo;
    QString path;

    miGestor();
};

#endif // MIGESTOR_H
