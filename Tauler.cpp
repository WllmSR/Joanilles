
//suposem que tenim fstream, no istream o ostream, fstream, no som gays
#include "Tauler.h"
Tauler::Tauler() {
    for (int i = 0; i < N_FILES; ++i) {
        for (int j = 0; j < N_COLUMNES; ++j) {
            m_tauler[i][j] = Fitxa();  
        }
    }
}


void Tauler::inicialitza(const string& nomFitxer){
    fstream myfile;
    myfile.open(nomFitxer, ios::in);
    if(myfile.is_open()){
        char columna="";
        char fila="";
        while(!eof()){
            myfile>>columna;
            myfile>>fila;
            //despres continuem amb la inicialització
        }
    }
    }
        
    
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
