#include "Moviment.h"
void Moviment::mirarCapturesDretaEsquerra(const Posicio& origen, vector<pair<Posicio, int>>& parametrePosicions, vector<pair<Posicio, bool>>& parametreCaptures, const Fitxa m_tauler[][9]) {
    int filaNova = -1;
    int filaNova2 = -1;
    int colDret1 = -1;
    int colDret2 = -1;
    int colEsq1 = -1;
    int colEsq2 = -1;
    bool capturatDret = false;
    bool capturatEsquerra = false;
    int valoRetornDreta=0;
    int valoRetornEsquerra=0;
    ColorFitxa colourTemporal =  m_tauler[origen.getFila()][origen.getColumna()].getColor();
    int staticTemporal = static_cast<int>(colourTemporal);
    if (esValid(origen.getFila() + staticTemporal, origen.getColumna() + 1)) {
        if (!m_tauler[origen.getFila() + staticTemporal][origen.getColumna() + 1].esAmic(m_tauler[origen.getFila()][origen.getColumna()])) {
            colDret1 = origen.getColumna() + 1;
            filaNova = origen.getFila() + staticTemporal;
     //vol dir que es enemic o espai buit
        }else
            valoRetornDreta=1;
    }
    if (esValid(origen.getFila() +staticTemporal, origen.getColumna() - 1)) {
        if (!m_tauler[origen.getFila() + staticTemporal][origen.getColumna() - 1].esAmic(m_tauler[origen.getFila()][origen.getColumna()])) {
            colEsq1 = origen.getColumna() - 1;
            filaNova = origen.getFila() + staticTemporal;
        }else
            valoRetornEsquerra=1;
    }

    if (filaNova != -1) {
        if (colDret1 != -1) {
            if (m_tauler[filaNova][colDret1].esBuit()) {
                colDret2 = colDret1;
                filaNova2 = filaNova;
                    valoRetornDreta=0;
            } else if (m_tauler[filaNova][colDret1].esEnemic(m_tauler[origen.getFila()][origen.getColumna()])) {
                if (esValid(filaNova + staticTemporal, colDret1 + 1) && m_tauler[filaNova + staticTemporal][colDret1 + 1].esBuit()) {
                    filaNova2 = filaNova +staticTemporal; 
                    colDret2 = colDret1 + 1;
                    capturatDret = true;
                    valoRetornDreta=2;
                }else{
                    valoRetornDreta=1;
                }
            }
        }
        if (colEsq1 != -1) {
            if (m_tauler[filaNova][colEsq1].esBuit()) {
                colEsq2 = colEsq1;
                filaNova2 = filaNova;
                valoRetornEsquerra=0;
            } else if (m_tauler[filaNova][colEsq1].esEnemic(m_tauler[origen.getFila()][origen.getColumna()])) {
                if (esValid(filaNova + staticTemporal, colEsq1 - 1) && m_tauler[filaNova + staticTemporal][colEsq1 - 1].esBuit()) {
                    filaNova2 = filaNova + staticTemporal;
                    colEsq2 = colEsq1 - 1;
                    capturatEsquerra = true;
                    valoRetornEsquerra=2;

                }else{
                    valoRetornDreta=1;
                }
            }
        }
    }
        Posicio fitxaDreta(filaNova2, colDret2);        Posicio fitxaDretaCap(filaNova, colDret1);
        Posicio fitxaEsquerra(filaNova2, colEsq2);      Posicio fitxaEsquerraCap(filaNova, colEsq1);

        parametrePosicions.push_back(make_pair(fitxaDreta, valoRetornDreta));
        parametreCaptures.push_back(std::make_pair(fitxaDretaCap, capturatDret));
        parametrePosicions.push_back(make_pair(fitxaEsquerra, valoRetornEsquerra));
        parametreCaptures.push_back(std::make_pair(fitxaEsquerraCap, capturatEsquerra));
}
void Moviment::DFSNormal(const Fitxa m_tauler[][9], vector<vector<Posicio>>& recorregut,vector<vector<Posicio>>&pecesCaptured,  const Posicio& original) {
    vector<vector<pair<Posicio, bool>>> m_taulerVisitats;
    m_taulerVisitats.resize(9, vector<pair<Posicio, bool>>(9));
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            m_taulerVisitats[i][j].first = m_tauler[i][j].getPosicio(); 
            m_taulerVisitats[i][j].second = false;
        }
    }
 std::stack <tuple<Posicio, vector<Posicio>, vector<Posicio>>> m_stackPerVisitar;
    while (!m_stackPerVisitar.empty()) {
        std::tuple<Posicio, std::vector<Posicio>, std::vector<Posicio>> element = m_stackPerVisitar.top();
        Posicio temporal=std::get<0>(element);
        std::vector<Posicio> m_vector=std::get<1>(element);
        std::vector<Posicio> m_cap = std::get<2>(element);
        m_stackPerVisitar.pop();
        if (!m_taulerVisitats[temporal.getFila()][temporal.getColumna()].second) {
            m_taulerVisitats[temporal.getFila()][temporal.getColumna()].second = true;
            vector<pair<Posicio, int>> posicions;
            vector<pair<Posicio, bool>> capturades;    
            mirarCapturesDretaEsquerra(temporal, posicions, capturades, m_tauler);
            int valor1Dret=posicions[0].second;;
            int valor2Esquerra=posicions[1].second;
// DRETA 
if (valor1Dret == 2) {
    // Hi ha captura i podem continuar
    if (!m_taulerVisitats[posicions[0].first.getFila()][posicions[0].first.getColumna()].second) {
        vector<Posicio> nouCami = m_vector;
        nouCami.push_back(posicions[0].first);
        vector<Posicio> novesCaptures = m_cap;
        if (capturades[0].second) {
            novesCaptures.push_back(capturades[0].first);
        }
        m_stackPerVisitar.push(std::make_tuple(posicions[0].first, nouCami, novesCaptures));
    }
} else if (valor1Dret == 0) {
    vector<Posicio> nouCami = m_vector;
    nouCami.push_back(posicions[0].first);
    recorregut.push_back(nouCami);
    pecesCaptured.push_back(m_cap);
}else if(valor1Dret==1){
recorregut.push_back(m_vector);   
pecesCaptured.push_back(m_cap);
}
//  ESQUERRA 
if (valor2Esquerra == 2) {
    if (!m_taulerVisitats[posicions[1].first.getFila()][posicions[1].first.getColumna()].second) {
        vector<Posicio> nouCami = m_vector;
        nouCami.push_back(posicions[1].first);
        vector<Posicio> novesCaptures = m_cap;
        if (capturades[1].second) {
            novesCaptures.push_back(capturades[1].first);
        }
        m_stackPerVisitar.push(std::make_tuple(posicions[1].first, nouCami, novesCaptures));
    }
} else if (valor2Esquerra == 0) {
    vector<Posicio> nouCami = m_vector;
    nouCami.push_back(posicions[1].first);
    recorregut.push_back(nouCami);
    pecesCaptured.push_back(m_cap);
    }else{
    recorregut.push_back(m_vector);
    pecesCaptured.push_back(m_cap);
        }
    }    
}
}
void Moviment::mirarCapturesDames(int AmuntBaix,int continuarDreta, int continuarEsquerra,const Posicio& origen,vector<Posicio>& parametrePosicionsDreta,vector<Posicio>& parametrePosicionsEsquerra, pair<Posicio, bool>& parametreCapturesDreta,pair<Posicio, bool>& parametreCapturadesEsquerra, const Fitxa m_tauler[][9])
{    
    continuarDreta=-1;
    continuarEsquerra=-1;
    ColorFitxa temporalColorr=m_tauler[origen.getFila()][origen.getColumna()].getColor();
    int staticTemporal=static_cast<int>(temporalColorr)*AmuntBaix;

    int i = origen.getFila()+staticTemporal; 
    int j = origen.getColumna()+1;
    int valorDret1=0;
    int valorEsquerra2=0;
    bool trobat=false;
    while(!trobat&&esValid(i, j)){
        if(m_tauler[i][j].esBuit()){
            parametrePosicionsDreta.push_back(m_tauler[i][j].getPosicio());
            i=i+staticTemporal;
            j=j+1;
        }else if(m_tauler[i][j].esEnemic(m_tauler[origen.getFila()][origen.getColumna()])||m_tauler[i][j].esAmic(m_tauler[origen.getFila()][origen.getColumna()])){
            trobat=true;
        }    
        
    }
    if(trobat){
       if(m_tauler[i][j].esEnemic(m_tauler[origen.getFila()][origen.getColumna()])){
            if(m_tauler[i+staticTemporal][j+1].esBuit()){
                parametrePosicionsDreta.push_back(m_tauler[i+staticTemporal][j+1].getPosicio());
            parametreCapturesDreta=make_pair(m_tauler[i][j].getPosicio(), true);
                continuarDreta=0;
        }else{
                i=i-staticTemporal;
                j=j-1;
                if(m_tauler[i][j].esBuit()){
                    parametrePosicionsDreta.push_back(m_tauler[i][j].getPosicio());
                    continuarDreta=1;
                }
                }
            }else{
                i=i-staticTemporal;
                j=j-1;    
                if(m_tauler[i][j].esBuit()){
                    parametrePosicionsDreta.push_back(m_tauler[i][j].getPosicio());
                    continuarDreta = 2;
                }
            }

    }else{
        i=i-staticTemporal;
        j=j-1;
        if(m_tauler[i][j].esBuit()){
            parametrePosicionsDreta.push_back(m_tauler[i][j].getPosicio());
        }
        continuarDreta=3;
    }
    i =origen.getFila()+staticTemporal;
    j =origen.getColumna()-1;
    bool trobat=false;
    while(!trobat&& esValid(i,j)){
     if(m_tauler[i][j].esBuit()){
        parametrePosicionsEsquerra.push_back(m_tauler[i][j].getPosicio());
        i=i+staticTemporal;
        j=j-1;
     }
     else if(m_tauler[i][j].esEnemic(m_tauler[origen.getFila()][origen.getColumna()])||m_tauler[i][j].esAmic(m_tauler[origen.getFila()][origen.getColumna()])){
        trobat=true;
     }
    }
    if(trobat){
        if(m_tauler[i][j].esEnemic(m_tauler[origen.getFila()][origen.getColumna()])){
            if(m_tauler[i+staticTemporal][j-1].esBuit()){
                parametrePosicionsEsquerra.push_back(m_tauler[i+staticTemporal][j-1].getPosicio());
           parametreCapturadesEsquerra = make_pair(m_tauler[i][j].getPosicio(), true);
                continuarEsquerra=0;
        }else{
                i=i-staticTemporal;
                j=j+1;
                if(m_tauler[i][j].esBuit()){
                    parametrePosicionsEsquerra.push_back(m_tauler[i][j].getPosicio());
                    continuarEsquerra=1;
                }
                }
            }else{
                i=i-staticTemporal;
                j=j+1;    
                if(m_tauler[i][j].esBuit()){
                    parametrePosicionsEsquerra.push_back(m_tauler[i][j].getPosicio());
                    continuarEsquerra=2;
                }
            }

    }else{
        i=i-staticTemporal;
        j=j+1;
        if(m_tauler[i][j].esBuit()){
            parametrePosicionsEsquerra.push_back(m_tauler[i][j].getPosicio());
            continuarEsquerra =3;
        }
    }   
} 

