#ifndef POSICAO_H
#define POSICAO_H

class Posicao {
private:
    int x;
    int y;

public:
    Posicao(int x = 0, int y = 0) : x(x), y(y) {}

    Posicao getPosition() const { return *this; } //Posiçao das peças 
    int getX() const { return x; }
    int getY() const { return y; }

    Posicao somar(const Posicao& delta) const { //Variação da posição
        return Posicao(x + delta.x, y + delta.y);
    }
};

#endif