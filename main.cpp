
#include <iostream>
#include <vector>
#include <fstream>
#include "Minimax.h"
using namespace std;



// Función para imprimir el tablero
void imprimirJuego(char partida[6][7]) {
    int i, j;

    cout << "  ";
    for (i = 0; i < 7; i++) std::cout << i + 1 << "   ";
    cout << "\n  ";

    for (i = 0; i < 6; i++) {
        std::cout << " ";
        for (j = 0; j < 7; j++) std::cout << "--- ";
        std::cout << "\n";
        std::cout << "|";
        for (j = 0; j < 7; j++) std::cout << " " << partida[i][j] << " |";
        std::cout << "\n";
    }

    std::cout << " ";
    for (i = 0; i < 7; i++) std::cout << "--- ";
    std::cout << "\n";
}

// Función para contar las posibilidades de movimiento
int posibilidades(char partida[6][7]) {
    int j;
    int cont = 0;

    for (j = 0; j < 7; j++) {
        if (partida[0][j] == ' ') {
            cont += 1;
        }
    }

    return cont;
}

// Función para verificar la victoria de la CPU
int victoria(char partida[6][7], char ficha) {
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
    for (j = 0; j < 6; j++) {
        for (i = 0; i < (7 - 3); i++) {
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

// Función para aplicar la tirada del jugador o la CPU
void tirar(char partida[6][7], int columna, char ficha) {
    for (int i = 0; i < 6; i++) {
        if (partida[6 - 1 - i][columna] == ' ') {
            partida[6 - 1 - i][columna] = ficha;
            break;
        }
    }
}

// Función heurística para evaluar la posición actual del tablero
double Heuristica(char partida[6][7]) {
    if (victoria(partida, 'X')) return 1000;
    if (victoria(partida, 'O')) return -1000;
    else return 0;
}

// Función para cargar la última partida desde un archivo CSV
void cargarUltimaPartida(char partida[6][7]) {
    ifstream archivo("ultima_partida.csv");

    if (archivo.is_open()) {
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 7; j++) {
                archivo >> partida[i][j];
            }
        }

        archivo.close();
    }
}

// Función para guardar la partida actual en un archivo CSV
void guardarPartida(char partida[6][7]) {
    ofstream archivo("ultima_partida.csv");

    if (archivo.is_open()) {
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 7; j++) {
                archivo << partida[i][j] << " ";
            }
            archivo << endl;
        }

        archivo.close();
    }
}


// Función para cargar el historial de partidas desde un archivo CSV
void cargarHistorial(vector<string>& historial) {
    ifstream archivo("historial_partidas.csv");

    historial.clear();  // Limpiar el vector antes de cargar nuevas partidas

    if (archivo.is_open()) {
        string linea;
        while (getline(archivo, linea)) {
            historial.push_back(linea);
        }

        archivo.close();
    }
}

// Función para actualizar las estadísticas de victorias en un archivo CSV
void actualizarEstadisticas(char ganador) {
    ifstream archivo("estadisticas.csv");
    int victoriasIA, victoriasJugador;

    if (archivo.is_open()) {
        archivo >> victoriasIA >> victoriasJugador;
        archivo.close();

        if (ganador == 'O') {
            victoriasIA++;
        } else if (ganador == 'X') {
            victoriasJugador++;
        }

        ofstream nuevoArchivo("estadisticas.csv");
        nuevoArchivo << victoriasIA << " " << victoriasJugador;
        nuevoArchivo.close();
    }
}

void mostrarEstadisticasYHistorial() {
    ifstream estadisticasArchivo("estadisticas.csv");
    ifstream historialArchivo("historial_partidas.csv");

    int victoriasIA, victoriasJugador;

    if (estadisticasArchivo.is_open()) {
        estadisticasArchivo >> victoriasIA >> victoriasJugador;
        estadisticasArchivo.close();

        cout << "Estadísticas:\n";
        cout << "Victorias de la IA: " << victoriasIA << "\n";
        cout << "Victorias del jugador: " << victoriasJugador << "\n";
    }

    vector<string> historial;
    cargarHistorial(historial);

    if (!historial.empty()) {
        cout << "\nHistorial de Partidas:\n";
        for (const string& partida : historial) {
            cout << partida << "\n";
        }
    } else {
        cout << "\nNo hay partidas en el historial.\n";
    }
}


