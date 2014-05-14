#include "metacampos.h"

void metaCampos::imprimir()
{
      qDebug () <<"IMPRIMIENDO SUS CAMPOS ";

      for( int i = 0; i< this->campos.size(); i++ )
      {
          Campo(campos.at(i)).imprimir();
      }
}


metaCampos::metaCampos()
{
}
