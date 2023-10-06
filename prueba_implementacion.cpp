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
    Bitacora failed_logins();

    return 0;
}
