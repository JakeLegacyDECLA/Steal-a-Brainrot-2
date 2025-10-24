/*
Nombre: César Daniel Aguilar Kuri
Matricula: A01712823
Nombre del Proyecto: Steal a Brainrot!
Materia: Programación de estructuras de datos y algoritmos fundamentales
Profesor: Eduardo Daniel Juárez Pineda
*/

#ifndef MERGESORTRAREZA_H
#define MERGESORTRAREZA_H

#include <vector>
#include <string>
#include <unordered_map>
#include <utility>
#include <cctype>

using namespace std;

inline bool menorRarezaNombre(const string& r1, const string& n1, const string& r2, const string& n2) { // O(1)
    int a = rarityRank(r1); // O(1)
    int b = rarityRank(r2); // O(1)
    if (a < b) return true;  // O(1)
    if (a > b) return false; // O(1)
    return n1 < n2;          // O(1)
}

inline void combinarRareza(vector<string>& nombres, vector<string>& rarezas, vector<float>& costos, size_t l, size_t m, size_t r) { // O(n)
    size_t n1 = m - l + 1; // O(1)
    size_t n2 = r - m;     // O(1)

    vector<string> Lnom(n1), Rnom(n2); // O(n)
    vector<string> Lrar(n1), Rrar(n2); // O(n)
    vector<float>  Lcos(n1), Rcos(n2); // O(n)

    for (size_t i = 0; i < n1; ++i) {  // O(n)
        Lnom[i] = nombres[l + i];      // O(1)
        Lrar[i] = rarezas[l + i];      // O(1)
        Lcos[i] = costos [l + i];      // O(1)
    }
    for (size_t j = 0; j < n2; ++j) {  // O(n)
        Rnom[j] = nombres[m + 1 + j];  // O(1)
        Rrar[j] = rarezas[m + 1 + j];  // O(1)
        Rcos[j] = costos [m + 1 + j];  // O(1)
    }

    size_t i = 0, j = 0; // O(1)
    size_t k = l;        // O(1)

    while (i < n1 && j < n2) { // O(n)
        if (menorRarezaNombre(Lrar[i], Lnom[i], Rrar[j], Rnom[j])) { // O(1)
            nombres[k] = Lnom[i]; // O(1)
            rarezas[k] = Lrar[i]; // O(1)
            costos[k]  = Lcos[i]; // O(1)
            ++i;                  // O(1)
        } else {
            nombres[k] = Rnom[j]; // O(1)
            rarezas[k] = Rrar[j]; // O(1)
            costos[k]  = Rcos[j]; // O(1)
            ++j;                  // O(1)
        }
        ++k; // O(1)
    }
    while (i < n1) {             // O(n)
        nombres[k] = Lnom[i];    // O(1)
        rarezas[k] = Lrar[i];    // O(1)
        costos[k]  = Lcos[i];    // O(1)
        ++i; ++k;                // O(1)
    }
    while (j < n2) {             // O(n)
        nombres[k] = Rnom[j];    // O(1)
        rarezas[k] = Rrar[j];    // O(1)
        costos[k]  = Rcos[j];    // O(1)
        ++j; ++k;                // O(1)
    }
}

inline void mergesort_rareza_rec(vector<string>& nombres, vector<string>& rarezas, vector<float>& costos, size_t l, size_t r) { // O(n log n)
    if (l >= r) return;                 // O(1)
    size_t m = l + (r - l) / 2;         // O(1)
    mergesort_rareza_rec(nombres, rarezas, costos, l, m);     // O(n log n)
    mergesort_rareza_rec(nombres, rarezas, costos, m + 1, r); // O(n log n)
    combinarRareza(nombres, rarezas, costos, l, m, r);        // O(n)
}

inline void mergeSortPorRareza(vector<string>& nombres, vector<string>& rarezas, vector<float>& costos) { // O(n log n)
    size_t n = nombres.size();                 // O(1)
    if (rarezas.size() != n || costos.size() != n) return; // O(1)
    if (n < 2) return;                        // O(1)
    mergesort_rareza_rec(nombres, rarezas, costos, 0, n - 1); // O(n log n)
}

#endif
