#include "Posicio.h"
#include <iostream>
using namespace std;
Posicio::Posicio(const array<char, 2>& pos)
{
    fila = pos[1] - '0';
    columna = pos[0] - 'a' + 1;
    columna = columna - 1;
    fila = fila - 1;
}
bool Posicio::operator==(const Posicio& other) const
{
    return ((fila == other.fila) && (columna == other.columna));
}

