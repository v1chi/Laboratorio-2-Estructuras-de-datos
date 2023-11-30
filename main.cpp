
#include <bits/stdc++.h>
#include <fstream>
#include <sstream>
using namespace std;


void GuardarPartida(char tablero[6][7], const string &nombreArchivo) {
    ofstream archivo(nombreArchivo);
    if (archivo.is_open()) {
        for (int i = 0; i < 6; ++i) {
            for (int j = 0; j < 7; ++j) {
                archivo << tablero[i][j] << ",";
            }
            archivo << "\n";
        }
        archivo.close();
        cout << "Partida guardada correctamente.\n";
    } else {
        cerr << "Error al abrir el archivo para guardar la partida.\n";
    }
}

void CargarPartida(char tablero[6][7], const string &nombreArchivo) {
    ifstream archivo(nombreArchivo);
    if (archivo.is_open()) {
        for (int i = 0; i < 6; ++i) {
            string fila;
            if (getline(archivo, fila)) {
                istringstream iss(fila);
                char c;
                for (int j = 0; j < 7; ++j) {
                    if (iss >> c) {
                        tablero[i][j] = c;
                        iss.ignore(); // Ignorar la coma
                    }
                }
            }
        }
        archivo.close();
        cout << "Partida cargada correctamente.\n";
    } else {
        cerr << "Error al abrir el archivo para cargar la partida.\n";
    }
}

int main() {
    char tablero[6][7] = {0};
    //NuevaPartida(tablero);

    string archivoPartida = "partida.csv";
    string archivoPuntuacion = "puntuacion.csv";

    int opcion;
    do {
        cout << "Menú Principal:\n";
        cout << "1. Jugar una partida\n";
        cout << "2. Ver puntuación jugador vs máquina\n";
        cout << "3. Guardar partida\n";
        cout << "4. Cargar partida\n";
        cout << "5. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1: {
                char dificultad;
                cout << "Seleccione la dificultad (Fácil: F, Medio: M, Difícil: D): ";
                cin >> dificultad;

                int profundidadMaxima;
                switch (dificultad) {
                    case 'F':
                    case 'f':
                        //algo
                        break;
                    case 'M':
                    case 'm':
                        //algo
                        break;
                    case 'D':
                    case 'd':
                        //algo
                        break;
                    default:
                        cout << "Dificultad no válida.\n";
                        continue;
                }

                // Lógica del juego 
                
                break;
            }
            case 2: {
                // Ver puntuación jugador vs máquina 
                break;
            }
            case 3: {
                GuardarPartida(tablero, archivoPartida);
                break;
            }
            case 4: {
                CargarPartida(tablero, archivoPartida);
                break;
            }
            case 5:
                cout << "¡Hasta luego!\n";
                break;
            default:
                cout << "Opción no válida. Inténtelo de nuevo.\n";
        }

    } while (opcion != 5);

    return 0;
}
