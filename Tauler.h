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
    //vector de fitxes "utilitzables?

public:

    void inicialitza(const string& nomFitxer);  //constructor?

    //metode buida moviments
    void actualitzaMovimentsValids();  //a totes les fitxes + al vector de fitxes?

    bool mouFitxa(const Posicio& origen, const Posicio& desti);

    string toString() const;       //reconvertir al format del fitxer

//pas a fitxers???
};

#endif
