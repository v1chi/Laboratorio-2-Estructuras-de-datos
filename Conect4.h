#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include "Arbol.h"

class Conect4 {
    public:
        char tablero[6][7]; // Matriz del tablero
        int puntuacionJugador;
        int puntuacionIA;
        int profundidad;
        std::string archivoCSV; // Nombre del archivo CSV

        // Constructor
        Conect4();

        // Funciones del juego
        void imprimirTablero();
        void setProfundidad(int);
        bool realizarMovimiento(int, char);
        bool verificarVictoria(char);
        void guardarPartida();
        void cargarPartida();
        int obtenerColumnaIA();
        int evaluarTablero();
        int evaluarVentana(char, char, char, char);

    };

Conect4::Conect4() : puntuacionJugador(0), puntuacionIA(0), archivoCSV("partidas.csv") {
    // Inicializar el tablero
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 7; ++j) {
            tablero[i][j] = ' ';
        }
    }
}

void Conect4::imprimirTablero() {
    std::cout << "\n 1 2 3 4 5 6 7\n";
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 7; ++j) {
            std::cout << "|" << tablero[i][j];
        }
        std::cout << "|\n";
    }
    std::cout << "---------------\n";
}

void Conect4::setProfundidad(int pr) {
    profundidad = pr;
}

bool Conect4::realizarMovimiento(int columna, char jugador) {
    // Retorna true si el movimiento es válido, false si no lo es
    columna--; // Ajustar la columna a índice base 0

    if (columna < 0 || columna >= 7 || tablero[0][columna] != ' ') {
        std::cout << "Movimiento inválido. Inténtalo de nuevo.\n";
        return false;
    }

    // Buscar la fila disponible para el movimiento
    int fila = 5;
    while (fila >= 0 && tablero[fila][columna] != ' ') {
        fila--;
    }

    // Realizar el movimiento
    tablero[fila][columna] = jugador;
    return true;
}

bool Conect4::verificarVictoria(char jugador) {
    // Verificar victoria horizontal
    for (int fila = 0; fila < 6; ++fila) {
        for (int col = 0; col < 4; ++col) {
            if (tablero[fila][col] == jugador && tablero[fila][col + 1] == jugador && tablero[fila][col + 2] == jugador && tablero[fila][col + 3] == jugador) {
                return true;
            }
        }
    }

    // Verificar victoria vertical
    for (int col = 0; col < 7; ++col) {
        for (int fila = 0; fila < 3; ++fila) {
            if (tablero[fila][col] == jugador && tablero[fila + 1][col] == jugador && tablero[fila + 2][col] == jugador && tablero[fila + 3][col] == jugador) {
                return true;
            }
        }
    }

    // Verificar victoria en diagonal (ascendente)
    for (int fila = 3; fila < 6; ++fila) {
        for (int col = 0; col < 4; ++col) {
            if (tablero[fila][col] == jugador && tablero[fila - 1][col + 1] == jugador && tablero[fila - 2][col + 2] == jugador && tablero[fila - 3][col + 3] == jugador) {
                return true;
            }
        }
    }

    // Verificar victoria en diagonal (descendente)
    for (int fila = 0; fila < 3; ++fila) {
        for (int col = 0; col < 4; ++col) {
            if (tablero[fila][col] == jugador && tablero[fila + 1][col + 1] == jugador && tablero[fila + 2][col + 2] == jugador && tablero[fila + 3][col + 3] == jugador) {
                return true;
            }
        }
    }

    return false;
}

void Conect4::guardarPartida() {
    std::ofstream archivo(archivoCSV, std::ios::app);

    if (archivo.is_open()) {
        for (int i = 0; i < 6; ++i) {
            for (int j = 0; j < 7; ++j) {
                archivo << tablero[i][j] << ",";
            }
        }
        archivo << "\n";
        archivo.close();
        std::cout << "Partida guardada exitosamente.\n";
    } else {
        std::cout << "Error al guardar la partida.\n";
    }
}

