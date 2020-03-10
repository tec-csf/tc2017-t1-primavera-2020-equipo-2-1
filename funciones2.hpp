#include <fstream>  // archivos
#include <stack>
#include <vector>

using namespace std;

// Imprime el código fuente como esta en .cpp
void imprimir_raw(ifstream &archivo);

// Pasa a un vector cada línea del código fuente, sin espacios iniciales, para su análisis
void llenar(vector<string> &fuente, ifstream &archivo);

// Cuenta OE de línea actual
int contador_OE(string line);

// Regresa polinomio con la complejidad de línea actual
string analizar_complejidad(string &line, string &poli, vector<string> &fuente, int const &num_linea, stack<string>& loops_condiciones, stack<string>& loops_condiciones_end);

// Analiza complejidad de if/elses
// string if_condition(vector<string> &fuente, int &num_linea, stack<string>& loops_condiciones, stack<string>& loops_condiciones_end);

// Analiza la complejidad del for
string for_loop(string &linea, stack<string>& loops_condiciones, stack<string>& loops_condiciones_end);

// Analiza la complejidad del while
string while_loop(vector<string> &fuente, int const &num_linea, stack<string>& loops_condiciones, stack<string>& loops_condiciones_end);

void if_condicion(vector<string> &fuente, int num_linea, stack<string>& loops_condiciones, stack<string>& loops_condiciones_end);

// Auxiliares en for_loop y while_loop
bool is_in(char car, int const &opcion);
bool is_in(string sub, int const &opcion);

// Limpia polinomios para mejor interpretación
string eliminar_espacios(string &linea);

// Imprime tabla con formato
void imprimir_tabla(vector<string> &fuente);
vector <string> poli_ifs;