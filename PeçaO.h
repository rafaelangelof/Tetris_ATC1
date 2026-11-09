#ifndef PECA_O_H
#define PECA_O_H

#include "Peça.h"

class PecaO : public Peca {
public:
    PecaO(const Posicao& posInicial = Posicao(4, 0)): Peca(posInicial, { Posicao(0, 0), Posicao(1, 0), Posicao(0, 1), Posicao(1, 1) }, 2) {
    }
};

#endif