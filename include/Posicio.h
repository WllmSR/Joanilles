#pragma once
#ifndef POSICIO_H
#define POSICIO_H
#include <array>

class Posicio
{
private:
    int fila;
    int columna;

public:
    Posicio() { fila = 0; columna = 0; }
    Posicio(const std::array<char, 2>& pos);
    void inicialitza(int fill, int coll) { fila = fill; columna = coll; }
    Posicio(int Nfila, int Ncolumna) { fila = Nfila; columna = Ncolumna; }
    int getFila() const { return fila; }
    int getColumna() const { return columna; }

    bool operator==(const Posicio& other) const;
    Posicio& operator=(const Posicio& other);
};

#endif
