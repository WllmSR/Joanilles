#include "Fitxa.h"

Fitxa::Fitxa(){
}
Fitxa::Fitxa(TipusFitxa t, ColorFitxa c){
  m_tipusFitxa=t;
  m_colorFitxa=c;
}      
TipusFitxa Fitxa::getTipus() const{
  return m_tipusFitxa;}
ColorFitxa Fitxa::getColor() const{return m_colorFitxa;}
void Fitxa::setTipus(TipusFitxa t){
  m_tipusFitxa=t;}
void Fitxa::setColor(ColorFitxa c){
  m_colorFitxa=c;}
void Fitxa::afegeixMoviment(const Moviment& m){
  
}
const vector<Moviment>& Fitxa::getMoviments() const{
      
}
void Fitxa::netejaMoviments(){
  
}
bool Fitxa::esBuida() const{
}
void Fitxa::ferDama(){
}
