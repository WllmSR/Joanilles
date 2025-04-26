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

public:
    Moviment();

    void afegeixPas(const Posicio& p);      //un sol metode?? constructor?
    void afegeixCaptura(const Posicio& p);     
    const vector<Posicio>& getRecorregut() const;
    const vector<Posicio>& getCaptures() const;
//la funcio mirarCapturesDretaEsquerra, s'haura de modificar una mica, els parametres no estan del tot correcta, pero l'estrucutra del codi està ben plantejat
mirarCapturesDretaEsquerra(const Casella& origen, vector<Casella>& parametrePosicions, vector<pair<Casella, bool>>& parametreCaptures, const Casella m_tauler[][8])     Posicio getDestiFinal() const;
    int numCaptures() const;
};

#endif
