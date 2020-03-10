#include <iostream> // cin y cout
#include <fstream>  // archivos
#include <string>   // substr()
#include <cstdio>   // printf()
#include <stack>
#include <vector>
#include "funciones.hpp"

using namespace std;

void imprimir_raw(ifstream &archivo) {
  cout << "\n  CÓDIGO FUENTE: \n\n";
  string line;
  while(getline(archivo, line))
    cout << "  " << line << '\n';
  cout << '\n';
}


void llenar(vector<string> &fuente, ifstream &archivo) {
  string str;
  while(getline(archivo, str)) {
    if(str.find_first_not_of(' ') != string::npos) {
      if(str[0] == ' ') {
        while(str[0] == ' ')
          str = str.substr(1, str.length());
      }
      fuente.__emplace_back(str);
    }
  }
}


int contador_OE(string const &line) {
  string::const_iterator i;
  int conta = 0;
  int flag = 0;
  char flak = ' ';

  for(i = line.begin(); i != line.end(); ++i) {
      if(*i == '+' || *i == '-' || *i == '*' || *i == '/' || *i == '%' || *i == '<' || *i == '>' || *i == '=' || *i == '[') {
          if (flag == 0 || (flak != *i && flag == 1)) {
              ++conta;
              flak = *i;
              flag = 1;
          } else
              flag = 0;
      } else
          flag = 0;
  }

  if(line.find("return") != string::npos || line.find("&&") != string::npos || line.find("||") != string::npos)
      ++conta;
  if(line.find("<<") != string::npos || line.find("#include") != string::npos || line.find("void") != string::npos)
      conta -= 3;
  if(conta < 0)
    conta = 0;

  return conta;
}


string analizar_complejidad(string &line, string &poli, vector<string> &fuente, int &num_linea, stack<string>& loops_condiciones, stack<string>& loops_condiciones_end) {
  string::const_iterator i;
  string complejidad_linea;
  int flag = 0;
  char flak = ' ';

  if (line.substr(0,4).compare("void") == 0) {
    return "0";
  }
  else if(line.find("for(") != string::npos || line.find("for (") != string::npos) {
    complejidad_linea = for_loop(line, loops_condiciones, loops_condiciones_end);
    if (poli.length() > 0 && poli.at(poli.length()-1) != '(')
        poli += "+";
    poli += complejidad_linea + "+(" + loops_condiciones.top() + ")(";
    loops_condiciones.pop();
    return complejidad_linea;
  }
  else if(line.find("while(") != string::npos || line.find("while (") != string::npos) {
    complejidad_linea = while_loop(fuente, num_linea, loops_condiciones, loops_condiciones_end);
    if (poli.length() > 0 && poli.at(poli.length() - 1) != '(')
        poli+= "+";
    poli += complejidad_linea + "+(" + loops_condiciones.top() + ")(";
    loops_condiciones.pop();
    return complejidad_linea;
  }
  // else if (line.find("if(") != string::npos || line.find("if (") != string::npos){
  //     complejidad_linea = if_condition(fuente, num_linea, loops_condiciones, loops_condiciones_end);
  //     if (poli.length() > 0 && poli.at(poli.length() - 1) != '(') {
  //         poli += "+";
  //     }
  //     poli += complejidad_linea;
  //     return to_string(contador_OE(line));
  // }
  else if(line.at(0) == '}') {
    if (loops_condiciones_end.size() > 0) {
        poli += ")";
        loops_condiciones_end.pop();
    }
    return "0";
  } else if(line.size() == 0)
    return "0";
  else {
    complejidad_linea = to_string(contador_OE(line));

    if (poli.length() > 0 && poli.at(poli.length()-1) != '(')
        poli += "+";
    poli += complejidad_linea;
    return complejidad_linea;
  }
}


void if_condicion(string &poli, vector<string> &fuente, int num_linea, stack<string>& loops_condiciones, stack<string>& loops_condiciones_end) { }


