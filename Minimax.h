#include <iostream>
#include <climits>
#include <vector>

using namespace std;

struct Nodo {
    struct Nodo** hijos;
    int* movimientos;
    int n_hijos;
    char tablero[6][7];
    double valor;
    int nivel;
};

class Minimax {
public:
    Minimax();
    ~Minimax();
    int ElegirMejorTirada(char partida[6][7], int dificultad);
    static const int FACIL = 1;
    static const int MEDIO = 2;
    static const int DIFICIL = 3;

    
private:
    void copiarTablero(char tablero1[6][7], char tablero2[6][7]);
    Nodo crearNodo(char tablero[6][7], int nivel, int dificultad, int posibilidades, bool victoriaIA, bool victoriaJugador);
    void crearNivel(Nodo* Padre, char ficha, int dificultad, int posibilidades, bool victoriaIA, bool victoriaJugador);
    void crearDobleNivel(Nodo* raiz, int dificultad, int posibilidades, bool victoriaIA, bool victoriaJugador);
    void crearArbol(Nodo* raiz, int profundidad, int dificultad, int posibilidades, bool victoriaIA, bool victoriaJugador);
    void BorraArbol(Nodo* raiz);
    double Heuristica(char partida[6][7]);
    double minimax(Nodo* raiz, int profundidad, double alfa, double beta, bool esMaximizador);
    int ElegirTiradaDificultad(char partida[6][7], int dificultad);
    void tirar(char partida[6][7], int columna, char ficha);
    int victoria(char partida[6][7], char ficha);
    int posibilidades(char partida[6][7]);

};

Minimax::Minimax() {}

Minimax::~Minimax() {}

void Minimax::copiarTablero(char tablero1[6][7], char tablero2[6][7]) {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 7; j++) {
            tablero2[i][j] = tablero1[i][j];
        }
    }
}

Nodo Minimax::crearNodo(char tablero[6][7], int nivel, int dificultad, int posibilidades, bool victoriaIA, bool victoriaJugador) {
    int i;
    int j = 0;
    Nodo p;

    p.nivel = nivel;
    copiarTablero(tablero, p.tablero);
    p.n_hijos = posibilidades;
    p.valor = Heuristica(p.tablero);
    if (victoriaIA || victoriaJugador || p.nivel == 2 * dificultad + 2) {
        p.n_hijos = 0;
    }

    if (p.n_hijos != 0) {
        p.hijos = new Nodo*[p.n_hijos];
        p.movimientos = new int[p.n_hijos];
        for (i = 0; i < 7; ++i) {
            if (tablero[0][i] == ' ') {
                p.movimientos[j] = i;
                ++j;
            }
        }
    } else {
        p.hijos = nullptr;
        p.movimientos = nullptr;
    }

    return p;
}

void Minimax::crearNivel(Nodo* Padre, char ficha, int dificultad, int posibilidades, bool victoriaIA, bool victoriaJugador) {
    for (int i = 0; i < Padre->n_hijos; ++i) {
        Nodo* Hijo = new Nodo;
        copiarTablero(Padre->tablero, Hijo->tablero);
        tirar(Hijo->tablero, Padre->movimientos[i], ficha);
        *Hijo = crearNodo(Hijo->tablero, Padre->nivel + 1, dificultad, posibilidades, victoriaIA, victoriaJugador);
        Padre->hijos[i] = Hijo;
    }
}
void Minimax::crearDobleNivel(Nodo* raiz, int dificultad, int posibilidades, bool victoriaIA, bool victoriaJugador) {
    crearNivel(raiz, 'X', dificultad, posibilidades, victoriaIA, victoriaJugador);
    for (int i = 0; i < raiz->n_hijos; ++i) {
        crearNivel(raiz->hijos[i], 'O', dificultad, posibilidades, victoriaIA, victoriaJugador);
    }
}

void Minimax::crearArbol(Nodo* raiz, int profundidad, int dificultad, int posibilidades, bool victoriaIA, bool victoriaJugador) {
    crearDobleNivel(raiz, dificultad, posibilidades, victoriaIA, victoriaJugador);
    if (profundidad == 0) return;
    else {
        for (int i = 0; i < raiz->n_hijos; ++i) {
            for (int j = 0; j < raiz->hijos[i]->n_hijos; ++j) {
                crearArbol(raiz->hijos[i]->hijos[j], profundidad - 1, dificultad, posibilidades, victoriaIA, victoriaJugador);
            }
        }
    }
}

void Minimax::BorraArbol(Nodo* raiz) {
    if (raiz->n_hijos == 0) {
        delete raiz;
    } else {
        for (int i = 0; i < raiz->n_hijos; ++i) {
            BorraArbol(raiz->hijos[i]);
        }
        delete[] raiz->hijos;
        delete[] raiz->movimientos;
    }
}

