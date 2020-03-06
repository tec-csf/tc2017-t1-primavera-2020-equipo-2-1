#include <iostream>
#include <fstream>
#include <stack>
#include <cstdio>
#include <string>


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

  Codigo a;
  ifstream archivo;

  archivo.open(path);//direccion del archivo a leer
  if(archivo.fail()) {
    cout << "Error, no se encontro el archivo" << endl;
    return 0;
  } else {
    a.analizarComplejidad(archivo);
    archivo.close();
  return 0;
  }
}
