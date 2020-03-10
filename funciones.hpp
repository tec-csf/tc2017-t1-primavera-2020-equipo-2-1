#include <fstream>  // archivos
#include <stack>
#include <vector>

using namespace std;

/* Imprime el código fuente como se encuentra en su archivo.
 *
 * @param &archivo: es la referencia del archivo que se lee desde la terminal
 *
 */
void imprimir_raw(ifstream &archivo);


/* Pasa en cada espacio de un vector de strings cada línea del código fuente,
 * para su análisis de complejidad.
 *
 * @param &fuente: almacenará por espacio, una línea del código.
 * @param &archivo: es la referencia del archivo que se lee desde la terminal.
 *
 */
void llenar(vector<string> &fuente, ifstream &archivo);


/* Cuenta OE de línea actual, regresa el valor entero.
 *
 * @param &line (constante): contiene línea de código a interpretar.
 *              (constante evita que se cree copia, ahorrando costo computaiconal)
 *
 */
int contador_OE(string const &line);


/* Regresa polinomio con la complejidad de línea actual
 *
 * @param &line: contiene línea de código a interpretar.
 * @param &poli: irá concatenando el polinomio de todo el código.
 * @param &fuente: vector que almacenará por espacio, una línea del código.
 * @param &num_linea: indice que indica osbre qué línea se está iterando.
 * @param &loops_condiciones: auxiliar en mantener los ciclos anidados.
 * @param &loops_condiciones_end: auxiliar en mantener los ciclos anidados.
 *
 */
string analizar_complejidad(string &line, string &poli, vector<string> &fuente, int const &num_linea, stack<string>& loops_condiciones, stack<string>& loops_condiciones_end);


/* Analiza complejidad de if/elses; regresa polinomio más complejo de if/elses.
 *
 * @param &fuente: vector que almacenará por espacio, una línea del código.
 * @param &num_linea: indice que indica osbre qué línea se está iterando.
 * @param &loops_condiciones: auxiliar en mantener los ciclos anidados.
 * @param &loops_condiciones_end: auxiliar en mantener los ciclos anidados.
 *
 */
string if_condicion(vector<string> &fuente, int num_linea, stack<string>& loops_condiciones, stack<string>& loops_condiciones_end);


/* Regresa polinomio con complejidad del for; modifica por referencia al polinomio final.
 *
 * @param &poli: irá concatenando el polinomio de todo el código.
 * @param &fuente: vector que almacenará por espacio, una línea del código.
 * @param &num_linea: indice que indica osbre qué línea se está iterando.
 * @param &loops_condiciones: auxiliar en mantener los ciclos anidados.
 * @param &loops_condiciones_end: auxiliar en mantener los ciclos anidados.
 *
 */
string for_loop(string &linea, stack<string>& loops_condiciones, stack<string>& loops_condiciones_end);

/* Regresa polinomio con complejidad del while; modifica por referencia al polinomio final.
 *
 * @param &fuente: vector que almacenará por espacio, una línea del código.
 * @param &num_linea (constante): indice que indica osbre qué línea se está iterando.
 * @param &loops_condiciones: auxiliar en mantener los ciclos anidados.
 * @param &loops_condiciones_end: auxiliar en mantener los ciclos anidados.
 *
 */
string while_loop(vector<string> &fuente, int const &num_linea, stack<string>& loops_condiciones, stack<string>& loops_condiciones_end);


/* Auxiliares en for_loop y while_loop; confirma que símbolo está en línea de código.
 *
 * @param car: una parte del string de la línea de código analizándose.
 * @param sub: una parte del string de la línea de código analizándose.
 * @param &opcion (constante): decide qué caso se analizará:
 *                                                        1 = operadores.
 *                                                        2 = comparadores.
 *
 */
bool is_in(char car, int const &opcion);
bool is_in(string sub, int const &opcion);


/* Auxiliar en if_condicion; regresa complejidad de la.
 *
 * @param &line: contiene línea de código a interpretar.
 * @param &fuente: vector que almacenará por espacio, una línea del código.
 * @param num_linea: indice que indica osbre qué línea se está iterando.
 * @param &loops_condiciones: auxiliar en mantener los ciclos anidados.
 * @param &loops_condiciones_end: auxiliar en mantener los ciclos anidados.
 *
 */
string analizar_complejidad_if(string &line, vector<string> &fuente, int &num_linea, stack<string>& loops_condiciones, stack<string>& loops_condiciones_end);


/* Limpia polinomios para mejor interpretación,
 * eliminando tabulaciones iniciales y lineas vacías
 *
 * @param &linea: contiene línea de código a interpretar.
 *
 */
string eliminar_espacios(string &linea);


/* Imprime tabla con formato
 *
 * @param &fuente: vector que almacenará por espacio, una línea del código.
 *
 */
void imprimir_tabla(vector<string> &fuente);
