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
class Moviment {
private:
    vector<vector<Posicio>> recorregut;
    vector<vector<Posicio>> pecesCapturades;
    vector<Posicio> destins;
    vector<Posicio> captures;
int mnumTotalCapturades;
public:
    Moviment(){mnumTotalCapturades=0;}
    ~Moviment(){mnumTotalCapturades=0;}
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
    mnumTotalCapturades=0;
}
  const vector<Posicio>& getRecorregut(int posicioIndex) const{
return recorregut[posicioIndex];
}
const vector<Posicio>& getCaptures(int posicioIndex) const{
return pecesCapturades[posicioIndex]; 
}
void mirarCapturesDretaEsquerra(const Posicio& origen, vector<pair<Posicio, int>>& parametrePosicions, vector<pair<Posicio, bool>>& parametreCaptures, const Fitxa m_tauler[][9]);

Posicio getDestiFinal(int index) const{
destins(index);
}
vector<vector<Posicio>>& getTotalRecorregut()const{return destins;}
vector<vector<Posicio>>& getTotalCaptures()const{return pecesCapturades;}
int getNumCap(int index)const{return pecesCapturades[index];}
int getNumTotalCap()const{
return mnumTotalCapturades;
}
void DFSDames(const Fitxa m_tauler[][9], vector<vector<Posicio>>& recorregut,vector<vector<Posicio>>&pecesCaptured , const Posicio& original);    
void DFSNormal(const Fitxa m_tauler[][9], vector<vector<Posicio>>& recorregut,vector<vector<Posicio>>&pecesCaptured , const Posicio& original); //aquesta funcio es la que s'ha de cridar per fer el DFS, i es la que s'ha de modificar per fer el DFS normal
int numCaptures(int index) const;
int numCapturesTotal()const;
void mirarCapturesDames(int AmuntBaix,int continuarDreta, int continuarEsquerra,const Posicio& origen,vector<Posicio>& parametrePosicionsDreta,vector<Posicio>& parametrePosicionsEsquerra, pair<Posicio, bool>& parametreCapturesDreta,pair<Posicio, bool>& parametreCapturadesEsquerra, const Fitxa m_taules[][9]); 

void actualitzaMoviments(const Fitxa m_tauler[][9], const Posicio& original);

bool esValid(int fila, int columna)const{return (fila>=0&&fila<=8)&&(columna>=0&&columna<=8);}
};
#endif
