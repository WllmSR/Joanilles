#include "Moviment.h"
#include <iostream>
using namespace std;
void Moviment::CleanMoviment() {
    for (auto& fitxa : recorreguts) {
        fitxa.clear();
    }
    recorreguts.clear();

    for (auto& fitxa : pecesCapturades) {
        fitxa.clear();
    }
    pecesCapturades.clear();
    destins.clear();
    captures.clear();
}
Moviment::~Moviment() { CleanMoviment(); }
bool camiExisteix(const std::vector<std::vector<Posicio>>& poma, const std::vector<Posicio>& cami) {
    for (const auto& existent : poma) {
        if (existent == cami) {
            return true;
        }
    }
    return false;
}

const std::vector<Posicio>& Moviment::getRecorregut(int posicioIndex) const { return recorreguts[posicioIndex]; }
const std::vector<Posicio>& Moviment::getCaptures(int posicioIndex) const { return pecesCapturades[posicioIndex]; }
void Moviment::actualitzaMoviments(std::vector<std::vector<std::pair<int, int>>> taulerTraduit, const Posicio& original){
    std::pair<int, int> titits = taulerTraduit[original.getFila()][original.getColumna()];
    if (titits.first == 1) {
        DFSDames(taulerTraduit, recorreguts, pecesCapturades, original);
    }
    else if (titits.first == 0) {
        DFSNormal(taulerTraduit, recorreguts, pecesCapturades, original);
    }
    else {
        return;
    }
    for (const auto fitxa : recorreguts) {
        for (const auto element : fitxa) {
            if (find(destins.begin(), destins.end(), element) == destins.end()) {
                destins.push_back(element);
            }
        }
    }
    for (const auto fitxa : pecesCapturades) {
        for (const auto element : fitxa) {
            if (find(captures.begin(), captures.end(), element) == captures.end()) {
                captures.push_back(element);
            }
        }

    }
}/**/
void Moviment::mirarCapturesDames(bool inici, int AmuntBaix, int& continuarDreta, int& continuarEsquerra, const Posicio& origen, std::vector<Posicio>& parametrePosicionsDreta, std::vector<Posicio>& parametrePosicionsEsquerra, std::pair<Posicio, bool>& parametreCapturesDreta, std::pair<Posicio, bool>& parametreCapturadesEsquerra, std::vector<std::vector<std::pair<int, int>>> taulerTraduit, const std::vector<Posicio>& capturesActuals) {
    continuarDreta = -1;
    continuarEsquerra = -1;

    int staticTemporal = AmuntBaix;
int i = origen.getFila() + staticTemporal;
    int j = origen.getColumna() + 1;
    bool trobat = false;

    while (!trobat && esValid(i, j)) {
        if (taulerTraduit[i][j].first == -1) {
            parametrePosicionsDreta.push_back(Posicio(i, j));
            i += staticTemporal;
            j += 1;
        }
        else {
            trobat = true;
        }
    }

    if (trobat) {
        bool jaCapturada = std::find_if(capturesActuals.begin(), capturesActuals.end(), [&](const Posicio& p) {
            return p.getFila() == i && p.getColumna() == j;
            }) != capturesActuals.end();
            int colorActual = taulerTraduit[origen.getFila()][origen.getColumna()].second;
            int colorPeca = taulerTraduit[i][j].second;
            bool esEnemic = (colorPeca != colorActual && colorPeca != 0);
            if (!jaCapturada && esEnemic && esValid(i + staticTemporal, j + 1) && taulerTraduit[i + staticTemporal][j + 1].first == -1) {
                parametrePosicionsDreta.push_back(Posicio(i + staticTemporal, j + 1));
                parametreCapturesDreta = { Posicio(i, j), true };
                continuarDreta = 0;
            }
            else {
                if (!inici) {
                    parametrePosicionsDreta.clear();
                    parametreCapturesDreta.second = false;
                }
                else if (inici) {
                }

            }
    }
    else if (!inici) {
        parametrePosicionsDreta.clear();
        parametreCapturesDreta.second = false;

    }
    else if (inici) {
    }
    
    i = origen.getFila() + staticTemporal;
    j = origen.getColumna() - 1;
    trobat = false;

    while (!trobat && esValid(i, j)) {
        if (taulerTraduit[i][j].first == -1) {
            parametrePosicionsEsquerra.push_back(Posicio(i, j));
            i += staticTemporal;
            j -= 1;
        }
        else {
            trobat = true;
        }
    }
    if (trobat) {
        bool jaCapturada = std::find_if(capturesActuals.begin(), capturesActuals.end(), [&](const Posicio& p) {
            return p.getFila() == i && p.getColumna() == j;
            }) != capturesActuals.end();
            int colorActual = taulerTraduit[origen.getFila()][origen.getColumna()].second;
            int colorPeca = taulerTraduit[i][j].second;
            bool esEnemic = (colorPeca != colorActual && colorPeca != 0);
            if (!jaCapturada && esEnemic && esValid(i + staticTemporal, j - 1) && taulerTraduit[i + staticTemporal][j - 1].first == -1) {
                parametrePosicionsEsquerra.push_back(Posicio(i + staticTemporal, j - 1));
                parametreCapturadesEsquerra = { Posicio(i, j), true };
                continuarEsquerra = 0;
            }
            else {
                if (!inici) {
                    parametrePosicionsEsquerra.clear();
                    parametreCapturadesEsquerra.second = false;
                }
                else {
                }

            }
    }
    else if (!inici) {
        parametrePosicionsEsquerra.clear();
        parametreCapturadesEsquerra.second = false;

    }
    else if (inici) {
    }
}
void Moviment::DFSDames(std::vector<std::vector<std::pair<int, int>>> taulerTraduit, std::vector<std::vector<Posicio>>& recorregut, std::vector<std::vector<Posicio>>& pecesCaptured, const Posicio& original) {
    std::vector<std::vector<std::pair<Posicio, bool>>> m_taulerVisitats(8, std::vector<std::pair<Posicio, bool>>(8));
    for (int i = 0; i < 8; ++i)
        for (int j = 0; j < 8; ++j)
            m_taulerVisitats[i][j] = { Posicio(i, j), false };

    std::stack<std::tuple<Posicio, std::vector<Posicio>, std::vector<Posicio>, bool>> m_stackPerVisitar;
    m_stackPerVisitar.push({ original, {original}, {}, false });
    bool inici = true;
    while (!m_stackPerVisitar.empty()) {
        std::tuple < Posicio, std::vector<Posicio>, std::vector<Posicio>, bool >Deon = m_stackPerVisitar.top();
        Posicio posActual = std::get<0>(Deon);
        std::vector<Posicio> camiActual = std::get<1>(Deon);
        std::vector<Posicio> capturesActuals = std::get<2>(Deon);
        bool haCapturat = std::get<3>(Deon);
        m_stackPerVisitar.pop();
        if (m_taulerVisitats[posActual.getFila()][posActual.getColumna()].second) continue;
        m_taulerVisitats[posActual.getFila()][posActual.getColumna()].second = true;

        for (int direccio : {-1, 1}) {
            std::vector<Posicio> posicionsDreta, posicionsEsquerra;
            std::pair<Posicio, bool> capturaDreta, capturaEsquerra;
            int continuarDreta = -1, continuarEsquerra = -1;

            mirarCapturesDames(inici, direccio, continuarDreta, continuarEsquerra, posActual, posicionsDreta, posicionsEsquerra, capturaDreta, capturaEsquerra, taulerTraduit, capturesActuals);

            auto processarMoviment = [&](const std::vector<Posicio>& posicions,
                int continuar,
                const std::pair<Posicio, bool>& captura) {
                    if (posicions.empty()) return;

                    std::vector<Posicio> nouCami = camiActual;
                    nouCami.insert(nouCami.end(), posicions.begin(), posicions.end());

                    std::vector<Posicio> novesCaptures = capturesActuals;
                    if (captura.second) {
                        novesCaptures.push_back(captura.first);
                    }
                    else {
                    }

                    if (continuar == 0) {

                        if (captura.second) {
                            if (std::find(recorregut.begin(), recorregut.end(), nouCami) == recorregut.end()) {
                                recorregut.push_back(nouCami);
                                pecesCaptured.push_back(novesCaptures);
                            }
                        }

                        m_stackPerVisitar.push({ posicions.back(), nouCami, novesCaptures, true });
                    }
                    else {
                        if (std::find(recorregut.begin(), recorregut.end(), nouCami) == recorregut.end()) {
                            recorregut.push_back(nouCami);
                            pecesCaptured.push_back(novesCaptures);
                        }
                        else {
                        }
                    }
                };

            processarMoviment(posicionsDreta, continuarDreta, capturaDreta);
            processarMoviment(posicionsEsquerra, continuarEsquerra, capturaEsquerra);

        }

        inici = false;
    }
   }

