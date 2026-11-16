#ifndef SCORE_H
#define SCORE_H

/**
 * Gere a pontuacao de um jogo tipo Tetris:
 * pontos, nivel e linhas eliminadas.
 */
class Score {
private:
    long long pontos = 0;
    int nivel = 1;
    int linhasEliminadas = 0;

public:
    Score() = default;

    long long getPoints() const;
    int getLevel() const;
    int getLinesCleared() const;

    /**
     * Regista a eliminacao de linhas (0 a 4).
     * Os pontos usam o nivel ATUAL (antes de eventual subida de nivel).
     * 0 linhas nao faz nada. Lanca std::invalid_argument se fora de 0..4.
     */
    void addLineClear(int linhas);

    /** 1 ponto por celula descida com soft drop. distancia em celulas, >= 0. */
    void addSoftDrop(int distancia);

    /** 2 pontos por celula descida com hard drop. distancia em celulas, >= 0. */
    void addHardDrop(int distancia);

    /** Volta ao estado inicial: 0 pontos, nivel 1, 0 linhas. */
    void reset();
};

#endif // SCORE_H
