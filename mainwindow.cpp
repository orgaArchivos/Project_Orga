#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QComboBox>
#include <QCheckBox>
#include <QWidgetItem>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::cargarTablas(metaCampos tablas)
{
    ui->listWidget->clear();
    ui->listWidget->addItem(tablas.nom_tabla);

    tablas.imprimir();

//El evento que desplegará los datos de la tabla al hacer doble clic en el nombre
    connect(ui->listWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)),
                this, SLOT(clickElemento()));
}


void MainWindow::clickElemento()
{
    QMessageBox *box = new QMessageBox();
    box->setGeometry(200,200,200,200);
    box->setText("LOL FUNCA!");
    box->show();
}

void MainWindow::on_actionNuevo_Archivo_triggered()
{
    //fclose(this->archivo);
        QString fileName = QFileDialog::getSaveFileName(this,tr("Guardar archivo"),QDir::currentPath(), tr("Archivos (*.gbd)") );
       if(!fileName.isEmpty()){

          this->path = fileName;
          this->gestor.path = fileName;
          bool creado = this->gestor.crearArchivo(path);
                if( creado){
                    QMessageBox::information(this,"Correcto","Archivo creado y abierto correctamente");
                    this->ui->statusLabel->setText(this->path);
                    this->ui->menuCrear->setEnabled(true);

                    //Inicializa el archivo con la primera información necesaria.
                    masterBloque master(sizeof(master),sizeof(master),sizeof(master));
                    this->gestor.escribirMasterBloque(master);

                }else{
                    QMessageBox::critical(this,"Error","Error al abrir el archivo creado");
                }
            }else{
                QMessageBox::critical(this,"Error","Posiblemente no se creó su archivo");
            }
}

