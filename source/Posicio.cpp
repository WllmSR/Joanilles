#include "Posicio.h"
using namespace std;
Posicio::Posicio(const array<char, 2>& pos)
{
    fila = pos[1] - '0';
    fila = fila-1;
    columna = pos[0] - 'a' + 1;
    columna = columna-1;
}

bool Posicio::operator==(const Posicio& other) const
{
    return ((fila == other.fila) && (columna == other.columna));
}

Posicio& Posicio::operator=(const Posicio& other)
{

    fila = other.fila;
    columna = other.columna;

    return *this;    //punter GOD
}
