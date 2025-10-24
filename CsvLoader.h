/*
Nombre: César Daniel Aguilar Kuri
Matricula: A01712823
Nombre del Proyecto: Steal a Brainrot!
Materia: Programación de estructuras de datos y algoritmos fundamentales
Profesor: Eduardo Daniel Juárez Pineda
*/

#ifndef CSVLOADER_H
#define CSVLOADER_H

#include <fstream>
#include <sstream>

// Lee CSV: Nombre,Rareza,Costo (con comillas opcionales en Nombre)
bool cargarDesdeCSV(const string& rutaCSV,
                    vector<string>& nombres,
                    vector<string>& rarezas,
                    vector<float>&  costos,
                    const vector<string>& existentrarity)
{
    ifstream in(rutaCSV);
    if (!in.is_open()) {
        cerr << "No se pudo abrir el archivo: " << rutaCSV << "\n";
        return false;
    }

    auto rarezaValida = [&](const string& r){
        return find(existentrarity.begin(), existentrarity.end(), r) != existentrarity.end();
    };

    string linea;
    bool primera = true;
    size_t lineNum = 0;
    while (std::getline(in, linea)) {
        ++lineNum;
        if (primera) { // saltar encabezados
            primera = false;
            continue;
        }
        if (linea.empty()) continue;

        // Parser CSV simple: Nombre (puede venir entre comillas y con comas), Rareza, Costo
        string nombre, rareza, costoStr;
        stringstream ss(linea);

        // 1) Nombre (soporta comillas)
        if (ss.peek() == '"') {
            ss.get(); // quitar "
            std::getline(ss, nombre, '"'); // lee hasta la siguiente "
            if (ss.peek() == ',') ss.get(); // quitar coma
        } else {
            std::getline(ss, nombre, ','); // hasta coma
        }

        // 2) Rareza
        std::getline(ss, rareza, ',');

        // 3) Costo (resto de la línea)
        std::getline(ss, costoStr);

        // Trim básicos (opcional)
        auto trim = [](string& s){
            while (!s.empty() && isspace((unsigned char)s.front())) s.erase(s.begin());
            while (!s.empty() && isspace((unsigned char)s.back()))  s.pop_back();
        };
        trim(nombre); trim(rareza); trim(costoStr);

        if (nombre.empty() || rareza.empty() || costoStr.empty()) {
            cerr << "Línea " << lineNum << ": campos vacíos, se omite.\n";
            continue;
        }

        // Validar rareza
        if (!rarezaValida(rareza)) {
            cerr << "Línea " << lineNum << ": rareza '" << rareza << "' inválida, se fuerza a Common.\n";
            rareza = "Common";
        }

        // Convertir costo
        try {
            float costo = std::stof(costoStr);
            if (costo < 0.0f) costo = 0.0f;
            nombres.push_back(nombre);
            rarezas.push_back(rareza);
            costos.push_back(costo);
        } catch (...) {
            cerr << "Línea " << lineNum << ": costo inválido '" << costoStr << "', se omite.\n";
        }
    }
    return true;
}

#endif