#include <vector>
#include <string>

using namespace std;

class Bitacora {
public:
    // Constructor para crear una Bitacora vacia
    Bitacora(vector<string> campos, string campoClave>);

    // Carga un registro individual a la Bitacora
    void CargaIndividual(vector<string> registro);

    // Carga varios registros desde un archivo
    void CargaLotes(string nombreArchivo);

    // Ordena la Bitacora por un campo clave
    bool Ordena(string campoClave);

    // Consulta registros en la Bitacora dentro de un rango
    vector<vector<string>> Consulta(string campoClave, string desde, string hasta);

    // Limpia la Bitacora
    void Limpiar();

private:
    vector<vector<string>> Registros;
};
