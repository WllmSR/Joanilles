#ifndef FITXA_H
#define FITXA_H

#include <vector>
#include "posicio.h"
#include "moviment.h"
using namespace std;

typedef enum {
    TIPUS_NORMAL,
    TIPUS_DAMA,
    TIPUS_EMPTY
} TipusFitxa;

typedef enum {
    COLOR_NEGRE,   //-1?
    COLOR_BLANC    //+1?
} ColorFitxa;

class Fitxa {
private:
    TipusFitxa tipus;
    ColorFitxa color;
    vector<Moviment> moviments;

public:
    Fitxa();
    Fitxa(TipusFitxa t, ColorFitxa c);

    TipusFitxa getTipus() const;
    ColorFitxa getColor() const;

    void setTipus(TipusFitxa t);     //setters?
    void setColor(ColorFitxa c);

    void afegeixMoviments(const Moviment& m);
    const vector<Moviment>& getMoviments() const;

    void netejaMoviments(); 

    bool esBuida() const; //"moviments?"
    void ferDama();
};

#endif

