#include <string>
#include <vector>
#include <iostream>
#include <regex>
#include "Bitacora.cpp"
//#include "Bitacora.h"

using namespace std;

int main() {
	Bitacora B({"Mes", "Dia", "Hora", "IP", "Falla"}, "Dia");
	Bitacora BC({"Mes", "Dia", "Hora", "IP", "Falla"}, "Dia");
	int choice;
	vector<vector<string>> registros;
	string desde, hasta, lote;
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
				while(registro[0].size()!=3 || (registro[0] != "ene" && registro[0] != "feb" && registro[0] != "mar" && registro[0] != "abr" && registro[0] != "may" && registro[0] != "jun" && registro[0] != "jul" && registro[0] != "ago" && registro[0] != "sep" && registro[0] != "oct" && registro[0] != "nov" && registro[0] != "dic")){
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
				cout<<"Indica la direccion IP (en formato xxx.xx.xxx.xx:xxxx): ";
				cin>>registro[3];
				regex regexIP("^(\\d{1,3}\\.){3}\\d{1,3}:(\\d{1,5})$");
			    while (!regex_match(registro[3], regexIP)) {
			        cout << "Asegurese de cumplir con el formato de la direccion IP e ingrese nuevamente: ";
			        cin.ignore();
			        cin >> registro[3];
			    }
				cout<<"Indica la razon de falla: ";
				cin.ignore();
				getline(cin, registro[4]);
				B.CargaIndividual(registro);
				registros.push_back(registro);
				bitacora_limpia=false;
				cout<<"Carga individual exitosa"<<endl;
			}
			break;
		case 3:
			if(!bitacora_creada){
                cout<<"La bitacora no ha sido creada todavia"<<endl;
            } else{
            	vector<string> registro(5);
				cout<<"Ingrese el lote completo (Mes Dia Hora IP Falla): ";
				cin.ignore();
				getline(cin, lote);
				//int cantidadEspacios = count(lote.begin(), lote.end(), ' ');
				if(count(lote.begin(), lote.end(), ' ')<4){
			        cout<<"Asegurese de cumplir con los cinco campos e ingrese nuevamente: ";
			        cin.ignore();
					getline(cin, lote);
			    }
		    	stringstream ss(lote);
	            for (int i = 0; i < 4; ++i) {
	                ss >> registro[i];
	            }
	            getline(ss, registro[4]);
		        B.CargaLotes(lote);
		        registros.push_back(registro);
		        bitacora_limpia=false;
	        	cout<<"Lote cargado"<<endl;
			    }
	    	break;
		case 4:
			if(!bitacora_creada){
                cout<<"La bitacora no ha sido creada todavia"<<endl;
            } else{
				B.Ordena("ordenamiento.txt");
				bitacora_ordenada=true;
				cout<<"Ordenamiento exitoso"<<endl; 
				/*if(!B.Bitacora({"Mes", "Dia", "Hora", "IP", "Falla"}, "Mes")){
					cout<<"No se puede ordenar si no existe un registro previo"<<endl;
				}*/
			}
			break;
		case 5:
			if(!bitacora_creada){
                cout<<"La bitacora no ha sido creada todavia"<<endl;
            } 
			/*if(!bitacora_ordenada){
                cout<<"La bitacora no ha sido ordenada todavia"<<endl;
            } */
			if(bitacora_limpia){
                cout<<"La bitacora esta limpia, no hay registros para consultar"<<endl;
            } else{
					cout<<"Indique el dia inicial de la consulta: ";
					cin>>desde;
					cout<<"Indique el dia final de la consulta: ";
					cin>>hasta;
					BC.CargaLotes("ordenamiento.txt");
					BC.Consulta(desde, hasta);
					showConsultaResult(registros);
			}
			break;
		case 6:
			if(!bitacora_creada){
                cout<<"La bitacora no ha sido creada todavia"<<endl;
            } else{
				B.Limpiar();
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
