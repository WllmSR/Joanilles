#include "Tauler.h"
Tauler::Tauler() {
    for (int i = 0; i < N_FILES; ++i) {
        for (int j = 0; j < N_COLUMNES; ++j) {
            m_tauler[i][j] = Fitxa();  // Calls default constructor (TIPUS_EMPTY, COLOR_EMPTY)
        }
    }
}


void Tauler::inicialitza(const string& nomFitxer){
    
}
void Tauler::actualitzaMovimentsValids(){
    
}
void Tauler::getPosicionsPossibles(const Posicio& origen, int& nPosicions, Posicio posicionsPossibles[]){
    
}
bool Tauler::mouFitxa(const Posicio& origen, const Posicio& desti){
    
}
  string toString() const{
}

#endif
