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
    ui->tableWidget->setColumnWidth(0,120);
    ui->tableWidget->setColumnWidth(2,50);
    ui->pushButton->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_A));
    ui->pushButton_2->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_D));
    ui->pushButton_3->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_G));
    ui->pushButton_4->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_N));
    ui->pushButton_5->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_G));
    ui->pushButton_6->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_B));

   // ui->tabWidget->setCurrentIndex(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::cargarTablas(vector<metaCampos> tablas)
{
     ui->tableWidget_2->clearContents();
     ui->listWidget->clear();

     for(std::size_t i=0;i<tablas.size();++i)
      {
        ui->listWidget->addItem(metaCampos(tablas.at(i)).nom_tabla);
      }

    connect(ui->listWidget, SIGNAL(itemClicked(QListWidgetItem*)),this, SLOT(clickElemento()));

}


void MainWindow::clickElemento()
{

   this->gestor.cerrarArchivo();

   ui->tableWidget_2->AdjustToContents;

   for(int i = 0; i < ui->tableWidget_2->columnCount(); i++)
    {
          ui->tableWidget_2->model()->removeColumns(i,ui->tableWidget_2->columnCount());
    }

    for(int i=0; i < ui->tableWidget_2->rowCount(); i++)
    {
           ui->tableWidget_2->model()->removeRows(i,ui->tableWidget_2->rowCount());
    }

    for(int i = 0; i < ui->tableWidget_2->columnCount(); i++)
     {
        for(int j = 0; j < ui->tableWidget_2->columnCount(); j++)
         {
            ui->tableWidget_2->removeCellWidget(i,j);
         }
     }
    int index_clic = ui->listWidget->currentRow();
    this->act_tabla = index_clic;

    vector<metaCampos> tablas =  this->gestor.leermetaData();

    metaCampos elegida =  metaCampos(tablas.at(index_clic));

    for(int i = 0; i < elegida.cant_campos ; i++)
    {
      ui->tableWidget_2->insertColumn(i);
      QTableWidgetItem* qtwi = new QTableWidgetItem(QString(Campo(elegida.campos.at(i)).nombre),QTableWidgetItem::Type);


      if(Campo(elegida.campos.at(i)).indice == 1)
      {
          qDebug () <<Campo(elegida.campos.at(i)).nombre <<"  es indice, en la posicion " << i;
          //Guardamos la posicion en la tabla del campo que es indice. Así podemos saber cual serán los datos
          //de la tabla que guardaremos en el indice

          this->act_index = (i);
      }

      //Sumamos uno, en adelante, será 1 = 8212; 2=12312; 3=16408 para this->act_tabla

      ui->tableWidget_2->setHorizontalHeaderItem(i,qtwi);
    }

   const int ultima_fila = ui->tableWidget_2->rowCount();
   ui->tableWidget_2->insertRow(ultima_fila);

   ui->pushButton_4->setEnabled(true);
   ui->pushButton_5->setEnabled(true);
   ui->pushButton_6->setEnabled(true);
   ui->actionCrear_Registro->setEnabled(true);

    vector <datas> info =this->gestor.leerdataBloque();

    vector<datas>::const_iterator it;
    int i=0;

    for (it = info.begin(); it != info.end(); ++it) {
        QTableWidgetItem *setdes = new QTableWidgetItem;

       // if( datas(*it).datos != " ")
         setdes->setText(datas(*it).datos);

        //cout <<i<<endl;

        if(datas(*it).tabla == this->act_tabla && setdes->text() != "" )
        {
            ui->tableWidget_2->setItem(0,i,setdes);
            cout <<datas(*it).datos<<endl;
            cout <<this->act_tabla<<endl;
        }
        i+=1;
        cout<<"ROWCONT " <<ui->tableWidget_2->rowCount()<< endl ;
        ui->tableWidget_2->insertRow(ui->tableWidget_2->rowCount() );
    }

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
                    masterBloque master;
                    master.actual_metadata= sizeof(master)+4;
                    master.primer_metadata= sizeof(master)+4;
                    master.prox_libre= sizeof(master)+4;

                    this->gestor.escribirMasterBloque(master);
                    this->gestor.escribirTablas(1);

                }else{
                    QMessageBox::critical(this,"Error","Error al abrir el archivo creado");
                }
            }else{
                QMessageBox::critical(this,"Error","Posiblemente no se creó su archivo");
            }
       ui->tabWidget->setCurrentIndex(0);
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
                 // qDebug ()  << "TAMAÑO: " <<tamanio <<endl;

                  if(tamanio > 16)
                  {
                      vector <metaCampos> tablas =  this->gestor.leermetaData();
                      cargarTablas(tablas);
                  }

                  ui->actionCrear_Registro->setEnabled(false);
                  ui->actionCrear_Campo->setEnabled(false);
                  ui->actionCrear_Tabla->setEnabled(false);

                  //ui->tabWidget->setCurrentIndex(0);
                  on_tabWidget_currentChanged();

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
    const int ultima_fila = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(ultima_fila);
}

//Encargado de insertar un nuevo registro al archivo
void MainWindow::on_actionCrear_Registro_triggered()
{
    const int ultima_fila = ui->tableWidget_2->rowCount();
    ui->tableWidget_2->insertRow(ultima_fila);
}

