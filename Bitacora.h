#ifndef BITACORA_H
#define BITACORA_H

#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

typedef vector<string> evento;

class Bitacora {
   public:
    // Constructor para crear una Bitacora vacia
    Bitacora(evento campos, string campoClave);

    // Destructor de Bitacora
    ~Bitacora();

    // Carga un registro individual a la Bitacora
    void cargaIndividual(evento registro);

    // Carga varios registros desde un archivo
    void cargaLotes(string nombreArchivo);

    // Ordena la Bitacora por un campo clave
    bool ordena(string nombreOrdenamiento);

    // Consulta registros en la Bitacora dentro de un rango
    vector<evento> consulta(string desde, string hasta);

    // Limpia la Bitacora
    void limpiar();

   private:
    // Algoritmos de ordenamiento
    int partition(vector<evento>& arr, int start, int end);
    void quickSort(vector<evento>& arr, int start, int end);
    int busquedaBinaria(int val, bool encontrarPrimero);

    string campoClave;
    int campoClaveIndex;
    evento campos;
    vector<evento> bitacora;
    vector<evento> bitacoraOrdenada;
};

#endif