#include <iostream>
#include <string>
#include <vector>

#include "Bitacora.cpp"
// #include "Bitacora.h"

using namespace std;
/*
void showConsultaResult(vector<vector<string>> consultaRes) {
    for (int i = 0; i < consultaRes.size(); i++) {
        for (int j = 0; j < consultaRes[i].size(); j++) {
            cout << consultaRes[i][j] << " ";
        }
        cout << endl;
    }
}*/

int main(int argc, char const *argv[]) {
    Bitacora b1({"mes", "dia", "hora", "ip", "razon"}, "dia");

    b1.CargaLotes("bitacora.txt");
    // b1.Ordena("testingb1.txt");
    // showConsultaResult(b1.Consulta("4", "12"));
    return 0;
}
