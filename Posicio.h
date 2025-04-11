#ifndef POSICIO_H
#define POSICIO_H

#include <string>
using namespace std;

class Posicio {
private:
    int fila;
    int columna;

public:
    Posicio();
    Posicio(const string& pos);

    int getFila() const;
    int getColumna() const;
    //setters?

    string toString() const;
    bool operator==(const Posicio& other) const;
};

#endif