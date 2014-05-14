#include "metadata.h"

void metaData::imprimir()
{
      qDebug () <<"POSDATABLOQUE "<<this->pos_databloque;
      qDebug () <<"NOMBRE "<<nom_tabla;
      qDebug () <<"CANT CAMPOS "<<this->cant_campos;
}

metaData::metaData()
{
}
