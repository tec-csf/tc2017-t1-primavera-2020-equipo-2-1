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
        if(cont.find("<<")!= string::npos||cont.find("#include")!= string::npos||cont.find("void")!= string::npos){
            conta-=2;
        }
        return conta;
}

void leer(ifstream &ref) {
    int cont = 1;
    string s, contenido;

    cout << "No. Línea || " << " Código\t\t\t\t\t\t || " << "OE: " << '\n';
    cout << "-------------------------------------------------------------------" << '\n';

    while(getline(ref, s)) {
        cout << "   " << cont << "\t ||  ";
        contenido += s;
        cout << contenido << "\t\t\t\t ||  " << contador(contenido, '+') << endl;
        contenido = "";
        ++cont;
    }
}

//Método principal
int main(int argc, char const *argv[]){
    string path="";
    string option=*(argv+1);
    if(option=="-i"){
        path=*(argv+2);
    }
    else{
        cout<<"opcion '"+option+"' no encontrada"<<endl;
        return 0;
    }
    int cantidad;
    ifstream archivo;
    archivo.open(path);//direccion del archivo a leer
    if(archivo.fail()){
        cout<<"Error, no se encontro el archivo"<<endl;
        return 0;
    }
    else{
    leer(archivo);
    archivo.close();
    return 0;
    }
}
