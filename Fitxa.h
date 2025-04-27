#ifndef FITXA_H
#define FITXA_H

#include <vector>
#include "posicio.h"
#include "moviment.h"
using namespace std;

typedef enum {
    TIPUS_EMPTY = -1,
    TIPUS_NORMAL = 0,
    TIPUS_DAMA = 1
} TipusFitxa;

typedef enum {
    COLOR_NEGRE = -1,
    COLOR_BLANC = 1
} ColorFitxa;

class Fitxa {
private:
    TipusFitxa tipus;
    ColorFitxa color;
    Posicio posFitxa;                   //no ho haviem posat
    vector<Moviment> moviments;

public:
    Fitxa();
    Fitxa(TipusFitxa t, ColorFitxa c);   //es poden passar chars/ints

    TipusFitxa getTipus() const;
    ColorFitxa getColor() const;

    void setTipus(TipusFitxa t);     //setters?
    void setColor(ColorFitxa c);

    void afegeixMoviments(const Moviment& m);
    const vector<Moviment>& getMoviments() const;

    void netejaMoviments(); 

    bool esBuida() const; //"moviments?" + kills???
    void ferDama();
};

#endif
