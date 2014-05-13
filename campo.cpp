#include "campo.h"

void Campo::imprimir()
{
       cout <<"\n";
       cout << "nombre: " << std::string(nombre)<<endl;
       cout <<"longitud: "<<longitud<<endl;
       cout <<"tipo: "<<this->tipo<<endl;
       cout <<"indice: "<<this->indice<<endl;
}

Campo::Campo(QString nombre, int longitud, int tipo, int indice)
{
    strcpy(this->nombre, nombre.toStdString().c_str());
    this->longitud = longitud;
    this->tipo = tipo;
    this->indice = indice;
}

Campo::Campo()
{

}
