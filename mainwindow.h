#ifndef MAINWINDOW_H
#define MAINWINDOW_H
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
    FILE *archivo;
    QString path;

private slots:
    void on_actionNuevo_Archivo_triggered();
    void on_actionAbrir_Archivo_triggered();
    void on_actionCrear_Registro_triggered();
    void on_actionCrear_Campo_triggered();
    void on_actionCrear_Tabla_triggered();
    void on_actionCerrar_Archivo_triggered();
    void on_actionGuardar_triggered();
    void on_actionSalir_triggered();
    void crearTabla();
    void clickElemento();
    void on_pushButton_clicked();



    void on_btnCerrar_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
};

#endif // MAINWINDOW_H
