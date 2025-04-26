#ifndef MOVIMENT_H
#define MOVIMENT_H

#include <vector>
#include "posicio.h"
using namespace std;

class Moviment {
private:
    vector<Posicio> recorregut;
    vector<Posicio> pecesCapturades;  //podem ferho amb la classe fitxa???      podem afegir un metode que ho revisi
    //int+constructor per guardar el nombre de captures o només metode???

//hauriem de modificar vector<Posicio> recorregut i vector<Posicio> pecesCapturades per : vector<vector<Fitxa>>m_recorregut vector<vector<Fitxa>> m_capturades (Fitxa==posicio basicament)

public:
    Moviment();

    void afegeixPas(const Posicio& p);      //un sol metode?? constructor?
    void afegeixCaptura(const Posicio& p);     
    const vector<Posicio>& getRecorregut() const;
    const vector<Posicio>& getCaptures() const;
//la funcio mirarCapturesDretaEsquerra, s'haura de modificar una mica, els parametres no estan del tot correcta, pero l'estrucutra del codi està ben plantejat
mirarCapturesDretaEsquerra(const Casella& origen, vector<Casella>& parametrePosicions, vector<pair<Casella, bool>>& parametreCaptures, const Casella m_tauler[][8])     Posicio getDestiFinal() const;
void Moviments::DFS(const Fitxa m_tauler[][8], vector<vector<Fitxa>>& recorregut,vector<vector<Fitxa>>&pecesCaptured  const Fitxa& original);    
int numCaptures() const;
};

#endif
