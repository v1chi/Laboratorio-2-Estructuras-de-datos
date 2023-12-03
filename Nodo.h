#pragma once
#include <iostream>
#include <vector>
#include <fstream>

// Clase Nodo
class Nodo {
    public:
        int valor;
        std::vector<Nodo*> hijos;
        Nodo(){
            valor = 0;
        };
        ~Nodo() {
        for (Nodo* hijo : hijos) {
            delete hijo;
        }
    }
};