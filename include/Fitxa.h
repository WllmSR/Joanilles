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
    COLOR_BLANC = 1,
    COLOR_EMPTY = 0
} ColorFitxa;

class Fitxa {
private:
    TipusFitxa tipus;
    ColorFitxa color;
    Posicio posFitxa;
    Moviment moviments;

public:
    Fitxa() { tipus = TIPUS_EMPTY; color = COLOR_EMPTY; posFitxa(); }
    Fitxa(char tipusIcolor, const array<char, 2>& pos, const Fitxa& tauler[][9]);                                   //Joannnnn

    TipusFitxa getTipus() const { return tipus; }
    ColorFitxa getColor() const { return color; }
    const Moviment getMoviments() const { return moviments; }

    void setTipus(int t) { tipus = (TipusFitxa)t; }
    void setColor(int c) { color = (ColorFitxa)c; }

    void afegeixMoviments(const Moviment& m);                                       //Joannnn

    void netejaMoviments() { moviments.CleanMoviment(); }

    bool movimentsEsBuit() const { return moviments.empty(); }
    void ferDama() { tipus = TIPUS_DAMA; }
    bool esBuit()const{return tipus==COLOR_EMPTY;}
    bool esAmic(const Fitxa& variable)const{return color==variable.color;}
    bool esEnemic(const Fitxa& variable)const{return color!=variable.color;}
    void calcularPosicionsPossibles(const Fitxa m_tauler[][9], const Posicio& original){
        moviments.actualitzaMoviments(const Fitxa m_tauler[][9], const Posicio& original);

    }
};

#endif

