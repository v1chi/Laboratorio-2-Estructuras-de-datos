#include <bits/stdc++.h>

class Tablero {

private:
    const int filas = 6;
    const int columnas = 7;
    char** tablero;
    vector<int> columnasDisponibles;
    int profundidadMaxima;

public:

    //Constructor
    Tablero() {
        // Inicializar el tablero
        tablero = new char*[filas];
        for (int i = 0; i < filas; ++i) {
            tablero[i] = new char[columnas];
            for (int j = 0; j < columnas; ++j) {
                tablero[i][j] = ' ';
            }
        }

        // Inicializar las columnas disponibles
        columnasDisponibles = std::vector<int>(columnas, filas - 1);
    }

    //Constructor en base a archivo
    Tablero(const std::string& archivo){
         cargarPartida(archivo);
    }

    //Destructor
    ~Tablero() {
        // Liberar memoria del tablero
        for (int i = 0; i < filas; ++i) {
            delete[] tablero[i];
        }
        delete[] tablero;
    }

    //Guardar partida en archivo
    void guardarPartida(const string& archivo) const {
        ofstream salida(archivo);

        if (!salida) {
            cout << "Error al abrir el archivo para guardar la partida." << endl;
            return;
        }

        // Guardar el estado actual del tablero en el archivo
        for (int i = 0; i < filas; ++i) {
            for (int j = 0; j < columnas; ++j) {
                salida << tablero[i][j] << " ";
            }
            salida << "\n";
        }

        salida.close();
        
    }

    //Cargar partida en base a un archivo
    void cargarPartida(const string& archivo) {
        ifstream entrada(archivo);

        if (!entrada) {
            cout << "Error al abrir el archivo para cargar la partida. Se creará un tablero nuevo." << endl;
            return;
        }

        // Cargar el estado del tablero desde el archivo
        for (int i = 0; i < filas; ++i) {
            for (int j = 0; j < columnas; ++j) {
                entrada >> tablero[i][j];
            }
        }

        // Luego de cargar el tablero, verificar el estado
        char ganador = verificarGanador();
        if (ganador != ' ') {
            cout << "La partida cargada ya tiene un ganador: " << ganador << endl;
    }

    entrada.close();
}

    //Imprimir estado del tablero
    void imprimirTablero() const {
        // Imprimir el tablero
        std::cout << std::endl;
        for (int i = 0; i < filas; ++i) {
            for (int j = 0; j < columnas; ++j) {
                std::cout << "|" << tablero[i][j];
            }
            std::cout << "|" << std::endl;
        }

        // Imprimir números de columna
        for (int i = 0; i < columnas; ++i) {
            std::cout << "|" << i + 1;
        }
        std::cout << "|" << std::endl << std::endl;
    }

    // Métodos para configurar la dificultad
    void establecerDificultadFacil() {
        profundidadMaxima = 3; // Profundidad baja para nivel fácil
    }

    void establecerDificultadMedia() {
        profundidadMaxima = 5; // Profundidad intermedia para nivel medio
    }

    void establecerDificultadDificil() {
        profundidadMaxima = 7; // Profundidad alta para nivel difícil
    }

    int getProfundidad(){
        return profundidadMaxima;
    }

    vector<int> columnasDisponibles getColumnasDisponibles(){
        return vector<int> columnasDisponibles;
    }
    
    //Movimiento del jugador
    bool hacerMovimiento(int columna, char jugador) {
        // Verificar si la columna está llena
        if (columnasDisponibles[columna - 1] < 0) {
            cout << "Columna llena. Elige otra columna." << endl;
            return false;
        }

        // Realizar el movimiento
        int fila = columnasDisponibles[columna - 1];
        tablero[fila][columna - 1] = jugador;
        columnasDisponibles[columna - 1]--;

        return true;
    }

    //Verificar si la columna está llena
    bool columnaLlena(int columna) const {
        return columnasDisponibles[columna - 1] < 0;
    }

    //Verificar si el tablero está lleno
    bool tableroLLeno() const {
        // Verificar si el tablero está lleno (empate)
        for (int i = 0; i < columnas; ++i) {
            if (!columnaLlena(i + 1)) {
                return false;
            }
        }
        return true;
        
    };

    //Ver quien ganó
    char verificarGanador() const {
        // Verificar líneas horizontales
        for (int i = 0; i < filas; ++i) {
            for (int j = 0; j < columnas - 3; ++j) {
                if (tablero[i][j] == 'X' && tablero[i][j + 1] == 'X' && tablero[i][j + 2] == 'X' && tablero[i][j + 3] == 'X') {
                    return 'X';
                } else if (tablero[i][j] == 'O' && tablero[i][j + 1] == 'O' && tablero[i][j + 2] == 'O' && tablero[i][j + 3] == 'O') {
                    return 'O';
                }
            }
        }

        // Verificar líneas verticales
        for (int i = 0; i < filas - 3; ++i) {
            for (int j = 0; j < columnas; ++j) {
                if (tablero[i][j] == 'X' && tablero[i + 1][j] == 'X' && tablero[i + 2][j] == 'X' && tablero[i + 3][j] == 'X') {
                    return 'X';
                } else if (tablero[i][j] == 'O' && tablero[i + 1][j] == 'O' && tablero[i + 2][j] == 'O' && tablero[i + 3][j] == 'O') {
                    return 'O';
                }
            }
        }

        // Verificar diagonales descendentes (hacia la derecha)
        for (int i = 0; i < filas - 3; ++i) {
            for (int j = 0; j < columnas - 3; ++j) {
                if ((tablero[i][j] == 'X' && tablero[i + 1][j + 1] == 'X' && tablero[i + 2][j + 2] == 'X' && tablero[i + 3][j + 3] == 'X') ||
                    (tablero[i][j] == 'O' && tablero[i + 1][j + 1] == 'O' && tablero[i + 2][j + 2] == 'O' && tablero[i + 3][j + 3] == 'O')) {
                    return tablero[i][j];
                }
            }
        }

        // Verificar diagonales ascendentes (hacia la izquierda)
        for (int i = 3; i < filas; ++i) {
            for (int j = 0; j < columnas - 3; ++j) {
                if ((tablero[i][j] == 'X' && tablero[i - 1][j + 1] == 'X' && tablero[i - 2][j + 2] == 'X' && tablero[i - 3][j + 3] == 'X') ||
                    (tablero[i][j] == 'O' && tablero[i - 1][j + 1] == 'O' && tablero[i - 2][j + 2] == 'O' && tablero[i - 3][j + 3] == 'O')) {
                    return tablero[i][j];
                }
            }
        }

        return ' '; // No hay ganador en ninguna dirección
    }

    int evaluarTablero(const Tablero& tablero) {
        // Evaluar el estado del tablero desde el punto de vista de 'X' y 'O'
        if (tablero.verificarGanador() == 'X') {
            return 1;  // Gana 'X'
        } else if (tablero.verificarGanador() == 'O') {
            return -1;  // Gana 'O'
        } else if (tablero.tableroLLeno()) {
            return 0;  // Empate
        } else {
            return 9999;  // El juego no ha terminado
        }
    }
    
};
