#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>
#include <stack>

using namespace std;

class Codigo
{
  // variables (todo estos son privados)
  stack<string> loops_condiciones;
  stack<string> loops_condiciones_end;
  string ops_compuestos[4];
  string comps_compuestos[4];
  char ops_simples[6];
  char comps_simples[3];

  // method declaration (definition will be made in cpp)
  public:
    Codigo();
    ~Codigo();

    void analizarComplejidad(string *codigo, int numeroLineas);

  protected:
    string forLoop(string linea);
    string whileLoop(string *codigo, int numero_lineas, int i);
    int identificarOE(string linea);
    bool isIn(string sub, string *array);
    bool isIn(char car, char *array);

  private:

};
