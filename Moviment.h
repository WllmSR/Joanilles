#ifndef MOVIMENT_H
#define MOVIMENT_H
#include <vector>
#include <tuple>
#include <utility> // per pair
#include <algorithm> //per find, m'ha fet pal escriure mes codi
#include <string>
#include <stack>//fem ús de l'algorisme dfs, per tant es necessari utilitzar un stack, ho podem fer recursivament  tambe
#include "Posicio.h"
using namespace std;
class Moviment {
private:
    vector<vector<Posicio>> recorregut;
    vector<vector<Posicio>> pecesCapturades;
    vector<Posicio> destins
public:
    Moviment();
    ~Moviment();
    //void afegeixPas(const Posicio& p);      //un sol metode?? constructor?
    //void afegeixCaptura(const Posicio& p);     
    const vector<Posicio>& getRecorregut(int posicioIndex) const;
    const vector<Posicio>& getCaptures(int posicioIndex) const;
void mirarCapturesDretaEsquerra(const Fitxa& origen, vector<Fitxa>& parametrePosicions, vector<pair<Fitxa, bool>>& parametreCaptures, const Fitxa m_tauler[][8])     Posicio getDestiFinal() const;
void DFSDames(const Fitxa m_tauler[][8], vector<vector<Fitxa>>& recorregut,vector<vector<Fitxa>>&pecesCaptured , const Fitxa& original);    
void DFSNormal(const Fitxa m_tauler[][8], vector<vector<Fitxa>>& recorregut,vector<vector<Fitxa>>&pecesCaptured , const Fitxa& original); //aquesta funcio es la que s'ha de cridar per fer el DFS, i es la que s'ha de modificar per fer el DFS normal
int numCaptures(int index) const;
int numCapturesTotal()const;
void mirarCapturesDames(const Fitxa& origen,vector<Fitxa>& parametrePosicionsDreta,vector<Fitxa>& parametrePosicionsEsquerra, vector<pair<Fitxa, bool>>& parametreCapturesDreta,vector<pair<Fitxa, bool>>& parametreCapturadesEsquerra, const Fitxa m_taules[][9]); 
void actualitzaMoviments(const Fitxa m_tauler[][8], const Fitxa& original, vector<Fitxa>& m_posicionsPossibles, vector<Fitxa>& m_posicionsCapturades);

};

#endif
