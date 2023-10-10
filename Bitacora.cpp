#include "Bitacora.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

// Constructor para crear una Bitacora vacia
Bitacora::Bitacora(vector<string> campos, string campo_clave) {
    this->campo_clave = campo_clave;
    this->campos = campos;
    for (int i = 0; i < campos.size() - 1; i++) {
        if (campos[i] == campo_clave) {
            campo_clave_index = i;
        }
    }
    bitacora_ordenada = bitacora;
}

// Destructor de Bitacora
Bitacora::~Bitacora(){};

// Carga un registro individual a la Bitacora
void Bitacora::CargaIndividual(vector<string> registro) {
    for (int i = 0; i < registro.size() - 1; i++) {
        bitacora[i].push_back(registro[i]);
    }
}

// Carga varios registros desde un archivo
void Bitacora::CargaLotes(string nombreArchivo) {
    ifstream archivo(nombreArchivo);
    if (archivo.is_open()) {
        string linea;
        while (!archivo.eof()) {
            getline(archivo, linea);
            istringstream ss(linea);
            string mes, dia, hora, ip, razon;
            ss >> mes >> dia >> hora >> ip;
            getline(ss, razon);
            razon.erase(0, 1);
            vector<string> reg = {mes, dia, hora, ip, razon};
            CargaIndividual(reg);
        }
    }
    archivo.close();
}

// TODO Ordena la Bitacora por un campo clave
bool Bitacora::Ordena(string nombreOrdenamiento) {
    // Convertir vector de campo clave a int
    vector<int> bitacora_temp;
    transform(bitacora[campo_clave_index].begin(),
              bitacora[campo_clave_index].end(), back_inserter(bitacora_temp),
              [](const string& str) { return stoi(str); });

    // Ordenar la bitacora
    quickSort(bitacora_temp, 0, bitacora_temp.size() - 1);

    // Insertar los valores de la bitacora ya ordenada en el archivo de texto
    ofstream paraInsertar(nombreOrdenamiento);
    if (paraInsertar.is_open()) {
        int j = campos.size();
        for (int i = 0; i < bitacora_ordenada.size() - 1; i++) {
            for (int j = 0; j < campos.size() - 1; j++) {
                paraInsertar << bitacora_ordenada[i][j] << " ";
            }
            paraInsertar << endl;
        }
        return true;
    } else {
        return false;
    }
}
// TODO Consulta registros en la Bitacora dentro de un rango
// Debuggear el casting de string a int del campo clave de los registros de
// bitacora ordenada
vector<vector<string>> Bitacora::Consulta(string desde, string hasta) {
    vector<vector<string>> resultados;
    int from = stoi(desde);
    int to = stoi(hasta);

    for (vector<string> registro : bitacora_ordenada) {
        int valor = stoi(registro[campo_clave_index]);
        if (valor >= from && valor <= to) {
            resultados.push_back(registro);
        }
    }
    return resultados;
}

int Bitacora::dividir(vector<int> arr, int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
            for (int k = 0; k < campos.size() - 1; k++) {
                bitacora_ordenada[k][i].swap(bitacora_ordenada[k][j]);
            }
        }
    }
    swap(arr[i + 1], arr[high]);
    for (int k = 0; k < campos.size() - 1; k++) {
        bitacora_ordenada[k][i + 1].swap(bitacora_ordenada[k][high]);
    }
    return (i + 1);
}

// Quicksort modificado para modificar todos los campos de la bitacora
vector<string> Bitacora::quickSort(vector<int> arr, int low, int high) {
    vector<string> arrs;
    if (low < high) {
        int pi = dividir(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
    for (int i = 0; i < arr.size(); i++) {
        arrs.push_back(to_string(arr[i]));
    }
    return arrs;
}

// Limpia la Biticora
void Bitacora::Limpiar() { bitacora.clear(); }
