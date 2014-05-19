#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "masterbloque.h"
#include "metadata.h"
#include "metacampos.h"
#include "databloque.h"
#include "campo.h"
#include "migestor.h"
#include "datas.h"
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
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class QComboBox;
class QCheckBox;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QList<QPointer <QCheckBox> > indice;
    QList<QPointer <QComboBox> > tipos_datos;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private:
    Ui::MainWindow *ui;
    miGestor gestor;
    QString path;
    metaData metaTemp;

private slots:
    void on_actionNuevo_Archivo_triggered();
    void on_actionAbrir_Archivo_triggered();
    void on_actionCrear_Registro_triggered();
    void on_actionCrear_Campo_triggered();
    void on_actionCrear_Tabla_triggered();
    void on_actionCerrar_Archivo_triggered();
    void on_actionGuardar_triggered();
    void on_actionSalir_triggered();
    void cargarTablas(vector<metaCampos> tablas);
    void clickElemento();
    void on_pushButton_clicked();

    void on_btnCerrar_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_tabWidget_currentChanged(int index);
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
};

#endif // MAINWINDOW_H
