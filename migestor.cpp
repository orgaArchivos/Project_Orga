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

    fseek(archivo,0,SEEK_SET);

    if(archivo==NULL)
         qDebug() << "NO SE ABRE";

    fread(&master,sizeof(master),1,archivo);

    return master;

 //   fclose(archivo); // Cierra el archivo


}

void miGestor::escribirMasterBloque(masterBloque master)
{
    fseek(this->archivo,0,SEEK_SET);  //Posicionar el apuntador del archivo 0 SEEK_SET Desde el principio del archivo

    fwrite(&master,sizeof(master),1,archivo); // Grabar el Registro completo
   // fclose(archivo); // Cierra el archivo
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
         qDebug() <<"size of" << sizeof(metadata);
          masterBloque master = leerMasterBloque(master);
         qDebug () << "será escrita en " << master.prox_libre;

         fwrite(&metadata,master.prox_libre,1,archivo);

         //master.prox_libre += 4096;
    }

}



miGestor::miGestor()
{

}
