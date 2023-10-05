#include "Bitacora.h"

#include <algorithm>
#include <fstream>
#include <string>

using namespace std;

// Constructor para crear una Bitacora vacaa
Bitacora::Bitacora(const vector<string> campos, const string campo_clave) {
    this->campo_clave = campo_clave;
    this->campos = campos;
    for (int i = 0; i < campos.size() - 1; i++) {
        if (campos[i] == campo_clave) {
            campo_clave_index = i;
        }
    }
}

// Carga un registro individual a la Bitacora
void Bitacora::CargaIndividual(const vector<string> registro) {
    for (int i = 0; i < registro.size() - 1; i++) {
        bitacora[i].push_back(registro[i]);
    }
}

// TODO Carga varios registros desde un archivo
void Bitacora::CargaLotes(const string nombreArchivo) {
    ifstream archivo(nombreArchivo);
    string linea;

    while (getline(archivo, linea)) {
        // Implementa aqui la logica para separar los campos de la linea y
        int reference_end = -1;

        for (int i = 0; i < linea.size() - 1; i++) {
            vector<string> *registro = new vector<string>();
            int reference_start = reference_end + 1;
            if (linea[i] == ' ') {
                int reference_end = i;
                int linea_longitud = reference_end - reference_start;
                registro->push_back(
                    linea.substr(reference_start, linea_longitud));
                CargaIndividual(*registro);
                delete registro;
            }
        }
    }

    archivo.close();
}

// TODO Ordena la Bitacora por un campo clave
void Bitacora::Ordena(const string &campoClave) {
    // Implementa aqui la logica de ordenacion de registros por el campo clave
}

// TODO Consulta registros en la Bitacora dentro de un rango
vector<vector<string>> Bitacora::Consulta(const string &campoClave,
                                          const string &desde,
                                          const string &hasta) {
    vector<vector<string>> resultados;
    // Implementa aqui la logica de consulta utilizando campoClave, desde y
    // hasta
    return resultados;
}

// Limpia la Bit�cora
void Bitacora::Limpiar() { bitacora.clear(); }
