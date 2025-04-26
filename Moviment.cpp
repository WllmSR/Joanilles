#include "Moviment.h"
Moviment::Moviment(){
  
}
void Moviment::afegeixPas(const Posicio& p){
  
}              // Afegir pas del moviment
void Moviment::afegeixCaptura(const Posicio& p){
  
}          // Afegir una peça capturada
const vector<Posicio>& Moviment::getRecorregut() const{
  
}
const vector<Posicio>& Moviment::getCaptures() const{
  
}

void Moviments::mirarCapturesDretaEsquerra(const Casella& origen, vector<Casella>& parametrePosicions, vector<pair<Casella, bool>>& parametreCaptures, const Casella m_tauler[][8]) {
    int filaNova = -1;
    int filaNova2 = -1;
    int colDret1 = -1;
    int colDret2 = -1;
    int colEsq1 = -1;
    int colEsq2 = -1;
    
    bool capturatDret = false;
    bool capturatEsquerra = false;

    // Mirem dreta
    if (esValid(origen.m_fila + variable, origen.m_columna + 1)) {
        if (!m_tauler[origen.m_fila + variable][origen.m_columna + 1].esAmic()) {
            colDret1 = origen.m_columna + 1;
            filaNova = origen.m_fila + variable;
        }
    }

    // Mirem esquerra
    if (esValid(origen.m_fila + variable, origen.m_columna - 1)) {
        if (!m_tauler[origen.m_fila + variable][origen.m_columna - 1].esAmic()) {
            colEsq1 = origen.m_columna - 1;
            filaNova = origen.m_fila + variable;
        }
    }

    if (filaNova != -1) {
        // Dreta
        if (colDret1 != -1) {
            if (m_tauler[filaNova][colDret1].esBuit()) {
                colDret2 = colDret1;
                filaNova2 = filaNova;
            } else if (m_tauler[filaNova][colDret1].esEnemic()) {
                if (esValid(filaNova + variable, colDret1 + 1) && m_tauler[filaNova + variable][colDret1 + 1].esBuit()) {
                    filaNova2 = filaNova + variable;
                    colDret2 = colDret1 + 1;
                    capturatDret = true;
                }
            }
        }

        // Esquerra
        if (colEsq1 != -1) {
            if (m_tauler[filaNova][colEsq1].esBuit()) {
                colEsq2 = colEsq1;
                filaNova2 = filaNova;
            } else if (m_tauler[filaNova][colEsq1].esEnemic()) {
                if (esValid(filaNova + variable, colEsq1 - 1) && m_tauler[filaNova + variable][colEsq1 - 1].esBuit()) {
                    filaNova2 = filaNova + variable;
                    colEsq2 = colEsq1 - 1;
                    capturatEsquerra = true;
                }
            }
        }
    }

   if (filaNova2 != -1 && colDret2 != -1) {
        parametrePosicions.push_back(Casella(filaNova2, colDret2));
        parametreCaptures.push_back({Casella(filaNova, colDret1), capturatDret});
    }
    if (filaNova2 != -1 && colEsq2 != -1) {
        parametrePosicions.push_back(Casella(filaNova2, colEsq2));
        parametreCaptures.push_back({Casella(filaNova, colEsq1), capturatEsquerra});
    }
}
Posicio Moviment::getDestiFinal() const{
  
}
int Moviment::numCaptures() const{
}
bool Moviment::esCaptura() const{
}

#endif
