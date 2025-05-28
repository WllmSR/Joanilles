#pragma once
#ifndef POSICIO_H
#define POSICIO_H

#include <array>
#include <string>
#include <ostream>

class Posicio {
private:
    int fila;
    int columna;

public:
    Posicio() : fila(0), columna(0) {}
    Posicio(const std::array<char, 2>& pos);

    Posicio(const std::string& hola) {
        fila = hola[1] - '0';
        columna = hola[0] - 'a';
        fila = fila - 1;
    }

    Posicio(int Nfila, int Ncolumna) : fila(Nfila), columna(Ncolumna) {}

    void setFila(int f) { fila = f; }
    void setColumna(int c) { columna = c; }

    int getFila() const { return fila; }
    int getColumna() const { return columna; }

    bool operator==(const Posicio& other) const;
    Posicio& operator=(const Posicio& other) {
        if (this != &other) {
            fila = other.fila;
            columna = other.columna;
        }
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& output, const Posicio& temporal) {
        output << "fila: " << temporal.fila << ", columna: " << temporal.columna << std::endl;
        return output;
    }
};

#endif

