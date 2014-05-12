#include "migestor.h"

bool miGestor::crearArchivo(QString path)
{
    this->archivo = fopen(path.toStdString().c_str(),"wb");

    if(archivo!=NULL)
        return true;
    else
        return false;
}

bool miGestor::abrirArchivo(QString path)
{
       this->archivo = fopen(path.toStdString().c_str(),"rb+");
         if( archivo!= NULL){
            return true;
         }else{
             return false;
         }
}

bool miGestor::cerrarArchivo()
{
    int cerrado = fclose(this->archivo);

    if(cerrado == EOF)
        return false;
    else
        return true;

}

masterBloque miGestor::leerMasterBloque( masterBloque master)
{
   // this->archivo=fopen(this->path.toStdString().c_str(),"rb");
                       // en modo de solo lectura
    this->archivo = fopen(path.toStdString().c_str(),"rb+");
    rewind(archivo);

    if(archivo==NULL)
         qDebug() << "NO SE ABRE";

    fread(&master,sizeof(master),1,archivo);


    //El puntero queda al final del masterbloque
    return master;

 //   fclose(archivo); // Cierra el archivo


}

void miGestor::escribirMasterBloque(masterBloque master)
{
    fseek(this->archivo,0,SEEK_SET);  //Posicionar el apuntador del archivo 0 SEEK_SET Desde el principio del archivo

    qDebug ()  << "SIZEOF MASTERBLOQUE" << sizeof(master);

    fwrite(&master,sizeof(master),1,archivo); // Grabar el Registro completo

    // fclose(archivo); // Cierra el archivo

    fflush(archivo);
}

void miGestor::ByteArrayToMetadata(char * byteArray, int &byteArrayLen, int pos, metaData &readStruct, Campo &temp)
{
   this->archivo = fopen(path.toStdString().c_str(),"rb+");

   //while(pos < byteArrayLen){
     memcpy(&(readStruct.prox_libre), &byteArray[pos], sizeof(int));
     pos+= sizeof(int);

    // cout<<readStruct.prox_libre<<" ";


    memcpy(&(readStruct.nom_tabla), &byteArray[pos], sizeof(const char *));
    pos+= sizeof(char);



  //  cout<<"\n"<<readStruct.nom_tabla<<" ";

    memcpy(&(readStruct.pos_databloque), &byteArray[pos], sizeof(int));
    pos+= sizeof(int);

     //cout<<readStruct.pos_databloque<<" ";

    memcpy(&(readStruct.cant_campos), &byteArray[pos], sizeof(int));
    pos+= sizeof(int);
   cout<<readStruct.cant_campos<<" ";

    cout<<"\n"<<readStruct.nom_tabla<<" ";
    cout<<readStruct.prox_libre<<" ";
    cout<<readStruct.pos_databloque<<" ";


     // cout<<readStruct.cant_campos<<" ";

  /*  for( int i = 0; i< readStruct.cant_campos; i++)
    {
        memcpy(&(temp.nombre), &byteArray[pos],sizeof(const char *));
        pos+= sizeof(int);

        memcpy(&(temp.longitud), &byteArray[pos],sizeof(int));
        pos+= sizeof(int);

        memcpy(&(temp.tipo), &byteArray[pos],sizeof(int));
        pos+= sizeof(int);

        memcpy(&(temp.indice), &byteArray[pos],sizeof(int));
        pos+= sizeof(int);

        readStruct.campos.push_back(temp);
    }*/


 // }
 }

void miGestor::leermetaData()
{
    this->archivo = fopen(path.toStdString().c_str(),"rb+");
   // qDebug() <<"size of metadata" << sizeof(metadata);
    masterBloque master = leerMasterBloque(master);
   // qDebug () << "será escrita en " << master.prox_libre;
    char * byteArray= new char[4096];
    //Posicionarlo en
  //  fseek(archivo,sizeof(master),SEEK_SET);

    metaData readStruct;

    Campo temp;
    int pos = 12;

    fseek(archivo,12,SEEK_SET);


    //cout<< SEEK_CUR<<" poisiion actuAL ";

    fread(&readStruct,sizeof(readStruct),1,archivo);
       // Lee el "Registro", de tamano=sizeof(registro) del archivo "alias"

    cout<<readStruct.cant_campos<<" cant campos"<<endl;
    cout<<"\n"<<readStruct.nom_tabla<<" nombre tabla"<<endl;
    cout<<readStruct.prox_libre<<" prox libre "<<endl;
    cout<<readStruct.pos_databloque<<" pos databloque"<<endl;

    //Campo temp;

    for( int i = 0; i< readStruct.cant_campos; i++)
       {
           memcpy(&(temp.nombre), &byteArray[pos],sizeof(const char *));
           pos+= sizeof(int);

           memcpy(&(temp.longitud), &byteArray[pos],sizeof(int));
           pos+= sizeof(int);

           memcpy(&(temp.tipo), &byteArray[pos],sizeof(int));
           pos+= sizeof(int);

           memcpy(&(temp.indice), &byteArray[pos],sizeof(int));
           pos+= sizeof(int);

           //readStruct.campos.push_back(temp);
       }

     //QString foo5 = QString::fromUtf8(readStruct.nom_tabla);

    // cout<<"\n"<<foo5.toStdString()<<" ";

     //cout<<readStruct.prox_libre<<" ";
    // cout<<readStruct.pos_databloque<<" ";

   /* memcpy(&(readStruct.prox_libre), &byteArray[pos], sizeof(int));
    pos+= sizeof(int);

   // cout<<readStruct.prox_libre<<" ";


   memcpy(&(readStruct.nom_tabla), &byteArray[pos], sizeof(const char *));
   pos+= sizeof(char);


 //  cout<<"\n"<<readStruct.nom_tabla<<" ";

   memcpy(&(readStruct.pos_databloque), &byteArray[pos], sizeof(int));
   pos+= sizeof(int);

    //cout<<readStruct.pos_databloque<<" ";

   memcpy(&(readStruct.cant_campos), &byteArray[pos], sizeof(int));
   pos+= sizeof(int);
  cout<<readStruct.cant_campos<<" ";




    ByteArrayToMetadata(byteArray,byteArrayLen,12,readStruct,temp);*/

}

void miGestor::escribirmetaData(metaData metadata)
{
    //Escribe los datos de la tabla, sus campos, nombre


    if(this->archivo == NULL)
      {
        qDebug() <<"NULO";
      }
    else
    {
         this->archivo = fopen(path.toStdString().c_str(),"rb+");
         qDebug() <<"size of metadata" << sizeof(metadata);
         masterBloque master = leerMasterBloque(master);
         qDebug () << "será escrita en " << master.prox_libre;

         fseek(archivo,sizeof(master),SEEK_SET);

         qDebug () << "TAMAÑO DE TABLA " << sizeof(metadata);

         metadata.imprimir();


         fwrite(&metadata,sizeof(metadata),1,archivo);

         qDebug () << "" << QString::fromUtf8(metadata.nom_tabla);

         fflush(archivo);

    }

}



miGestor::miGestor()
{

}
