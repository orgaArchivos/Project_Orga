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

masterBloque miGestor::leerMasterBloque( masterBloque master)
{
    this->archivo=fopen(this->path.toStdString().c_str(),"rb");
                       // en modo de solo lectura

    if(archivo==NULL)
         qDebug() << "NO SE ABRE";

    fread(&master,sizeof(master),1,archivo);

    return master;

    fclose(archivo); // Cierra el archivo


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
