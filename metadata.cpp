#include "metadata.h"

void metaData::imprimir()
{
    cout<<"PROXLIBRE "<<this->prox_libre<<endl;
     cout<<"POSDATABLOQUE "<<this->pos_databloque<<endl;

      cout<<"NOMBRE "<<nom_tabla<<endl;

    //  qDebug () << "NOMBRE" << nom_tabla;
      cout<<"CANT CAMPOS "<<this->cant_campos<<endl;

   /*   for( int i= 0; i< campos.size() ; i++)
      {
          Campo uno = campos.at(i);
          uno.imprimir();
      }*/
}

QString metaData::getNomTabla()
{
    //return this->nom_tabla.toStdString();
}

metaData::metaData()
{
}