//Encargado de cargar el contenido de un archivo fisico ya existente
void MainWindow::on_actionAbrir_Archivo_triggered()
{
    QMessageBox msgBox;
    msgBox.setText("Actualmente está usando otro archivo");
    msgBox.setInformativeText("¿Quiere cerrarlo y abrir uno nuevo?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    int ret = msgBox.exec();
    switch (ret) {
       case QMessageBox::Yes:
    {
        //fclose(archivo);
         QString filename = QFileDialog::getOpenFileName(this, tr("Abrir archivo"), QDir::currentPath(),  tr("Archivos (*.gbd)") );
         this->path = filename;
         this->gestor.path = filename;
        if( !filename.isNull() )
         {
            bool abierto = this->gestor.abrirArchivo(path);
             if( abierto){
                 QMessageBox::information(this,"Correcto","Archivo creado y abierto correctamente");
                 this->ui->statusLabel->setText(this->path);
                 this->ui->menuCrear->setEnabled(true);

                  masterBloque master = gestor.leerMasterBloque(master);

                  fseek(this->gestor.archivo, 0, SEEK_END); // Colocar el cursor al final del ficher
                  int tamanio = ftell(this->gestor.archivo);
                  qDebug ()  << "TAMAÑO: " <<tamanio <<endl;

                  //Solo si tiene una longitud mayor que el master bloque se leerá el resto.

                  if(tamanio > 12)
                  {
                      metaCampos tablas =  this->gestor.leermetaData();

                      cargarTablas(tablas);
                  }


             }else{
                 QMessageBox::critical(this,"Error","Error al abrir el archivo creado");
             }
         }
    }
           break;
       case QMessageBox::No:

          break;
       default:
           // should never be reached
           break;
     }
}

//Encargado de salvar todo el contenido que se ha escrito en los archivos
void MainWindow::on_actionGuardar_triggered()
{

}

//Encargado de cerrar los archivos utilizados
void MainWindow::on_actionCerrar_Archivo_triggered()
{

    if(this->gestor.cerrarArchivo()){
        //si esta abierto el archivo principal entonces se cierra
            QMessageBox::information(this,"Correcto","El archivo se cerro correctamente");
            this->ui->statusLabel->setText("");
        }else{
            QMessageBox::critical(this,"Error","Hubo un error al momento de cerrar el archivo");
        }
}

//Encargado de cerrar la ventana principal y terminar la ejecucion del programa
void MainWindow::on_actionSalir_triggered()
{
   this->ui->btnCerrar->click();
}

//Encargado de crear un nuevo campo
void MainWindow::on_actionCrear_Campo_triggered()
{

}

//Encargado de insertar un nuevo registro al archivo
void MainWindow::on_actionCrear_Registro_triggered()
{

}

void MainWindow::on_actionCrear_Tabla_triggered()
{
       bool ok;
       QString nombre = QInputDialog::getText(this, tr("Nombre de la tabla"),
                                            tr("Guardar como:"), QLineEdit::Normal,
                                            "", &ok);

       this->metaTemp.prox_libre = sizeof(metaTemp);

       if (ok && !nombre.isEmpty())
       {
           string tmp = nombre.toStdString();
           strcpy(this->metaTemp.nom_tabla, tmp.c_str());
       }

      //INICIALIZAR EN CERO LA POSICION DE LA DATA DE LA TABLA PORQUE AUN NO TIENE REGISTROS.
       this->metaTemp.pos_databloque = 0;

    for(int i = 0; i < 1; i++){
      QPointer <QCheckBox> mi_check = new QCheckBox(this);
      QPointer <QComboBox> mi_combo = new QComboBox(this);

      QStringList tipos;
      tipos <<"ENTERO"
            <<"CADENA";

      QStringList indices;
      indices <<"SI"
            <<"NO";

      mi_combo->addItems(tipos);

      indice.append(mi_check);
      tipos_datos.append(mi_combo);

      const int ultima_fila = ui->tableWidget->rowCount();
      ui->tableWidget->insertRow(ultima_fila);

      ui->tableWidget->setCellWidget(i,1,mi_combo);
      ui->tableWidget->setCellWidget(i,2,mi_check);
    }

    ui->pushButton->setEnabled(true);
    ui->pushButton_2->setEnabled(true);
    ui->pushButton_3->setEnabled(true);

}


void MainWindow::on_btnCerrar_clicked()
{
    this->close();
}

void MainWindow::on_pushButton_clicked()
{
    QPointer <QCheckBox> mi_check = new QCheckBox(this);
    QPointer <QComboBox> mi_combo = new QComboBox(this);

    QStringList tipos;
    tipos <<"ENTERO" <<"CADENA";

    mi_combo->addItems(tipos);

    indice.append(mi_check);
    tipos_datos.append(mi_combo);

    const int ultima_fila = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(ultima_fila);

    ui->tableWidget->setCellWidget(ultima_fila,1,mi_combo);
    ui->tableWidget->setCellWidget(ultima_fila,2,mi_check);
}

void MainWindow::on_pushButton_2_clicked()
{
   const int ultima_fila = ui->tableWidget->rowCount();
   ui->tableWidget->removeRow(ultima_fila-1);
   delete tipos_datos.at(ultima_fila-1);
   tipos_datos.removeAt(ultima_fila-1);
}

void MainWindow::on_pushButton_3_clicked()
{
    int iRows = ui->tableWidget->rowCount();

    this->metaTemp.cant_campos = iRows;

    this->gestor.escribirmetaData(this->metaTemp);

    for(int i = 0; i < iRows; ++i)
    {
      //Convertir el widget a combobox
      QComboBox *myCB = dynamic_cast<QComboBox*>(ui->tableWidget->cellWidget(i,1));
      //Convertir el widget a checkbox
      QCheckBox *myCHK = dynamic_cast<QCheckBox*>(ui->tableWidget->cellWidget(i,2));

      QAbstractItemModel* model = ui->tableWidget->model();
      QModelIndex idx = model->index(i,0);
     //Sacar en string el nombre del campo
      QString str1 = model->data(idx).toString();
       //Sacar en qstring la longitud del campo, luego convertirla a int
      QModelIndex idx2 = model->index(i,3);
      QString str2 = model->data(idx2).toString();

      Campo campoTemp;

      strcpy(campoTemp.nombre, str1.toStdString().c_str());
      campoTemp.longitud = str2.toInt();

      if(myCB->currentText() == "CADENA")
          campoTemp.tipo = 0;
      else
          campoTemp.tipo = 1;

      if(myCHK->isChecked())
          campoTemp.indice = 1;
      else
          campoTemp.indice = 0;

      this->gestor.escribirCampo(campoTemp);

    }

    metaTemp.imprimir();

    //Limpiar la qTableWidget, si los datos fueron guardados correctamente y si cumplen las validaciones
    for(int i=0; i < iRows; i++)
    {
       this->on_pushButton_2_clicked();
    }

}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    if(ui->tabWidget->currentIndex() == 0 )
    {
       ui->actionCrear_Tabla->setEnabled(true);
       ui->actionCrear_Campo->setEnabled(false);
       ui->actionCrear_Registro->setEnabled(false);
    }
    if(ui->tabWidget->currentIndex() == 1 )
    {
        ui->actionCrear_Tabla->setEnabled(false);
        ui->actionCrear_Campo->setEnabled(true);
        ui->actionCrear_Registro->setEnabled(true);
    }

}

void MainWindow::on_tabWidget_windowIconTextChanged(const QString &iconText)
{

}
