/*
Nombre: César Daniel Aguilar Kuri
Matricula: A01712823
Nombre del Proyecto: Steal a Brainrot!
Materia: Programación de estructuras de datos y algoritmos fundamentales
Profesor: Eduardo Daniel Juárez Pineda
*/


// LIBRERIAS
#include <iostream>
#include <vector>
#include <string>
#include <algorithm> // find
#include <limits>    // numeric_limits
#include <utility> // para usar swap

// CLASES

#include "MergeSortCosto.h"
#include "MergeSortNombre.h"
#include "MergeSortRareza.h"
#include "CsvLoader.h"
#include "Stack.h"

using namespace std;

// MÉTODOS
void mostrarArreglos(const vector<string>& nombres,
                     const vector<string>& rarezas,
                     const vector<float>& costos) {
    cout << "Nombre, Rareza, Costo\n";
    for (size_t i = 0; i < nombres.size(); ++i) {
        cout << nombres[i] << ", " << rarezas[i] << ", " << costos[i] << "\n";
    }
}

// Captura un bloque de N personajes y los AGREGA (continúa desde el tamaño actual)
void capturarPersonajes(vector<string>& nombres,
                        vector<string>& rarezas,
                        vector<float>& costos,
                        const vector<string>& existentrarity)
{
    int cuantos = 0;
    cout << "¿Cuántos personajes ingresarás en este bloque? ";
    while (!(cin >> cuantos) || cuantos <= 0) {
        cout << "Valor inválido. Ingresa un entero > 0: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    // limpiar salto antes de usar getline
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int k = 0; k < cuantos; ++k) {
        string nombre, rareza;
        float  costo;

        size_t idx = nombres.size(); // índice real siguiente
        cout << "\nRegistro no. " << (idx + 1) << "\n";

        // nombre
        cout << "Nombre del personaje: ";
        getline(cin >> ws, nombre);
        while (nombre.empty()) {
            cout << "El nombre no puede estar vacío. Intenta de nuevo: ";
            getline(cin >> ws, nombre);
        }

        // rareza (validada)
        cout << "Rarezas válidas: Common, Rare, Epic, Legendary, BrainrotGod, Secret\n";
        cout << "Rareza: ";
        getline(cin >> ws, rareza);
        while (find(existentrarity.begin(), existentrarity.end(), rareza) == existentrarity.end()) {
            cout << "Rareza inválida. Debe ser una de: ";
            for (const auto& r : existentrarity) cout << r << " ";
            cout << "\nIntenta de nuevo: ";
            getline(cin >> ws, rareza);
        }

        // costo
        cout << "Costo (>= 0): ";
        while (!(cin >> costo) || costo < 0.0f) {
            cout << "Costo inválido. Debe ser >= 0. Intenta de nuevo: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        nombres.push_back(nombre);
        rarezas.push_back(rareza);
        costos.push_back(costo);
    }
    cout << "\nCaptura completa. Total acumulado: " << nombres.size() << "\n";
}

// MAIN 
int main() {
    // Arreglos PERSISTENTES para toda la sesión
    StackPersonajes pila;
    vector<string> nombres;
    vector<string> rarezas;
    vector<float>  costos;
    vector<string> existentrarity = {
        "Common","Rare","Epic","Legendary","BrainrotGod","Secret"
    };

    while (true) {
        // Menú
        cout << "\nBienvenido a Steal a Brainrot!\n";
        cout << "Selecciona la opción que quieres ejecutar:\n";
        cout << "1. Cargar lista predeterminada de personajes para probar\n";
        cout << "2. Ingresar personajes, rarezas y costos a arreglos\n";
        cout << "3. Consultar arreglos\n";
        cout << "4. Ordenar personajes por costo (Merge Sort)\n";
        cout << "5. Ordenar personajes por nombre (Merge Sort)\n";
        cout << "6. Ordenar personajes por rareza (Merge Sort)\n";
        cout << "7. Consultar ultimo personaje (Estructura de datos Stack)\n";
        cout << "8. Eliminar ultimo personaje (Estructura de datos Stack)\n";
        cout << "9. Salir\n";
        cout << "> ";

        int op;
        if (!(cin >> op)) {
            // entrada no numérica
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Entrada inválida.\n";
            continue;
        }

        // Rango válido
        if (op < 1 || op > 9) {
            cout << "Opción no válida. Intenta (1-9).\n";
            continue;
        }

        if (op == 1) {
            string ruta;
            cout << "Ingrese Ruta del CSV: ";
            cin >> ruta;

            size_t antes = nombres.size();
            if (cargarDesdeCSV(ruta, nombres, rarezas, costos, existentrarity)) {
                pila.syncDesdeArreglos(nombres, rarezas, costos);
                cout << "\nSe añadieron " << (nombres.size() - antes) << " registros desde " << ruta << "\n";
                mostrarArreglos(nombres, rarezas, costos);
            } else {
                cout << "No se pudo cargar el archivo.\n";
                continue;
            }
        }

        // Acciones
        if (op == 2) {
            capturarPersonajes(nombres, rarezas, costos, existentrarity);
            pila.syncDesdeArreglos(nombres, rarezas, costos);
            continue;

        } else if (op == 3) {
            cout << "\nConsulta de Arreglos:\n";
            mostrarArreglos(nombres, rarezas, costos);
            continue;

        } else if (op == 4) {
            cout << "[Merge Sort] (Ordena por Costo)\n";
            cout << "Arreglos actuales: \n";
            mostrarArreglos(nombres, rarezas, costos);
            cout << "==================================\n";
            cout << "Arreglos con Merge Sort (Costo): \n";
            mergeSortPorCosto(nombres, rarezas, costos);
            mostrarArreglos(nombres, rarezas, costos);
            continue;

        } else if (op == 5) {
            cout << "[Merge Sort] (Ordena por Nombre)\n";
            cout << "Arreglos actuales: \n";
            mostrarArreglos(nombres, rarezas, costos);
            cout << "==================================\n";
            cout << "Arreglos con Merge Sort (Nombre): \n";
            mergeSortPorNombre(nombres, rarezas, costos);
            mostrarArreglos(nombres, rarezas, costos);
            continue;   

        } else if (op == 6) {
            cout << "[Merge Sort] (Ordena por Rareza)\n";
            cout << "Arreglos actuales: \n";
            mostrarArreglos(nombres, rarezas, costos);
            cout << "==================================\n";
            cout << "Arreglos con Merge Sort (Rareza): \n";
            mergeSortPorRareza(nombres, rarezas, costos);
            mostrarArreglos(nombres, rarezas, costos);
            continue;

        } else if (op == 7) {
            cout << "[Estructura Líneal Stack] (Consulta ultimo personaje de arreglo)\n";
            const Row* u = pila.top();
            if (!u) {
                cout << "Stack vacio!!!, (ingresar personajes porfavor)\n";
                continue;
            } else {
                cout << "El ultimo personaje del arreglo es: " << u -> nombre << ", " << u -> rareza << ", " << u -> costo << "\n";
                continue;
            }

        } else if (op == 8) {
            cout << "[Estructura Líneal Stack] (Elimina ultimo personaje de arreglo)\n";

            if (pila.size() != nombres.size()) {
                pila.syncDesdeArreglos(nombres, rarezas, costos);
            }

            if (pila.empty()) {
                cout << "Stack vacio!!! (ingresar personajes porfavor)\n";
                continue;
            }

            if (pila.pop()) {
                if (!nombres.empty()) {
                    nombres.pop_back();
                    rarezas.pop_back();
                    costos.pop_back();
                }
                cout << "Se eliminó el ultimo personaje. \n";
            }

        continue;

        } else if (op == 9) {
            cout << "Sesión terminada, sigue coleccionando Brainrots!\n";
            break;
        }
        return 0;
    }
}
