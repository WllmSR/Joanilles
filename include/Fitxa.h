#pragma once
#ifndef FITXA_H
#define FITXA_H

#include <array>
#include "Posicio.h"
#include "Moviment.h"

enum TipusFitxa {
    TIPUS_EMPTY = -1,
    TIPUS_NORMAL = 0,
    TIPUS_DAMA = 1
};

enum ColorFitxa {
    COLOR_NEGRE = -1,
    COLOR_BLANC = 1,
    COLOR_EMPTY = 0
};

class Fitxa {
private:
    TipusFitxa tipus;
    ColorFitxa color;
    Posicio posFitxa;
    Moviment moviments;

public:
    Fitxa() : tipus(TIPUS_EMPTY), color(COLOR_EMPTY), posFitxa() {}
    Fitxa(char tipusIcolor, const std::array<char, 2>& pos);

    TipusFitxa getTipus() const { return tipus; }
    ColorFitxa getColor() const { return color; }
    std::vector<Posicio> getMoviments() const { return moviments.getTotalDestins(); }
    std::vector<std::vector<Posicio>> getCaptures()const { return moviments.getTotalCaptures();}
    std::vector<std::vector<Posicio>> getCamins()const { return moviments.getTotalRecorregut(); }
    Posicio getPos() const { return posFitxa; }
    void setPos(int j, int i) { posFitxa.setColumna(j);posFitxa.setFila(i);}

    void setTipus(TipusFitxa t) { tipus = static_cast<TipusFitxa>(t); }
    void setColor(ColorFitxa c) { color = static_cast<ColorFitxa>(c); }

    void netejaMoviments() { moviments.CleanMoviment(); }
    void ferDama() { tipus = TIPUS_DAMA; }
    bool esBuit() const { return tipus == TIPUS_EMPTY; }
    bool esAmic(const Fitxa& variable) const { return color == variable.color; }
    bool esEnemic(const Fitxa& variable) const { return color != variable.color; }
    void calcularPosicionsPossibles(const Fitxa tauler[][8], const Posicio& original);
};

#endif