void Moviment::DFSDames(const Fitxa m_tauler[][9], vector<vector<Posicio>>& recorregut,vector<vector<Posicio>>&pecesCaptured , const Posicio& original) {
    vector<vector<pair<Posicio, bool>>> m_taulerVisitats;
    m_taulerVisitats.resize(9, vector<pair<Posicio, bool>>(9));
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            m_taulerVisitats[i][j].first = m_tauler[i][j].getPosicio(); 
            m_taulerVisitats[i][j].second = false;
        }
    }
    std::stack <tuple<Posicio, vector<Posicio>, vector<Posicio>>> m_stackPerVisitar;
    m_stackPerVisitar.push(std::make_tuple(original, std::vector<Posicio>{original}, std::vector<Posicio>{}));
    vector<pair<Posicio, bool>> pecesCaptured;
    while (!m_stackPerVisitar.empty()) {
        auto element = m_stackPerVisitar.top();
        auto temporal=std::get<0>(element);
        auto m_vector=std::get<1>(element);
        auto m_cap = std::get<2>(element);
        m_stackPerVisitar.pop();
        if (!m_taulerVisitats[temporal.getFila()][temporal.getColumna()].second) {
            m_taulerVisitats[temporal.getFila()][temporal.getColumna()].second = true;
            vector<Posicio> posicionsDreta;
            vector<Posicio> posicionsEsquerra;
            int continuarDreta=-1;
            int continuarEsquerra=-1;
            pair<Posicio, bool> capturadesDreta;
            pair<Posicio, bool> capturadesEsquerra;
            int AmuntBaix =1;
            mirarCapturesDames(AmuntBaix,continuarDreta, continuarEsquerra, temporal,posicionsDreta,posicionsEsquerra, capturadesDreta,capturadesEsquerra, m_tauler);
                if(continuarDreta==0){
                    
                        vector<Posicio> novesCaptures = m_cap;
                    if(capturadesDreta.second){    
                        novesCaptures.push_back(capturadesDreta.first);
                            }
                    for(int i =0;i<posicionsDreta.size();i++){
                        if(!m_taulerVisitats[posicionsDreta[i].getFila()][posicionsDreta[i].getColumna()].second){
                            vector<Posicio> nouCami=m_vector;
                            nouCami.push_back(posicionsDreta[i]);
                            
                        
                            m_stackPerVisitar.push({posicionsDreta[i], nouCami, novesCaptures});
                        }
                    }
                }else{
                vector<Posicio> nouCami = m_vector;
                nouCami.insert(nouCami.end(), posicionsDreta.begin(), posicionsDreta.end());
                recorregut.push_back(nouCami);
                pecesCaptured.push_back(m_cap);
                }
                if(continuarEsquerra==0){
                     vector<Posicio> novesCaptures = m_cap;
                            if(capturadesDreta.second){
                                novesCaptures.push_back(capturadesEsquerra.first);
                            }
                    for(int i =0;i<posicionsEsquerra.size();i++){
                        if(!m_taulerVisitats[posicionsEsquerra[i].getFila()][posicionsEsquerra[i].getColumna()].second){
                            vector<Posicio>nouCami=m_vector;
                            nouCami.push_back(posicionsEsquerra[i]);
                           
                        m_stackPerVisitar.push({posicionsDreta[i], nouCami,novesCaptures});
                        }
                    }
                }else{
                    vector<Posicio> nouCami=m_vector;
                    nouCami.insert(nouCami.end(), posicionsEsquerra.begin(), posicionsEsquerra.end());
                    recorregut.push_back(nouCami);
                    pecesCaptured.push_back(m_cap);
                }
                continuarDreta=-1;
                continuarEsquerra=-1;
                posicionsDreta.clear();
                posicionsEsquerra.clear();
                    AmuntBaix=-1;
        mirarCapturesDames(AmuntBaix, continuarDreta,continuarEsquerra, temporal,posicionsDreta,posicionsEsquerra, capturadesDreta,capturadesEsquerra, m_tauler);
         if(continuarDreta==0){
            vector<Posicio> novesCaptures = m_cap;
                            if(capturadesDreta.second){
                                novesCaptures.push_back(capturadesDreta.first);
                            }        
            for(int i =0;i<posicionsDreta.size();i++){
                        if(!m_taulerVisitats[posicionsDreta[i].getFila()][posicionsDreta[i].getColumna()].second){
                            vector<Posicio> nouCami=m_vector;
                            nouCami.push_back(posicionsDreta[i]);
                            
                            m_stackPerVisitar.push({posicionsDreta[i], nouCami, novesCaptures});
                        }
                    }
                }else{
                vector<Posicio> nouCami = m_vector;
                nouCami.insert(nouCami.end(), posicionsDreta.begin(), posicionsDreta.end());
                recorregut.push_back(nouCami);
                pecesCaptured.push_back(m_cap);
                }
                if(continuarEsquerra==0){
                            vector<Posicio> novesCaptures = m_cap;
                            if(capturadesDreta.second){
                                novesCaptures.push_back(capturadesEsquerra.first);
                            }
                 
                    for(int i =0;i<posicionsEsquerra.size();i++){
                        if(!m_taulerVisitats[posicionsEsquerra[i].getFila()][posicionsEsquerra[i].getColumna()].second){
                            vector<Posicio>nouCami=m_vector;
                            nouCami.push_back(posicionsEsquerra[i]);
                        m_stackPerVisitar.push({posicionsDreta[i], nouCami,novesCaptures});
                        }
                    }
                }else{
                    vector<Posicio> nouCami=m_vector;
                    nouCami.insert(nouCami.end(), posicionsEsquerra.begin(), posicionsEsquerra.end());
                    recorregut.push_back(nouCami);
                    pecesCaptured.push_back(m_cap);
                                }
       }
    }
}
void Moviment::actualitzaMoviments(const Fitxa m_tauler[][9], const Posicio& original, vector<Posicio>& m_posicionsPossibles, vector<Posicio>& m_posicionsCapturades){
    TipusFitxa titits = m_tauler[original.getFila()][original.getColumna()].getTipus(); 
    if(titits==TIPUS_DAMA){
        DFSDames(m_tauler, recorregut, pecesCapturades, original);
    }else if(titits==TIPUS_NORMAL){
        DFSNormal(m_tauler, recorregut, pecesCapturades, original);
    }else{
        return;
    }
    //vector<Posicio>& m_posicionsPossibles, vector<Posicio>& m_posicionsCapturades
    for(const auto fitxa: recorregut){
        for(const auto element: fitxa){
            if(find(destins.begin(), destins.end(), element)==destins.end()){
                destins.push_back(element);
            }
        }
    }
    for(const auto fitxa: pecesCapturades){
        for(const auto element: fitxa){
            if(find(captures.begin(),captures.end(), element)==captures.end()){
                captures.push_back(element);
            }
        }
    }   
    //per copiar tots els camins:
    
}
