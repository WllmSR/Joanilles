#ifndef TAULER_H
#define TAULER_H

#include "fitxa.h"
#include "posicio.h"
#include <string>
#include <array>
using namespace std;

#define N_FILES 8
#define N_COLUMNES 8

class Tauler {
private:

    Fitxa m_tauler[N_FILES][N_COLUMNES];

public:
    Tauler();
    ~Tauler(){}
    void inicialitza(const string& nomFitxer);  
    string toString() const;      
    void getPosicionsPossibles(const Posicio& origen, int& nPosicions, Posicio posicionsPossibles[]);
    void actualitzaMovimentsValids(); 
    bool mouFitxa(const Posicio& origen, const Posicio& desti);
};


