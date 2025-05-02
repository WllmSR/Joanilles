#ifndef MOVIMENT_H
#define MOVIMENT_H
#include <vector>
#include <tuple>
#include <utility> // per pair
#include <algorithm> //per find, m'ha fet pal escriure mes codi
#include <string>
#include <stack>//fem ús de l'algorisme dfs, per tant es necessari utilitzar un stack, ho podem fer recursivament  tambe
#include "Posicio.h"
#include "Fitxa.h"
using namespace std;
class Moviment{
private:
    vector<vector<Posicio>> recorregut;
    vector<vector<Posicio>> pecesCapturades;
    vector<Posicio> destins;
    vector<Posicio> captures;

public:
    Moviment(){}
    ~Moviment() { CleanMoviment(); }
void CleanMoviment(){
    for(int i =0;i<recorregut.size();i++){
        recorregut[i].clear();
    }
    recorregut.clear();
    for(int i =0;i<pecesCapturades.size();i++){
        pecesCapturades[i].clear();
    }
    pecesCapturades.clear();
    destins.clear();
}
const vector<Posicio>& getRecorregut(int posicioIndex) const{
return recorregut[posicioIndex];
}
const vector<Posicio>& getCaptures(int posicioIndex) const{
return pecesCapturades[posicioIndex]; 
}
void mirarCapturesDretaEsquerra(const Posicio& origen, vector<pair<Posicio, int>>& parametrePosicions, vector<pair<Posicio, bool>>& parametreCaptures, const Fitxa m_tauler[][9]);
void mirarCapturesDames(int AmuntBaix, int& continuarDreta, int& continuarEsquerra, const Posicio& origen, vector<Posicio>& parametrePosicionsDreta, vector<Posicio>& parametrePosicionsEsquerra, pair<Posicio, bool>& parametreCapturesDreta, pair<Posicio, bool>& parametreCapturadesEsquerra, const Fitxa m_tauler[][9]);
void DFSDames(const Fitxa m_tauler[][9], vector<vector<Posicio>>& recorregut, vector<vector<Posicio>>& pecesCaptured, const Posicio& original);
void DFSNormal(const Fitxa m_tauler[][9], vector<vector<Posicio>>& recorregut, vector<vector<Posicio>>& pecesCaptured, const Posicio& original) 
    {
        TipusFitxa titits = m_tauler[original.getFila()][original.getColumna()].getTipus();
        if (titits == TIPUS_DAMA) {
            DFSDames(m_tauler, recorregut, pecesCapturades, original);
        }
        else if (titits == TIPUS_NORMAL) {
            DFSNormal(m_tauler, recorregut, pecesCapturades, original);
        }
        else {
            return;
        }
        for (const auto fitxa : recorregut) {
            for (const auto element : fitxa) {
                if (find(destins.begin(), destins.end(), element) == destins.end()) {
                    destins.push_back(element);
                }
            }
        }
        for (const auto fitxa : pecesCapturades) {
            for (const auto element : fitxa) {
                if (find(captures.begin(), captures.end(), element) == captures.end()) {
                    captures.push_back(element);
                }
            }
        
}
void actualitzaMoviments(const Fitxa m_tauler[][9], const Posicio& original);

bool esValid(int fila, int columna);

};
bool Moviment::esValid(int fila, int columna); {
    return (fila >= 0 && fila <= 8) && (columna >= 0 && columna <= 8);
}
#endif
