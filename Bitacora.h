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
    void CargaIndividual(vector<string> registro);

    // Carga varios registros desde un archivo
    void CargaLotes(string nombreArchivo);

    // Ordena la Bitacora por un campo clave
    void Ordena(string nombreOrdenamiento);

    // Consulta registros en la Bitacora dentro de un rango
    vector<Dato> Consulta(string desde, string hasta);

    void CopiaBitacora(string nombreArchivo);

    // Limpia la Bitacora
    void Limpiar();

   private:
    // Algoritmos de ordenamiento
    int partition(vector<int>& arr, int start, int end);
    void quickSort(vector<int>& arr, int start, int end);

    string campo_clave;
    int campo_clave_index;
    vector<string> campos;
    vector<Dato> bitacora;
    vector<Dato> bitacora_ordenada;
};