void MainWindow::on_actionCrear_Tabla_triggered()
{
       bool ok;

       QString nombre = QInputDialog::getText(this, tr("Nombre de la tabla"),
                                            tr("Guardar como:"), QLineEdit::Normal,
                                            "", &ok);


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
      tipos <<"ENTERO" <<"CADENA";

      QStringList indices;
      indices <<"SI"  <<"NO";

      mi_combo->addItems(tipos);
      //mi_combo->setFixedSize(87,25);
      mi_combo->setFixedHeight(25);
      mi_combo->setFixedWidth(87);

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
    ui->actionCrear_Campo->setEnabled(true);

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
      fflush(this->gestor.archivo);

    }

    //Limpiar la qTableWidget, si los datos fueron guardados correctamente y si cumplen las validaciones
    for(int i=0; i < iRows; i++)
    {
       this->on_pushButton_2_clicked();
    }

    fseek(this->gestor.archivo,4112,SEEK_SET);
     //escribir el proximo libre de la data
    int pos = 4116;

   // qDebug () << "Antes ini"<< ftell(this->gestor.archivo);

    fwrite(&pos,sizeof(int),1,this->gestor.archivo);

    fseek(this->gestor.archivo,8212,SEEK_SET);
     //escribir el proximo libre de los indices
    int pos2 = 8216;
   // qDebug () << "Antes ini"<< ftell(this->gestor.archivo);

    fwrite(&pos2,sizeof(int),1,this->gestor.archivo);

 //   qDebug () <<" Despues ini"<<ftell(this->gestor.archivo);

    fclose(this->gestor.archivo);
    this->gestor.abrirArchivo(this->path);

    vector <metaCampos> tablas =  this->gestor.leermetaData();
    cargarTablas(tablas);

}

void MainWindow::on_tabWidget_currentChanged()
{
    if(ui->tabWidget->currentIndex() == 0 )
    {
       ui->actionCrear_Tabla->setEnabled(true);
       //ui->actionCrear_Campo->setEnabled(false);
       ui->actionCrear_Registro->setEnabled(false);
    }
    else if(ui->tabWidget->currentIndex() == 1 )
    {
        ui->actionCrear_Tabla->setEnabled(false);
        ui->actionCrear_Campo->setEnabled(false);
        ui->actionCrear_Registro->setEnabled(false);
    }
}

void MainWindow::on_pushButton_4_clicked()
{
    const int ultima_fila = ui->tableWidget_2->rowCount();
    ui->tableWidget_2->insertRow(ultima_fila);

}

void MainWindow::on_pushButton_5_clicked()
{
    int iRows = ui->tableWidget_2->rowCount();
    int col = ui->tableWidget_2->columnCount();

    for(int i = 0; i < iRows; ++i)
    {
      for(int j = 0; j < col; ++j)
      {
          QAbstractItemModel* model = ui->tableWidget_2->model();
          QModelIndex idx = model->index(i,j);
         //Sacar en string el nombre del campo
          QString str1 = model->data(idx).toString();

          datas datos;

          strcpy(datos.datos, str1.toStdString().c_str());
          datos.tamano = str1.length();
          datos.tabla = this->act_tabla;

          int pos = this->gestor.getProxData();

          this->gestor.escribirdataBloque(datos);

         //se guardará en el indice solo si el indice de la tabla actual es igual a la columna
          //de la tabla donde esta dicho campo llave
          int p = 8216;

          if(j == this->act_index)
          {
              for(int i=1;i<(act_tabla+1);i++)
              {
                  p+=4096;
              }

              qDebug () << "SE ESCRIBIRÁ EN " << p ;

              indice1 ind ;

              ind.pos_enarchivo = pos;
            //  ind.valor_llave = datos.datos;
              strcpy(ind.valor_llave, str1.toStdString().c_str());

              this->gestor.escribirIndice(p,ind);

              //Al mismo tiempo se deben ir escribiendo los indices de la tabla

          }

      }
    }

    //Limpiar la qTableWidget, si los datos fueron guardados correctamente y si cumplen las validaciones
    for(int i=0; i < iRows; i++)
    {
        const int ultima_fila = ui->tableWidget_2->rowCount();
        ui->tableWidget_2->removeRow(ultima_fila-1);

    }
}

void MainWindow::on_pushButton_6_clicked()
{
    QString text = QInputDialog::getText(this,tr("Ingrese el campo clave"),tr("Buscar"),QLineEdit::Normal,"");

  //  qDebug() << text;

    vector <datas> info =this->gestor.leerdataBloque();

    vector<datas>::const_iterator it;

    bool mostrar = false;
     QString dato;
    int i = 0;
    for (it = info.begin(); it != info.end(); ++it) {

        if(datas(*it).tabla == this->act_tabla && this->act_index == i)
        {
              //   qDebug()<< datas(*it).datos;
                if(text == datas(*it).datos )
                {
                       mostrar = true;
                       dato = datas(*it).datos;
                }
        }
        i++;
        if(mostrar){
            QMessageBox::information(
                    this,
                    tr("ENCONTRADO"),
                    tr( datas(*it).datos));
           return;
        }
    }

    if(!mostrar){
        QMessageBox::information(
                this,
                tr(""),
                tr("No encontrado") );

    }


   }
