#include "Moviment.h"
void Moviment::CleanMoviment() {
    for (auto& fitxa : recorregut) {
        fitxa.clear();
    }
    recorregut.clear();

    for (auto& fitxa : pecesCapturades) {
        fitxa.clear();
    }
    pecesCapturades.clear();
    destins.clear();
    captures.clear();
}
Moviment::~Moviment() { CleanMoviment(); }
const std::vector<Posicio>& Moviment::getRecorregut(int posicioIndex) const { return recorregut[posicioIndex]; }
const std::vector<Posicio>& Moviment::getCaptures(int posicioIndex) const { return pecesCapturades[posicioIndex]; }
void Moviment::actualitzaMoviments(std::vector<std::vector<std::pair<int, int>>> taulerTraduit, const Posicio& original) {
    std::pair<int, int> titits = taulerTraduit[original.getFila()][original.getColumna()];

    if (titits.first ==0){
        DFSDames(taulerTraduit, recorregut, pecesCapturades, original);
    }
    else if (titits.second ==1) {
        DFSNormal(taulerTraduit, recorregut, pecesCapturades, original);
    }
    else {
        return;
    }
    for (const auto fitxa : recorregut) {
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
}
void Moviment::mirarCapturesDretaEsquerra(const Posicio& origen, std::vector<std::pair<Posicio, int>>& parametrePosicions, std::vector<std::pair<Posicio, bool>>& parametreCaptures, std::vector<std::vector<std::pair<int, int>>>taulerTraduit) {
    int filaNova = -1;
    int filaNova2 = -1;
    int colDret1 = -1;
    int colDret2 = -1;
    int colEsq1 = -1;
    int colEsq2 = -1;
    bool capturatDret = false;
    bool capturatEsquerra = false;
    int valoRetornDreta = 0;
    int valoRetornEsquerra = 0;
    int staticTemporal = taulerTraduit[origen.getFila()][origen.getColumna()].second;
 
    if (esValid(origen.getFila() + staticTemporal, origen.getColumna() + 1)) {
        if (taulerTraduit[origen.getFila() + staticTemporal][origen.getColumna() + 1].second != taulerTraduit[origen.getFila()][origen.getColumna()].second) {
            colDret1 = origen.getColumna() + 1;
            filaNova = origen.getFila() + staticTemporal;
        }
        else
            valoRetornDreta = 1;
    }
    else {
        valoRetornDreta = 1;
    }
    if (esValid(origen.getFila() + staticTemporal, origen.getColumna() - 1)) {
        if (taulerTraduit[origen.getFila() + staticTemporal][origen.getColumna() - 1].second != taulerTraduit[origen.getFila()][origen.getColumna()].second) {
            colEsq1 = origen.getColumna() - 1;
            filaNova = origen.getFila() + staticTemporal;
        }
        else
            valoRetornEsquerra = 1;
    }
    else {
        valoRetornEsquerra = 1;
    }
    if (filaNova != -1) {
        if (colDret1 != -1) {
            if (taulerTraduit[filaNova][colDret1].first == 0) {
                colDret2 = colDret1;
                filaNova2 = filaNova;
                valoRetornDreta = 0;
            }
            else if (taulerTraduit[filaNova][colDret1].second != taulerTraduit[origen.getFila()][origen.getColumna()].second) {
                if (esValid(filaNova + staticTemporal, colDret1 + 1) && taulerTraduit[filaNova + staticTemporal][colDret1 + 1].first == 0) {
                    filaNova2 = filaNova + staticTemporal;
                    colDret2 = colDret1 + 1;
                    capturatDret = true;
                    valoRetornDreta = 2;
                }
                else {
                    valoRetornDreta = 1;
                }
            }
        }
        if (colEsq1 != -1) {
            if (taulerTraduit[filaNova][colEsq1].first == 0) {
                colEsq2 = colEsq1;
                filaNova2 = filaNova;
                valoRetornEsquerra = 0;
            }
            else if (taulerTraduit[filaNova][colEsq1].second != taulerTraduit[origen.getFila()][origen.getColumna()].second) {
                if (esValid(filaNova + staticTemporal, colEsq1 - 1) && taulerTraduit[filaNova + staticTemporal][colEsq1 - 1].first == 0) {
                    filaNova2 = filaNova + staticTemporal;
                    colEsq2 = colEsq1 - 1;
                    capturatEsquerra = true;
                    valoRetornEsquerra = 2;
                }
                else {
                    valoRetornDreta = 1;
                }
            }
        }
    }
    Posicio fitxaDreta(filaNova2, colDret2);        Posicio fitxaDretaCap(filaNova, colDret1);
    Posicio fitxaEsquerra(filaNova2, colEsq2);      Posicio fitxaEsquerraCap(filaNova, colEsq1);

    parametrePosicions.push_back(std::make_pair(fitxaDreta, valoRetornDreta));
    parametreCaptures.push_back(std::make_pair(fitxaDretaCap, capturatDret));
    parametrePosicions.push_back(std::make_pair(fitxaEsquerra, valoRetornEsquerra));
    parametreCaptures.push_back(std::make_pair(fitxaEsquerraCap, capturatEsquerra));
}
void Moviment::mirarCapturesDames(int AmuntBaix, int& continuarDreta, int& continuarEsquerra, const Posicio& origen, std::vector<Posicio>& parametrePosicionsDreta, std::vector<Posicio>& parametrePosicionsEsquerra, std::pair<Posicio, bool>& parametreCapturesDreta, std::pair<Posicio, bool>& parametreCapturadesEsquerra, std::vector<std::vector<std::pair<int, int>>>taulerTraduit)
{

    continuarDreta = -1;
    continuarEsquerra = -1;

    int staticTemporal = taulerTraduit[origen.getFila()][origen.getColumna()].second * AmuntBaix;

    int i = origen.getFila() + staticTemporal;
    int j = origen.getColumna() + 1;
    int valorDret1 = 0;
    int valorEsquerra2 = 0;
    bool trobat = false;
    while (!trobat && esValid(i, j)) {
        if (taulerTraduit[i][j].first == 0) {
            parametrePosicionsDreta.push_back(Posicio(i, j));
            i = i + staticTemporal;
            j = j + 1;
        }
        else if (taulerTraduit[i][j].second != taulerTraduit[origen.getFila()][origen.getColumna()].second || taulerTraduit[i][j].second == taulerTraduit[origen.getFila()][origen.getColumna()].second) {
            trobat = true;
        }
    }
    if (trobat) {
        if (taulerTraduit[i][j].second != taulerTraduit[origen.getFila()][origen.getColumna()].second) {
            if (taulerTraduit[i + staticTemporal][j + 1].first == 0) {//si es buit
                parametrePosicionsDreta.push_back(Posicio(i + staticTemporal, j + 1));
                parametreCapturesDreta = std::make_pair(Posicio(i, j), true);
                continuarDreta = 0;
            }
            else {
                i = i - staticTemporal;
                j = j - 1;
                if (i == origen.getFila() && j == origen.getColumna()) {
                    continuarDreta = 1;
                }
                else {
                    continuarDreta = 2;
                }
            }
        }
        else {
            continuarDreta = 3;
        }
    }
    else {
        continuarDreta = 4;
    }
    i = origen.getFila() + staticTemporal;
    j = origen.getColumna() - 1;
    trobat = false;
    while (!trobat && esValid(i, j)) {
        if (taulerTraduit[i][j].first == 0) {
            parametrePosicionsEsquerra.push_back(Posicio(i, j));
            i = i + staticTemporal;
            j = j - 1;
        }
        else if (taulerTraduit[i][j].second != taulerTraduit[origen.getFila()][origen.getColumna()].second || taulerTraduit[i][j].second == taulerTraduit[origen.getFila()][origen.getColumna()].second) {
            trobat = true;
        }
    }
    if (trobat) {
        if (taulerTraduit[i][j].second != taulerTraduit[origen.getFila()][origen.getColumna()].second) {
            if (taulerTraduit[i + staticTemporal][j - 1].first == 0) {
                parametrePosicionsEsquerra.push_back(Posicio(i + staticTemporal, j - 1));
                parametreCapturadesEsquerra = std::make_pair(Posicio(i, j), true);
                continuarEsquerra = 0;
            }
            else {
                i = i - staticTemporal;
                j = j + 1;
                if (i == origen.getFila() && j == origen.getColumna()) {
                    continuarEsquerra = 1;
                }
                else {
                    continuarEsquerra = 2;
                }
            }
        }
        else {
            continuarEsquerra = 3;
        }

    }
    else {
        continuarEsquerra = 4;
    }
}
void Moviment::DFSDames(std::vector<std::vector<std::pair<int, int>>>taulerTraduit, std::vector<std::vector<Posicio>>& recorregut, std::vector<std::vector<Posicio>>& pecesCaptured, const Posicio& original) {
    std::vector<std::vector<std::pair<Posicio, bool>>> m_taulerVisitats;
    m_taulerVisitats.resize(9, std::vector<std::pair<Posicio, bool>>(9));
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            m_taulerVisitats[i][j].first = Posicio(i,j);
            m_taulerVisitats[i][j].second = false;
        }
    }
    std::stack <std::tuple<Posicio, std::vector<Posicio>, std::vector<Posicio>, bool>> m_stackPerVisitar;
    m_stackPerVisitar.push(std::make_tuple(original, std::vector<Posicio>{original}, std::vector<Posicio>{}, false));
    //std::vector<std::pair<Posicio, bool>> pecesCaptured;
    bool inici = true;
    while (!m_stackPerVisitar.empty()) {
        auto element = m_stackPerVisitar.top();
        auto temporal = std::get<0>(element);
        auto m_vector = std::get<1>(element);
        auto m_cap = std::get<2>(element);
        bool hasCapturat = std::get<3>(element);
        m_stackPerVisitar.pop();
        if (!m_taulerVisitats[temporal.getFila()][temporal.getColumna()].second) {
            m_taulerVisitats[temporal.getFila()][temporal.getColumna()].second = true;
            std::vector<Posicio> posicionsDreta;
            std::vector<Posicio> posicionsEsquerra;
            int continuarDreta = -1;
            int continuarEsquerra = -1;
            std::pair<Posicio, bool> capturadesDreta;
            std::pair<Posicio, bool> capturadesEsquerra;
            int AmuntBaix = 1;
            mirarCapturesDames(AmuntBaix, continuarDreta, continuarEsquerra, temporal, posicionsDreta, posicionsEsquerra, capturadesDreta, capturadesEsquerra, taulerTraduit);
            if (hasCapturat) {
                if (continuarDreta == 0) {
                    std::vector<Posicio> nouCami = m_vector;
                    for (const auto& p : posicionsDreta) nouCami.push_back(p);
                    std::vector<Posicio> novesCaptures = m_cap;
                    if (capturadesDreta.second) { novesCaptures.push_back(capturadesDreta.first); };
                    m_stackPerVisitar.push(make_tuple(posicionsDreta.back(), nouCami, novesCaptures, true));
                }
                else {
                    recorregut.push_back(m_vector);
                    pecesCaptured.push_back(m_cap);
                }
            }
            else {
                if (inici) {
                    if (continuarDreta == 0) {
                        std::vector<Posicio> nouCami = m_vector;
                        for (const auto& p : posicionsDreta) nouCami.push_back(p);
                        std::vector<Posicio> novesCaptures = m_cap;
                        if (capturadesDreta.second) { novesCaptures.push_back(capturadesDreta.first); }

                        m_stackPerVisitar.push(make_tuple(posicionsDreta.back(), nouCami, novesCaptures, true));
                    }
                    else {
                        if (!posicionsDreta.empty()) {
                            std::vector<Posicio> nouCami = m_vector;
                            for (auto& p : posicionsDreta) nouCami.push_back(p);
                            recorregut.push_back(nouCami);
                            pecesCaptured.push_back(m_cap);
                        }
                    }
                }
                else {
                    if (!posicionsDreta.empty()) {
                        std::vector<Posicio> nouCami = m_vector;
                        for (auto& p : posicionsDreta) nouCami.push_back(p);
                        recorregut.push_back(nouCami);
                        pecesCaptured.push_back(m_cap);
                    }
                }
            }
            if (hasCapturat) {
                if (continuarEsquerra == 0) {
                    std::vector<Posicio> nouCami = m_vector;
                    for (const auto& p : posicionsEsquerra) nouCami.push_back(p);
                    std::vector<Posicio> novesCaptures = m_cap;
                    if (capturadesEsquerra.second) novesCaptures.push_back(capturadesEsquerra.first);

                    m_stackPerVisitar.push(make_tuple(posicionsEsquerra.back(), nouCami, novesCaptures, true));
                }
                else {
                    recorregut.push_back(m_vector);
                    pecesCaptured.push_back(m_cap);
                }
            }
            else {
                if (inici) {
                    if (continuarEsquerra == 0) {
                        std::vector<Posicio> nouCami = m_vector;
                        for (const auto& p : posicionsEsquerra) nouCami.push_back(p);
                        std::vector<Posicio> novesCaptures = m_cap;
                        if (capturadesEsquerra.second) novesCaptures.push_back(capturadesEsquerra.first);

                        m_stackPerVisitar.push(make_tuple(posicionsEsquerra.back(), nouCami, novesCaptures, true));
                    }
                    else {
                        if (!posicionsEsquerra.empty()) {
                            std::vector<Posicio> nouCami = m_vector;
                            for (auto& p : posicionsEsquerra) nouCami.push_back(p);
                            recorregut.push_back(nouCami);
                            pecesCaptured.push_back(m_cap);
                        }
                    }
                }
                else {
                    if (!posicionsEsquerra.empty()) {
                        std::vector<Posicio> nouCami = m_vector;
                        for (auto& p : posicionsEsquerra) nouCami.push_back(p);
                        recorregut.push_back(nouCami);
                        pecesCaptured.push_back(m_cap);
                    }
                }
            }


            continuarDreta = -1;
            continuarEsquerra = -1;
            posicionsDreta.clear();
            posicionsEsquerra.clear();
            AmuntBaix = -1;
            mirarCapturesDames(AmuntBaix, continuarDreta, continuarEsquerra, temporal, posicionsDreta, posicionsEsquerra, capturadesDreta, capturadesEsquerra, taulerTraduit);
            if (hasCapturat) {
                if (continuarDreta == 0) {
                    std::vector<Posicio> nouCami = m_vector;
                    for (const auto& p : posicionsDreta) nouCami.push_back(p);
                    std::vector<Posicio> novesCaptures = m_cap;
                    if (capturadesDreta.second) novesCaptures.push_back(capturadesDreta.first);

                    m_stackPerVisitar.push(make_tuple(posicionsDreta.back(), nouCami, novesCaptures, true));
                }
                else {
                    recorregut.push_back(m_vector);
                    pecesCaptured.push_back(m_cap);
                }
            }
            else {
                if (inici) {
                    if (continuarDreta == 0) {
                        std::vector<Posicio> nouCami = m_vector;
                        for (const auto& p : posicionsDreta) nouCami.push_back(p);
                        std::vector<Posicio> novesCaptures = m_cap;
                        if (capturadesDreta.second) novesCaptures.push_back(capturadesDreta.first);

                        m_stackPerVisitar.push(make_tuple(posicionsDreta.back(), nouCami, novesCaptures, true));
                    }
                    else {
                        if (!posicionsDreta.empty()) {
                           std::vector<Posicio> nouCami = m_vector;
                            for (auto& p : posicionsDreta) nouCami.push_back(p);
                            recorregut.push_back(nouCami);
                            pecesCaptured.push_back(m_cap);
                        }
                    }
                }
                else {
                    if (!posicionsDreta.empty()) {
                        std::vector<Posicio> nouCami = m_vector;
                        for (auto& p : posicionsDreta) nouCami.push_back(p);
                        recorregut.push_back(nouCami);
                        pecesCaptured.push_back(m_cap);
                    }
                }
            }

            if (hasCapturat) {
                if (continuarEsquerra == 0) {
                    std::vector<Posicio> nouCami = m_vector;
                    for (const auto& p : posicionsEsquerra) nouCami.push_back(p);
                    std::vector<Posicio> novesCaptures = m_cap;
                    if (capturadesEsquerra.second) novesCaptures.push_back(capturadesEsquerra.first);

                    m_stackPerVisitar.push(make_tuple(posicionsEsquerra.back(), nouCami, novesCaptures, true));
                }
                else {
                    recorregut.push_back(m_vector);
                    pecesCaptured.push_back(m_cap);
                }
            }
            else {
                if (inici) {
                    if (continuarEsquerra == 0) {
                       std:: vector<Posicio> nouCami = m_vector;
                        for (const auto& p : posicionsEsquerra) nouCami.push_back(p);
                        std::vector<Posicio> novesCaptures = m_cap;
                        if (capturadesEsquerra.second) novesCaptures.push_back(capturadesEsquerra.first);

                        m_stackPerVisitar.push(make_tuple(posicionsEsquerra.back(), nouCami, novesCaptures, true));
                    }
                    else {
                        if (!posicionsEsquerra.empty()) {
                            std::vector<Posicio> nouCami = m_vector;
                            for (auto& p : posicionsEsquerra) nouCami.push_back(p);
                            recorregut.push_back(nouCami);
                            pecesCaptured.push_back(m_cap);
                        }
                    }
                }
                else {
                    if (!posicionsEsquerra.empty()) {
                        std::vector<Posicio> nouCami = m_vector;
                        for (auto& p : posicionsEsquerra) nouCami.push_back(p);
                        recorregut.push_back(nouCami);
                        pecesCaptured.push_back(m_cap);
                    }
                }
            }
            inici = false;
        }
    }
}
void Moviment::DFSNormal(std::vector<std::vector<std::pair<int, int>>>taulerTraduit, std::vector<std::vector<Posicio>>& recorregut, std::vector<std::vector<Posicio>>& pecesCaptured, const Posicio& original) {
    std::vector<std::vector<std::pair<Posicio, bool>>> m_taulerVisitats;
    m_taulerVisitats.resize(8, std::vector<std::pair<Posicio, bool>>(8));
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            m_taulerVisitats[i][j].first = Posicio(i, j);
            m_taulerVisitats[i][j].second = false;
        }
    }

    bool inici = true;
    std::stack<std::tuple<Posicio, std::vector<Posicio>, std::vector<Posicio>, bool>> m_stackPerVisitar;
    while (!m_stackPerVisitar.empty()) {
        std::tuple<Posicio, std::vector<Posicio>, std::vector<Posicio>, bool> element = m_stackPerVisitar.top();
    Posicio temporal = std::get<0>(element);
        std::vector<Posicio> m_vector = std::get<1>(element);
        std::vector<Posicio> m_cap = std::get<2>(element);
        bool hasCapturat = std::get<3>(element);
        m_stackPerVisitar.pop();
        if (!m_taulerVisitats[temporal.getFila()][temporal.getColumna()].second) {
            m_taulerVisitats[temporal.getFila()][temporal.getColumna()].second = true;
            std::vector<std::pair<Posicio, int>> posicions;
            std::vector<std::pair<Posicio, bool>> capturades;
            mirarCapturesDretaEsquerra(temporal, posicions, capturades, taulerTraduit);
            int valor1Dret = posicions[0].second;;
            int valor2Esquerra = posicions[1].second;
            if (hasCapturat) {
                if (valor1Dret == 2 && !m_taulerVisitats[posicions[0].first.getFila()][posicions[0].first.getColumna()].second) {
                    std::vector<Posicio> nouCami = m_vector;
                    nouCami.push_back(posicions[0].first);
                    std::vector<Posicio>novesCaptures = m_cap;
                    if (capturades[0].second) {
                        novesCaptures.push_back(capturades[0].first);
                    }
                    m_stackPerVisitar.push(std::make_tuple(posicions[0].first, nouCami, novesCaptures, true));
                }
                else {
                    recorregut.push_back(m_vector);
                    pecesCapturades.push_back(m_cap);
                }
            }
            else {
                if (inici) {
                    if (valor1Dret == 2 && !m_taulerVisitats[posicions[0].first.getFila()][posicions[0].first.getColumna()].second) {
                        std::vector<Posicio> nouCami = m_vector;
                        nouCami.push_back(posicions[0].first);
                        std::vector<Posicio>novesCaptures = m_cap;
                        if (capturades[0].second) {
                            novesCaptures.push_back(capturades[0].first);
                        }
                        m_stackPerVisitar.push(std::make_tuple(posicions[0].first, nouCami, novesCaptures, true));
                    }
                    else if (valor1Dret == 0) {
                        std::vector<Posicio>nouCami = m_vector;
                        nouCami.push_back(posicions[0].first);
                        recorregut.push_back(m_vector);
                        pecesCaptured.push_back(m_cap);
                    }
                    else {
                        recorregut.push_back(m_vector);
                        pecesCaptured.push_back(m_cap);
                    }
                }
            }
            if (hasCapturat) {
                if (valor2Esquerra == 2 && !m_taulerVisitats[posicions[1].first.getFila()][posicions[1].first.getColumna()].second) {
                    std::vector<Posicio> nouCami = m_vector;
                    nouCami.push_back(posicions[1].first);
                    std::vector<Posicio>novesCaptures = m_cap;
                    if (capturades[1].second) {
                        novesCaptures.push_back(capturades[1].first);
                    }
                    m_stackPerVisitar.push(std::make_tuple(posicions[1].first, nouCami, novesCaptures, true));
                }
                else {
                    recorregut.push_back(m_vector);
                    pecesCapturades.push_back(m_cap);
                }
            }
            else {
                if (inici) {
                    if (valor2Esquerra == 2 && !m_taulerVisitats[posicions[1].first.getFila()][posicions[1].first.getColumna()].second) {
                        std::vector<Posicio> nouCami = m_vector;
                        nouCami.push_back(posicions[1].first);
                        std::vector<Posicio>novesCaptures = m_cap;
                        if (capturades[1].second) {
                            novesCaptures.push_back(capturades[1].first);
                        }
                        m_stackPerVisitar.push(std::make_tuple(posicions[1].first, nouCami, novesCaptures, true));
                    }
                    else if (valor2Esquerra == 0) {
                        std::vector<Posicio>nouCami = m_vector;
                        nouCami.push_back(posicions[1].first);
                        recorregut.push_back(m_vector);
                        pecesCaptured.push_back(m_cap);
                    }
                    else {
                        recorregut.push_back(m_vector);
                        pecesCaptured.push_back(m_cap);
                    }
                }
            }
            inici = false;
        }
    }
}
