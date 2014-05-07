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

    crearTabla();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::crearTabla()
{
    ui->listWidget->addItem("algo");

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
    fclose(this->archivo);
        QString fileName = QFileDialog::getSaveFileName(this,tr("Guardar archivo"),QDir::currentPath(), tr("Archivos (*.gbd)") );
       if(!fileName.isEmpty()){

          this->path = fileName;
          this->archivo = fopen(path.toStdString().c_str(),"wb");

                if( archivo!= NULL){
                    QMessageBox::information(this,"Correcto","Archivo creado y abierto correctamente");
                    this->ui->statusLabel->setText(this->path);
                    this->ui->menuCrear->setEnabled(true);
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
        fclose(archivo);
         QString filename = QFileDialog::getOpenFileName(this, tr("Abrir archivo"), QDir::currentPath(),  tr("Archivos (*.gbd)") );
         this->path = filename;
        if( !filename.isNull() )
         {
           this->archivo = fopen(filename.toStdString().c_str(),"rb+");
             if( archivo!= NULL){
                 QMessageBox::information(this,"Correcto","Archivo creado y abierto correctamente");
                 this->ui->statusLabel->setText(this->path);
                 this->ui->menuCrear->setEnabled(true);
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
   /* //verifica si esta abierto el archivo
    if(this->fileRecord.isOpen()){
        //simplemente se hace un flush para mandarlos a guardar
        if(this->fileRecord.flush() && this->indicesFile.flush()){
            QMessageBox::information(this,"Correcto","El archivo se ha guardado correctamente");
        }else{
            QMessageBox::critical(this,"Error","Hubo un error al momento de guardar el archivo");
        }
    }else{
        QMessageBox::critical(this,"Error","No tiene un archivo abierto que pueda salvar");
    }*/
}

//Encargado de cerrar los archivos utilizados
void MainWindow::on_actionCerrar_Archivo_triggered()
{
   /* //Cierra el archivo de indices
    this->indicesFile.close();
    if(this->fileRecord.isOpen()){
        //si esta abierto el archivo principal entonces se cierra
        if(this->fileRecord.close() && !this->indicesFile.isOpen()){

            //limpia el vector de campos del archivo
            while(this->fileRecord.fieldsSize() != 0){
                this->fileRecord.removeField(0);
            }

            //Limpia el mapa de indices primarios
            this->fileRecord.cleanMap();
            QMessageBox::information(this,"Correcto","El archivo se cerro correctamente");
        }else{
            QMessageBox::critical(this,"Error","Hubo un error al momento de cerrar el archivo");
        }
    }else{
        QMessageBox::critical(this,"Error","No tiene un archivo abierto que pueda cerrar");
    }*/
}

//Encargado de cerrar la ventana principal y terminar la ejecucion del programa
void MainWindow::on_actionSalir_triggered()
{
   this->ui->btnCerrar->click();
}

//Encargado de crear un nuevo campo
void MainWindow::on_actionCrear_Campo_triggered()
{
 /*   //verifica que si hay registros dentro del archivo no cree ningun campo
    if(!this->fileRecord.indexesIsEmpty()){
        QMessageBox::critical(this,"Error","Ya no puede agregar un campo al archivo");
        return;
    }

    //verifica si el archivo esta abierto
    if(this->fileRecord.isOpen()){
        //crea una nueva ventana para pedir el nuevo campo
        NewFieldWindow* createField = new NewFieldWindow();

        //ejecuta la ventana
        createField->exec();

        //obtiene el nuevo campo que se ha creado
        Field* newField = createField->getField();

        //verifica que no sea nulo y verifica si este campo es la llave principal
        if(newField != NULL){
            for(int i = 0; i < this->fileRecord.fieldsSize(); i++){
                if(this->fileRecord.getField(i)->isKey()){
                    newField->setKey(0);
                    i = this->fileRecord.fieldsSize();
                }
            }
            //se agrega el nuevo campo al vector
            this->fileRecord.addField(newField);
        }

        //se manda a escribir los campos al archivo
        string header = this->fileRecord.toStringHeader();
        cout<<header<<endl;
        this->fileRecord.setDataStart(header.size());
        this->fileRecord.seekp(0,ios_base::beg);
        this->fileRecord.write(header.c_str(),header.size());
        this->fileRecord.flush();

        //se obtiene el tamanio de cada registro del archivo
        vector<Field*> fields = this->fileRecord.getFields();
        int rl = 0;
        for(int i = 0; i < fields.size(); i++){
            rl += fields.at(i)->getLength();
        }
        this->fileRecord.setRecordLength(rl);

        //se elimina la ventana creada
        delete createField;
    }else{
        QMessageBox::critical(this,"Error","No tiene un archivo abierto para crear un Campo");
    }*/
}

/*//Encargada de modificar un campo ya existente
void MainWindow::on_modifyField_triggered()
{
   //verifica que si ya hay registros en el archivo no se pueda modificar ningun campo
    if(!this->fileRecord.indexesIsEmpty()){
        QMessageBox::critical(this,"Error","No puede modificar campos");
        return;
    }

    //verifica que archivo este abierto
    if(this->fileRecord.isOpen()){
        //crea una nueva ventana para pedir el campo que se desea modificar y por cual
        ModifyFieldWindow* modifyField = new ModifyFieldWindow();

        //se le manda el vector de campos para el combobox
        modifyField->setFields(this->fileRecord.getFields());
        modifyField->exec();

        //se toma el nuevo campo creado
        Field* newField = modifyField->getField();

        if(newField != NULL){
            //toma el indice para modificar ese campo
            int index = modifyField->getIndex();

            //modifica los atributos de un campo
            this->fileRecord.modifyField(index,newField);
        }else{

        }

        //escribe en el archivo el  nuevo header
        string header = this->fileRecord.toStringHeader();
        this->fileRecord.seekp(0,ios_base::beg);
        this->fileRecord.write(header.c_str(),header.size());
        this->fileRecord.flush();

        delete modifyField;
    }else{
        QMessageBox::warning(this,"Error","No tiene un archivo abierto para modificar sus campos");
    }
}*/

/*//Encargado de mostrar en la tabla principal todos los campos existentes
void MainWindow::on_listField_triggered()
{
    //verifica que el archivo este abierto
    if(!this->fileRecord.isOpen()){
        QMessageBox::warning(this,"Error","No tiene un archivo abierto para mostrar sus campos");
        return;
    }

    //verifica que existan campos en el vector de campos
    if(this->fileRecord.fieldsSize() <= 0){
        QMessageBox::warning(this,"Error","El archivo abierto no contiene campos");
        return;
    }

    //se crea un modelo para modificarlo y luego solo ponerselo a la tabla de la ventata principal
    QStandardItemModel* model = new QStandardItemModel(1,1,this);

    //se hacen los encabezados de la tabla
    model->setHorizontalHeaderItem(0,new QStandardItem(QString("Nombre")));
    model->setHorizontalHeaderItem(1,new QStandardItem(QString("Tipo")));
    model->setHorizontalHeaderItem(2,new QStandardItem(QString("Llave")));
    model->setHorizontalHeaderItem(3,new QStandardItem(QString("Longitud")));
    model->setHorizontalHeaderItem(4,new QStandardItem(QString("Decimales")));

    //Se llenan las filas de tabla y se itera cuantas veces hayan campos para listarlos
    QString tmp;
    vector<Field*> fields = this->fileRecord.getFields();
    stringstream ss;

    for(int i = 0; i < fields.size(); i++){

        //columna de nombre
        tmp = QString::fromStdString(fields.at(i)->getName());
        model->setItem(i,0,new QStandardItem(tmp));

        //columna del tipo
        if(fields.at(i)->getType() == 'C'){
            model->setItem(i,1,new QStandardItem("Cadena"));
        }else if(fields.at(i)->getType() == 'E'){
            model->setItem(i,1,new QStandardItem("Entero"));
        }else{
            model->setItem(i,1,new QStandardItem("Real"));
        }

        //columna de la llave
        if(fields.at(i)->isKey()){
            model->setItem(i,2,new QStandardItem("Llave Primaria"));
        }else{
            model->setItem(i,2,new QStandardItem("No es Llave"));
        }

        //columna del tamanio
        ss<<fields.at(i)->getLength();
        tmp = QString::fromStdString(ss.str());
        ss.str("");
        model->setItem(i,3,new QStandardItem(tmp));

        //columna de los lugares decimales
        ss<< fields.at(i)->getDecimalPlaces();
        tmp = QString::fromStdString(ss.str());
        ss.str("");
        model->setItem(i,4,new QStandardItem(tmp));
    }
    //solo se le asigna el modelo a la tabla principal
    ui->MWTable->setModel(model);
}*/

//Encargado de insertar un nuevo registro al archivo
void MainWindow::on_actionCrear_Registro_triggered()
{
   /* //verifica que existan campos en el archivo
    if(this->fileRecord.fieldsSize() == 0){
        QMessageBox::warning(this,"Error","No tiene campos en el archivo, por favor ingrese un campo para continuar");
        return;
    }

    //Validar que cuando se ingrese la llave, esta sea unica
    vector<string> record;
    vector<Field*> tmpfields = this->fileRecord.getFields();

    for(int i = 0; i < tmpfields.size(); i++){
        Field* currentField = tmpfields[i];

        InputDialog* idialog = new InputDialog();
        idialog->setField(currentField);
        idialog->exec();

        QString text = idialog->getString();

        record.push_back(text.toStdString());
        delete idialog;
    }

    //verifica que la cantidad de ingresos sea igual a la cantidad de campos
    if(record.size() != tmpfields.size()){
        QMessageBox::critical(this,"Error","Error en la cantidad de campos que lleno");
        return;
    }

    //crea un nuevo registro
    Record* newRecord =  new Record(tmpfields,record);

    //verficica que la llave primaria no exista
    if(this->fileRecord.addRecord(newRecord)){
        //Obtiene un vector de indices principales
        vector<PrimaryIndex*> indexes = this->fileRecord.getIndexes();

        //genera como un toString para los indicies
        stringstream ss;
        for(int i = 0; i < indexes.size(); i++){
            ss<<indexes.at(i)->toString();
            if(i != indexes.size() -1){
                ss<<'/';
            }
        }

        //guarda los indices primarios en el archivo
        this->indicesFile.seekp(0,ios_base::beg);
        this->indicesFile.write(ss.str().c_str(),ss.str().length());
        this->indicesFile.flush();

        QMessageBox::information(this,"Correcto","Se ingreso correctamente el nuevo registro");
        delete newRecord;
        //lo borra de memoria, pero ya esta guardado en el archivo
    }else{
        //borra el nuevo registro porque no sirvio de nada
        QMessageBox::critical(this,"Error","Hubo un error al insertar el nuevo registro");
        delete newRecord;
    }*/
}

void MainWindow::on_actionCrear_Tabla_triggered()
{
    bool ok;
       QString nombre = QInputDialog::getText(this, tr("Nombre de la tabla"),
                                            tr("Guardar como:"), QLineEdit::Normal,
                                            "", &ok);
       if (ok && !nombre.isEmpty())
           qDebug () << nombre;
           //label->setText(text);


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
     // mi_combo2->addItems(indices);

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
    tipos <<"ENTERO"
          <<"CADENA";

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

    for(int i = 0; i < iRows; ++i)
    {

      QComboBox *myCB = dynamic_cast<QComboBox*>(ui->tableWidget->cellWidget(i,1));
      QCheckBox *myCHK = dynamic_cast<QCheckBox*>(ui->tableWidget->cellWidget(i,2));

      QAbstractItemModel* model = ui->tableWidget->model();
      QModelIndex idx = model->index(i,0);
      QString str1 = model->data(idx).toString();

      QModelIndex idx2 = model->index(i,3);
      QString str2 = model->data(idx2).toString();

      qDebug () <<  str1;
      qDebug () <<myCB->currentText();
      qDebug () <<myCHK->isChecked();
      qDebug () <<  str2;
    }


}
