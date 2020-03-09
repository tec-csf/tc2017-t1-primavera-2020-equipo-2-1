#include <fstream>  // archivos
#include <stack>
#include <vector>

using namespace std;

void imprimir_raw(ifstream &archivo);
void llenar(vector<string> &fuente, ifstream &archivo);
int contador_OE(string line);
string analizar_complejidad(string &line, string &poli, vector<string> &fuente, int const &num_linea);
string for_loop(string &linea, stack<string>& loops_condiciones, stack<string>& loops_condiciones_end);
string while_loop(vector<string> &fuente, int const &num_linea, stack<string>& loops_condiciones, stack<string>& loops_condiciones_end);
bool is_in(char car, int const &opcion);
bool is_in(string sub, int const &opcion);
string eliminar_espacios(string &linea);
void imprimir_tabla(vector<string> &fuente);
