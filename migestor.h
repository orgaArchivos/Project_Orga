#ifndef MIGESTOR_H
#define MIGESTOR_H
#include <stdio.h>
#include <iostream>
#include <ctype.h>
#include "masterbloque.h"
#include "metadata.h"
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
    void leermetaData(metaData metadata);
    void escribirmetaData(metaData metadata);
    void leerdataBloque(DATABloque data);
    void escribirdataBloque(DATABloque data);

    FILE *archivo;
    QString path;

    miGestor();
};

#endif // MIGESTOR_H
