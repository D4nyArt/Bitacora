/*Este programa es la implementacion del ADT de una bitacora generalizada que
 * consta de los metodos: cargaIndividual, cargaLotes, ordena, consulta y
 * limpia*/

// Creado el 25 de septiembre del 2023
// Editado el 15 de octubre del 2023

// Esteban Leal Menendez | A01369877
// Stephanie Ortega Espinosa | A01369902
// Daniel Arteaga Mercado | A01369706

#include "Bitacora.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

// Constructor para crear una Bitacora vacia
Bitacora::Bitacora(evento campos, string campoClave) {
    this->campoClave = campoClave;
    this->campos = campos;
    for (int i = 0; i < campos.size() - 1; i++) {
        if (campos[i] == campoClave) {
            campoClaveIndex = i;
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
    bitacora.push_back(registro);
}

/**
 * Carga varios registros desde un archivo de texto.
 *
 * @param nombreArchivo El nombre del archivo desde el cual se cargaran los
 * registros. Debe estar en un formato compatible con los campos de la bitacora.
 */
void Bitacora::cargaLotes(string nombreArchivo) {
    ifstream archivo(nombreArchivo);
    if (archivo.is_open()) {
        string linea;
        while (getline(archivo, linea)) {
            istringstream ss(linea);
            evento reg(campos.size());

            // Leer los primeros campos
            for (int i = 0; i < campos.size() - 1; ++i) {
                if (!(ss >> reg[i])) {
                    cerr << "Error al leer el archivo: " << nombreArchivo
                         << endl;
                    return;
                }
            }

            // Leer el �ltimo campo (raz�n de la falla) que puede contener
            // espacios
            getline(ss, reg[campos.size() - 1]);
            reg[campos.size() - 1].erase(0, 1);
            bitacora.push_back(reg);
        }
        archivo.close();
    }
}

/**
 * Ordena la Bitacora segun un campo clave y guarda los registros en un archivo
 * de texto.
 *
 * @param nombreOrdenamiento El nombre del archivo de texto en el que se
 * guardaran los registros ordenados.
 * @return Devuelve un valor booleano, true si la operacion de ordenamiento y
 * guardado fue exitosa, o false en caso de que no se pueda abrir el archivo de
 * destino. La Bitacora ordenada se guarda en el archivo especificado si la
 * operacion es exitosa.
 */

bool Bitacora::ordena(string nombreOrdenamiento) {
    bitacoraOrdenada = bitacora;

    quickSort(bitacoraOrdenada, 0, bitacoraOrdenada.size() - 1);

    ofstream archivo(nombreOrdenamiento);

    if (archivo.is_open()) {
        for (evento reg : bitacoraOrdenada) {
            for (string campo : reg) {
                archivo << campo << " ";
            }
            archivo << endl;  // Agrega un salto de línea después de cada
                              // evento
        }

        archivo.close();
        cout << "Datos escritos en el archivo salida.txt." << endl;
        return true;
    } else {
        cerr << "Error al abrir el archivo." << endl;
        return false;
    }
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
    int desdeNum = stoi(desde);
    int hastaNum = stoi(hasta);

    int indexDesde = busquedaBinaria(desdeNum, true);
    int indexHasta = busquedaBinaria(hastaNum, false);

    if(indexDesde == -1 || indexHasta == -1){
        for (evento registro: bitacoraOrdenada) {
            int valor = stoi(registro[campoClaveIndex]);
            if (valor >= desdeNum && valor <= hastaNum) {
                resultados.push_back(registro);
            }
        }
        return resultados;
    }

    for (int i = indexDesde; i <= indexHasta; i++) {
        resultados.push_back(bitacoraOrdenada[i]);
    }
    return resultados;
}

/**
 * Realiza la particion de un arreglo en el contexto de un algoritmo de
 * ordenamiento QuickSort.
 *
 * @param arr Un vector de enteros que se va a particionar.
 * @param start Indice de inicio de la particion.
 * @param end Indice de fin de la particion.
 * @return El indice donde se coloca el elemento pivote despues de la particion.
 */
int Bitacora::partition(vector<evento>& arr, int start, int end) {
    int pivotElement = stoi(arr[end][campoClaveIndex]);
    evento pivotevento = arr[end];
    int pivotIndex;
    vector<evento> temp;

    for (int i = start; i <= end; i++) {
        if (stoi(arr[i][campoClaveIndex]) < pivotElement) {
            temp.push_back(arr[i]);
        }
    }

    pivotIndex = temp.size();
    temp.push_back(pivotevento);

    for (int i = start; i <= end; i++) {
        if (stoi(arr[i][campoClaveIndex]) >= pivotElement) {
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
 * Indice donde se encuentra el valor (true) o el ultimo indice (false) en caso
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
    int fin = bitacoraOrdenada.size() - 1;
    int resultado = -1;

    while (inicio <= fin) {
        int medio = inicio + (fin - inicio) / 2;
        int valorMedio = stoi(bitacoraOrdenada[medio][campoClaveIndex]);

        if (valorMedio == val) {
            resultado = medio;
            if (encontrarPrimero) {
                fin = medio - 1;
            } else {
                inicio = medio + 1;
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
 * Limpia la Bitacora, eliminando todos los registros almacenados en ella.
 */
void Bitacora::limpiar() { bitacora.clear(); }
