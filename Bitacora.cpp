#include "Bitacora.h"
#include <fstream>
#include <algorithm>

using namespace std;

// Constructor para crear una Bit�cora vac�a
Bitacora::Bitacora() {
    registros.clear();
}

// Carga un registro individual a la Bit�cora
void Bitacora::CargaIndividual(const vector<string>& registro) {
    registros.push_back(registro);
}

// Carga varios registros desde un archivo
void Bitacora::CargaLotes(const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);
    string linea;

    while (getline(archivo, linea)) {
        vector<string> registro;
        // Implementa aqu� la l�gica para separar los campos de la l�nea y llenar el registro
        registros.push_back(registro);
    }

    archivo.close();
}

// Ordena la Bit�cora por un campo clave
void Bitacora::Ordena(const string& campoClave) {
    // Implementa aqu� la l�gica de ordenaci�n de registros por el campo clave
}

// Consulta registros en la Bit�cora dentro de un rango
vector<vector<string>> Bitacora::Consulta(const string& campoClave,
                                          const string& desde,
                                          const string& hasta) {
    vector<vector<string>> resultados;
    // Implementa aqu� la l�gica de consulta utilizando campoClave, desde y hasta
    return resultados;
}

// Limpia la Bit�cora
void Bitacora::Limpiar() {
    registros.clear();
}