void Moviment::mirarCapturesDretaEsquerra(const Posicio& origen, std::vector<std::pair<Posicio, int>>& parametrePosicions, std::vector<std::pair<Posicio, bool>>& parametreCaptures, std::vector<std::vector<std::pair<int, int>>> taulerTraduit) {
    int staticTemporal = taulerTraduit[origen.getFila()][origen.getColumna()].second;
    // Variables separades per a cada direcció
    int filaNovaDreta = -1, filaNova2Dreta = -1, colDret1 = -1, colDret2 = -1;
    int filaNovaEsq = -1, filaNova2Esq = -1, colEsq1 = -1, colEsq2 = -1;
    bool capturatDret = false, capturatEsquerra = false;
    int valoRetornDreta = 1, valoRetornEsquerra = 1; // per defecte moviment no vàlid

    // --- Direcció dreta ---
    if (esValid(origen.getFila() + staticTemporal, origen.getColumna() + 1)){
        if (taulerTraduit[origen.getFila() + staticTemporal][origen.getColumna() + 1].second != taulerTraduit[origen.getFila()][origen.getColumna()].second &&
            taulerTraduit[origen.getFila() + staticTemporal][origen.getColumna() + 1].first != -1){
            // peça enemiga
            colDret1 = origen.getColumna() + 1;
            filaNovaDreta = origen.getFila() + staticTemporal;

            if (esValid(filaNovaDreta + staticTemporal, colDret1 + 1) && taulerTraduit[filaNovaDreta + staticTemporal][colDret1 + 1].first == -1) {
                filaNova2Dreta = filaNovaDreta + staticTemporal;
                colDret2 = colDret1 + 1;
                capturatDret = true;
                valoRetornDreta = 2;
            }
        }
        else if (taulerTraduit[origen.getFila() + staticTemporal][origen.getColumna() + 1].first == -1){
            // cas moviment normal
            colDret2 = origen.getColumna() + 1;
            filaNova2Dreta = origen.getFila() + staticTemporal;
            valoRetornDreta = 0;
        }
    }

    // --- Direcció esquerra ---
    if (esValid(origen.getFila() + staticTemporal, origen.getColumna() - 1)) {
        if (taulerTraduit[origen.getFila() + staticTemporal][origen.getColumna() - 1].second != taulerTraduit[origen.getFila()][origen.getColumna()].second &&
            taulerTraduit[origen.getFila() + staticTemporal][origen.getColumna() - 1].first != -1){
            // peça enemiga
            colEsq1 = origen.getColumna() - 1;
            filaNovaEsq = origen.getFila() + staticTemporal;

            if (esValid(filaNovaEsq + staticTemporal, colEsq1 - 1) && taulerTraduit[filaNovaEsq + staticTemporal][colEsq1 - 1].first == -1) {
                filaNova2Esq = filaNovaEsq + staticTemporal;
                colEsq2 = colEsq1 - 1;
                capturatEsquerra = true;
                valoRetornEsquerra = 2;
            }
        }
        else if (taulerTraduit[origen.getFila() + staticTemporal][origen.getColumna() - 1].first == -1) {
            colEsq2 = origen.getColumna() - 1;
            filaNova2Esq = origen.getFila() + staticTemporal;
            valoRetornEsquerra = 0;
        }
    }

    // Crear objectes Posicio
    Posicio fitxaDreta(filaNova2Dreta, colDret2);
    Posicio fitxaDretaCap(filaNovaDreta, colDret1);

    Posicio fitxaEsquerra(filaNova2Esq, colEsq2);
    Posicio fitxaEsquerraCap(filaNovaEsq, colEsq1);

    // Afegir resultats
    parametrePosicions.push_back({ fitxaDreta, valoRetornDreta });
    parametreCaptures.push_back({ fitxaDretaCap, capturatDret });

    parametrePosicions.push_back({ fitxaEsquerra, valoRetornEsquerra });
    parametreCaptures.push_back({ fitxaEsquerraCap, capturatEsquerra });
  
}


