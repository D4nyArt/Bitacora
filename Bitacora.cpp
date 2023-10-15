/*Este programa es la implementacion del ADT de una bitacora generalizada que
 * consta de los metodos: cargaIndividual, cargaLotes, ordena, consulta y
 * limpia*/

// Creado el 5 de Octubre del 2023
// Editado ----------------------

// Esteban Leal Menéndez | A01369877
// Stephanie Ortega Espinosa | A01369902
// Daniel Arteaga Mercado | A01369706

#include "Bitacora.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

void showConsultaResult(vector<evento> consultaRes) {
    for (int i = 0; i < consultaRes.size(); i++) {
        for (int j = 0; j < consultaRes[i].size(); j++) {
            cout << consultaRes[i][j] << " ";
        }
        cout << endl;
    }
}

void showVectorStr(const evento vec) {
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
Bitacora::Bitacora(evento campos, string campo_clave) {
    this->campo_clave = campo_clave;
    this->campos = campos;
    for (int i = 0; i < campos.size() - 1; i++) {
        if (campos[i] == campo_clave) {
            campo_clave_index = i;
        }
    }
    // bitacora.resize(campos.size());
}

// Destructor de Bitacora
Bitacora::~Bitacora(){};

/**
 * Agrega registros individuales a la bitacora existente.
 *
 * @param registro Un vector de cadenas de texto que contiene la informacion del
 * registro a agregar. Cada elemento del vector representa un evento especifico
 * del registro.
 */
void Bitacora::cargaIndividual(evento registro) {
    for (int i = 0; i < registro.size(); i++) {
        bitacora.push_back(registro);
    }
}

/**
 * Carga varios registros desde un archivo de texto.
 *
 * @param nombreArchivo El nombre del archivo desde el cual se cargarán los
 * registros. Debe estar en un formato compatible con los campos de la bitacora.
 */
void Bitacora::cargaLotes(string nombreArchivo) {
    ifstream archivo(nombreArchivo);
    if (archivo.is_open()) {
        string linea;
        while (getline(archivo, linea)) {
            istringstream ss(linea);
            evento reg(campos.size());
            string campo_especifico;
            while (ss >> campo_especifico) {
                reg.push_back(campo_especifico);
            }
            if (campos.size() < reg.size()) {
                stringstream ss;
                for (int i = campos.size(); i < reg.size(); ++i) {
                    ss << reg[i];
                    if (i < reg.size() - 1) {
                        ss << " ";
                    }
                }
                reg.resize(campos.size());
                reg.push_back(ss.str());
                showVectorStr(reg);
                cargaIndividual(reg);
            }
            archivo.close();
        }
    }
}

/**
 * Ordena la Bitacora segun un campo clave y guarda los registros en un archivo
 * de texto.
 *
 * @param nombreOrdenamiento El nombre del archivo de texto en el que se
 * guardarán los registros ordenados.
 * @return Devuelve un valor booleano, true si la operacion de ordenamiento y
 * guardado fue exitosa, o false en caso de que no se pueda abrir el archivo de
 * destino. La Bitacora ordenada se guarda en el archivo especificado si la
 * operación es exitosa.
 */

bool Bitacora::ordena(string nombreOrdenamiento) {
    bitacora_ordenada = bitacora;

    quickSort(bitacora_ordenada, 0, bitacora_ordenada.size() - 1);
    showConsultaResult(bitacora_ordenada);

    // TODO Insertar los valores de la bitacora ya ordenada en el archivo de
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

/**
 * Realiza una consulta en una bitacora previamente ordenada para recuperar
 * registros dentro de un rango de valores.
 *
 * @param desde Limite inferior del rango de registros
 * a consultar.
 * @param hasta Limite superior del rango de registros
 * a consultar.
 * @return Un vector de vectores de cadenas de texto que
 * caen dentro del rango especificado [desde, hasta]. Los registros se devuelven
 * en el orden en que se encuentran en la bitacora y pueden contener multiples
 * campos representados por cadenas de texto.
 */
vector<evento> Bitacora::consulta(string desde, string hasta) {
    vector<evento> resultados;
    int index_desde = busquedaBinaria(stoi(desde), true);
    int index_hasta = busquedaBinaria(stoi(hasta), false);

    for (int i = index_desde; i <= index_hasta; i++) {
        resultados.push_back(bitacora_ordenada[i]);
    }
    return resultados;
}

/**
 * Realiza la partición de un arreglo en el contexto de un algoritmo de
 * ordenamiento QuickSort.
 *
 * @param arr Un vector de enteros que se va a particionar.
 * @param start Indice de inicio de la particion.
 * @param end Indice de fin de la particion.
 * @return El indice donde se coloca el elemento pivote despues de la particion.
 */
int Bitacora::partition(vector<evento>& arr, int start, int end) {
    int pivotElement = stoi(arr[end][campo_clave_index]);
    evento pivotevento = arr[end];
    int pivotIndex;
    vector<evento> temp;

    for (int i = start; i <= end; i++) {
        if (stoi(arr[i][campo_clave_index]) < pivotElement) {
            temp.push_back(arr[i]);
        }
    }

    pivotIndex = temp.size();
    temp.push_back(pivotevento);

    for (int i = start; i <= end; i++) {
        if (stoi(arr[i][campo_clave_index]) >= pivotElement) {
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

/**
 * Realiza la ordenacion de un vector y ordena una copia de la bitacora
 * utilizando el algoritmo QuickSort.
 *
 * @param arr Vector de enteros que se va a ordenar.
 * @param start Indice de inicio de la lista a ordenar.
 * @param end Indice de fin de la lista a ordenar.
 */
void Bitacora::quickSort(vector<evento>& arr, int start, int end) {
    if (start < end) {
        int partitionIndex = partition(arr, start, end);
        quickSort(arr, start, partitionIndex - 1);
        quickSort(arr, partitionIndex + 1, end);
    }
}

/**
 * Realiza una busqueda binaria en la bitcora ordenada para encontrar un valor
 * especifico.
 *
 * @param val El valor que se desea buscar en la bitacora.
 * @param encontrarPrimero Un valor booleano que determina si se busca el primer
 * índice donde se encuentra el valor (true) o el último índice (false) en caso
 * de valores duplicados.
 * @return El indice en la bitacora donde se encuentra el valor buscado. Si no
 * se encuentra, se devuelve -1. Si se especifica buscar el primer indice y no
 * se encuentra el valor, se devuelve el indice donde deberia insertarse para
 * mantener el orden. Si se especifica buscar el ultimo indice y no se encuentra
 * el valor, se devuelve el indice inmediatamente despues del ultimo elemento
 * igual.
 */
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

/**
 * Limpia la Bitácora, eliminando todos los registros almacenados en ella.
 */
void Bitacora::limpiar() { bitacora.clear(); }
