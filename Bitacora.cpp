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
            vector<string>* registro = new vector<string>();
            int reference_start = reference_end + 1;
            if (i == INDEX_ANTES_DE_ESPACIO_ANTES_DE_TEXTO) {
                registro->push_back(linea.substr(reference_start + 1));
                CargaIndividual(*registro);
                delete registro;
                break;  // segun paletta, no podemos usar ni brake ni continue,
                        // pero pues le preguntamos el lunes
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
bool Bitacora::Ordena(string campoClave) {
    // El campo clave ya lo tenemos desde el constructor, segun yo no es
    // necesario recibirlo como parametro en esta funcion, es necesario
    // revisarlo

    ofstream bitacora_ordenada("bitacora_ordenada.txt");
    bitacora_ordenada << "my text here!" << endl;
}

// TODO Consulta registros en la Bitacora dentro de un rango
vector<vector<string>> Bitacora::Consulta(string campoClave, string desde,
                                          string hasta) {
    vector<vector<string>> resultados;
    // Implementa aqui la logica de consulta utilizando campoClave, desde y
    // hasta
    return resultados;
}

int partition(std::vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

// Quicksort function
vector<string> quickSort(vector<int> arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
    return arr;
}

// Limpia la Biticora
void Bitacora::Limpiar() { bitacora.clear(); }