void Moviment::DFSNormal(
    std::vector<std::vector<std::pair<int, int>>> taulerTraduit,
    std::vector<std::vector<Posicio>>& problemes,
    std::vector<std::vector<Posicio>>& pecesCaptured,
    const Posicio& original
) {
    std::vector<std::vector<std::pair<Posicio, bool>>> m_taulerVisitats(8, std::vector<std::pair<Posicio, bool>>(8));
    for (int i = 0; i < 8; ++i)
        for (int j = 0; j < 8; ++j)
            m_taulerVisitats[i][j] = { Posicio(i, j), false };

    std::stack<std::tuple<Posicio, std::vector<Posicio>, std::vector<Posicio>, bool>> m_stackPerVisitar;
    m_stackPerVisitar.push({ original, {original}, {}, false });
    bool inici = true;
    while (!m_stackPerVisitar.empty()) {

        std::tuple < Posicio, std::vector<Posicio>, std::vector<Posicio>, bool >Deon = m_stackPerVisitar.top();
        Posicio posActual = std::get<0>(Deon);
        std::vector<Posicio> camiActual = std::get<1>(Deon);
        std::vector<Posicio> capturesActuals = std::get<2>(Deon);
        bool haCapturat = std::get<3>(Deon);
        m_stackPerVisitar.pop();
        if (m_taulerVisitats[posActual.getFila()][posActual.getColumna()].second) continue;
        m_taulerVisitats[posActual.getFila()][posActual.getColumna()].second = true;

        std::vector<std::pair<Posicio, int>> posicions;
        std::vector<std::pair<Posicio, bool>> capturades;

        mirarCapturesDretaEsquerra(posActual, posicions, capturades, taulerTraduit);
        // Gestionar cada direcció (dreta i esquerra)
        int contador = 0;
        for (int dir = 0; dir < 2; dir++) {
            contador++;
            const Posicio& dest = posicions[dir].first;
            int tipusMoviment = posicions[dir].second;
            const auto& captura = capturades[dir];
            if (haCapturat){
                if (tipusMoviment == 2 && !m_taulerVisitats[dest.getFila()][dest.getColumna()].second) {
                    //vol dir qu podem continuar:
                    auto nouCami = camiActual;
                    auto novesCaptures = capturesActuals;
                    nouCami.push_back(dest);
                    if (captura.second) novesCaptures.push_back(captura.first);
                    m_stackPerVisitar.push({ dest, nouCami, novesCaptures, true });
                   
                }
                else {
                    if (!camiExisteix(problemes, camiActual)) {
                        problemes.push_back(camiActual);
                        pecesCaptured.push_back(capturesActuals);
                    }
                }
            }
            else {
                //no hem capturat abans
                if (inici) {
                    if (tipusMoviment == 2 && !m_taulerVisitats[dest.getFila()][dest.getColumna()].second){
                        auto nouCami = camiActual;
                        auto novesCaptures = capturesActuals;
                        nouCami.push_back(dest);
                        if (captura.second) novesCaptures.push_back(captura.first);
                        m_stackPerVisitar.push({ dest, nouCami, novesCaptures, true });
                    }
                    else if (tipusMoviment == 0){
                        auto nouCami = camiActual;
                        nouCami.push_back(dest);
                        if (!camiExisteix(problemes, nouCami)) {
                            problemes.push_back(nouCami);
                            pecesCaptured.push_back(capturesActuals);
                        }
                        else {
                        }
                    }
                    else{
                        if (!camiExisteix(problemes, camiActual)) {
                            problemes.push_back(camiActual);
                            pecesCaptured.push_back(capturesActuals);

                        }
                    }

                }
                else {
                    if (!camiExisteix(problemes, camiActual)) {
                        problemes.push_back(camiActual);
                        pecesCaptured.push_back(capturesActuals);
                    }
                }

            }
        }


        inici = false;
    }
}


