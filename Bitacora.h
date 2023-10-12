#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

typedef vector<string> Dato;

class Bitacora {
   public:
    // Constructor para crear una Bitacora vacia
    Bitacora(vector<string> campos, string campo_clave);

    // Destructor de Bitacora
    ~Bitacora();

    // Carga un registro individual a la Bitacora
    void cargaIndividual(vector<string> registro);

    // Carga varios registros desde un archivo
    void cargaLotes(string nombreArchivo);

    // Ordena la Bitacora por un campo clave
    bool ordena(string nombreOrdenamiento);

    // Consulta registros en la Bitacora dentro de un rango
    vector<Dato> consulta(string desde, string hasta);

    void CopiaBitacora(string nombreArchivo);

    // Limpia la Bitacora
    void limpiar();

   private:
    // Algoritmos de ordenamiento
    int partition(vector<int>& arr, int start, int end);
    void quickSort(vector<int>& arr, int start, int end);
    int busquedaBinaria(int val, bool encontrarPrimero);

    string campo_clave;
    int campo_clave_index;
    vector<string> campos;
    vector<Dato> bitacora;
    vector<Dato> bitacora_ordenada;
};
