#include <iostream>
#include <string>
#include <vector>

#include "Bitacora.cpp"
// #include "Bitacora.h"

using namespace std;

void showConsultaResult(vector<vector<string>> consultaRes) {
    for (int i = 0; i < consultaRes.size(); i++) {
        for (int j = 0; j < consultaRes[i].size(); j++) {
            cout << consultaRes[i][j] << " ";
        }
        cout << '\n';
    }
}

int main() {
    Bitacora B({"Mes", "Dia", "Hora", "IP", "Falla"}, "Mes");
    Bitacora BC({"Mes", "Dia", "Hora", "IP", "Falla"}, "Mes");
    int choice;
    vector<string> registro(5);
    string desde, hasta, lote;
    bool bitacora_creada = false;
    bool bitacora_ordenada = false;
    do {
        cout << "_________________________________________________" << endl;
        cout << "			Menu			" << endl;
        cout << "\n0) Salir del programa\n1) Crear bitacora\n2) Carga "
                "individual \n3) Carga lotes \n4) Ordenar bitacora\n5) "
                "Consultar bitacora\n6) Limpiar bitacora"
             << endl;
        cout << "\nPresione el numero de la opcion que desee realizar: ";
        cin >> choice;

        switch (choice) {
            case 0:
                break;
            case 1:
                // Bitacora B({"Mes", "Dia", "Hora", "IP", "Falla"}, "Mes");
                B = Bitacora({"Mes", "Dia", "Hora", "IP", "Falla"}, "Mes");
                bitacora_creada = true;
                cout << "Bitacora creada" << endl;
                break;
            case 2:
                if (!bitacora_creada) {
                    cout << "La bitacora no ha sido creada todavia" << endl;
                } else {
                    cout << "Indica el mes (coloca las primeras 3 letras): "
                         << endl;
                    cin >> registro[0];
                    while (registro[0].size() != 3) {
                        cout << "El mes debe tener exactamente 3 letras. "
                                "Ingrese nuevamente: ";
                        cin.ignore();
                        cin >> registro[0];
                    }
                    cout << "Indica el dia: " << endl;
                    cin >> registro[1];
                    while (stoi(registro[1]) < 1 || stoi(registro[1]) > 31) {
                        cout << "El dia debe estar en el rango de 1 a 31. "
                                "Ingrese nuevamente: ";
                        cin.ignore();
                        cin >> registro[1];
                    }
                    cout << "Indica la hora (hh:mm:ss): " << endl;
                    cin >> registro[2];
                    while (registro[2].size() != 8 || registro[2][2] != ':' ||
                           registro[2][5] != ':' ||
                           stoi(registro[2].substr(0, 2)) > 23 ||
                           stoi(registro[2].substr(3, 2)) > 59 ||
                           stoi(registro[2].substr(6, 2)) > 59) {
                        cout << "Asegúrese de cumplir con el formato de hora e "
                                "ingrese nuevamente: ";
                        cin.ignore();
                        cin >> registro[2];
                    }
                    cout << "Indica la direccion IP en formato "
                            "xxx.xx.xxx.xx:xxxx : "
                         << endl;
                    cin >> registro[3];
                    cout << "Indica la razon de falla: " << endl;
                    cin >> registro[4];
                    B.CargaIndividual(registro);
                }
                break;
            case 3:
                if (!bitacora_creada) {
                    cout << "La bitacora no ha sido creada todavia" << endl;
                } else {
                    cout << "Ingrese el lote completo (Mes Dia Hora IP Falla): "
                         << endl;
                    cin.ignore();
                    getline(cin, lote);
                    B.CargaLotes(lote);
                    cout << "Lote cargado" << endl;
                }
                break;
            case 4:
                if (!bitacora_creada) {
                    cout << "La bitacora no ha sido creada todavia" << endl;
                } else {
                    B.Ordena("ordenamiento.txt");
                    bitacora_ordenada = true;
                    cout << "Ordenamiento exitoso" << endl;
                    /*if(!B.Bitacora({"Mes", "Dia", "Hora", "IP", "Falla"},
                    "Mes")){ cout<<"No se puede ordenar si no existe un registro
                    previo"<<endl;
                    }*/
                }
                break;
            case 5:
                if (!bitacora_creada) {
                    cout << "La bitacora no ha sido creada todavia" << endl;
                }
                if (!bitacora_ordenada) {
                    cout << "La bitacora no ha sido ordenada todavia" << endl;
                } else {
                    cout << "Indique el mes inicial de la consulta: " << endl;
                    cin >> desde;
                    cout << "Indique el mes final de la consulta: " << endl;
                    cin >> hasta;
                    BC.CargaLotes("ordenamiento.txt");
                    showConsultaResult(BC.Consulta(desde, hasta));
                }
                break;
            case 6:
                B.Limpiar();
                cout << "Bitacora limpia :)" << endl;
                break;
            default:
                cout << "Numero no valido, intenta de nuevo" << endl;
                break;
        }
    } while (choice != 0);
    return 0;
}
