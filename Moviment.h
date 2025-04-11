#ifndef MOVIMENT_H
#define MOVIMENT_H

#include <vector>
#include "posicio.h"
using namespace std;

class Moviment {
private:
    vector<Posicio> recorregut;        // Cam� des de la posici� d'origen (exclosa) fins a la final
    vector<Posicio> pecesCapturades;   // Posicions de peces eliminades

public:
    Moviment();

    void afegeixPas(const Posicio& p);              // Afegir pas del moviment
    void afegeixCaptura(const Posicio& p);          // Afegir una pe�a capturada
    const vector<Posicio>& getRecorregut() const;
    const vector<Posicio>& getCaptures() const;

    Posicio getDestiFinal() const;
    int numCaptures() const;
    bool esCaptura() const;
};

#endif