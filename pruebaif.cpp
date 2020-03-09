#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>
#include <stack>

#include "clase.hpp"

using namespace std;

//CONSTRUCTOR
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
Codigo::~Codigo() { }

void Codigo::analizarComplejidad(string *codigo, int num_lineas) {
    string polinomio;
    int numeroLoops = loops_condiciones.size();

    printf("%-5s || %-55s || %-50s \n", "Línea", "Código", "OE" );
    printf("%s\n", "--------------------------------------------------------------------------------------------");

    for(int i = 0; i < num_lineas; ++i) {
        string complejidadLinea = "";

        if (codigo[i].substr(0,4).compare("void") == 0) {

            printf("%- 5d || %-54s ||\n", i + 1, codigo[i].c_str());
            // cout << "(" << i + 1 << ")\t" << codigo[i] << endl;
        }
        else if(codigo[i].substr(0, 4).compare("for(") == 0 || codigo[i].substr(0, 5).compare("for (") == 0) {
            complejidadLinea = forLoop(codigo[i]);

            printf("%- 5d || %-54s || %-49s \n", i + 1, codigo[i].c_str(), complejidadLinea.c_str());
            // cout << "(" <<i+1<<")\t"<<codigo[i]<<"\tOE: "<<complejidadLinea<<endl;

            if (polinomio.length() > 0 && polinomio.at(polinomio.length()-1) != '(') {
                polinomio += "+";
            }
            polinomio += complejidadLinea + "+(" + loops_condiciones.top() + ")(";
            loops_condiciones.pop();
        }
        else if (codigo[i].substr(0, 6).compare("while(") == 0 || codigo[i].substr(0, 7).compare("while (") == 0) {
            complejidadLinea = whileLoop(codigo, num_lineas, i);

            printf("%- 5d || %-54s || %-49s \n", i + 1, codigo[i].c_str(), complejidadLinea.c_str());
            // cout<<"("<<i+1<<")\t"<<codigo[i]<<"\tOE: "<<complejidadLinea<<endl;

            if (polinomio.length()>0 && polinomio.at(polinomio.length()-1) !='('){
                polinomio+= "+";
            }
            polinomio+= complejidadLinea + "+(" + loops_condiciones.top() + ")(";
            loops_condiciones.pop();
        }
        else if (codigo[i].at(0) == '}') {
            printf("%- 5d || %-54s ||\n", i + 1, codigo[i].c_str());
            // cout<<"("<<i+1<<")\t"<<codigo[i]<<endl;
            if (loops_condiciones_end.size() > 0) {
                polinomio += ")";
                loops_condiciones_end.pop();
            }
        } else {
            complejidadLinea = to_string(identificar_OE(codigo[i]));
            printf("%- 5d || %-54s || %-49s \n", i + 1, codigo[i].c_str(), complejidadLinea.c_str());
            // cout<<"("<<i+1<<")\t"<<codigo[i]<<"\tOE: "<<complejidadLinea<<endl;

            if (polinomio.length() > 0 && polinomio.at(polinomio.length()-1) != '(') {
                polinomio+= "+";
            }
            polinomio+= complejidadLinea;
        }
    }
    printf("%s\n", "--------------------------------------------------------------------------------------------");
    cout << endl;
    cout << "Polinomio: " << polinomio << '\n' << endl;
}

string Codigo::forLoop(string linea) {
    string expresion = "";
    string iteraciones = "";
    string salto = "";
    int i = 0;
    int pos_asignacion, pos_puntoComa1, pos_comparacion, pos_puntoComa2;
    bool complejidad_logaritmica = false;

    while(linea.at(i) != '='){
        ++i;
    }
    pos_asignacion = i+1;
    while(linea.at(i) != ';'){
        ++i;
    }
    pos_puntoComa1 = i+1;
    while(!isIn(linea.at(i), comps_simples) && !isIn(linea.substr(i, 2), comps_compuestos)){
        ++i;
    }
    if(linea.at(i+1) == '='){
        ++i;
    }
    pos_comparacion = i+1;
    while(linea.at(i) != ';'){
        ++i;
    }
    pos_puntoComa2 = i+1;

    if (identificar_OE(linea.substr(pos_puntoComa2, linea.length() - pos_puntoComa2 - 1))>1){
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
        loops_condiciones.push("logn");
        loops_condiciones_end.push("logn");
        return "logn";
    }

    expresion+= to_string(identificar_OE(linea.substr(0, pos_puntoComa1))) + "+(" + to_string(identificar_OE(linea.substr(pos_puntoComa1, pos_puntoComa2 - pos_puntoComa1))) + ")(";
    iteraciones+= "(" + linea.substr(pos_comparacion, pos_puntoComa2 - pos_comparacion - 1) + "-(" + linea.substr(pos_asignacion, pos_puntoComa1 - pos_asignacion - 1) + "))";
    expresion+= iteraciones + "+1)";
    if (salto.length()>0){
        expresion+= "/" + salto;
    }
    expresion+= "+(" + to_string(identificar_OE(linea.substr(pos_puntoComa2, linea.length() - pos_puntoComa2 - 1))) + ")" + iteraciones;
    if (salto.length()>0){
        expresion+= "/" + salto;
        iteraciones+= ")/" + salto;
    }

    loops_condiciones.push(iteraciones);
    loops_condiciones_end.push(iteraciones);

    return expresion;
}


