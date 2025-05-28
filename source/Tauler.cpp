#include "Tauler.h"
#include <iostream>
using namespace std;
void Tauler::actualitzaMovimentsValids(){
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            
            m_tauler[i][j].netejaMoviments();
            if (!m_tauler[i][j].getTipus() != TIPUS_EMPTY) {
                Posicio pos(i, j);
                m_tauler[i][j].calcularPosicionsPossibles(m_tauler, pos);
            }
        }
    }
}
void Tauler::actualitzaTaulerNormal(int valor, std::vector<Posicio>camiActual){
    Posicio posActual = camiActual[0];
    for (int j = 1; j <= valor; j++) {
        Posicio posSeguent = camiActual[j];

        int filaDiferencia = posSeguent.getFila() - posActual.getFila();
        int columnaDiferencia = posSeguent.getColumna() - posActual.getColumna();
       
        if (abs(filaDiferencia) == 2 && abs(columnaDiferencia) == 2) {
            int filaCapturada = (posActual.getFila() + posSeguent.getFila()) / 2;
            int columnaCapturada = (posActual.getColumna() + posSeguent.getColumna()) / 2;

            m_tauler[filaCapturada][columnaCapturada] = Fitxa();
        }

        posActual = posSeguent;
    }

    m_tauler[posActual.getFila()][posActual.getColumna()] = m_tauler[camiActual[0].getFila()][camiActual[0].getColumna()];
    m_tauler[camiActual[0].getFila()][camiActual[0].getColumna()] = Fitxa();
}
void actual(int valor, std::vector<Posicio>camiActual) {
    Posicio poisicioActual = camiActual[0];
    for (int i = 1;i <= valor;i++) {
        Posicio posicioSeguent = camiActual[i];
        int filaDiferencia = posicioSeguent.getFila() - poisicioActual.getColumna();
        int columnaDiferencia = posicioSeguent.getColumna() - poisicioActual.getColumna();
        if (abs(filaDiferencia == 2) && abs(columnaDiferencia)) {

        }
    }
}
void Tauler::inicialitza(const std::string& nomFitxer){
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
        std::array<char, 2> pos = { linia[2], linia[3] };
        Posicio p(pos);
        int fila = p.getFila();
        int col = p.getColumna();
        switch (tipusIcolor)
        {
        case 'O':
            m_tauler[fila][col].setTipus(TIPUS_NORMAL);
            m_tauler[fila][col].setColor(COLOR_BLANC);
            break;
        case 'X':
            m_tauler[fila][col].setTipus(TIPUS_NORMAL);
            m_tauler[fila][col].setColor(COLOR_NEGRE);
            break;
        case 'D':
            m_tauler[fila][col].setTipus(TIPUS_DAMA);
            m_tauler[fila][col].setColor(COLOR_BLANC);
            break;
        case 'R':
            m_tauler[fila][col].setTipus(TIPUS_DAMA);
            m_tauler[fila][col].setColor(COLOR_NEGRE);
            break;
        default:
            m_tauler[fila][col].setTipus(TIPUS_EMPTY);
            m_tauler[fila][col].setColor(COLOR_EMPTY);
            break;
        }

        m_tauler[fila][col].setPos(p.getColumna(), p.getFila());

    }
    fitxer.close();
    actualitzaMovimentsValids();
}
void Tauler::getPosicionsPossibles(const Posicio& origen, int& nPosicions, Posicio posicionsPossibles[]) {
    const int MAX_POSICIONS = 20; // o el que pertoqui
    nPosicions = 0;
    if (m_tauler[origen.getFila()][origen.getColumna()].getTipus() != TIPUS_EMPTY){
        for (const auto& pos : m_tauler[origen.getFila()][origen.getColumna()].getMoviments()) {
            if(pos.getFila()!=origen.getFila()&&pos.getColumna()&&origen.getColumna()){
                posicionsPossibles[nPosicions++] = pos;
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



bool Tauler::mouFitxa(const Posicio& origen, const Posicio& desti){
    if (m_tauler[origen.getFila()][origen.getColumna()].getTipus() == TIPUS_EMPTY) {
        return false;
    
    }
    Fitxa fitxa = m_tauler[origen.getFila()][origen.getColumna()];
    if (fitxa.esBuit()) {;return false; };
    const std::vector<std::vector<Posicio>> recorreguts = fitxa.getCamins();
    const std::vector<std::vector<Posicio>> pecesCapturades = fitxa.getCaptures();
    for (const auto& temporal : recorreguts)
    {
        for (const auto& temporal1 : temporal)
            cout << temporal1;
        cout << endl;
    }
    for (size_t i = 0; i < recorreguts.size(); i++) {
        int valor = trobarDestifinal(recorreguts[i], desti);
        if (!recorreguts[i].empty() && valor != -1){
           // Update the board depending on the type of piece (normal or dama)
            if (fitxa.getTipus() != TIPUS_EMPTY){
                actualitzaTaulerNormal(valor,recorreguts[i]);
            }
            else {
                
            }
            if ((fitxa.getColor() == COLOR_BLANC && desti.getFila() == 0) ||
                (fitxa.getColor() == COLOR_NEGRE && desti.getFila() == 7)) {
                m_tauler[desti.getFila()][desti.getColumna()].ferDama();
            }
    actualitzaMovimentsValids();
            return true;
        }
        else {
        }
    }
    return false;
}
std::string Tauler::toString() const
{
    std::string resultat;

    for (int fila = N_FILES - 1; fila >= 0; --fila)
    {
        resultat += std::to_string(fila + 1) + ": ";
        for (int col = 0; col < N_COLUMNES; ++col)
        {
            const Fitxa& fitxa = m_tauler[fila][col];

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
                    codiPeça = '_';
                    break;
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
                    codiPeça = '_';
                    break;
                }
                break;
            default:
                codiPeça = '_';
                break;
            }

            resultat += codiPeça;
            resultat += ' ';  // Afegim espai entre peces
        }
       
        resultat += '\n';
    }

    resultat += "   a b c d e f g h\n";  // Capçalera de columnes

    return resultat;
}

void Tauler::printTaulerComplert()
{
    std::cout << "  a b c d e f g h\n";

    for (int fila = 0; fila < N_FILES; ++fila)
    {
        std::cout << fila + 1 << " ";

        for (int col = 0; col < N_COLUMNES; ++col)
        {
            const Fitxa& fitxa = m_tauler[fila][col];
            
            if (fitxa.getTipus() != TIPUS_EMPTY)
            {
                if (fitxa.getColor() == COLOR_BLANC)
                {
                    switch (fitxa.getTipus())
                    {
                    case TIPUS_NORMAL:
                        cout<<'O';
                        break;
                    case TIPUS_DAMA:
                        cout<<'D';
                        break;
                    default:
                        break;
                    }
                }
                else if (fitxa.getColor() == COLOR_NEGRE)
                {
                    switch (fitxa.getTipus())
                    {
                    case TIPUS_NORMAL:
                        cout<<'X';
                        break;
                    case TIPUS_DAMA:
                        cout<<'R';
                        break;
                    default:
                        break;
                    }
                }
            }
            else {
                cout << "_";
            }
            cout << " ";
          }

        std::cout << std::endl;
    }
    
}

