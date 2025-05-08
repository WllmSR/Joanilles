#include "Tauler.h"
//prime comprovem que actualitzaTaulerNormal funciona perfectament
void Tauler::actualitzaTaulerNormal(int valor, std::vector<Posicio>camiActual){

    Posicio posActual = camiActual[0]; // sempre comencem pel primer element del camí
    for (int j = 1; j <= valor; j++) {
        Posicio posSeguent = camiActual[j];

        int filaDiferencia = posSeguent.getFila() - posActual.getFila();
        int columnaDiferencia = posSeguent.getColumna() - posActual.getColumna();
        // Si la distància és exactament un moviment de captura (2 caselles diagonalment)
        if (abs(filaDiferencia) == 2 && abs(columnaDiferencia) == 2) {
            int filaCapturada = (posActual.getFila() + posSeguent.getFila()) / 2;
            int columnaCapturada = (posActual.getColumna() + posSeguent.getColumna()) / 2;

            // Eliminar la peça capturada
            m_tauler[filaCapturada][columnaCapturada] = Fitxa();
        }

        posActual = posSeguent;
    }

    // Finalment, moure la fitxa al destí
    m_tauler[posActual.getFila()][posActual.getColumna()] = m_tauler[camiActual[0].getFila()][camiActual[0].getColumna()];
    m_tauler[camiActual[0].getFila()][camiActual[0].getColumna()] = Fitxa();
}
void Tauler::actualitzaTaulerDames(int valor, std::vector<Posicio>camiActual) {
    Posicio posActual = camiActual[0]; 

    // Process each step in the path up to the destination
    for (int j = 1; j <= valor; j++) {
        Posicio posSeguent = camiActual[j];

        // Calculate the direction of movement
        int filaDiferencia = posSeguent.getFila() - posActual.getFila();
        int columnaDiferencia = posSeguent.getColumna() - posActual.getColumna();

        // Check all squares between posActual and posSeguent
        int filaPas = (filaDiferencia > 0) ? 1 : -1;
        int columnaPas = (columnaDiferencia > 0) ? 1 : -1;

        int fila = posActual.getFila() + filaPas;
        int columna = posActual.getColumna() + columnaPas;

        while (fila != posSeguent.getFila() && columna != posSeguent.getColumna()) {
            // If there is a piece here, it should be captured
            if (!m_tauler[fila][columna].getTipus()==TIPUS_EMPTY) {
                m_tauler[fila][columna] = Fitxa(); // Clear the captured piece
            }

            fila += filaPas;
            columna += columnaPas;
        }

        posActual = posSeguent;
    }

    // Move the piece to the final destination
    m_tauler[posActual.getFila()][posActual.getColumna()] = m_tauler[camiActual[0].getFila()][camiActual[0].getColumna()];
    m_tauler[camiActual[0].getFila()][camiActual[0].getColumna()] = Fitxa();
}
void Tauler::inicialitza(const std::string& nomFitxer) {
    std::ifstream fitxer(nomFitxer);
    if (!fitxer.is_open()) {
        return;
    }
   std:: string linia;
    for (int i = 0;i < N_FILES;i++) {
        for (int j = 0;j < N_COLUMNES;j++) {
      
            m_tauler[i][j] = Fitxa();
        }
    }
    while (getline(fitxer, linia)) {
        if (linia.length() < 3) continue;
        char tipusIcolor = linia[0];
        std::array<char, 2> pos = { linia[1], linia[2] };
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
    //per ser guais anem a utilitzar iterators
    Fitxa temporal = m_tauler[origen.getFila()][origen.getColumna()];
    if (temporal.getTipus() != TIPUS_EMPTY) {
        for (std::vector<Posicio>::iterator it= fitxa.getMoviments().begin();it != fitxa.getMoviments().end();it++) {
            posicionsPossibles[nPosicions++] = *it;
        }
    }
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

int Tauler::trobarDestifinal(std::vector<Posicio> burrito, const Posicio& valor)const {
    int contador = 0;
    for (std::vector<Posicio>::iterator it = burrito.begin();it != burrito.end();it++) {
        if (*it == valor)
            return contador;
        else
            contador++;
           
    }
    return -1;
}
bool Tauler::mouFitxa(const Posicio& origen, const Posicio& desti) {
    Fitxa fitxa = m_tauler[origen.getFila()][origen.getColumna()];
    if (fitxa.esBuit()) return false;
    const std::vector<std::vector<Posicio>> recorreguts = fitxa.getCamins();
    const std::vector<std::vector<Posicio>> pecesCapturades = fitxa.getCaptures();

    for (size_t i = 0; i < recorreguts.size(); i++) {
        int valor = trobarDestifinal(recorreguts[i], desti);
        if (!recorreguts[i].empty() && valor != -1) {
            // Update the board depending on the type of piece (normal or dama)
            if (fitxa.getTipus() == TIPUS_NORMAL) {
                actualitzaTaulerNormal(valor, recorreguts[i]);
            }
            else {
                actualitzaTaulerDames(valor, recorreguts[i]);
            }

            // Move the piece to the destination
            m_tauler[desti.getFila()][desti.getColumna()] = fitxa;
            m_tauler[origen.getFila()][origen.getColumna()] = Fitxa();

            // Check if the piece should be promoted to a dama
            if ((fitxa.getColor() == COLOR_BLANC && desti.getFila() == 0) ||
                (fitxa.getColor() == COLOR_NEGRE && desti.getFila() == 7)) {
                m_tauler[desti.getFila()][desti.getColumna()].ferDama();
            }

            // Update valid moves after the move
            actualitzaMovimentsValids();
            return true;
        }
    }

    return false;
}

std::string Tauler::toString() const
{
    std::vector<std::string> linies;
    int nLinies = 0;
    for (int fila = 0; fila < N_FILES; ++fila)
    {
        for (int col = 0; col < N_COLUMNES; ++col)
        {
            const Fitxa& fitxa = m_tauler[fila][col];
            if (fitxa.getTipus() != TIPUS_EMPTY)
            {
                char codiPeça;
                switch (fitxa.getColor())
                {
                case COLOR_BLANC:
                    switch (fitxa.getTipus()) {
                    case TIPUS_NORMAL:
                        codiPeça = 'O';
                        break;
                    case TIPUS_DAMA:
                        codiPeça = 'D';
                        break;
                    default:
                        continue;
                    }
                    break;
                case COLOR_NEGRE:
                    switch (fitxa.getTipus())
                    {
                    case TIPUS_NORMAL:
                        codiPeça = 'X';
                        break;
                    case TIPUS_DAMA:
                        codiPeça = 'R';
                        break;
                    default:
                        continue;
                    }
                    break;

                default:
                    continue;
                }
                char codiColumna = 'a' + col;
                char codiFila = '1' + fila;
                std::string unaLinia = std::string(1, codiPeça) + " " + codiColumna + codiFila;
                linies.push_back(unaLinia);
                nLinies++;
            }
        }
    }
    std::string finalment = "";
    for (int i = 0; i < nLinies; ++i)
    {
        finalment += linies[i];
        finalment += '\n';
    }
    return finalment;
}