string Codigo::whileLoop(string *codigo, int numero_lineas, int i){
    string expresion = "";
    string iteraciones = "";
    string salto = "";
    stack<int> parentesis;
    bool complejidad_logaritmica;
    char variable_incremental;
    int pos_asignacion, pos_puntoComa, pos_comparacion, pos_parentesis, linea_variableIncremental;
    pos_puntoComa = codigo[i-1].length()-1;
    int a = pos_puntoComa;;
    int b = 0;

    while(codigo[i-1].at(a) != '=') {
        --a;
    }
    pos_asignacion = a + 1;

    while(!isIn(codigo[i].at(b), comps_simples) && !isIn(codigo[i].substr(b, 2), comps_compuestos)) {
        ++b;
    }
    if(codigo[i].at(b+1) == '=') {
        ++b;
    }
    pos_comparacion = b + 1;
    while(codigo[i].at(b) != ')') {
        ++b;
    }
    pos_parentesis = b + 1;

    variable_incremental = codigo[i - 1].at(pos_asignacion - 2);
    for(int j = i; j < numero_lineas; ++j) {
        if(codigo[j].at(0) == variable_incremental || (j>i && codigo[j].length()>2 && codigo[j].at(codigo[j].length()-2) == variable_incremental)) {
            linea_variableIncremental = j;
            break;
        }
        if(codigo[j].at(codigo[j].length()-1) == '{')
            parentesis.push(1);
        if(codigo[j].at(0) == '}')
            parentesis.pop();
        if(j > i && parentesis.size() == 0){
            linea_variableIncremental = j - 1;
            break;
        }
    }

    if (identificar_OE(codigo[linea_variableIncremental])>1){
        int operacion = codigo[linea_variableIncremental].length()-2;

        while(!isIn(codigo[linea_variableIncremental].at(operacion), ops_simples)){
            --operacion;
        }
        if(codigo[linea_variableIncremental].at(operacion) == '*' || codigo[linea_variableIncremental].at(operacion) == '/' || codigo[linea_variableIncremental].at(operacion-1) == '*' || codigo[linea_variableIncremental].at(operacion-1) == '/'){
            complejidad_logaritmica = true;
        } else {
            ++operacion;
            salto.append(codigo[linea_variableIncremental].substr(operacion, (codigo[linea_variableIncremental].length()-1)-operacion));
        }
    }

    if (complejidad_logaritmica){
        loops_condiciones.push("logn");
        loops_condiciones_end.push("logn");
        return "logn";
    }

    expresion+= "(" + to_string(identificar_OE(codigo[i])) + ")(";
    iteraciones+= "(" + codigo[i].substr(pos_comparacion, pos_parentesis - pos_comparacion - 1) + "-(" + codigo[i-1].substr(pos_asignacion, pos_puntoComa - pos_asignacion) + "))";
    expresion+= iteraciones + "+1)";
    if (salto.length()>0){
        expresion+= "/" + salto;
        iteraciones+= ")/" + salto;
    }

    loops_condiciones.push(iteraciones);
    loops_condiciones_end.push(iteraciones);

    return expresion;
}


int Codigo::identificar_OE(string linea) {
    int num = 0;
    for(int i = 0; i < linea.length(); ++i) {
        if((i < (linea.length() - 1)) && (isIn(linea.substr(i, 2), comps_compuestos) || isIn(linea.substr(i, 2), ops_compuestos))) {
            ++i;
            ++num;
        }
        else if(isIn(linea.at(i), comps_simples) || isIn(linea.at(i), ops_simples)) {
            ++num;
        }
    }
    return num;
}




bool Codigo::isIn(string sub, string *array) {
    for(int i = 0; i < 4; ++i) {
        if(sub.compare(array[i]) == 0)
            return true;
    }
    return false;
}


bool Codigo::isIn(char car, char *array) {
    for(int i = 0; i < 7; ++i) {
        if(car == array[i])
            return true;
    }
    return false;
}
