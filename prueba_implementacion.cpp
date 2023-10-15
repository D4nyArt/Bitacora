#include <string>
#include <vector>
#include <iostream>
#include <regex>
#include "Bitacora.cpp"
//#include "Bitacora.h"

using namespace std;

/*void showConsultaResult(vector<vector<string>> consultaRes) {
    for (int i = 0; i < consultaRes.size(); i++) {
        for (int j = 0; j < consultaRes[i].size(); j++) {
            cout << consultaRes[i][j] << " ";
        }
        cout << endl;
    }
}*/

int main() {
	Bitacora B({"Mes", "Dia", "Hora", "IP", "Falla"}, "Dia");
	int choice;
	vector<vector<string>> registros;
	string desde, hasta, nomArchivo;
	bool bitacora_creada=false;
	bool bitacora_ordenada=false;
	bool bitacora_limpia=true;
	while(true){
		cout<<"-------------------------------------------------"<<endl;
		cout<<"			Menu			"<<endl;
		cout<<"-------------------------------------------------"<<endl;
	    cout<<"\n0) Salir del programa\n1) Crear bitacora\n2) Carga individual \n3) Carga lotes \n4) Ordenar bitacora\n5) Consultar bitacora\n6) Limpiar bitacora"<<endl;
	    cout<<"\nPresione el numero de la opcion que desee realizar: ";
	    cin>>choice;
	
	    switch (choice){
	    case 0:
            return 0;
	    case 1:
			B = Bitacora({"Mes", "Dia", "Hora", "IP", "Falla"}, "Dia");
            bitacora_creada=true;
            bitacora_limpia=true;
			cout<<"Bitacora creada"<<endl;
			break;
		case 2:
			if(!bitacora_creada){
                cout<<"La bitacora no ha sido creada todavia"<<endl;
            } else{
            	vector<string> registro(5);
				cout<<"Indica el mes (coloca las primeras 3 letras en minuscula): ";
				cin.ignore();
				cin>>registro[0];
				regex regexFecha("^(ene|feb|mar|abr|may|jun|jul|ago|sep|oct|nov|dic)$");
				while(!regex_match(registro[0], regexFecha)){
			        cout<<"El mes debe tener exactamente 3 letras en minuscula. Ingrese nuevamente: ";
			        cin.ignore();
			        cin>>registro[0];
			    }
				cout<<"Indica el dia: ";
				cin>>registro[1];
				while(stoi(registro[1])<1 || stoi(registro[1])>31){
			        cout<<"El dia debe estar en el rango de 1 a 31. Ingrese nuevamente: ";
			        cin>>registro[1];
			    }
				cout<<"Indica la hora (hh:mm:ss): ";
				cin>>registro[2];
				while (registro[2].size()!=8 || registro[2][2]!=':' || registro[2][5]!=':' || stoi(registro[2].substr(0, 2))>23 || stoi(registro[2].substr(3, 2))>59 || stoi(registro[2].substr(6, 2))>59){
			        cout<<"Asegurese de cumplir con el formato de hora e ingrese nuevamente: ";
			        cin.ignore();
			        cin>>registro[2];
			    }
				cout<<"Indica la direccion IP (en formato 1-3 digitos.1-2 digitos.1-3 digitos.1-2 digitos:xxxx): ";
				cin>>registro[3];
				regex regexIP("^(\\d{1,3}\\.\\d{1,2}\\.\\d{1,3}\\.\\d{1,2}):(\\d{4})$");
			    while (!regex_match(registro[3], regexIP)) {
			        cout << "Asegurese de cumplir con el formato de la direccion IP e ingrese nuevamente: ";
			        cin.ignore();
			        cin >> registro[3];
			    }
				cout<<"Indica la razon de falla: ";
				cin.ignore();
				getline(cin, registro[4]);
				B.cargaIndividual(registro);
				bitacora_limpia=false;
				bitacora_ordenada=false;
				cout<<"Carga individual exitosa"<<endl;
			}
			break;
		case 3:
			if(!bitacora_creada){
                cout<<"La bitacora no ha sido creada todavia"<<endl;
            } else{
            	vector<string> registro(5);
				cout<<"Ingrese el nombre del archivo con los registros a cargar: ";
				cin>>nomArchivo;
		        B.cargaLotes(nomArchivo);
		        bitacora_limpia=false;
		        bitacora_ordenada=false;
	        	cout<<"Lote cargado"<<endl;
			    }
	    	break;
		case 4:
			if(!bitacora_creada){
                cout<<"La bitacora no ha sido creada todavia"<<endl;
            } else if(bitacora_limpia){
                cout<<"No hay registros para ordenar"<<endl;
            } else if(bitacora_ordenada){
                cout<<"La bitacora ya esta ordenada"<<endl;
            } else{
            	cout<<"Ingrese el nombre del archivo donde se guardara el ordenamiento: ";
				cin>>nomArchivo;
				B.ordena(nomArchivo);
				bitacora_ordenada=true;
				cout<<"Ordenamiento exitoso"<<endl;
			}
			break;
		case 5:
			if(!bitacora_creada){
                cout<<"La bitacora no ha sido creada todavia"<<endl;
            } else if(bitacora_limpia){
                cout<<"No hay registros para consultar"<<endl;
            } else if(!bitacora_ordenada){
                cout<<"La bitacora no ha sido ordenada todavia"<<endl;
            } else{
					cout<<"Indique el dia inicial de la consulta: ";
					cin>>desde;
					cout<<"Indique el dia final de la consulta: ";
					cin>>hasta;
					B.cargaLotes("ordenamiento.txt");
					B.consulta(desde, hasta);
					showConsultaResult(registros);
			}
			break;
		case 6:
			if(!bitacora_creada){
                cout<<"La bitacora no ha sido creada todavia"<<endl;
            } else if(bitacora_limpia){
                cout<<"No hay registros para limpiar"<<endl;
            } else {
				B.limpiar();
				bitacora_limpia=true;
				cout<<"Bitacora limpia :)"<<endl;
			}
			break;
		default:
	        cout<<"Esa opcion no se encuentra en el menu, intenta de nuevo"<<endl;
	        break;
		}
	}
	return 0;
}
