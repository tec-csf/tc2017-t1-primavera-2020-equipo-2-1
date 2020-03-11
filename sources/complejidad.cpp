#include <iostream> // cin y cout
#include <fstream>  // archivos
#include <string>   // substr()
#include <cstdio>   // printf()
#include <stack>
#include <vector>
#include "funciones.hpp"
#include "puente.cpp"
using namespace std;

int main(int argc, char const *argv[]) {
  string opcion = *(argv + 1);
  string path;

  if (opcion == "-i") {
    path = *(argv + 2);
  } else {
    cout << "Comando \"" << opcion << "\"" << "no reconocido." << endl;
    return 0;
  }

  ifstream archivo_fuente;

  archivo_fuente.open(path);
  if(archivo_fuente.fail()) {
    cout << "Error, no se encontró el código fuente" << endl;
    return 0;
  } else {
    imprimir_raw(archivo_fuente);
    archivo_fuente.close();
    archivo_fuente.open(path);
    vector<string> fuente;

    llenar(fuente, archivo_fuente);
    archivo_fuente.close();

    imprimir_tabla(fuente);

    return 0;
  }
  
}
