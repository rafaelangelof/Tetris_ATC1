#include <curses.h>
#include <chrono>
#include <thread>
#include "PeçaT.h"
#include "PeçaO.h"
#include <windows.h>

// Dimensões padrão do tabuleiro de Tetris
const int LARGURA_TAB = 10;
const int ALTURA_TAB = 20;

// Função de desenho (Camada UI) separada da lógica
static void desenharJogo(const Peca& pecaAtiva) {
    erase();

    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);

    // Centrar a área de jogo no ecrã (cada célula tem 2 colunas de largura)
    int origem_x = (max_x - (LARGURA_TAB * 2)) / 2;
    int origem_y = (max_y - ALTURA_TAB) / 2;

    // Desenhar moldura do tabuleiro
    attron(COLOR_PAIR(3));
    for (int y = 0; y < ALTURA_TAB; ++y) {
        mvaddch(origem_y + y, origem_x - 1, 219);
        mvaddch(origem_y + y, origem_x + (LARGURA_TAB * 2), 219);
    }
    for (int x = 0; x <= LARGURA_TAB * 2 + 1; ++x) {
        mvaddch(origem_y + ALTURA_TAB, origem_x - 1 + x, 219);
    }
    attroff(COLOR_PAIR(3));

    // Desenhar todos os blocos absolutos da peça ativa
    attron(COLOR_PAIR(pecaAtiva.getCor()));
    std::vector<Posicao> blocos = pecaAtiva.obterBlocosAbsolutos();
    for (size_t i = 0; i < blocos.size(); ++i) {
        int tela_x = origem_x + (blocos[i].getX() * 2);
        int tela_y = origem_y + blocos[i].getY();

        if (blocos[i].getY() >= 0 && blocos[i].getY() < ALTURA_TAB &&
            blocos[i].getX() >= 0 && blocos[i].getX() < LARGURA_TAB) {
            mvprintw(tela_y, tela_x, "  ");
        }
    }
    attroff(COLOR_PAIR(pecaAtiva.getCor()));

    refresh();
}

int main() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE); // getch() não-bloqueante
    curs_set(0);

    if (has_colors()) {
        start_color();
        init_pair(1, COLOR_MAGENTA, COLOR_MAGENTA); // Peça T
        init_pair(2, COLOR_YELLOW, COLOR_YELLOW);   // Peça O
        init_pair(3, COLOR_WHITE, COLOR_BLACK);     // Moldura
    }

    // Criar uma peça T derivada
    PecaO peca(Posicao(4, 0));

    // Temporização conforme guião: frequência base e submúltiplo para a gravidade
    const int FPS = 60;
    const int FRAMES_PARA_DESCER = 30; // Desce a cada 30 iterações (0.5s)
    int contadorFrames = 0;
    bool a_correr = true;

    while (a_correr) {
        // Input teclado
        int tecla = getch();
        switch (tecla) {
        case KEY_LEFT:
        case 'a':
        case 'A':
            peca.moverEsquerda();
            break;
        case KEY_RIGHT:
        case 'd':
        case 'D':
            peca.moverDireita();
            break;
        case KEY_DOWN:
        case 's':
        case 'S':
            peca.descer();
            break;
        case 'q':
        case 'Q':
        case 27: // ESC
            a_correr = false;
            break;
        }

        // Contador de frames 
        contadorFrames++;
        if (contadorFrames >= FRAMES_PARA_DESCER) {
            peca.descer();
            contadorFrames = 0;
        }

        // Renderização
        desenharJogo(peca);

        // Cadência de 60 frames por segundo
        std::this_thread::sleep_for(std::chrono::milliseconds(1000 / FPS));
    }

    endwin();
    return 0;
}