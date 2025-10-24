/*
Nombre: César Daniel Aguilar Kuri
Matricula: A01712823
Nombre del Proyecto: Steal a Brainrot!
Materia: Programación de estructuras de datos y algoritmos fundamentales
Profesor: Eduardo Daniel Juárez Pineda
*/

#ifndef STACK_H
#define STACK_H

#include <vector>
#include <string>

using namespace std;

struct Row {
    string nombre;
    string rareza;
    float  costo;
};

class StackPersonajes {
    vector<Row> items;

public:
    StackPersonajes() = default;

    void clear() {
        items.clear();
    }

    void syncDesdeArreglos(const vector<string>& nombres,
                           const vector<string>& rarezas,
                           const vector<float>&  costos) {
        items.clear(); // O(1)
        size_t n = nombres.size(); // O(1)
        items.reserve(n); // O(1)
        for (size_t i = 0; i < n; ++i) { // O(n)
            items.push_back({nombres[i], rarezas[i], costos[i]}); // O(1)
        }
    }

    void push(const string& nombre, const string& rareza, float costo) {
        items.push_back({nombre, rareza, costo}); // O(1)
    }

    bool pop() {
        if (items.empty()) {
            return false; // O(1)
        } 
        items.pop_back(); // O(1)
        return true;
    }

    bool empty() const {
        return items.empty(); // O(1)
    }

    size_t size() const {
        return items.size(); // O(1)
    }

    const Row* top() const {
        if (items.empty()) { // O(1)
            return NULL;
        }
        return &items.back(); // O(1)
    }
};

#endif
