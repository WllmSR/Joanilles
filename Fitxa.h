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
    COLOR_NEGRE,
    COLOR_BLANC
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
    void setTipus(TipusFitxa t);
    void setColor(ColorFitxa c);
    void afegeixMoviment(const Moviment& m);
    const vector<Moviment>& getMoviments() const;
    void netejaMoviments();
    bool esBuida() const;
    void ferDama();
};

#endif

