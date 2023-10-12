#include "Bitacora.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

void showConsultaResult(vector<Dato> consultaRes) {
    for (int i = 0; i < consultaRes.size(); i++) {
        for (int j = 0; j < consultaRes[i].size(); j++) {
            cout << consultaRes[i][j] << " ";
        }
        cout << endl;
    }
}

void showVectorStr(const vector<string> vec) {
    for (const string str : vec) {
        cout << str << " " << endl;
    }
}

void showVectorInt(const vector<int> vec) {
    for (const int num : vec) {
        cout << num << " ";
    }
}

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
// En teoria CargaLotes ya esta generelizado
void Bitacora::CargaLotes(string nombreArchivo) {
    ifstream archivo(nombreArchivo);
    if (archivo.is_open()) {
        string linea;
        while (getline(archivo, linea)) {
            istringstream ss(linea);
            vector<string> reg(campos.size());
            string campo_especifico;
            while (ss >> campo_especifico) {
                reg.push_back(campo_especifico);
            }
            if (!ss.eof()) {
                string campo_especifico_espacios;
                getline(ss, campo_especifico_espacios);
                reg.push_back(campo_especifico_espacios);
            }
            CargaIndividual(reg);
        }
        archivo.close();
    }
}

// TODO Ordena la Bitacora por un campo clave
void Bitacora::Ordena(string nombreOrdenamiento) {
    bitacora_ordenada = bitacora;
    // Convertir vector de campo clave a int
    vector<int> bitacora_temp;
    transform(bitacora[campo_clave_index].begin(),
              bitacora[campo_clave_index].end(), back_inserter(bitacora_temp),
              [](const string& str) { return stoi(str); });

    // Ordenar la bitacora
    quickSort(bitacora_temp, 0, bitacora_temp.size() - 1);

    // Insertar los valores de la bitacora ya ordenada en el archivo de
    // texto
    /*
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
    */
}
// TODO Consulta registros en la Bitacora dentro de un rango
// Debuggear el casting de string a int del campo clave de los registros de
// bitacora ordenada
vector<vector<string>> Bitacora::Consulta(string desde, string hasta) {
    vector<vector<string>> resultados;
    int index_desde = busquedaBinaria(stoi(desde), true);
    int index_hasta = busquedaBinaria(stoi(hasta), false);

    for (int i = index_desde; i <= index_hasta; i++) {
        resultados.push_back(bitacora_ordenada[i]);
    }
    return resultados;
}

int Bitacora::partition(vector<int>& arr, int start, int end) {
    int pivotElement = arr[end];
    int pivotIndex;
    vector<int> temp;

    for (int i = start; i <= end; i++) {
        if (arr[i] < pivotElement) {
            temp.push_back(arr[i]);
        }
    }

    pivotIndex = temp.size();
    temp.push_back(pivotElement);

    for (int i = start; i <= end; i++) {
        if (arr[i] >= pivotElement) {
            temp.push_back(arr[i]);
        }
    }

    int index = 0;
    for (int i = start; i <= end && index < temp.size(); i++) {
        arr[i] = temp[index];
        index++;
    }
    return start + pivotIndex > end ? end : start + pivotIndex;
}

void Bitacora::quickSort(vector<int>& arr, int start, int end) {
    if (start < end) {
        int partitionIndex = partition(arr, start, end);
        quickSort(arr, start, partitionIndex - 1);
        quickSort(arr, partitionIndex + 1, end);
    }
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
                fin = medio - 1;  // Buscar el primer índice hacia la izquierda
            } else {
                inicio = medio + 1;  // Buscar el último índice hacia la derecha
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
