
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
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

// Función para convertir el tablero en una cadena para almacenar en archivos CSV
string convertirTableroAString(char partida[6][7]) {
    stringstream ss;
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 7; j++) {
            ss << partida[i][j] << " ";
        }
    }
    return ss.str();
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

// Función para cargar una partida desde un archivo CSV
// Función para cargar una partida desde un archivo CSV
void cargarPartida(char partida[6][7]) {
    ifstream archivo("ultima_partida.csv");

    if (archivo.is_open()) {
        for (int i = 0; i < 6; i++) {
            string fila;
            getline(archivo, fila);  // Leer toda la línea como una cadena

            istringstream ss(fila);
            for (int j = 0; j < 7; j++) {
                ss >> partida[i][j];
            }
        }

        archivo.close();
    } else {
        cout << "No se pudo abrir el archivo de partida guardada.\n";
    }
}

// Función para guardar una partida en el historial de partidas
void guardarEnHistorial(char partida[6][7], int ganador) {
    ofstream archivoHistorial("historial_partidas.csv", ios::app);

    if (archivoHistorial.is_open()) {
        archivoHistorial << convertirTableroAString(partida) << "," << ganador << "\n";
        archivoHistorial.close();
    } else {
        cout << "No se pudo abrir el archivo de historial de partidas.\n";
    }
}

void reiniciarTablero(char partida[6][7]) {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 7; j++) {
            partida[i][j] = ' ';
        }
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
    int ganadasIA = 0, ganadasJugador = 0;

    while (true) {
        cout << "---------------------------------------------" << endl;
        std::cout << "Menú:\n";
        std::cout << "1. Jugar contra la IA\n";
        std::cout << "2. Cargar partida\n";
        std::cout << "3. Ver historial de partidas\n";
        std::cout << "4. Ver puntuacion maquina vs jugador\n";
        std::cout << "5. Salir\n";
        std::cout << "Seleccione una opción: "<< endl;
        cout << "---------------------------------------------" << endl;
        
        int opcion;
        std::cin >> opcion;
        char jugador = 'X', ia = 'O';

        if (opcion == 1) {
            // Jugar contra la IA
            int dificultad;
            std::cout << "Seleccione la dificultad (1: Fácil, 2: Medio, 3: Difícil): ";
            std::cin >> dificultad;

            std::cout << "¿Quiere empezar primero? (1: Si, 0: No): ";
            int jugadorPrimero;
            std::cin >> jugadorPrimero;
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
                            ganadasJugador++;
                            guardarEnHistorial(tablero, (victoria(tablero, 'O') ? 1 : (victoria(tablero, 'X') ? 2 : 0)));
                            reiniciarTablero(tablero);
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
                        ganadasIA++;
                        guardarEnHistorial(tablero, (victoria(tablero, 'O') ? 1 : (victoria(tablero, 'X') ? 2 : 0)));
                        reiniciarTablero(tablero);
                        break;
                    }
                    
                    cout << "Desea salir? (1.Si 2.No)" << endl;
                    int salirPartida;
                    cin >> salirPartida;
                    if(salirPartida == 1){
                        guardarPartida(tablero);
                        reiniciarTablero(tablero);
                        break;
                    }
                    else{
                        continue;
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
                        ganadasIA++;
                        guardarEnHistorial(tablero, (victoria(tablero, 'O') ? 1 : (victoria(tablero, 'X') ? 2 : 0)));
                        reiniciarTablero(tablero);
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
                            ganadasJugador++;
                            guardarEnHistorial(tablero, (victoria(tablero, 'O') ? 1 : (victoria(tablero, 'X') ? 2 : 0)));
                            reiniciarTablero(tablero);
                            break;
                        }
                    } else {
                        std::cout << "Columna no válida. Inténtelo de nuevo.\n";
                        continue;
                    }
                    
                    cout << "Desea salir? (1.Si 2.No)" << endl;
                    int salirPartida;
                    cin >> salirPartida;
                    if(salirPartida == 1){
                        guardarPartida(tablero);
                        reiniciarTablero(tablero);
                        break;
                    }
                    else{
                        continue;
                    }
                }
            }
        } else if (opcion == 2) {
            cargarPartida(tablero);
            imprimirJuego(tablero);
            while(true){
                int dificultad;
                std::cout << "Seleccione la dificultad (1: Fácil, 2: Medio, 3: Difícil): ";
                std::cin >> dificultad;
                
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
                        ganadasJugador++;
                        guardarEnHistorial(tablero, (victoria(tablero, 'O') ? 1 : (victoria(tablero, 'X') ? 2 : 0)));
                        reiniciarTablero(tablero);
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
                    ganadasIA++;
                    guardarEnHistorial(tablero, (victoria(tablero, 'O') ? 1 : (victoria(tablero, 'X') ? 2 : 0)));
                    reiniciarTablero(tablero);
                    break;
                }
                        
                cout << "Desea salir? (1.Si 2.No)" << endl;
                int salirPartida;
                cin >> salirPartida;
                if(salirPartida == 1){
                    guardarPartida(tablero);
                    reiniciarTablero(tablero);
                    break;
                }
                else{
                    continue;
                }
            }
            
        } else if (opcion == 3) {
            cout << "No disponible por el momento" << endl;
        } else if (opcion == 4) {
             cout << "Ver puntuacion maquina vs jugador" << endl;
             cout << "Puntaje maquina: " << ganadasIA << endl;
             cout << "Puntaje jugador: " << ganadasJugador << endl;
        } else if (opcion == 5) {
            std::cout << "Hasta luego.\n";
            break;
        } else {
            std::cout << "Opción no válida. Inténtelo de nuevo.\n";
        }
    }
    return 0;
}