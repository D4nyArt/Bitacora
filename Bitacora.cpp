#include "Bitacora.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

// Constructor para crear una Bitacora vacia
// Constructor si jala
Bitacora::Bitacora(vector<string> campos, string campo_clave) {
    this->campo_clave = campo_clave;
    this->campos = campos;
    for (int i = 0; i < campos.size() - 1; i++) {
        if (campos[i] == campo_clave) {
            campo_clave_index = i;
        }
    }
    bitacora.resize(campos.size());
}

// Destructor de Bitacora
Bitacora::~Bitacora(){};

// Carga un registro individual a la Bitacora
// CargaIndividual ya jala
void Bitacora::CargaIndividual(vector<string> registro) {
    for (int i = 0; i < registro.size(); i++) {
        bitacora[i].push_back(registro[i]);
    }
}

// Carga varios registros desde un archivo
// CargaLotes ya jala
void Bitacora::CargaLotes(string nombreArchivo) {
    ifstream archivo(nombreArchivo);
    if (archivo.is_open()) {
        string linea;
        while (!archivo.eof()) {
            getline(archivo, linea);
            cout << linea << endl;
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
    bitacora_ordenada = bitacora;
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
    int index_desde = busquedaBinaria(stoi(desde), true);
    int index_hasta = busquedaBinaria(stoi(hasta), false);

    for (int i=index_desde; i<= index_hasta; i++) {
        resultados.push_back(bitacora_ordenada[i]);
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


int Bitacora::busquedaBinaria(int val, bool encontrarPrimero) {
    int inicio = 0;
    int fin = bitacora_ordenada.size() - 1;
    int resultado = -1;

    while (inicio <= fin) {
        int medio = inicio + (fin - inicio) / 2;
        int valorMedio = stoi(bitacora_ordenada[medio][campo_clave_index]);

        if (valorMedio == val) {
            resultado = medio;
            if (encontrarPrimero) {
                fin = medio - 1; // Buscar el primer índice hacia la izquierda
            } else {
                inicio = medio + 1; // Buscar el último índice hacia la derecha
            }
        } else if (valorMedio < val) {
            inicio = medio + 1;
        } else {
            fin = medio - 1;
        }
    }

    return resultado;
}

// Limpia la Biticora
void Bitacora::Limpiar() { bitacora.clear(); }