string for_loop(string &linea, stack<string>& loops_condiciones, stack<string>& loops_condiciones_end) {
  string expresion = "";
  string iteraciones = "";
  string salto = "";
  int i = 0;
  int pos_asignacion, pos_puntoComa1, pos_comparacion, pos_puntoComa2;
  bool complejidad_logaritmica = false;

  while(linea.at(i) != '=')
      ++i;
  pos_asignacion = i + 1;
  while(linea.at(i) != ';')
      ++i;
  pos_puntoComa1 = i + 1;
  while(!is_in(linea.at(i), 2) && !is_in(linea.substr(i, 2), 2))
      ++i;
  if(linea.at(i + 1) == '=')
      ++i;
  pos_comparacion = i + 1;
  while(linea.at(i) != ';')
      ++i;
  pos_puntoComa2 = i + 1;

  if (contador_OE(linea.substr(pos_puntoComa2, linea.length() - pos_puntoComa2 - 1)) > 1) {
      int a = 0;
      int b = linea.length()-1;

      while(linea.at(b) != ')')
          --b;
      a = b;
      while(linea.at(a) != '=' && linea.at(a) != '-' && linea.at(a) != '+' && linea.at(a) != '*' && linea.at(a) != '/')
          --a;
      if(linea.at(a) == '*' || linea.at(a) == '/' || linea.at(a-1) == '*' || linea.at(a-1) == '/')
          complejidad_logaritmica = true;
      else {
          ++a;
          salto.append(linea.substr(a, b-a));
      }
  }

  if (complejidad_logaritmica){
      loops_condiciones.push("logn");
      loops_condiciones_end.push("logn");
      return "logn";
  }

  expresion += to_string(contador_OE(linea.substr(0, pos_puntoComa1))) + "+(" + to_string(contador_OE(linea.substr(pos_puntoComa1, pos_puntoComa2 - pos_puntoComa1))) + ")(";
  iteraciones += "(" + linea.substr(pos_comparacion, pos_puntoComa2 - pos_comparacion - 1) + "-(" + linea.substr(pos_asignacion, pos_puntoComa1 - pos_asignacion - 1) + "))";
  expresion+= iteraciones + "+1)";
  if (salto.length() > 0)
      expresion += "/" + salto;
  expresion += "+(" + to_string(contador_OE(linea.substr(pos_puntoComa2, linea.length() - pos_puntoComa2 - 1))) + ")" + iteraciones;
  if (salto.length() > 0) {
      expresion+= "/" + salto;
      iteraciones+= ")/" + salto;
  }

  iteraciones = eliminar_espacios(iteraciones);
  expresion = eliminar_espacios(expresion);

  loops_condiciones.push(iteraciones);
  loops_condiciones_end.push(iteraciones);

  return expresion;
}


