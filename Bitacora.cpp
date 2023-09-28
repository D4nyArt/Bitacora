#include "Bitacora.h"
#include <fstream>
#include <algorithm>

using namespace std;

// Constructor para crear una Bitácora vacía
Bitacora::Bitacora() {
    registros.clear();
}

// Carga un registro individual a la Bitácora
void Bitacora::CargaIndividual(const vector<string>& registro) {
    registros.push_back(registro);
}

// Carga varios registros desde un archivo
void Bitacora::CargaLotes(const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);
    string linea;

    while (getline(archivo, linea)) {
        vector<string> registro;
        // Implementa aquí la lógica para separar los campos de la línea y llenar el registro
        registros.push_back(registro);
    }

    archivo.close();
}

// Ordena la Bitácora por un campo clave
void Bitacora::Ordena(const string& campoClave) {
    // Implementa aquí la lógica de ordenación de registros por el campo clave
}

// Consulta registros en la Bitácora dentro de un rango
vector<vector<string>> Bitacora::Consulta(const string& campoClave,
                                          const string& desde,
                                          const string& hasta) {
    vector<vector<string>> resultados;
    // Implementa aquí la lógica de consulta utilizando campoClave, desde y hasta
    return resultados;
}

// Limpia la Bitácora
void Bitacora::Limpiar() {
    registros.clear();
}

