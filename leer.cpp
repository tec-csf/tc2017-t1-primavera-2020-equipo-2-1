#include <iostream>
#include <fstream>
#include <stack>
#include <cstdio>
using namespace std;
//Hola

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
        if(cont.find("<<")!= string::npos||cont.find("#include")!= string::npos||cont.find("void")!= string::npos){
            conta-=2;
        }
        return conta;
}

void leer(ifstream &ref) {
    int cont = 1;
    string s, contenido;
    int cont2= 0;

    printf("%-11s || %-41s || %-3s \n", "No. Línea", "Código", "OE" );
    printf("%s\n", "--------------------------------------------------------------");

    while(getline(ref, s)) {
        contenido+=s;
        if(contenido.at(0)==' '){
            while(contenido.at(0)==' '){
            contenido=contenido.substr(1,contenido.length());
            }
        }
      printf("%-10d || %-40s || %-3d \n", cont, contenido.c_str(), contador(contenido, '+'));
      contenido = "";
      ++cont;
    }
}

//Método principal
int main(int argc, char const *argv[]) {
    string path = "";
    string option =* (argv + 1);
    if(option == "-i") {
        path =* (argv + 2);
    } else {
        cout << "opcion '" + option + "' no encontrada" << endl;
        return 0;
    }

    int cantidad;
    ifstream archivo;

    archivo.open(path);//direccion del archivo a leer
    if(archivo.fail()) {
        cout << "Error, no se encontro el archivo" << endl;
        return 0;
    } else {
    leer(archivo);
    archivo.close();
    return 0;
    }
}
