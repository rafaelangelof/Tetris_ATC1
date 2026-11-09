#ifndef PECA_H
#define PECA_H

#include "Position.h"
#include <vector>

class Peca {
private:
    Posicao origem;
    std::vector<Posicao> offsets; // Posição relativa 
    int cor;                      // Cores das peças
public:
    Peca(const Posicao& posInicial, const std::vector<Posicao>& blocosOffsets, int corPeca)
        : origem(posInicial), offsets(blocosOffsets), cor(corPeca) {
    }

    // Devolve a lista com as posições reais no tabuleiro
    std::vector<Posicao> obterBlocosAbsolutos() const {
        std::vector<Posicao> absolutos;
        for (size_t i = 0; i < offsets.size(); ++i) {
            absolutos.push_back(origem.somar(offsets[i]));
        }
        return absolutos;
    }

    void descer() {
        origem = origem.somar(Posicao(0, 1));
    }

    void moverEsquerda() {
        origem = origem.somar(Posicao(-1, 0));
    }

    void moverDireita() {
        origem = origem.somar(Posicao(1, 0));
    }

    Posicao getPosition() const { return origem.getPosition(); }
    int getCor() const { return cor; }
};

#endif