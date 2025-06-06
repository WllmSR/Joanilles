#pragma once
#include "Fitxa.h"

#include <string>
#include <fstream>
#include <array>
#include <iostream>
#define N_FILES 8
#define N_COLUMNES 8
using namespace std;
class Tauler {
private:

    Fitxa m_tauler[N_FILES][N_COLUMNES];

public:
    Tauler() {}
    ~Tauler() {}
    //void mostrarFormatSting()const;
    void inicialitza(const std::string& nomFitxer);
    std::string toString() const;
    void getPosicionsPossibles(const Posicio& origen, int& nPosicions, Posicio posicionsPossibles[]);
    void actualitzaMovimentsValids();
    bool mouFitxa(const Posicio& origen, const Posicio& desti);

    int trobarDestifinal(std::vector<Posicio> burrito,const Posicio& valor)const;
    void actualitzaTaulerNormal(int valor, std::vector<Posicio> camiActual);
   // void actualitzaTaulerDames(int valor, std::vector<Posicio>camiActual);
    void printTaulerComplert();
    
//    void printFacil();
    };



