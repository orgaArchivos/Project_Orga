#include "masterbloque.h"



masterBloque *masterBloque::getMasterBloque()
{
 /*   alias=fopen("PRODUCTOS.FIJ","rb"); // Abrir el archivo PRODUCTO.FIJ
                       // en modo de solo lectura
    fread(&registro,sizeof(registro),1,alias);
       // Lee el "Registro", de tamano=sizeof(registro) del archivo "alias"
    while(!feof(alias)) // Ciclo mientras no se encuentre el final del archivo
    {
      printf("\n\r%3d\t%30s\t%3d\t\t$%4.2f",registro.no_prod,registro.descrip,registro.cantidad,registro.precio);
      fread(&registro,sizeof(registro),1,alias);
    }
    fclose(alias); // Cierra el archivo*/
}

masterBloque::masterBloque(int prox_libre, int primer_metadata, int actual_metadata)
{
    this->prox_libre = prox_libre;
    this->primer_metadata = primer_metadata;
    this->actual_metadata = actual_metadata;
}

masterBloque::masterBloque()
{
}
