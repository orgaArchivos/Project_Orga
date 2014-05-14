#include "metacampos.h"

void metaCampos::imprimir()
{
      qDebug () <<"POSDATABLOQUE "<<this->pos_databloque;
      qDebug () <<"NOMBRE "<<nom_tabla;
      qDebug () <<"CANT CAMPOS "<<this->cant_campos;

      qDebug () <<"IMPRIMIENDO SUS CAMPOS ";

      for( int i = 0; i< this->campos.size(); i++ )
      {
          Campo(campos.at(i)).imprimir();
      }

}


metaCampos::metaCampos()
{
}