void Conect4::cargarPartida() {
    std::ifstream archivo(archivoCSV);

    if (archivo.is_open()) {
        // Lee la última línea del archivo y actualiza el tablero
        std::string ultimaLinea;
        while (archivo >> ultimaLinea);
        archivo.close();

        int k = 0;
        for (int i = 0; i < 6; ++i) {
            for (int j = 0; j < 7; ++j) {
                tablero[i][j] = ultimaLinea[k];
                k += 2;
            }
        }

        std::cout << "Partida cargada exitosamente.\n";
    } else {
        std::cout << "Error al cargar la partida.\n";
    }
}

int Conect4::obtenerColumnaIA() {
    // Implementa la lógica para que la IA elija la columna utilizando el algoritmo Minimax
    // y considerando la dificultad

    int mejorColumna = -1;
    int mejorValor = std::numeric_limits<int>::min();
    int profundidad = 4;  // Profundidad de búsqueda predeterminada

    // Ajustar la profundidad según la dificultad
    if (dificultad == 1) {
        profundidad = 2;
    } else if (dificultad == 3) {
        profundidad = 6;
    }

    // Generar árbol de posibles movimientos
    arbolIA.raiz = new Nodo();
    arbolIA.generarArbol(arbolIA.raiz, profundidad, true);

    // Evaluar y seleccionar el mejor movimiento
    for (Nodo* hijo : arbolIA.raiz->hijos) {
        int valor = arbolIA.minimax(hijo, profundidad, std::numeric_limits<int>::min(), std::numeric_limits<int>::max(), false);
        if (valor > mejorValor) {
            mejorValor = valor;
            // Obtener la columna del primer hijo con el mejor valor
            mejorColumna = hijo->hijos[0]->valor;
        }
    }

    // Liberar la memoria del árbol
    arbolIA.liberarArbol(arbolIA.raiz);

    return mejorColumna;
};

int Conect4::evaluarTablero() {
    int puntuacion = 0;

    // Evaluar horizontalmente
    for (int fila = 0; fila < 6; ++fila) {
        for (int col = 0; col < 4; ++col) {
            puntuacion += evaluarVentana(tablero[fila][col], tablero[fila][col + 1], tablero[fila][col + 2], tablero[fila][col + 3]);
        }
    }

    // Evaluar verticalmente
    for (int col = 0; col < 7; ++col) {
        for (int fila = 0; fila < 3; ++fila) {
            puntuacion += evaluarVentana(tablero[fila][col], tablero[fila + 1][col], tablero[fila + 2][col], tablero[fila + 3][col]);
        }
    }

    // Evaluar en diagonal (ascendente)
    for (int fila = 3; fila < 6; ++fila) {
        for (int col = 0; col < 4; ++col) {
            puntuacion += evaluarVentana(tablero[fila][col], tablero[fila - 1][col + 1], tablero[fila - 2][col + 2], tablero[fila - 3][col + 3]);
        }
    }

    // Evaluar en diagonal (descendente)
    for (int fila = 0; fila < 3; ++fila) {
        for (int col = 0; col < 4; ++col) {
            puntuacion += evaluarVentana(tablero[fila][col], tablero[fila + 1][col + 1], tablero[fila + 2][col + 2], tablero[fila + 3][col + 3]);
        }
    }

    return puntuacion;
}

int Conect4::evaluarVentana(char c1, char c2, char c3, char c4) {
    int puntuacion = 0;

    // Evaluar la ventana de cuatro fichas
    // Otorgar puntajes según la configuración, por ejemplo:
    // Dos en línea: +10
    // Tres en línea: +100
    // Cuatro en línea: +1000

    if (c1 == 'X') {
        if (c2 == 'X' && c3 == 'X' && c4 == 'X') {
            puntuacion += 1000;
        } else if (c2 == 'X' && c3 == 'X') {
            puntuacion += 100;
        } else if (c2 == 'X') {
            puntuacion += 10;
        }
    } else if (c1 == 'O') {
        if (c2 == 'O' && c3 == 'O' && c4 == 'O') {
            puntuacion -= 1000;
        } else if (c2 == 'O' && c3 == 'O') {
            puntuacion -= 100;
        } else if (c2 == 'O') {
            puntuacion -= 10;
        }
    }

    return puntuacion;
}