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
    this->archivo = fopen(path.toStdString().c_str(),"rb+");
    rewind(archivo);

    fread(&master,sizeof(master),1,archivo);

    //El puntero queda al final del masterbloque
    return master;

}

void miGestor::escribirMasterBloque(masterBloque master)
{
    fseek(this->archivo,0,SEEK_SET);  //Posicionar el apuntador del archivo 0 SEEK_SET Desde el principio del archivo

    fwrite(&master,sizeof(master),1,archivo); // Grabar el Registro completo
    int pos=ftell(archivo)+4;
    fwrite(&pos,sizeof(int),1,archivo);
    fflush(archivo);
}

void miGestor::ByteArrayToMetadata(char * byteArray, int &byteArrayLen, int pos, metaData &readStruct, Campo &temp)
{
   this->archivo = fopen(path.toStdString().c_str(),"rb+");

   //while(pos < byteArrayLen){
  /*   memcpy(&(readStruct.prox_libre), &byteArray[pos], sizeof(int));
     pos+= sizeof(int);*/

    memcpy(&(readStruct.nom_tabla), &byteArray[pos], sizeof(const char *));
    pos+= sizeof(char);

    memcpy(&(readStruct.pos_databloque), &byteArray[pos], sizeof(int));
    pos+= sizeof(int);


    memcpy(&(readStruct.cant_campos), &byteArray[pos], sizeof(int));
    pos+= sizeof(int);

     qDebug () <<readStruct.cant_campos<<" ";
     qDebug () <<"\n"<<readStruct.nom_tabla<<" ";
     qDebug () <<readStruct.pos_databloque<<" ";
 }

vector <metaCampos> miGestor::leermetaData()
{
    this->archivo = fopen(path.toStdString().c_str(),"rb+");

    vector <metaCampos> mistablas;

    masterBloque master = leerMasterBloque(master);

    metaCampos readStruct;

   // fseek(archivo,12,SEEK_SET);
    fseek(archivo,0,master.actual_metadata);

    int prox_libre;

    fread(&prox_libre,sizeof(int),1,archivo);

    qDebug() <<"PROXIM LIBRE " << prox_libre;

       int pos=56;
       Campo campo;

       while(pos<prox_libre)
       {
        fread(&readStruct,sizeof(metaData),1,archivo);

        for( int i = 0; i< readStruct.cant_campos; i++)
           {
              //leerCampo(temp);
              fread(&campo,sizeof(campo),1,archivo);

              readStruct.campos.push_back(campo);
           }
          pos+=sizeof(metaData)+readStruct.cant_campos*sizeof(campo);

          mistablas.push_back(readStruct);
       }

    return mistablas;
}

int miGestor::getProxMetadata()
{
    int prox_libre;
    rewind(archivo);
    masterBloque master;
    fread(&master,sizeof(master),1,archivo);
    fseek(archivo,0,master.actual_metadata);
    fread(&prox_libre,sizeof(int),1,archivo);

    return prox_libre;
}

void miGestor::escribirmetaData(metaData metadata)
{
         this->archivo = fopen(path.toStdString().c_str(),"rb+");

         masterBloque master = leerMasterBloque(master);

         int prox_libre=getProxMetadata();

            qDebug () <<prox_libre;

             fseek(archivo,prox_libre,SEEK_SET);

             fwrite(&metadata,sizeof(metadata),1,archivo);

             int p_act=ftell (archivo);

             qDebug () << "metadata escrita en " << ftell (archivo);

            // fflush(archivo);

               //ACTUALIZAR EL PROXIMO LIBRE
             fseek(archivo,12,SEEK_SET);

             fwrite(&p_act,sizeof(int),1,archivo);

             qDebug () <<"pa_ct" << p_act;

             fflush(archivo);
}

void miGestor::escribirCampo(Campo campo)
{
    this->archivo = fopen(path.toStdString().c_str(),"rb+");

    int prox_libre=getProxMetadata();

    qDebug () <<prox_libre <<"CAMPO";

     fseek(archivo,prox_libre,SEEK_SET);
     qDebug () <<ftell(archivo)<<"dpnde esta al escribir CAMPO";

    fwrite(&campo,sizeof(campo),1,archivo);

    fseek(archivo,sizeof(campo),SEEK_CUR);

    int p=prox_libre+sizeof(campo);

    fseek(archivo,12,SEEK_SET);

    fwrite(&p,sizeof(int),1,archivo);

    qDebug () <<p <<"PACT COMPO";

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
