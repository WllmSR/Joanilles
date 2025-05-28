#pragma once
#ifndef MOVIMENT_H
#define MOVIMENT_H

#include <vector>
#include <stack>
#include <tuple>
#include <utility>
#include <algorithm>
#include "Posicio.h"

class Fitxa;

class Moviment {
private:
    std::vector<std::vector<Posicio>> recorreguts;
    std::vector<std::vector<Posicio>> pecesCapturades;
    std::vector<Posicio> destins;
    std::vector<Posicio> captures;

public:
    Moviment() {}
    ~Moviment();
    void CleanMoviment();
    const std::vector<Posicio>& getRecorregut(int posicioIndex) const;
    const std::vector<Posicio>& getCaptures(int posicioIndex) const;
    void actualitzaMoviments(std::vector<std::vector<std::pair<int,int>>>, const Posicio& original);

        bool esValid(int fila, int columna) { return (fila <= 7 && fila >= 0) && (columna <= 7 && columna >= 0);}
    std::vector<std::vector<Posicio>> getTotalRecorregut() const{ return recorreguts; }
    std::vector<std::vector<Posicio>> getTotalCaptures() const { return pecesCapturades; }

    //a continuacio tenim els funcions de l'algorisme real: 
    void mirarCapturesDretaEsquerra(const Posicio& origen, std::vector<std::pair<Posicio, int>>& parametrePosicions, std::vector<std::pair<Posicio, bool>>& parametreCaptures, std::vector<std::vector<std::pair<int, int>>>taulerTraduit);
    void mirarCapturesDames(bool haCaptruat,int AmuntBaix, int& continuarDreta, int& continuarEsquerra, const Posicio& origen, std::vector<Posicio>& parametrePosicionsDreta, std::vector<Posicio>& parametrePosicionsEsquerra, std::pair<Posicio, bool>& parametreCapturesDreta, std::pair<Posicio, bool>& parametreCapturadesEsquerra, std::vector<std::vector<std::pair<int, int>>> taulerTraduit, const std::vector<Posicio>& capturesActuals);
    std::vector<Posicio> getTotalDestins()const { return destins; }
    void DFSDames(std::vector<std::vector<std::pair<int, int>>>taulerTraduit, std::vector<std::vector<Posicio>>& recorregut, std::vector<std::vector<Posicio>>& pecesCaptured, const Posicio& original);
    void DFSNormal(std::vector<std::vector<std::pair<int,int>>>, std::vector<std::vector<Posicio>>& recorregut, std::vector<std::vector<Posicio>>& pecesCaptured, const Posicio& original);


};

#endif
