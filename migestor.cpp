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

    memcpy(&(readStruct.nom_tabla), &byteArray[pos], sizeof(const char *));
    pos+= sizeof(char);

    memcpy(&(readStruct.pos_databloque), &byteArray[pos], sizeof(int));
    pos+= sizeof(int);

    memcpy(&(readStruct.cant_campos), &byteArray[pos], sizeof(int));
    pos+= sizeof(int);

 }

vector <metaCampos> miGestor::leermetaData()
{
    this->archivo = fopen(path.toStdString().c_str(),"rb+");

    vector <metaCampos> mistablas;

    masterBloque master = leerMasterBloque(master);

    int prox_libre;

    fread(&prox_libre,sizeof(int),1,archivo);
    int pos = ftell(archivo);

       while(pos<prox_libre)
       {
        metaCampos readStruct;
        fread(&readStruct,sizeof(metaData),1,archivo);

        pos+=sizeof(metaData);
        fseek(archivo,pos,SEEK_SET);

        for( int i = 0; i< readStruct.cant_campos; i++)
           {
              Campo campo;
              fread(&campo,sizeof(campo),1,archivo);

              readStruct.campos.push_back(campo);

               pos+=sizeof(campo);
           }

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

int miGestor::getProxData()
{
        this->archivo = fopen(path.toStdString().c_str(),"rb+");
        int prox_libre;

        fseek(this->archivo,4112,SEEK_SET);

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

               //ACTUALIZAR EL PROXIMO LIBRE
             fseek(archivo,12,SEEK_SET);

             fwrite(&p_act,sizeof(int),1,archivo);

         //    qDebug () <<"pa_ct" << p_act;

             fflush(archivo);
}

void miGestor::escribirCampo(Campo campo)
{
    this->archivo = fopen(path.toStdString().c_str(),"rb+");

    int prox_libre=getProxMetadata();

    qDebug () <<prox_libre <<"CAMPO";

     fseek(archivo,prox_libre,SEEK_SET);
//     qDebug () <<ftell(archivo)<<"donde esta al escribir CAMPO";

    fwrite(&campo,sizeof(campo),1,archivo);

    fseek(archivo,sizeof(campo),SEEK_CUR);

    int p=prox_libre+sizeof(campo);

    fseek(archivo,12,SEEK_SET);

    fwrite(&p,sizeof(int),1,archivo);

  //  qDebug () <<p <<"PACT COMPO";

    fflush(archivo);

}

void miGestor::leerCampo(Campo campo)
{
    fread(&campo,sizeof(campo),1,archivo);
}

vector <datas>  miGestor::leerdataBloque()
{
    this->archivo = fopen(path.toStdString().c_str(),"rb+");

    int prox_libre = getProxData();

    fseek(archivo,4116,SEEK_SET);

    vector <datas> info;

    for( int i= 4116; i< prox_libre; i++)
    {
        datas datos;

        //qDebug () << " empezando "<<ftell(archivo);
        fread(&datos,sizeof(datos),1,archivo);

    //    qDebug () << " dato "<<ftell(archivo);
        i+=sizeof(datos);
       // cout  << "dato " << datos.datos;
       // cout  << " Largo " << datos.tamano <<endl;

        info.push_back(datos);
    }

    return info;
}

void miGestor::escribirdataBloque( datas datos)
{
     this->archivo = fopen(path.toStdString().c_str(),"rb+");

     int prox_libre = getProxData();

     fseek(archivo,prox_libre,SEEK_SET);

     qDebug () <<"prox libre " << prox_libre;

     fwrite(&datos,sizeof(datos),1,archivo);

     qDebug () << " DESPUES DATOS "<<ftell(archivo) ;
     prox_libre+=sizeof(datos);

      qDebug () << " DATOS "<<datos.datos;

      qDebug () << " TAMANIO "<< datos.tamano;
      qDebug () << " TABLA "<< datos.tabla;


   //actualizar prox_libre del char * de data
     fseek(archivo,4112,SEEK_SET);

     qDebug () <<"actualizar prox libre " << prox_libre;

     fwrite(&prox_libre,sizeof(int),1,archivo);

     fflush(archivo);
}

void miGestor::escribirIndice()
{

}

void miGestor::leerIndice()
{

}

void miGestor::formarArray(char * bytearray,string info,int pos, int largo)
{

}



long miGestor::posPuntero()
{
    return ftell(archivo);
}



miGestor::miGestor()
{

}
