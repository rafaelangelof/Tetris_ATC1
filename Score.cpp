#include "Score.h"
#include <stdexcept>

namespace {
    // Pontos base por numero de linhas eliminadas de uma vez (indice = linhas)
    constexpr int PONTUACAO_LINHAS[] = {0, 100, 300, 500, 800};
    constexpr int MAX_LINHAS = 4;
    constexpr int LINHAS_POR_NIVEL = 10;
    constexpr int PONTOS_SOFT_DROP = 1;
    constexpr int PONTOS_HARD_DROP = 2;
}

long long Score::getPoints() const {
    return pontos;
}

int Score::getLevel() const {
    return nivel;
}

int Score::getLinesCleared() const {
    return linhasEliminadas;
}

void Score::addLineClear(int linhas) {
    if (linhas < 0 || linhas > MAX_LINHAS) {
        throw std::invalid_argument("Numero de linhas invalido");
    }
    if (linhas == 0) {
        return;
    }

    // Usa o nivel atual, antes de ser atualizado (comportamento classico)
    pontos += static_cast<long long>(PONTUACAO_LINHAS[linhas]) * nivel;

    linhasEliminadas += linhas;
    nivel = 1 + linhasEliminadas / LINHAS_POR_NIVEL;
}

void Score::addSoftDrop(int distancia) {
    if (distancia < 0) {
        throw std::invalid_argument("Distancia invalida");
    }
    pontos += static_cast<long long>(distancia) * PONTOS_SOFT_DROP;
}

void Score::addHardDrop(int distancia) {
    if (distancia < 0) {
        throw std::invalid_argument("Distancia invalida");
    }
    pontos += static_cast<long long>(distancia) * PONTOS_HARD_DROP;
}

void Score::reset() {
    pontos = 0;
    nivel = 1;
    linhasEliminadas = 0;
}
