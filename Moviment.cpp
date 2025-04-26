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
void Moviments::DFS(const Fitxa m_tauler[][8], vector<vector<Fitxa>>& recorregut,vector<vector<Fitxa>>&pecesCaptured  const Fitxa& original) {
    vector<vector<pair<Casella, bool>>> m_taulerVisitats;
    m_taulerVisitats.resize(8, vector<pair<Fitxa, bool>>(8));
    for (int i = 0; i < MAX_FILA; i++) {
        for (int j = 0; j < MAX_COLUMNA; j++) {
            m_taulerVisitats[i][j].first = m_tauler[i][j].m_posicio; 
            m_taulerVisitats[i][j].second = false;
        }
    }

    std::stack<pair<Fitxa, vector<Fitxa>>> m_stackPerVisitar;
    m_stackPerVisitar.push({original, {original}});
    vector<Fitxa> m_vectorCami;
    vector<Fitxa>m_vector
    while (!m_stackPerVisitar.empty()) {
        auto element = m_stackPerVisitar.top();
        temporal=element.first;
        m_vector=element.second;
        m_stackPerVisitar.pop();
        if (!m_taulerVisitats[temporal.m_posicio.m_fila][temporal.m_posicio.m_columna].second) {
            m_taulerVisitats[temporal.m_posicio.m_fila][temporal.m_posicio.m_columna].second = true;
            vector<Fitxa> posicions;
            vector<pair<Fitxa, bool>> capturades;
            mirarCapturesDretaEsquerra(temporal, posicions, capturades, m_tauler);
            if (!posicions.empty()) {
                for (int i = 0; i < posicions.size(); i++) {
                    if (!m_taulerVisitats[posicions[i].m_posicio.m_fila][posicions[i].m_posicio.m_columna].second) {
                        vector<Fitxa> nouCami= m_vector;
                        nouCami.push_back(posicions[i]);
                        m_stackPerVisitar.push({posicions[i], nouCami});
                    }
                }
            } else {
                recorregut.push_back(m_vector)
                pecesCaptured.push_back()
            }
        }
    }
    
}





Posicio Moviment::getDestiFinal() const{
  
}
int Moviment::numCaptures() const{
}
bool Moviment::esCaptura() const{
}

#endif
