#include <vector>
#include <string>

using namespace std;

class Bitacora {
public:
    // Constructor para crear una Bit�cora vac�a
    Bitacora();

    // Carga un registro individual a la Bit�cora
    void CargaIndividual(const vector<string>& registro);

    // Carga varios registros desde un archivo
    void CargaLotes(const string& nombreArchivo);

    // Ordena la Bit�cora por un campo clave
    void Ordena(const string& campoClave);

    // Consulta registros en la Bit�cora dentro de un rango
    vector<vector<string>> Consulta(const string& campoClave,
                                    const string& desde,
                                    const string& hasta);

    // Limpia la Bit�cora
    void Limpiar();

private:
    vector<vector<string>> registros;
};
