
#include <iostream>
#include <fstream>
#include <stack>
using namespace std;

int contador(string &cont,char c) {
    string::const_iterator i;
    int conta = 0;
    int flag = 0;
    char flak = ' ';
    
    for(i = cont.begin(); i != cont.end(); ++i) {
        if(*i == c || *i == '=' || *i == '-' || *i == '<' || *i == '>' || *i == '[') {
            if (flag == 0 || (flak != *i && flag == 1)) {
                ++conta;
                flak = *i;
                flag = 1;
            } else {
                flag = 0;
            }
        } else {
            flag = 0;
        }
    }
        if(cont.find("return") != string::npos || cont.find("&&") != string::npos || cont.find("||") != string::npos) {
            ++conta;
        }
        return conta;
};

string leer(ifstream &ref) {
    int cont = 1;
    string s, contenido;
    
    while(getline(ref, s)) {
        contenido += s;
        cout << contenido << " OE: " << contador(contenido, '+') << endl;
        contenido = "";
    }
};

int main() {
    int cantidad;
    string contenido;
    ifstream archivo;
    
    archivo.open("/home/rojo/Escritorio/texto.txt");
    contenido = leer(archivo);
    archivo.close();
}

