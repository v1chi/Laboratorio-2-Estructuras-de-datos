#include <iostream>
#include <limits>
#include <vector>
#include "Tablero.h"

struct Nodo {
    Tablero estadoTablero;
    int columna;
    int valor;

    Nodo(const Tablero& tablero, int col, int val) : estadoTablero(tablero), columna(col), valor(val) {}
};

class JugadorIA {
private:
    char jugadorIA;
    char jugadorHumano;
    int profundidadMaxima;

public:
    JugadorIA(char jugadorIA, char jugadorHumano, int profundidadMaxima)
        : jugadorIA(jugadorIA), jugadorHumano(jugadorHumano), profundidadMaxima(profundidadMaxima) {}

    int evaluarNodo(const Nodo& nodo) {
        return nodo.estadoTablero.evaluarTablero(nodo.estadoTablero);
    }

    Nodo minimax(Tablero& tablero, int profundidad, int alfa, int beta, bool esMaximizador) {
        char ganador = tablero.verificarGanador();
        if (ganador == jugadorIA) {
            return Nodo(tablero, -1, 1);
        } else if (ganador == jugadorHumano) {
            return Nodo(tablero, -1, -1);
        } else if (tablero.tableroLLeno() || profundidad == 0) {
            return Nodo(tablero, -1, 0);
        }

        int mejorValor;
        int mejorColumna;

        if (esMaximizador) {
            mejorValor = std::numeric_limits<int>::min();
            mejorColumna = -1;

            for (int columna = 0; columna < 7; ++columna) {
                if (!tablero.columnaLlena(columna)) {
                    Tablero nuevoTablero = tablero;
                    nuevoTablero.hacerMovimiento(columna, jugadorIA);

                    int valor = minimax(nuevoTablero, profundidad - 1, alfa, beta, false).valor;

                    if (valor > mejorValor) {
                        mejorValor = valor;
                        mejorColumna = columna;
                    }

                    alfa = std::max(alfa, mejorValor);
                    if (beta <= alfa) {
                        break;  // Poda alfa-beta
                    }
                }
            }
        } else {
            mejorValor = std::numeric_limits<int>::max();
            mejorColumna = -1;

            for (int columna = 0; columna < 7; ++columna) {
                if (!tablero.columnaLlena(columna)) {
                    Tablero nuevoTablero = tablero;
                    nuevoTablero.hacerMovimiento(columna, jugadorHumano);

                    int valor = minimax(nuevoTablero, profundidad - 1, alfa, beta, true).valor;

                    if (valor < mejorValor) {
                        mejorValor = valor;
                        mejorColumna = columna;
                    }

                    beta = std::min(beta, mejorValor);
                    if (beta <= alfa) {
                        break;  // Poda alfa-beta
                    }
                }
            }
        }

        return Nodo(tablero, mejorColumna, mejorValor);
    }

    int tomarDecision(Tablero& tablero) {
        int alfa = std::numeric_limits<int>::min();
        int beta = std::numeric_limits<int>::max();
        return minimax(tablero, profundidadMaxima, alfa, beta, true).columna;
    }
};
