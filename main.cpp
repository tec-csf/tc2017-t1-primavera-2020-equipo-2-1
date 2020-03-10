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
    if(str.find_first_not_of(' ') != std::string::npos) {
      if(str[0] == ' ') {
        while(str[0] == ' ')
          str = str.substr(1, str.length());
      }
      fuente.emplace_back(str);
    } else
      fuente.emplace_back(" ");
  }
}


int contador_OE(string line) {
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

  if(line.find("return") != string::npos || line.find("&&") != string::npos || line.find("||") != string::npos|| line.find("cout") != string::npos)
      ++conta;
  if(line.find("<<") != string::npos || line.find("#include") != string::npos || line.find("void") != string::npos)
      conta -= 2;
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
  else if (line.find("if(") != string::npos || line.find("if (") != string::npos || line.find("else") != string::npos || line.find("else{") != string::npos){
  complejidad_linea=to_string(contador_OE(line));
  if_condicion(fuente, num_linea,loops_condiciones, loops_condiciones_end);
  return complejidad_linea;
  }
   /*   if (poli.length() > 0 && poli.at(poli.length() - 1) != '(') {
   //       poli += "+";
   //   }
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
    */
  else {
    complejidad_linea = to_string(contador_OE(line));

    if (poli.length() > 0 && poli.at(poli.length()-1) != '(')
        poli += "+";
    poli += complejidad_linea;
    return complejidad_linea;
  }
}
void if_condicion(vector<string>& fuente, int num_linea,stack<string>& loops_condiciones, stack<string>& loops_condiciones_end){
  stack<char> capas;
  string poli_temp, poli_complejo;
  string complejidad_linea;
  poli_complejo="";
  bool atorado= false;
  int linea_atorada;
  capas.push('{');
  ++num_linea;
  while(!capas.empty()){
    poli_temp= analizar_complejidad(fuente[num_linea],poli_temp,fuente, num_linea, loops_condiciones,loops_condiciones_end);
    poli_complejo+=poli_temp+"+";
    if(fuente[num_linea].find('{')!= string::npos){
      capas.push('{');
    }
    else if(fuente[num_linea].find('}')!= string::npos){
      capas.pop();
    }

    ++num_linea;
  }
  poli_temp=poli_complejo;
  poli_complejo=poli_temp.substr(0,poli_temp.size()-1);
  //cout<<poli_complejo<<endl;
  poli_ifs.emplace_back(poli_complejo);
}
// string if_condition(vector<string> &fuente, int &num_linea, stack<string>& loops_condiciones, stack<string>& loops_condiciones_end) {
//     string expresion = "";
//     vector<string> opcion_de_expresion;
//     stack<int> llaves_if_actual;
//     int inicio_ifelse = num_linea;
//
//     for(int final_ifelse = inicio_ifelse; final_ifelse < fuente.size(); ++final_ifelse) {
//         if(fuente[final_ifelse].at(fuente[final_ifelse].length() - 2) == '{')
//             llaves_if_actual.push(1);
//         if(final_ifelse > inicio_ifelse && llaves_if_actual.size() == 0){
//             string temp = "";
//             string poli2 = "";
//             int sub_codigo_size = final_ifelse - inicio_ifelse - 1;
//             string sub_codigo[sub_codigo_size];
//
//             expresion += to_string(contador_OE(fuente[inicio_ifelse])) + "+";
//             for (int j = inicio_ifelse + 1, k = 0; j < final_ifelse; ++j, ++k)
//                 // sub_codigo[k] = fuente[j];
//                 temp += analizar_complejidad(fuente[j], poli2, fuente, j, loops_condiciones, loops_condiciones_end);
//             // temp += complejidad(sub_codigo, sub_codigo_size, inicio_ifelse);
//             // cout << "\n temp: " << temp << '\n';
//             opcion_de_expresion.push_back(temp);
//
//             if (fuente[final_ifelse].substr(1, 4).compare("else") == 0 || fuente[final_ifelse].substr(2, 4).compare("else") == 0 || fuente[final_ifelse+1].substr(0, 4).compare("else") == 0){
//                 inicio_ifelse = final_ifelse;
//             } else {
//                 num_linea = final_ifelse;
//                 break;
//             }
//         }
//         if(fuente[final_ifelse].at(0) == '}')
//             llaves_if_actual.pop();
//     }
//
//     expresion+= opcion_de_expresion[0];
//     // cout << "\n expresion: " << expresion << '\n';
//     return expresion;
// }


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
