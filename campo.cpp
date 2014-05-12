#include "campo.h"

Campo::Campo(const char *nombre, int longitud, int tipo, int indice)
{
    this->nombre = nombre;
    this->longitud = longitud;
    this->tipo = tipo;
    this->indice = indice;
}

Campo::Campo()
{

}
