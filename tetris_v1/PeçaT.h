#ifndef PECA_T_H
#define PECA_T_H

#include "Peça.h"

class PecaT : public Peca {
public:
    PecaT(const Posicao& posInicial = Posicao(4, 0)): Peca(posInicial, { Posicao(1, 0), Posicao(0, 1), Posicao(1, 1), Posicao(2, 1) }, 1) {
    }
};

#endif
