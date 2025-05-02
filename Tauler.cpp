#include "Tauler.h"
void Tauler::inicialitza(const string& nomFitxer) {
    ifstream fitxer(nomFitxer);
    if (!fitxer.is_open()) {
        cerr << "No s'ha pogut obrir el fitxer: " << nomFitxer << endl;
        return;
    }
    string linia;
    //primer el que podem fer es inicialitzar el tauler com tot buit
    for(int i =0;i<N_FILES;i++){
        for(int j =0;j<N_COLUMNES;j++){
            Fitxa temporal();
            m_tauler[i][j]=temporal;
        }
    }
    while (getline(fitxer, linia)) {
        if (linia.length() < 3) continue;
        
        char tipusIcolor = linia[0];
        // Creem un array<char, 2> amb la posició
        //ens hem d'encrecordar que el segon element del string linia es la columna de la fitxa i el tercer element es fila

        array<char, 2> pos = { linia[1], linia[2] };
        // Ara utilitzem aquest array per crear la posició
        Posicio p(pos); 

        int fila = p.getFila();
        int col = p.getColumna();

        m_tauler[fila][col] = Fitxa(tipusIcolor, pos, m_tauler);
    }

    fitxer.close();
    actualitzaMovimentsValids();
}
void Tauler::getPosicionsPossibles(const Posicio& origen, int& nPosicions, Posicio posicionsPossibles[]) {
    const Fitxa& fitxa = m_tauler[origen.getFila()][origen.getColumna()];
    posicionsPossibles=fitxa.getMoviments().getTotalDestins();
    nPosicions=posicionsPossibles.size();
}
void Tauler::actualitzaMovimentsValids() {
    for (int i = 1; i <= 8; i++) {
        for (int j = 1; j <= 8; j++) {
            m_tauler[i][j].netejaMoviments();
            if (!m_tauler[i][j].esBuit()) {
                Posicio pos(i, j);
                m_tauler[i][j].calcularPosicionsPossibles(m_tauler, pos);
            }
        }
    }
}
bool Tauler::mouFitxa(const Posicio& origen, const Posicio& desti) {

    Fitxa& fitxa = m_tauler[origen.getFila()][origen.getColumna()];
    if (fitxa.esBuit()) return false;

    const vector<vector<Posicio>>& recorreguts = fitxa.getMoviments().getTotalRecorregut();
    const vector<vector<Posicio>>& pecesCapturades = fitxa.getMoviments().getTotalCaptures();

    for (size_t i = 0; i < recorreguts.size(); i++) {
        if (!recorreguts[i].empty() && recorreguts[i].back() == desti) {
            // El moviment és vàlid
            for (const auto& p : pecesCapturades[i]) {
                m_tauler[p.getFila()][p.getColumna()] = Fitxa(); // Elimina la fitxa capturada
            }

            // Creem l'array<char, 2> per al destí
            array<char, 2> destiPos = { (char)(desti.getColumna() + 'a' - 1), (char)(desti.getFila() + '0') };
            m_tauler[desti.getFila()][desti.getColumna()] = fitxa;
            m_tauler[origen.getFila()][origen.getColumna()] = Fitxa();

            if ((fitxa.getColor() == COLOR_BLANC && desti.getFila() == 1) ||
                (fitxa.getColor() == COLOR_NEGRE && desti.getFila() == 8)) {
                m_tauler[desti.getFila()][desti.getColumna()].ferDama();
            }

            actualitzaMovimentsValids();
            return true;
        }
    }

    return false;
}




#endif
