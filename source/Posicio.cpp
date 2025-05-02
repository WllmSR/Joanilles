#include "Posicio.h"

Posicio::Posicio(const array<char, 2>& pos)
{
  fila = pos[1] - '0';
  columna = pos[0] - 'a' + 1;  
}

bool Posicio::operator==(const Posicio& other) const
{
  return ((fila==other.fila)&&(columna==other.columna));
}

Posicio& Posicio::operator=(const Posicio& other)
{
  
      fila = other.fila;
      columna = other.columna;
  
  return *this;    //punter GOD
}
