#include <iostream>
#include <fstream>
#include <stack>
#include <cstdio>
#include <string>

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
    // CONSTRUCTORES
    Codigo();

    // Destructor (SOLO UNO)
    ~Codigo();

    // type name(parameters);
    void analizarComplejidad(ifstream &ref);

  protected:
    string forLoop(string linea);
    int identificarOE(string linea);
    bool isIn(string sub, string *array);
    bool isIn(char car, char *array);

  private:

};
