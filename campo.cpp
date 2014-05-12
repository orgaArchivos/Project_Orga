#include "campo.h"

void Campo::imprimir()
{
  //  QString nom = QString::fromUtf8(this->nombre);
      cout << "nombre" << std::string(nombre);
      cout<<"longitud "<<longitud<<endl;
       cout<<"TIPO "<<this->tipo<<endl;
        cout<<"indice "<<this->indice<<endl;
}

Campo::Campo(QString nombre, int longitud, int tipo, int indice)
{
    strcpy(this->nombre, nombre.toStdString().c_str());
   // this->nombre = nombre.toStdString();
    this->longitud = longitud;
    this->tipo = tipo;
    this->indice = indice;
}

Campo::Campo()
{

}
