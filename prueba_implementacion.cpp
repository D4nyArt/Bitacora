#include <string>
#include <vector>
#include <iostream>

#include "Bitacora.h"

using namespace std;

void showConsultaResult(vector<vector<string>> consultaRes){
    for(int i=0; i<consultaRes.size(); i++){
        for(int j=0; j<consultaRes[i].size(); j++){
            cout << consultaRes[i][j] << " ";
        }        
        cout << '\n';
    }
}

int main(int argc, char const *argv[]) {
    Bitacora B({"Mes", "Dia", "Hora", "IP", "Falla"}, "Mes");
    B.CargaLotes("bitacora.txt");
    B.Ordena("Mes", "ordenamiento.txt");
    Bitacora BC({"Mes", "Dia", "Hora", "IP", "Falla"}, "Mes");
    BC.CargaLotes("ordenamiento.txt"); 
    string desde; 
    string hasta;
    cout << "Introduzca la fecha inicial de la consulta: ";
    cin >> desde; 
    cout << "Introduzca la fecha final de la consulta: ";  
    cin >> hasta;  
    showConsultaResult(BC.Consulta("Mes", desde, hasta));
    //Bitacora failed_logins();
    return 0;
}
