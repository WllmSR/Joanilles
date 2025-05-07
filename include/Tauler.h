#pragma once
#ifndef TAULER_H
#define TAULER_H
#include "Fitxa.h"

#include <string>
#include <fstream>
#include <array>

#define N_FILES 8
#define N_COLUMNES 8

class Tauler {
private:

    Fitxa m_tauler[N_FILES][N_COLUMNES];

public:
    Tauler() {}
    ~Tauler() {}
    void mostrarFormatSting()const;
    void inicialitza(const std::string& nomFitxer);
    std::string toString() const;
};

#endif
