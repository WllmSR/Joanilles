#include "Moviment.h"
Moviment::Moviment(){
  
}
Moviment::~Moviment(){


}
void Moviment::afegeixPas(const Posicio& p){
  
}              // Afegir pas del moviment
void Moviment::afegeixCaptura(const Posicio& p){
  
}          // Afegir una peça capturada
const vector<Posicio>& Moviment::getRecorregut(int posicioIndex) const{
return recorregut[posicioIndex];
}
const vector<Posicio>& Moviment::getCaptures(int posicioIndex) const{
return pecesCapturades[posicioIndex]; 
}

void Moviment::mirarCapturesDretaEsquerra(const Fitxa& origen, vector<Fitxa>& parametrePosicions, vector<pair<Fitxa, bool>>& parametreCaptures, const Fitxa m_tauler[][8]) {
    int filaNova = -1;
    int filaNova2 = -1;
    int colDret1 = -1;
    int colDret2 = -1;
    int colEsq1 = -1;
    int colEsq2 = -1;
    
    bool capturatDret = false;
    bool capturatEsquerra = false;

    // Mirem dreta
    if (esValid(origen.m_posicio.m_fila + origen.getColor(), origen.m_posicio.m_columna + 1)) {
        if (!m_tauler[origen.m_posicio.m_fila + origen.getColor()][origen.m_posicio.m_columna + 1].esAmic()) {
            colDret1 = origen.m_columna + 1;
            filaNova = origen.m_fila + origen.getColor();
        }
    }

    // Mirem esquerra
    if (esValid(origen.m_posicio.m_fila +origen.getColor(), origen.m_posicio.m_columna - 1)) {
        if (!m_tauler[origen.m_posicio.m_fila + origen.getColor()][origen.m_posicio.m_columna - 1].esAmic()) {
            colEsq1 = origen.m_posicio.m_columna - 1;
            filaNova = origen.m_posicio.m_fila + origen.getColor();
        }
    }

    if (filaNova != -1) {
        // Dreta
        if (colDret1 != -1) {
            if (m_tauler[filaNova][colDret1].esBuit()) {
                colDret2 = colDret1;
                filaNova2 = filaNova;
            } else if (m_tauler[filaNova][colDret1].esEnemic()) {
                if (esValid(filaNova + origen.getColor(), colDret1 + 1) && m_tauler[filaNova + origen.getColor()][colDret1 + 1].esBuit()) {
                    filaNova2 = filaNova +origen.getColor(); 
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
                if (esValid(filaNova + origen.getColor(), colEsq1 - 1) && m_tauler[filaNova + origen.getColor()][colEsq1 - 1].esBuit()) {
                    filaNova2 = filaNova + origen.getColor();;
                    colEsq2 = colEsq1 - 1;
                    capturatEsquerra = true;
                }
            }
        }
    }




        Fitxa fitxaDreta(filaNova2, colDret2);
        Fitxa fitxaDretaCap(filaNova, colDret1);
        Fitxa fitxaEsquerra(filaNova2, colEsq2);
        Fitxa fitxaEsquerraCap(filaNova, colEsq1);
        parametrePosicions.push_back(fitxaDreta);
        parametreCaptures.push_back(std::make_pair(fitxaDretaCap, capturatDret));
    
        parametrePosicions.push_back(fitxaEsquerra);
        parametreCaptures.push_back(std::make_pair(fitxaEsquerraCap, capturatEsquerra));

}
void Moviment::DFSNormal(const Fitxa m_tauler[][8], vector<vector<Fitxa>>& recorregut,vector<vector<Fitxa>>&pecesCaptured,  const Fitxa& original) {

    vector<vector<pair<Fitxa, bool>>> m_taulerVisitats;
    m_taulerVisitats.resize(8, vector<pair<Fitxa, bool>>(8));
    for (int i = 0; i < MAX_FILA; i++) {
        for (int j = 0; j < MAX_COLUMNA; j++) {
            m_taulerVisitats[i][j].first = m_tauler[i][j].m_posicio; 
            m_taulerVisitats[i][j].second = false;
        }
    }

    std::stack <tuple<Fitxa, vector<Fitxa>, vector<Fitxa>>> m_stackPerVisitar;
        //auto element = m_stackPerVisitar.top();
    //vector<pair<Fitxa, bool>> pecesCaptured;
    while (!m_stackPerVisitar.empty()) {
        std::tuple<Fitxa, std::vector<Fitxa>, std::vector<Fitxa>> element = m_stackPerVisitar.top();
        auto temporal=element.first;
        auto m_vector=element.second;
        auto m_cap = std::get<2>(element);
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
                        vector<Fitxa> novesCaptures  = m_cap;
                        if(capturades[i].second){
                            novesCaptures.push_back(capturades[i].first);
                        }
                        m_stackPerVisitar.push(std::make_tuple(posicions[i], nouCami, novesCaptures));
                    
                    }
                }
            } else {
                recorregut.push_back(m_vector);
                pecesCaptured.push_back(m_cap);
            }
        }
    }
    
}

