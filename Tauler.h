#ifndef TAULER_H
#define TAULER_H

#include "fitxa.h"
#include "posicio.h"
#include <string>
using namespace std;

#define N_FILES 8
#define N_COLUMNES 8

class Tauler {
private:
    Fitxa m_tauler[N_FILES][N_COLUMNES];

public:
    void inicialitza(const string& nomFitxer);
    void actualitzaMovimentsValids();
    void getPosicionsPossibles(const Posicio& origen, int& nPosicions, Posicio posicionsPossibles[]);
    bool mouFitxa(const Posicio& origen, const Posicio& desti);
    string toString() const;
};

#endif