int main() {
    Minimax minimax;  // Crear una instancia de la clase Minimax

    char tablero[6][7] = {
        {' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' '}
    };

    while (true) {
        std::cout << "Menú:\n";
        std::cout << "1. Jugar contra la IA\n";
        std::cout << "2. Cargar partida\n";
        std::cout << "3. Ver historial y estadisticas\n";
        std::cout << "4. Salir\n";
        std::cout << "Seleccione una opción: ";

        int opcion;
        std::cin >> opcion;

        if (opcion == 1) {
            // Jugar contra la IA
            int dificultad;
            std::cout << "Seleccione la dificultad (1: Fácil, 2: Medio, 3: Difícil): ";
            std::cin >> dificultad;

            std::cout << "¿Quiere empezar primero? (1: Si, 0: No): ";
            int jugadorPrimero;
            std::cin >> jugadorPrimero;

            char jugador = 'X', ia = 'O';
            imprimirJuego(tablero);

            if (jugadorPrimero == 1) {
                while (true) {
                    // Turno del jugador
                    int columnaJugador;
                    std::cout << "Turno del jugador. Ingrese el número de columna (1-7): ";
                    std::cin >> columnaJugador;

                    // Realizar movimiento del jugador
                    if (columnaJugador >= 1 && columnaJugador <= 7 && tablero[0][columnaJugador-1] == ' ') {
                        tirar(tablero, columnaJugador - 1, jugador);
                        imprimirJuego(tablero);

                        // Verificar victoria del jugador
                        if (victoria(tablero, jugador)) {
                            std::cout << "¡Has ganado! Fin del juego.\n";
                            actualizarEstadisticas('X');
                            guardarPartida(tablero);
                            break;
                        }
                    } else {
                        std::cout << "Columna no válida. Inténtelo de nuevo.\n";
                        continue;
                    }

                    // Turno de la IA
                    int columnaIA = minimax.ElegirMejorTirada(tablero, dificultad) + 1;
                    std::cout << "Turno de la IA. La IA elige la columna " << columnaIA << ".\n";

                    // Realizar movimiento de la IA
                    tirar(tablero, columnaIA - 1, ia);
                    imprimirJuego(tablero);

                    // Verificar victoria de la IA
                    if (victoria(tablero, ia)) {
                        std::cout << "¡La IA ha ganado! Fin del juego.\n";
                        actualizarEstadisticas('O');
                        guardarPartida(tablero);
                        break;
                    }
                }
            } else if (jugadorPrimero == 0) {
                while (true) {
                    // Turno de la IA
                    int columnaIA = minimax.ElegirMejorTirada(tablero, dificultad) + 1;
                    std::cout << "Turno de la IA. La IA elige la columna " << columnaIA << ".\n";

                    // Realizar movimiento de la IA
                    tirar(tablero, columnaIA - 1, ia);
                    imprimirJuego(tablero);

                    // Verificar victoria de la IA
                    if (victoria(tablero, ia)) {
                        std::cout << "¡La IA ha ganado! Fin del juego.\n";
                        actualizarEstadisticas('O');
                        guardarPartida(tablero);
                        break;
                    }

                    // Turno del jugador
                    int columnaJugador;
                    std::cout << "Turno del jugador. Ingrese el número de columna (1-7): ";
                    std::cin >> columnaJugador;

                    // Realizar movimiento del jugador
                    if (columnaJugador >= 1 && columnaJugador <= 7) {
                        tirar(tablero, columnaJugador - 1, jugador);
                        imprimirJuego(tablero);

                        // Verificar victoria del jugador
                        if (victoria(tablero, jugador)) {
                            std::cout << "¡Has ganado! Fin del juego.\n";
                            actualizarEstadisticas('X');
                            guardarPartida(tablero);
                            break;
                        }
                    } else {
                        std::cout << "Columna no válida. Inténtelo de nuevo.\n";
                        continue;
                    }
                }
            }
        } else if (opcion == 2) {
            cargarUltimaPartida(tablero);
            imprimirJuego(tablero);
            
        } else if (opcion == 3) {
            mostrarEstadisticasYHistorial();
        } else if (opcion == 4) {
            std::cout << "Hasta luego.\n";
            break;
        } else {
            std::cout << "Opción no válida. Inténtelo de nuevo.\n";
        }
    }

    return 0;
}