void Moviment::mirarCapturesDames(const Fitxa& origen,vector<Fitxa>& parametrePosicionsDreta,vector<Fitxa>& parametrePosicionsEsquerra, vector<pair<Fitxa, bool>>& parametreCapturesDreta,vector<pair<Fitxa, bool>>& parametreCapturadesEsquerra, const Fitxa m_taules[][9]){
    
    int i = origen.m_posicio.m_fila+origen.getColor();
    int j = origen.m_poisicio.m_columna+1;

    bool trobat=false;
    while(!trobat&&esValid(i, j)){
        if(m_tauler[i][j].esBuit()){
            parametrePosicionsDreta.push_back(m_tauler[i][j]); 
            i=i+orn.getColor();
            j=j+1;
        }else if(m_tauler[i][j].esEnemic()){
            trobat=true;
        }    
        
    }
    if(trobat){
        if(m_tauler[i+origen.getColor();][j+1].esBuit()){
            parametrePosicionsDreta.push_back(m_tauler[i+origen.getColor()][j+1]);
            parametreCapturesDreta.push_back(std::make_pair(m_tauler[i][j], true));
        }
    }else{
        //no hi ha captura possible, pero encara podem
        //ara mateix els index i i j estan en una posicio no valida, per tant hem de restar color fitxa i restar o sumar 1 a j
        i=i-origen.getColor();
        j=j-1;
        if(m_tauler[i][j].esBuit()){
            parametrePosicionsDreta.push_back(m_tauler[i][j]);
        }
    }
    i =origen.m_posicio.m_fila+origen.getColor();
    j =origen.m_posicio.m_columna-1;
    bool trobat=false;
    while(!trobat&& esValid(i,j)){
     if(m_tauler[i][j].esBuit()){
        parametrePosicionsEsquerra.push_back(m_tauler[i][j]);
        i=i+origen.getColor();
        j=j-1;
     }
     else if(m_tauler[i][j].esEnemic()){
        trobat=true;
     }
    }
   if(trobat){
    if(m_tauler[i+origen.getColor()]e[j-1].esBuit()){
        parametrePosicionsEsquerra.push_back(m_tauler[i+origen.getColor()][j-1]);
        .push_back(std::make_pair(m_tauler[i][j], true));
    }
   }else{
        //no hi ha captura possible, pero encara podem
        //ara mateix els index i i j estan en una posicio no valida, per tant hem de restar color fitxa i restar o sumar 1 a j
        i=i-origen.getColor();
        j=j+1;
        if(m_tauler[i][j].esBuit()){
            parametrePosicionsEsquerra.push_back(m_tauler[i][j]);
        }
    }
} 



