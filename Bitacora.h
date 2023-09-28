#ifndef BITACORA_H
#define BITACORA_H

#include <vector>
#include <string>

using namespace std;

class Bitacora {
public:
    // Constructor para crear una Bitácora vacía
    Bitacora();

    // Carga un registro individual a la Bitácora
    void CargaIndividual(const vector<string>& registro);

    // Carga varios registros desde un archivo
    void CargaLotes(const string& nombreArchivo);

    // Ordena la Bitácora por un campo clave
    void Ordena(const string& campoClave);

    // Consulta registros en la Bitácora dentro de un rango
    vector<vector<string>> Consulta(const string& campoClave,
                                    const string& desde,
                                    const string& hasta);

    // Limpia la Bitácora
    void Limpiar();

private:
    vector<vector<string>> registros;
};

#endif
