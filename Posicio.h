#ifndef POSICIO_H
#define POSICIO_H

//IMPORTANT: les files van de 1 a 8, no de 0 a 7.

#include <string>
using namespace std;

class Posicio
{
private:
    int fila;
    int columna;

public:
    Posicio() { fila = 0; columna = 0; }
    Posicio(const string& pos);

    int getFila() const { return fila; }
    int getColumna() const { return columna; }

    bool operator==(const Posicio& other) const;
    Posicio& operator=(const Posicio& other)
};

#endif
