#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

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
    bool Ordena(string nombreOrdenamiento);

    // Consulta registros en la Bitacora dentro de un rango
    vector<vector<string>> Consulta(string desde, string hasta);

    void CopiaBitacora(string nombreArchivo);

    // Limpia la Bitacora
    void Limpiar();

   private:
    
    // Algoritmos de ordenamiento
    int dividir(vector<int> arr, int low, int high);
    vector<string> quickSort(vector<int> arr, int low, int high);

    string campo_clave;
    int campo_clave_index;
    vector<string> campos;
    vector<vector<string>> bitacora;
    vector<vector<string>> bitacora_ordenada;
};
