#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>
#include <stack>

#include "clase.hpp"

using namespace std;


int main(int argc, char const *argv[]) {
    string path = "";
    string option =* (argv + 1);
    if(option == "-i") {
        path =* (argv + 2);
    } else {
        cout << "opcion '" + option + "' no encontrada" << endl;
        return 0;
    }

    ifstream archivo;

    archivo.open(path);//direccion del archivo a leer
    if(archivo.fail()) {
        cout << "Error, no se encontro el archivo" << endl;
        return 0;
    } else {
      string s;
      string line;

      int tam = 0;
      while(getline(archivo, line)) {
        ++tam;
      }

      archivo.close();
      archivo.open(path);

      string de_archivo[tam];
      int j = 0;

      while(getline(archivo, line)) {
          s += line;
          if(s.at(0)==' '){
              while(s.at(0)==' '){
              s = s.substr(1,s.length());
              }
          }
        de_archivo[j] = s;
        s = "";
        ++j;
      }

    archivo.close();

    Codigo a;

    a.analizarComplejidad(de_archivo, tam);
    return 0;
  }
}
