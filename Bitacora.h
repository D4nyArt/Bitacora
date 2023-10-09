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
    vector<string> CargaLotes(string nombreArchivo);

    // Ordena la Bitacora por un campo clave
    bool Ordena(string campoClave, string nombreOrdenamiento);

    // Consulta registros en la Bitacora dentro de un rango
    vector<vector<string>> Consulta(string campoClave, string desde,
                                    string hasta);

    // Limpia la Bitacora
    void Limpiar();

   private:
    string campo_clave;
    int campo_clave_index;
    vector<string> campos;
    vector<vector<string>> bitacora;

    // Constantes
    int INDEX_ANTES_DE_ESPACIO_ANTES_DE_TEXTO = 32;
};
