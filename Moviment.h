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

    Posicio getDestiFinal() const;
    int numCaptures() const;
};

#endif