string while_loop(vector<string> &fuente, int const &num_linea, stack<string>& loops_condiciones, stack<string>& loops_condiciones_end) {
  string expresion = "";
  string iteraciones = "";
  string salto = "";
  stack<int> parentesis;
  bool complejidad_logaritmica;
  char variable_incremental;
  int pos_asignacion, pos_puntoComa, pos_comparacion, pos_parentesis, linea_variableIncremental;
  pos_puntoComa = fuente[num_linea - 1].length()-1;
  int a = pos_puntoComa;;
  int b = 0;

  while(fuente[num_linea-1].at(a) != '=') {
      --a;
  }
  pos_asignacion = a + 1;

  while(!is_in(fuente[num_linea].at(b), 2) && !is_in(fuente[num_linea].substr(b, 2), 2)) {
      ++b;
  }
  if(fuente[num_linea].at(b+1) == '=') {
      ++b;
  }
  pos_comparacion = b + 1;
  while(fuente[num_linea].at(b) != ')') {
      ++b;
  }
  pos_parentesis = b + 1;

  variable_incremental = fuente[num_linea - 1].at(pos_asignacion - 2);
  for(int j = num_linea; j < fuente.size(); ++j) {
      if(fuente[j].at(0) == variable_incremental || (j > num_linea && fuente[j].length()>2 && fuente[j].at(fuente[j].length()-2) == variable_incremental)) {
          linea_variableIncremental = j;
          break;
      }
      if(fuente[j].at(fuente[j].length()-1) == '{')
          parentesis.push(1);
      if(fuente[j].at(0) == '}')
          parentesis.pop();
      if(j > num_linea && parentesis.size() == 0){
          linea_variableIncremental = j - 1;
          break;
      }
  }

  if (contador_OE(fuente[linea_variableIncremental]) > 1){
      int operacion = fuente[linea_variableIncremental].length() - 2;

      while(!is_in(fuente[linea_variableIncremental].at(operacion), 1)){
          --operacion;
      }
      if(fuente[linea_variableIncremental].at(operacion) == '*' || fuente[linea_variableIncremental].at(operacion) == '/' || fuente[linea_variableIncremental].at(operacion-1) == '*' || fuente[linea_variableIncremental].at(operacion-1) == '/'){
          complejidad_logaritmica = true;
      } else {
          ++operacion;
          salto.append(fuente[linea_variableIncremental].substr(operacion, (fuente[linea_variableIncremental].length()-1)-operacion));
      }
  }

  if (complejidad_logaritmica){
      loops_condiciones.push("logn");
      loops_condiciones_end.push("logn");
      return "logn";
  }

  expresion+= "(" + to_string(contador_OE(fuente[num_linea])) + ")(";
  iteraciones+= "(" + fuente[num_linea].substr(pos_comparacion, pos_parentesis - pos_comparacion - 1) + "-(" + fuente[num_linea-1].substr(pos_asignacion, pos_puntoComa - pos_asignacion) + "))";
  expresion+= iteraciones + "+1)";
  if (salto.length() > 0) {
      expresion += "/" + salto;
      iteraciones += ")/" + salto;
  }

  iteraciones = eliminar_espacios(iteraciones);
  expresion = eliminar_espacios(expresion);

  loops_condiciones.push(iteraciones);
  loops_condiciones_end.push(iteraciones);

  return expresion;
}


bool is_in(char car, int const &opcion) {
  switch (opcion) {
    case 1:
    {
      char ops_simples[] = {'=', '+', '-', '*', '/', '%'};
      for(int i = 0; i < 6; ++i) {
        if(car == ops_simples[i])
        return true;
      }
      return false;
    }
    case 2:
    {
      char comps_simples[] = {'>', '<', '!'};
      for(int i = 0; i < 3; ++i) {
        if(car == comps_simples[i])
        return true;
      }
      return false;
    }
    default:
      return false;
  }
}


bool is_in(string sub, int const &opcion) {
  switch (opcion) {
    case 1:
    {
        string ops_compuestos[] = {"++", "--", "||", "&&"};
      for(int i = 0; i < 4; ++i) {
          if(sub.compare(ops_compuestos[i]) == 0)
              return true;
      }
      return false;
    }
    case 2:
    {
      string comps_compuestos[] = {"==", "<=", ">=", "!="};
      for(int i = 0; i < 4; ++i) {
          if(sub.compare(comps_compuestos[i]) == 0)
              return true;
      }
      return false;
    }
    default:
      return false;
  }
}


string eliminar_espacios(string &linea) {
    string temp = "";
    for (int i = 0; i < linea.length(); ++i){
        if (linea.at(i) != ' ')
            temp+= linea.at(i);
    }
    return temp;
}


void imprimir_tabla(vector<string> &fuente) {
  stack<string> loops_condiciones;
  stack<string> loops_condiciones_end;
  string poli;

  printf("%s\n", " _________________________________________________________________________________________________________");
  printf(" |%-5s || %-55s || %-35s | \n", "Línea", "Código", "OE" );
  printf(" %s\n", "|-------------------------------------------------------------------------------------------------------|");

  for (int i = 0; i < fuente.size(); ++i)
    printf(" |%- 5d || %-54s || %-35s |\n", i, fuente[i].c_str(), analizar_complejidad(fuente[i], poli, fuente, i, loops_condiciones, loops_condiciones_end).c_str());

  printf(" %s\n", "---------------------------------------------------------------------------------------------------------");
  cout << "\n Polinomio: " << poli << '\n';
}
