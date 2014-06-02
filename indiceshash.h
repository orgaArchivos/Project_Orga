#ifndef INDICESHASH_H
#define INDICESHASH_H
#include<iostream>
#include<stdlib.h>
#include<conio.h>
#include<Math.h>
#include<fstream>
using namespace std;


typedef struct indicesHash no_hash;
class indicesHash
{
public:
    int data;
    int state; /* 0 para VACIO, 1 para REMOVIDO e 2 para OCUPADO */

    int funcion(int k, int m, int i);
    no_hash *Crea_Hash(int m);
    void Inserta_Hash(no_hash *T, int m, int k);
    int Busca_Hash(no_hash *T, int m, int k, int i);
    int Remove_Hash(no_hash *T, int m, int k);
    indicesHash();
};

#endif // INDICESHASH_H
