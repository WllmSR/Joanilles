#include "Posicio.h"
Posicio::Posicio(){
}
Posicio::Posicio(const string& pos){
  
}
int Posicio::getFila() const{
return fila;      
}
int Posicio::getColumna() const{
      return columna;
}
string Posicio::toString() const{
      
}
bool Posicio::operator==(const Posicio& other) const{
  return ((fila==other.fila)&&(columna==other.columna));
}

