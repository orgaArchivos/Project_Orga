#include "indiceshash.h"

int indicesHash::funcion(int k, int m, int i)
{
     return ((k+i)%m);
}

no_hash *indicesHash::Crea_Hash(int m)
{
    no_hash *temp;
    int i;
   if((temp = (no_hash*)malloc(m*sizeof(no_hash))) != NULL)
   {
        for(i = 0; i < m; i++)
           temp[i].state = 0;
        return temp;
   }
   else
        exit(0);
}

void indicesHash::Inserta_Hash(no_hash *T, int m, int k)
{
    int j, i = 0;
    do
    {
        j = funcion(k, m, i);
        if(T[j].state == 0 || T[j].state == 1)
        {
            T[j].data = k;
            T[j].state = 2;
            cout<<"\nElemento insertado con �xito!";
            return;
        }
        else
            i++;
    }while(i < m);
    cout<<"\nTabla llena!";
}

int indicesHash::Busca_Hash(no_hash *T, int m, int k, int i)
{
    int j;
    if(i < m)
    {
        j = funcion(k, m, i);
        if(T[j].state == 0)
            return -1;
        else
            if(T[j].state == 1)
                return Busca_Hash(T, m, k, i+1);
            else
                if(T[j].data == k)
                    return j;
                else
                    return Busca_Hash(T, m, k, i+1);
    }
    return -1;
}

int indicesHash::Remove_Hash(no_hash *T, int m, int k)
{
    int i;
    i = Busca_Hash(T, m, k, 0);
    if(i == -1)
        return -1;
    else
    {
        T[i].state = 1;
        return 1;
    }
}

indicesHash::indicesHash()
{
}
