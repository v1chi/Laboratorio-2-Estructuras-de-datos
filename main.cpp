#include <bits/stdc++.h>
#include <fstream>
#include <sstream>
#include "Conect4.h"
#include "ultimoJuego.csv"
using namespace std;

int main() {
    Conect4 juego;

    while (true) {
        std::cout << "Menú:\n";
        std::cout << "1. Jugar contra la IA\n";
        std::cout << "2. Cargar partida\n";
        std::cout << "3. Salir\n";
        std::cout << "Seleccione una opción: ";

        int opcion;
        std::cin >> opcion;

        if (opcion == 1) {
            // Jugar contra la IA
            int dificultad;
            std::cout << "Seleccione la dificultad (1: Fácil, 2: Medio, 3: Difícil): ";
            std::cin >> dificultad;

            // Establecer la profundidad del árbol según la dificultad
            if (dificultad == 1) {
                juego.setProfundidad(2);
            } else if (dificultad == 2) {
                juego.setProfundidad(4);
            } else if (dificultad == 3) {
                juego.setProfundidad(6);
            } else {
                std::cout << "Opción no válida. Saliendo...\n";
                return 0;
            }

            std::cout << "¿Quiere empezar primero? (1: Sí, 0: No): ";
            int jugadorPrimero;
            std::cin >> jugadorPrimero;

            // Lógica para empezar el juego
            // ...

        } else if (opcion == 2) {
            // Cargar partida
            juego.cargarPartida();

            // Preguntar quién quiere continuar (jugador o IA)
            // ...

            // Lógica para continuar el juego
            // ...

        } else if (opcion == 3) {
            std::cout << "Hasta luego.\n";
            return 0;
        } else {
            std::cout << "Opción no válida. Inténtelo de nuevo.\n";
        }
    }

    return 0;
}