#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <iostream>
using namespace std;
class Puente{
    public:
    string pyton(string s){
        string linea;
        ifstream archivo;
        string aux;
        ofstream archivo2;
        archivo2.open("polinomio.txt");
        archivo2<<s<<endl;
        archivo2.close();
        //system("sudo apt-get update");
        system("sudo apt-get -qq install python-pip");
        system("pip install -qq --user sympy");
        system("python T1_ComplejidadComputacional/sources/bridge.py");
        archivo.open("polinomio.txt");
        if(archivo.is_open()){
            while(getline(archivo,linea)){
                aux=linea;
            }
        }
        archivo.close();
        return aux;
    }
};
