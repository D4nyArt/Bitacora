#include "Bitacora.h"

#include <algorithm>
#include <fstream>
#include <string>

using namespace std;

// Constructor para crear una Bitacora vacaa
Bitacora::Bitacora(vector<string> campos, string campo_clave) {
    this->campo_clave = campo_clave;
    this->campos = campos;
    for (int i = 0; i < campos.size() - 1; i++) {
        if (campos[i] == campo_clave) {
            campo_clave_index = i;
        }
    }
}

// Carga un registro individual a la Bitacora
void Bitacora::CargaIndividual(vector<string> registro) {
    for (int i = 0; i < registro.size() - 1; i++) {
        bitacora[i].push_back(registro[i]);
    }
}

// Carga varios registros desde un archivo
void Bitacora::CargaLotes(string nombreArchivo) {
    ifstream archivo(nombreArchivo);
    string linea;

    while (getline(archivo, linea)) {
        int reference_end = -1;

        for (int i = 0; i < linea.size() - 1; i++) {
            vector<string> *registro = new vector<string>();
            int reference_start = reference_end + 1;
            if (i == INDEX_ANTES_DE_ESPACIO_ANTES_DE_TEXTO) {
                registro->push_back(linea.substr(reference_start + 1));
                CargaIndividual(*registro);
                delete registro;
                break;
            } else {
                if (linea[i] == ' ') {
                    int reference_end = i;
                    int linea_longitud = reference_end - reference_start;
                    registro->push_back(
                        linea.substr(reference_start, linea_longitud));
                    CargaIndividual(*registro);
                    delete registro;
                }
            }
            i++;
        }
    }

    archivo.close();
}

// TODO Ordena la Bitacora por un campo clave
void Bitacora::Ordena(string campoClave) {
    // Implementa aqui la logica de ordenacion de registros por el campo clave
}

// TODO Consulta registros en la Bitacora dentro de un rango
vector<vector<string>> Bitacora::Consulta(string campoClave, string desde,
                                          string hasta) {
    vector<vector<string>> resultados;
    // Implementa aqui la logica de consulta utilizando campoClave, desde y
    // hasta
    return resultados;
}

// Limpia la Biticora
void Bitacora::Limpiar() { bitacora.clear(); }
