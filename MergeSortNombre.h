/*
Nombre: César Daniel Aguilar Kuri
Matricula: A01712823
Nombre del Proyecto: Steal a Brainrot!
Materia: Programación de estructuras de datos y algoritmos fundamentales
Profesor: Eduardo Daniel Juárez Pineda
*/

#ifndef MERGERSORTNOMBRE_H 
#define MERGERSORTNOMBRE_H 

#include <vector>          
#include <string>          
#include <unordered_map>   
#include <utility>         
#include <cctype>         

using namespace std;       

inline bool nombreMenor(const string& a, const string& b) {        // O(1)
    return a < b;                                                  // O(1)
}

inline void mergePorNombre(                                        // O(n) sobre el segmento
    vector<string>& nombres,                                       // O(1)
    vector<string>& rarezas,                                       // O(1)
    vector<float>&  costos,                                        // O(1)
    size_t l, size_t m, size_t r) {                                // O(1)

    const size_t n1 = m - l + 1;                                   // O(1)
    const size_t n2 = r - m;                                       // O(1)

    vector<string> Ln(n1), Lr(n1);                                 // O(n)
    vector<float>  Lc(n1);                                         // O(n)
    vector<string> Rn(n2), Rr(n2);                                 // O(n)
    vector<float>  Rc(n2);                                         // O(n)

    for (size_t i = 0; i < n1; ++i) {                              // O(n)
        Ln[i] = nombres[l + i];                                    // O(1) por iteración
        Lr[i] = rarezas[l + i];                                    // O(1)
        Lc[i] = costos [l + i];                                    // O(1)
    }
    for (size_t j = 0; j < n2; ++j) {                              // O(n)
        Rn[j] = nombres[m + 1 + j];                                // O(1) por iteración
        Rr[j] = rarezas[m + 1 + j];                                // O(1)
        Rc[j] = costos [m + 1 + j];                                // O(1)
    }

    size_t i = 0, j = 0, p = l;                                    // O(1)
    while (i < n1 && j < n2) {                                     // O(n)
        if (nombreMenor(Ln[i], Rn[j]) || (!nombreMenor(Rn[j], Ln[i]))) {  // O(1)
            nombres[p] = Ln[i]; rarezas[p] = Lr[i]; costos[p] = Lc[i]; // O(1)
            ++i;                                                   // O(1)
        } else {
            nombres[p] = Rn[j]; rarezas[p] = Rr[j]; costos[p] = Rc[j]; // O(1)
            ++j;                                                   // O(1)
        }
        ++p;                                                       // O(1)
    }
    while (i < n1) {                                               // O(n)
        nombres[p] = Ln[i]; 
        rarezas[p] = Lr[i]; 
        costos[p] = Lc[i]; // O(1) por iteración
        ++i; ++p;                                                  // O(1)
    }
    while (j < n2) {                                               // O(n)
        nombres[p] = Rn[j]; 
        rarezas[p] = Rr[j]; 
        costos[p] = Rc[j]; // O(1) por iteración
        ++j; ++p;                                                  // O(1)
    }
}


inline void mergeSortNombreRec(                                    // O(n log n) sobre el segmento
    vector<string>& nombres,                                       // O(1)
    vector<string>& rarezas,                                       // O(1)
    vector<float>&  costos,                                        // O(1)
    size_t l, size_t r) {                                          // O(1)

    if (l >= r) return;                                            // O(1)
    size_t m = l + (r - l) / 2;                                    // O(1)
    mergeSortNombreRec(nombres, rarezas, costos, l, m);            // O(n log(n))
    mergeSortNombreRec(nombres, rarezas, costos, m + 1, r);        // O(n log(n))
    mergePorNombre(nombres, rarezas, costos, l, m, r);             // O(n)
}


inline void mergeSortPorNombre(                                    // O(n log n)
    vector<string>& nombres,                                       // O(1)
    vector<string>& rarezas,                                       // O(1)
    vector<float>&  costos) {                                      // O(1)

    if (nombres.size() <= 1) return;                               // O(1)
    mergeSortNombreRec(nombres, rarezas, costos,                   // O(n log n)
                       0, nombres.size() - 1);                     // O(1)
}

#endif 
