#include "Fitxa.h"

Fitxa::Fitxa(char tipusIcolor, const array<char, 2>& pos)
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

    posFitxa(pos);
    //original, es la Fitxa que estem calculant
moviments.actualitzaMoviments(m_tauler,posFitxa);

    //JOANNNNNN
}