double Minimax::Heuristica(char partida[6][7]) {
    if (victoria(partida, 'X')) return 1000;
    if (victoria(partida, 'O')) return -1000;
    else return 0;
}

double Minimax::minimax(Nodo* raiz, int profundidad, double alfa, double beta, bool esMaximizador) {
    if (profundidad == 0 || raiz->nivel == 0) {
        return raiz->valor;
    }

    if (esMaximizador) {
        double maxEval = -9999999;
        for (int i = 0; i < raiz->n_hijos; ++i) {
            double eval = minimax(raiz->hijos[i], profundidad - 1, alfa, beta, false);
            maxEval = max(maxEval, eval);
            alfa = max(alfa, eval);
            if (beta <= alfa) break;
        }
        return maxEval;
    } else {
        double minEval = 999999;
        for (int i = 0; i < raiz->n_hijos; ++i) {
            double eval = minimax(raiz->hijos[i], profundidad - 1, alfa, beta, true);
            minEval = min(minEval, eval);
            beta = min(beta, eval);
            if (beta <= alfa) break;
        }
        return minEval;
    }
}

int Minimax::ElegirTiradaDificultad(char partida[6][7], int dificultad) {
    Nodo raiz = crearNodo(partida, 0, dificultad, posibilidades(partida), false, false);
    int profundidad = 3;
    crearArbol(&raiz, profundidad, dificultad, posibilidades(partida), false, false);

    int mejorTirada = -1;
    double mejorValor = -999999;

    for (int i = 0; i < raiz.n_hijos; ++i) {
        double valor = minimax(raiz.hijos[i], dificultad, -99999, 99999, false);
        if (valor > mejorValor) {
            mejorValor = valor;
            mejorTirada = raiz.movimientos[i];
        }
    }

    BorraArbol(&raiz);
    return mejorTirada;
}

int Minimax::ElegirMejorTirada(char partida[6][7], int dificultad) {
    switch (dificultad) {
        case FACIL:
            // Implementa lógica para dificultad fácil (puedes ajustarla según sea necesario)
            return ElegirTiradaDificultad(partida, dificultad);
        case MEDIO:
            // Implementa lógica para dificultad medio (puedes ajustarla según sea necesario)
            return ElegirTiradaDificultad(partida, dificultad);
        case DIFICIL:
            // Implementa lógica para dificultad difícil (puedes ajustarla según sea necesario)
            return ElegirTiradaDificultad(partida, dificultad);
        default:
            cerr << "Dificultad no válida" << endl;
            return -1;
    }
}

void Minimax::tirar(char partida[6][7], int columna, char ficha) {
    for (int i = 0; i < 6; i++) {
        if (partida[6 - 1 - i][columna] == ' ') {
            partida[6 - 1 - i][columna] = ficha;
            break;
        }
    }
}

int Minimax::victoria(char partida[6][7], char ficha) {
    int i, j;

    // Chequeo horizontal
    for (i = 0; i < 6; i++) {
        for (j = 0; j < (7 - 3); j++) {
            if (partida[i][j] == ficha && partida[i][j + 1] == ficha &&
                partida[i][j + 2] == ficha && partida[i][j + 3] == ficha) {
                return 1;
            }
        }
    }

    // Chequeo vertical
    for (j = 0; j < 7; j++) {
        for (i = 0; i < (6 - 3); i++) {
            if (partida[i][j] == ficha && partida[i + 1][j] == ficha &&
                partida[i + 2][j] == ficha && partida[i + 3][j] == ficha) {
                return 1;
            }
        }
    }

    // Chequeo diagonal principal
    for (i = 0; i < (6 - 3); i++) {
        for (j = 0; j < (7 - 3); j++) {
            if (partida[i][j] == ficha && partida[i + 1][j + 1] == ficha &&
                partida[i + 2][j + 2] == ficha && partida[i + 3][j + 3] == ficha) {
                return 1;
            }
        }
    }

    // Chequeo diagonal contraria
    for (i = 0; i < 6; i++) {
        for (j = 7 - 1; j > 2; j--) {
            if (partida[i][j] == ficha && partida[i + 1][j - 1] == ficha &&
                partida[i + 2][j - 2] == ficha && partida[i + 3][j - 3] == ficha) {
                return 1;
            }
        }
    }

    return 0;
}

int Minimax::posibilidades(char partida[6][7]) {
    int j;
    int cont = 0;

    for (j = 0; j < 7; j++) {
        if (partida[0][j] == ' ') {
            cont += 1;
        }
    }

    return cont;
}