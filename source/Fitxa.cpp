#include "Fitxa.h"
using namespace std;
#include <iostream>
Fitxa::Fitxa(char tipusIcolor, const std::array<char, 2>& pos):posFitxa(pos)
{
    switch (tipusIcolor)
    {
    case 'O':
        tipus = TIPUS_NORMAL;
        color = COLOR_BLANC;
        break;
    case 'X':
        tipus = TIPUS_NORMAL;
        color = COLOR_NEGRE;
        break;
    case 'D':
        tipus = TIPUS_DAMA;
        color = COLOR_BLANC;
        break;
    case 'R':
        tipus = TIPUS_DAMA;
        color = COLOR_NEGRE;
        break;
    default:
        tipus = TIPUS_EMPTY;
        color = COLOR_EMPTY;
        break;
    }


}
void Fitxa::calcularPosicionsPossibles(const Fitxa tauler[][8], const Posicio& original){
    std::vector<std::vector<std::pair<int, int>>> taulerTraduir;
    taulerTraduir.resize(8, std::vector<std::pair<int,int>>(8));
   for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            taulerTraduir[i][j].first = static_cast<int>(tauler[i][j].getTipus());
            taulerTraduir[i][j].second = static_cast<int>(tauler[i][j].getColor());
        }
    }
    moviments.actualitzaMoviments(taulerTraduir, original);
}
