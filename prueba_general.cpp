#include <string>
#include <vector>
#include <iostream>
#include <regex>
#include "Bitacora.cpp"
//#include "Bitacora.h"

using namespace std;

/**
 * Funcion para imprimir el resultado de una consulta en la consola.
 * Complejidad O(n^2)
 *
 * @param consultaRes es un vector de eventos que regresada por la funcion consulta 
 */
void showConsultaResult(vector<evento> consultaRes) {
    for (int i = 0; i < consultaRes.size(); i++) {
        for (int j = 0; j < consultaRes[i].size(); j++) {
            cout << consultaRes[i][j] << " ";
        }
        cout << endl;
    }
}

int main(){
	int choice;
	string desde, hasta, nomArchivo;
	int num_campos = 5;
	vector<string> campos(num_campos);
	vector<string> registro(num_campos);
	string campo_clave;
    Bitacora* bitacoraPtr = nullptr;
    bitacoraPtr = nullptr;
	while(true){
		cout<<"-------------------------------------------------"<<endl;
		cout<<"			Menu			"<<endl;
		cout<<"-------------------------------------------------"<<endl;
	    cout<<"\n0) Salir del programa\n1) Crear bitacora\n2) Carga individual \n3) Carga lotes \n4) Ordenar bitacora\n5) Consultar bitacora\n6) Limpiar bitacora"<<endl;
	    cout<<"\nPresione el numero de la opcion que desee realizar: ";
	    cin>>choice;
	
	if(choice== 0){
		delete bitacoraPtr;
        return 0;
    }if(choice == 1){
        cout<<"Indica el numero de campos de la bitacora: ";
        cin >> num_campos;
        cout<<"Indica el nombre de los campos: "<<endl;
        for(int i=0; i<num_campos; i++){
            cin>>campos[i];
        }
        cout<<"Indica el nombre del campo clave: ";
        cin>>campo_clave;
        bitacoraPtr = new Bitacora(campos, campo_clave);
		cout<<"La bitacora sido creada"<<endl;
		continue;
    }if(choice== 2){
		if(bitacoraPtr == nullptr){
            cout<<"La bitacora no ha sido creada todavia"<<endl;
        } else{
            for(int i=0; i<num_campos; i++){
                cout<<"Indica el "<<campos[i]<<": ";
                cin>>registro[i];
            }
            bitacoraPtr->cargaIndividual(registro);
		}
		continue;
	}if(choice==3){
		if(bitacoraPtr == nullptr){
            cout<<"La bitacora no ha sido creada todavia"<<endl;
        } else{
        	vector<string> registro(num_campos);
			cout<<"Ingrese el nombre del archivo con los registros a cargar: ";	
			cin.ignore();			
			cin>>nomArchivo;
		    bitacoraPtr->cargaLotes(nomArchivo);
			}
	    continue;
	}if(choice== 4){
		if(bitacoraPtr == nullptr){
            cout<<"La bitacora no ha sido creada todavia"<<endl;
        } else{
			string nomArchivoOrdenado;
			cout<<"Ingrese el nombre del archivo donde se guardara la bitacora ordenada: ";
			cin>>nomArchivoOrdenado;
			bitacoraPtr->ordena(nomArchivoOrdenado);
		}
		continue;
	}if(choice== 5){
		if(bitacoraPtr == nullptr){
            cout<<"La bitacora no ha sido creada todavia"<<endl;
        }else{
			cout<<"Indique el valor inicial de la consulta: ";
			cin>>desde;
			cout<<"Indique el valor final de la consulta: ";
			cin>>hasta;
			int desde_num = stoi(desde);
        	int hasta_num = stoi(hasta);
			showConsultaResult(bitacoraPtr->consulta(desde, hasta));
			}
			continue;
		}if(choice == 6){
			if(bitacoraPtr == nullptr){
	            cout<<"La bitacora no ha sido creada todavia"<<endl;
	        }else {
				bitacoraPtr->limpiar();
			}
		}else{
		    cout<<"Esa opcion no se encuentra en el menu, intenta de nuevo"<<endl;
		}
	}
	delete bitacoraPtr;
	return 0;
}