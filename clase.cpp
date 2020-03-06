#include <iostream>
#include <stack>
#include <string>
#include <fstream>
#include <cstdio>

#include "clase.hpp"

using namespace std;

//CONSTRUCTORES
// Class::Class(std::string new_name)
//   : name(new_name) {}

Codigo::Codigo() {
  ops_compuestos[0] = "++";
  ops_compuestos[1] = "--";
  ops_compuestos[2] = "&&";
  ops_compuestos[3] = "||";

  comps_compuestos[0] = "==";
  comps_compuestos[1] = "<=";
  comps_compuestos[2] = ">=";
  comps_compuestos[3] = "!=";

  ops_simples[0] = '=';
  ops_simples[1] = '+';
  ops_simples[2] = '-';
  ops_simples[3] = '*';
  ops_simples[4] = '/';
  ops_simples[5] = '%';

  comps_simples[0] = '<';
  comps_simples[1] = '>';
  comps_simples[2] = '!';
}

// Destructor
Codigo::~Codigo() {
  // std::cout << "Goodbye " << title; // Optional
}

void Codigo::analizarComplejidad(ifstream &ref) {
    int i = 0;
    string s, contenido;
    string polinomio;
    int numeroLoops = loops_condiciones.size();

    printf("%-5s || %-41s || %-50s \n", "Línea", "Código", "OE" );
    printf("%s\n", "--------------------------------------------------------------------------------------------");

    while(getline(ref, s)) { // Como obtener el size de un arreglo
        contenido += s;
        string complejidadLinea = "";
        if(contenido.substr(0,4).compare("for(") == 0) {
            complejidadLinea = forLoop(contenido);

            printf("%-5d || %-40s || %-49s \n", i + 1, contenido.c_str(), complejidadLinea.c_str());

            if (polinomio.length()>0 && polinomio.at(polinomio.length()-1) !='(') {
                polinomio.append("+");
            }
            polinomio.append(complejidadLinea);
            polinomio.append("+(");
            polinomio.append(loops_condiciones.top());
            loops_condiciones.pop();
            polinomio.append(")(");
        }
        else if (contenido.at(0) == '}') {
            if (loops_condiciones_end.size() > 0) {
                polinomio.append(")");
                loops_condiciones_end.pop();
            }
        } else {
            complejidadLinea = to_string(identificarOE(contenido));
            printf("%-5d || %-40s || %-49s \n", i + 1, contenido.c_str(), complejidadLinea.c_str());

            if (polinomio.length() > 0 && polinomio.at(polinomio.length()-1) != '(') {
                polinomio.append("+");
            }
            polinomio.append(complejidadLinea);
        }
        contenido = "";
        ++i;
    }

    cout << '\n';
    cout << polinomio << endl;
}

string Codigo::forLoop(string linea){
    string expresion = "";
    string iteraciones = "";
    string salto = "";
    int i = 0;
    int pos_asignacion, pos_puntoComa1, pos_comparacion, pos_puntoComa2;
    bool complejidad_logaritmica = false;

    while(linea.at(i) != '=') {
        ++i;
    }
    pos_asignacion = i + 1;
    while(linea.at(i) != ';'){
        ++i;
    }
    pos_puntoComa1 = i + 1;
    while(!isIn(linea.at(i), comps_simples) && !isIn(linea.substr(i, 2), comps_compuestos)){
        ++i;
    }
    if(linea.at(i + 1) == '='){
        ++i;
    }
    pos_comparacion = i + 1;
    while(linea.at(i) != ';'){
        ++i;
    }
    pos_puntoComa2 = i + 1;

    if (identificarOE(linea.substr(pos_puntoComa2, linea.length() - pos_puntoComa2 - 1))>1){
        int a = 0;
        int b = linea.length()-1;

        while(linea.at(b) != ')'){
            --b;
        }
        a = b;
        while(linea.at(a) != '=' && linea.at(a) != '-' && linea.at(a) != '+' && linea.at(a) != '*' && linea.at(a) != '/'){
            --a;
        }
        if(linea.at(a) == '*' || linea.at(a) == '/' || linea.at(a-1) == '*' || linea.at(a-1) == '/'){
            complejidad_logaritmica = true;
        } else {
            ++a;
            salto.append(linea.substr(a, b-a));
        }
    }

    if (complejidad_logaritmica){
        loops_condiciones.push("log(n)");
        loops_condiciones_end.push("log(n)");
        return "log(n)";
    }

    expresion.append(to_string(identificarOE(linea.substr(0, pos_puntoComa1))));
    expresion.append("+(");
    expresion.append(to_string(identificarOE(linea.substr(pos_puntoComa1, pos_puntoComa2 - pos_puntoComa1))));
    expresion.append(")(");
    iteraciones.append(linea.substr(pos_comparacion, pos_puntoComa2 - pos_comparacion - 1));
    iteraciones.append("-(");
    iteraciones.append(linea.substr(pos_asignacion, pos_puntoComa1 - pos_asignacion - 1));
    iteraciones.append(")");
    expresion.append(iteraciones);
    expresion.append("+1)");
    if (salto.length()>0){
        expresion.append("/");
        expresion.append(salto);
    }
    expresion.append("+(");
    expresion.append(to_string(identificarOE(linea.substr(pos_puntoComa2, linea.length() - pos_puntoComa2 - 1))));
    expresion.append(")(");
    expresion.append(iteraciones);
    expresion.append(")");
    if (salto.length()>0){
        expresion.append("/");
        expresion.append(salto);
    }

    loops_condiciones.push(iteraciones);
    loops_condiciones_end.push(iteraciones);

    return expresion;
}

int Codigo::identificarOE(string linea){
    int num = 0;
    for(int i=0; i<linea.length(); ++i){
        if((i < (linea.length() - 1)) && (isIn(linea.substr(i, 2), comps_compuestos) || isIn(linea.substr(i, 2), ops_compuestos))){
            ++i;
            ++num;
        }
        else if(isIn(linea.at(i), comps_simples) || isIn(linea.at(i), ops_simples)){
            ++num;
        }
    }
    return num;
}

bool Codigo::isIn(string sub, string *array) {
    for(int i = 0; i < 4; ++i) {
        if(sub.compare(array[i]) == 0) {
            return true;
        }
    }
    return false;
}

bool Codigo::isIn(char car, char *array) {
    for(int i = 0; i < 6; ++i) {
        if(car == array[i]) {
            return true;
        }
    }
    return false;
}
