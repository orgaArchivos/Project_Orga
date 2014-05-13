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

   // qDebug ()  << "SIZEOF MASTERBLOQUE" << sizeof(master);

    fwrite(&master,sizeof(master),1,archivo); // Grabar el Registro completo

    fflush(archivo);
}

void miGestor::ByteArrayToMetadata(char * byteArray, int &byteArrayLen, int pos, metaData &readStruct, Campo &temp)
{
   this->archivo = fopen(path.toStdString().c_str(),"rb+");

   //while(pos < byteArrayLen){
     memcpy(&(readStruct.prox_libre), &byteArray[pos], sizeof(int));
     pos+= sizeof(int);

    memcpy(&(readStruct.nom_tabla), &byteArray[pos], sizeof(const char *));
    pos+= sizeof(char);

    memcpy(&(readStruct.pos_databloque), &byteArray[pos], sizeof(int));
    pos+= sizeof(int);


    memcpy(&(readStruct.cant_campos), &byteArray[pos], sizeof(int));
    pos+= sizeof(int);

     qDebug () <<readStruct.cant_campos<<" ";
     qDebug () <<"\n"<<readStruct.nom_tabla<<" ";
     qDebug () <<readStruct.prox_libre<<" ";
     qDebug () <<readStruct.pos_databloque<<" ";
 }

metaCampos miGestor::leermetaData()
{
    this->archivo = fopen(path.toStdString().c_str(),"rb+");

    masterBloque master = leerMasterBloque(master);

    metaCampos readStruct;

    fseek(archivo,12,SEEK_SET);

    fread(&readStruct,sizeof(metaData),1,archivo);
       // Lee el "Registro", de tamano=sizeof(registro) del archivo "alias"

    /* qDebug () <<readStruct.cant_campos<<" cant campos"<<endl;
     qDebug () <<"\n"<<readStruct.nom_tabla<<" nombre tabla"<<endl;
     qDebug () <<readStruct.prox_libre<<" prox libre "<<endl;
     qDebug () <<readStruct.pos_databloque<<" pos databloque"<<endl;

    qDebug () << "ANTES DE LEER CAMPOS " << ftell (archivo);*/

    Campo campo;

    for( int i = 0; i< readStruct.cant_campos; i++)
       {
          //leerCampo(temp);
          fread(&campo,sizeof(campo),1,archivo);

         // qDebug () << "CAMPO " << i+1 << ftell (archivo);

          readStruct.campos.push_back(campo);
       }

    return readStruct;
}

void miGestor::escribirmetaData(metaData metadata)
{
    //Escribe los datos de la tabla, sus campos, nombr

    if(this->archivo == NULL)
      {
        qDebug() <<"NULO";
      }
    else
    {
         this->archivo = fopen(path.toStdString().c_str(),"rb+");

         masterBloque master = leerMasterBloque(master);

         fseek(archivo,sizeof(master),SEEK_SET);

         fwrite(&metadata,sizeof(metadata),1,archivo);

         qDebug () << "metadata escrita en " << ftell (archivo);

         fflush(archivo);

         metadata.imprimir();
    }

}

void miGestor::escribirCampo(Campo campo)
{
    this->archivo = fopen(path.toStdString().c_str(),"rb+");

  //  qDebug ()  << "POS EN CAMPO" << ftell(archivo);

    fseek(archivo,0,SEEK_END);

    fwrite(&campo,sizeof(campo),1,archivo);

    //qDebug () << "CAMPO " <<campo.nombre<<" escrito en " << ftell (archivo);

    fflush(archivo);
}

void miGestor::leerCampo(Campo campo)
{
    //fseek(archivo,56,SEEK_SET);
    fread(&campo,sizeof(campo),1,archivo);

  //  campo.imprimir();

}

long miGestor::posPuntero()
{
    return ftell(archivo);
}



miGestor::miGestor()
{

}