void Moviment::DFSDames(const Fitxa m_tauler[][8], vector<vector<Fitxa>>& recorregut,vector<vector<Fitxa>>&pecesCaptured , const Fitxa& original) {
    vector<vector<pair<Fitxa, bool>>> m_taulerVisitats;
    m_taulerVisitats.resize(8, vector<pair<Fitxa, bool>>(8));
    for (int i = 0; i < MAX_FILA; i++) {
        for (int j = 0; j < MAX_COLUMNA; j++) {
            m_taulerVisitats[i][j].first = m_tauler[i][j].m_posicio; 
            m_taulerVisitats[i][j].second = false;
        }
    }

    std::stack <tuple<Fitxa, vector<Fitxa>, vector<Fitxa>>> m_stackPerVisitar;
    m_stackPerVisitar.push(std::make_tuple(original, std::vector<Fitxa>{original}, std::vector<Fitxa>{}));
    //es possible que hem d'actualitzar el stackPerVisitar, per tenir en compte les captures
    //ara nomes ens fa falta inicialitzar el vector de captures, ja que el recorregut es el mateix que el de les peces capturades
    vector<pair<Fitxa, bool>> pecesCaptured;
    while (!m_stackPerVisitar.empty()) {
        auto element = m_stackPerVisitar.top();
        auto temporal=element.first;
        auto m_vector=element.second;
        auto m_cap = element.third;
        m_stackPerVisitar.pop();
        if (!m_taulerVisitats[temporal.m_posicio.m_fila][temporal.m_posicio.m_columna].second) {
            m_taulerVisitats[temporal.m_posicio.m_fila][temporal.m_posicio.m_columna].second = true;
            vector<Fitxa> posicionsDreta;
            vector<Fitxa> posicionsEsquerra;
            vector<pair<Fitxa, bool>> capturadesDreta;
            vector<pair<Fitxa, bool>> capturadesEsquerra;
            mirarCapturesDames( temporal,posicionsDreta,posicionsEsquerra, capturesDreta,capturadesEsquerra, m_taules){

            if (posicionsDreta.size()>0||posicionsEsquerra.size()>0) {
                for (int i = 0; i < posicionsDreta.size(); i++) {
                    //primer mirem dreta 
                    //despres mirem esquerra
                    if (!m_taulerVisitats[posicionsDreta[i].m_posicio.m_fila][posicionsDreta[i].m_posicio.m_columna].second) {
                        vector<Fitxa> nouCami= m_vector;
                        nouCami.push_back(posicionsDreta[i]);
                        vector<Fitxa> novesCaptures  = m_cap;
                        if(capturadesDreta[i].second){
                            novesCaptures.push_back(capturadesDreta[i].first);
                        }
                        m_stackPerVisitar.push({posicionsDreta[i], nouCami, novesCaptures});
                    }
                }
                for(int i =0;i<posicionsEsquerra.size();i++){
                    if(!m_tauler[posicionsEsquerra[i].m_posicio.m_fila][m_posicionsEsquerra[i].m_posicio.m_columna]){
                        vector<Fitxa> nouCami = m_vector;
                        nouCami.push_back(posicionsEsquerra[i]);
                        vector<Fitxa>novesCaptures=m_cap;
                        if(capturadesEsquerra[i].second){
                            novesCaptures.push_back(capturadesEsquerra[i].first);
                        }
                        m_stackPerVisitar.push_back({posicionsEsquerra[i], nouCami, novesCaptures});
                    }
                }
            } else {
                recorregut.push_back(m_vector)
                pecesCaptured.push_back(m_cap)
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
void Moviment::actualitzaMoviments(const Fitxa m_tauler[][8], const Fitxa& original, vector<Fitxa>& m_posicionsPossibles, vector<Fitxa>& m_posicionsCapturades){
    DFS(m_tauler,m_recorregut, m_pecesCapturades, original);
    if(original.getTipus()==Tipus_DAMA){
        DFSDames(m_tauler, m_recorregut, m_pecesCapturades, original);
    }else if(orifinal.getTipus()==Tipus_NORMAL){
        DFSNormal(m_tauler, m_recorregut, m_pecesCapturades, original);
    }else{
        return;
    }
    for(const auto fitxa: m_recorregut){
        for(const auto element: fitxa){
            if(find(m_posicionsPossibles.begin(), m_posicionsPossibles.end(), element)==m_posicionsPossibles.end()){
                m_posicionsPossibles.push_back(element);
            }
        }
    }
    for(const auto fitxa: m_pecesCapturades){
        for(const auto element: fitxa){
            if(find(m_posicionsCapturades.begin(), m_posicionsCapturades.end(), element)==m_posicionsCapturades.end()){
                m_posicionsCapturades.push_back(element);
            }
        }
    }   
}
