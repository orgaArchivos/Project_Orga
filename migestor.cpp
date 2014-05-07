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

void miGestor::escribirMasterBloque(masterBloque master)
{
    fseek(this->archivo,0,SEEK_SET);  //Posicionar el apuntador del archivo 0 SEEK_SET Desde el principio del archivo

    fwrite(&master,sizeof(master),1,archivo); // Grabar el Registro completo
    fclose(archivo); // Cierra el archivo
}

miGestor::miGestor()
{
}
