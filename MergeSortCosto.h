/*
Nombre: César Daniel Aguilar Kuri
Matricula: A01712823
Nombre del Proyecto: Steal a Brainrot!
Materia: Programación de estructuras de datos y algoritmos fundamentales
Profesor: Eduardo Daniel Juárez Pineda
*/

#ifndef MERGERSORTCOSTO_H
#define MERGERSORTCOSTO_H

#include <vector>
#include <string>
#include <unordered_map>
#include <utility> //swap

using namespace std;

// ===== Jerarquía global de rarezas =====
// Common (menos importante) -> Secret (más importante)
inline int rarityRank(const string& r) { // O(1)
    static const unordered_map<string,int> RANK = { // O(1)
        {"Common", 1},
        {"Rare", 2},
        {"Epic", 3},
        {"Legendary", 4},
        {"BrainrotGod", 5},
        {"Secret", 6}
    };
    auto it = RANK.find(r); // O(1)
    return (it == RANK.end()) ? 0 : it->second; // 0 si no se reconoce (queda al inicio) // O(1)
}


inline bool menorCostoNombre(float c1, const string& n1, float c2, const string& n2) { // O(1)
    if (c1 < c2) { // O(1)
        return true; // O(1)
    } else if (c1 > c2) { // O(1)
        return false; // O(1)
    }
    return n1 < n2; // O(1)
}

inline void combinar(vector<string>& nombres, vector<string>& rarezas, vector<float>& costos, size_t l, size_t m, size_t r) { // O(n)
    size_t n1 = m - l+1; //elementos mitad izquierda // O(1)
    size_t n2 = r - m; //elementos mitad derecha // O(1)

    vector<string> Lnom(n1), Rnom(n2); // O(n)
    vector<string> Lrar(n1), Rrar(n2); // O(n)
    vector<float>  Lcos(n1), Rcos(n2); // O(n)

    //copiar lado izquierdo
    for (size_t i = 0; i < n1; i++) { // O(n)
        Lnom[i] = nombres[l + i]; // O(1)
        Lrar[i] = rarezas[l + i]; // O(1)
        Lcos[i] = costos[l + i]; // O(1)
    }

    //copiar lado derecho
    for (size_t j = 0; j < n2; j++) { // O(n)
        Rnom[j] = nombres[m + 1 + j]; // O(1)
        Rrar[j] = rarezas[m + 1 + j]; // O(1)
        Rcos[j] = costos[m + 1 + j]; // O(1)
    }
    
    size_t i = 0, j = 0; // O(1)
    size_t k = l; // O(1)
    
    while (i < n1 && j < n2) { // O(n)
        if (menorCostoNombre(Lcos[i], Lnom[i], Rcos[j], Rnom[j])) { // O(1)
            nombres[k] = Lnom[i]; // O(1)
            rarezas[k] = Lrar[i]; // O(1)
            costos[k] = Lcos[i]; // O(1)
            i++; // O(1)
        } else { // O(1)
            nombres[k] = Rnom[j]; // O(1)
            rarezas[k] = Rrar[j]; // O(1)
            costos[k] = Rcos[j]; // O(1)
            j++; // O(1)
        }
        k++; // O(1)
    }

    //copiar remanentes de izquierda si hay
    while (i < n1) { // O(n)
        nombres[k] = Lnom[i]; // O(1)
        rarezas[k] = Lrar[i]; // O(1)
        costos[k] = Lcos[i]; // O(1)
        i++; // O(1)
        k++; // O(1)
    }

    //copiar remanentes de derecha si hay
    while (j < n2) { // O(n) 
        nombres[k] = Rnom[j]; // O(1)   
        rarezas[k] = Rrar[j]; // O(1)
        costos[k] = Rcos[j]; // O(1)
        j++; // O(1)
        k++; // O(1)
    }
}

inline void mergesort_cost_rec( //funcion recursiva // O(n log n)
    vector<string>& nombres,
    vector<string>& rarezas,
    vector<float>&  costos,
    size_t l, size_t r)
{
    if (l >= r) return; // O(1) 

    size_t m = l + (r - l) / 2; // O(1) punto medio

    // Ordenar mitad izquierda // O(n log n)
    mergesort_cost_rec(nombres, rarezas, costos, l, m); // O(n log n)

    // Ordenar mitad derecha // O(n log n)
    mergesort_cost_rec(nombres, rarezas, costos, m + 1, r); // O(n log n)

    // Combinar ambas mitades ya ordenadas // O(n)
    combinar(nombres, rarezas, costos, l, m, r); // O(n)
}

inline void mergeSortPorCosto( // O(n log n)
    vector<string>& nombres,
    vector<string>& rarezas,
    vector<float>&  costos)
{
    size_t n = nombres.size(); // O(1)
    if (rarezas.size() != n || costos.size() != n) return; // O(1)
    if (n < 2) return; // O(1)

    mergesort_cost_rec(nombres, rarezas, costos, 0, n - 1); // O(n log n)
}

#endif
