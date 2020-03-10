#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>
#include <stack>
#include <vector>

using namespace std;

class Codigo {
  // variables (todo estos son privados)
  stack<string> loops_condiciones;
  stack<string> loops_condiciones_end;
  string ops_compuestos[4];
  string comps_compuestos[4];
  char ops_simples[6];
  char comps_simples[3];
  int linea_actual = 0; 

  // method declaration (definition will be made in cpp)
  public:
    Codigo();
    ~Codigo();

    void analizarComplejidad(string *codigo, int num_lineas);

  protected:
    string complejidad(string *codigo, int num_lineas, int i_real);
    string forLoop(string linea);
    string whileLoop(string *codigo, int numero_lineas, int i);
    string ifCondition(string *codigo, int numero_lineas, int i); 
    int identificar_OE(string linea);
    bool isIn(string sub, string *array);
    bool isIn(char car, char *array);
    string eliminarEspacios(string linea);

  private:

};

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

void Codigo::analizarComplejidad(string *codigo, int num_lineas){
    string polinomio = "";

    printf("%-5s || %-55s || %-50s \n", "Línea", "Código", "OE" );
    printf("%s\n", "--------------------------------------------------------------------------------------------");

    polinomio = complejidad(codigo, num_lineas, 0);

    printf("%s\n", "--------------------------------------------------------------------------------------------");
    cout << endl;

    cout << "Polinomio: " << polinomio  << '\n' << endl;
}

string Codigo::complejidad(string *codigo, int num_lineas, int i_real) {
    string polinomio;
    int numeroLoops = loops_condiciones.size();

    //printf("%-5s || %-55s || %-50s \n", "Línea", "Código", "OE" );
    //printf("%s\n", "--------------------------------------------------------------------------------------------");

    for(int i = 0, j = i_real; i < num_lineas; ++i, ++j) {
        string complejidadLinea = "";

        if (codigo[i].substr(0,4).compare("void") == 0) {

            printf("%- 5d || %-54s ||\n", j + 1, codigo[i].c_str());
            //cout << "(" << i + 1 << ")\t" << codigo[i] << endl;
        }
        else if(codigo[i].substr(0, 4).compare("for(") == 0 || codigo[i].substr(0, 5).compare("for (") == 0) {
            complejidadLinea = forLoop(codigo[i]);

            printf("%- 5d || %-54s || %-49s \n", j + 1, codigo[i].c_str(), complejidadLinea.c_str());
            //cout << "(" <<i+1<<")\t"<<codigo[i]<<"\tOE: "<<complejidadLinea<<endl;

            if (polinomio.length() > 0 && polinomio.at(polinomio.length()-1) != '(') {
                polinomio += "+";
            }
            polinomio += complejidadLinea + "+(" + loops_condiciones.top() + ")(";
            loops_condiciones.pop();
        }
        else if (codigo[i].substr(0, 6).compare("while(") == 0 || codigo[i].substr(0, 7).compare("while (") == 0) {
            complejidadLinea = whileLoop(codigo, num_lineas, i);

            printf("%- 5d || %-54s || %-49s \n", j + 1, codigo[i].c_str(), complejidadLinea.c_str());
            //cout<<"("<<i+1<<")\t"<<codigo[i]<<"\tOE: "<<complejidadLinea<<endl;

            if (polinomio.length()>0 && polinomio.at(polinomio.length()-1) !='('){
                polinomio+= "+";
            }
            polinomio+= complejidadLinea + "+(" + loops_condiciones.top() + ")(";
            loops_condiciones.pop();
        }
        else if (codigo[i].substr(0, 3).compare("if(") == 0 || codigo[i].substr(0, 4).compare("if (") == 0){
            complejidadLinea = ifCondition(codigo, num_lineas, i); 

            printf("%- 5d || %-54s || %-49s \n", j + 1, codigo[i].c_str(), to_string(identificar_OE(codigo[i])).c_str());
            //cout<<"("<<i+1<<")\t"<<codigo[i]<<"\tOE: "<<to_string(identificar_OE(codigo[i]))<<endl;

            if (polinomio.length() > 0 && polinomio.at(polinomio.length()-1) != '(') {
                polinomio+= "+";
            }
            polinomio+= complejidadLinea;

            i = linea_actual;
            j = linea_actual; 
        }
        else if (codigo[i].at(0) == '}') {
            printf("%- 5d || %-54s ||\n", j + 1, codigo[i].c_str());
            //cout<<"("<<i+1<<")\t"<<codigo[i]<<endl;
            if (loops_condiciones_end.size() > 0) {
                polinomio += ")";
                loops_condiciones_end.pop();
            }
        } else {
            complejidadLinea = to_string(identificar_OE(codigo[i]));
            printf("%- 5d || %-54s || %-49s \n", j + 1, codigo[i].c_str(), complejidadLinea.c_str());
            //cout<<"("<<i+1<<")\t"<<codigo[i]<<"\tOE: "<<complejidadLinea<<endl;

            if (polinomio.length() > 0 && polinomio.at(polinomio.length()-1) != '(' && polinomio.at(polinomio.length()-1) != '+') {
                polinomio+= "+";
            }
            polinomio+= complejidadLinea;
        }
    }
    //printf("%s\n", "--------------------------------------------------------------------------------------------");
    //cout << endl;

    //cout << "Polinomio: " << polinomio << '\n' << endl;
    return polinomio; 
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
    if (salto.length()>0){
        expresion+= "(";
    }
    iteraciones+= "(" + linea.substr(pos_comparacion, pos_puntoComa2 - pos_comparacion - 1) + "-(" + linea.substr(pos_asignacion, pos_puntoComa1 - pos_asignacion - 1) + "))";
    expresion+= iteraciones + "+1)";
    if (salto.length()>0){
        expresion+= "/" + salto + ")";
    }
    expresion+= "+(" + to_string(identificar_OE(linea.substr(pos_puntoComa2, linea.length() - pos_puntoComa2 - 1))) + ")";
    if (salto.length()>0){
        expresion+= "("; 
    }
    expresion+= iteraciones;
    if (salto.length()>0){
        expresion+= "/" + salto + ")";
        iteraciones+= "/" + salto;
    }

    iteraciones = eliminarEspacios(iteraciones); 
    expresion = eliminarEspacios(expresion);

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
    if (salto.length()>0){
        expresion+= "(";
    }
    iteraciones+= "(" + codigo[i].substr(pos_comparacion, pos_parentesis - pos_comparacion - 1) + "-(" + codigo[i-1].substr(pos_asignacion, pos_puntoComa - pos_asignacion) + "))";
    expresion+= iteraciones + "+1)";
    if (salto.length()>0){
        expresion+= "/" + salto + ")";
        iteraciones+= "/" + salto;
    }

    iteraciones = eliminarEspacios(iteraciones); 
    expresion = eliminarEspacios(expresion);

    loops_condiciones.push(iteraciones);
    loops_condiciones_end.push(iteraciones);

    return expresion;
}

string Codigo::ifCondition(string *codigo, int numero_lineas, int i){
    string expresion = "";
    vector<string> opcion_de_expresion; 
    stack<int> llaves_if_actual; 

    int inicio_ifelse = i; 
    for(int final_ifelse = inicio_ifelse; final_ifelse < numero_lineas; ++final_ifelse) {
        if(codigo[final_ifelse].at(0) == '}')
            llaves_if_actual.pop();
        if(final_ifelse > inicio_ifelse && llaves_if_actual.size() == 0){
            string temp = ""; 
            int sub_codigo_size = final_ifelse - inicio_ifelse - 1; 
            string sub_codigo[sub_codigo_size]; 

            expresion+= to_string(identificar_OE(codigo[inicio_ifelse])) + "+"; 
            for (int j=inicio_ifelse+1, k=0; j<final_ifelse; j++, k++){
                sub_codigo[k] = codigo[j]; 
                cout<<sub_codigo[k]<<endl;
            }
            temp+= complejidad(sub_codigo, sub_codigo_size, inicio_ifelse);
            opcion_de_expresion.push_back(temp); 

            if (codigo[final_ifelse].substr(1, 4).compare("else") == 0 || codigo[final_ifelse].substr(2, 4).compare("else") == 0){
                inicio_ifelse = final_ifelse; 
            } else if (codigo[final_ifelse+1].substr(0, 4).compare("else") == 0){
                final_ifelse++; 
                inicio_ifelse = final_ifelse;
            } else {
                linea_actual = final_ifelse; 
                break; 
            }
        }
        if(codigo[final_ifelse].at(codigo[final_ifelse].length()-2) == '{')
            llaves_if_actual.push(1);
    }

    expresion+= opcion_de_expresion[0];
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

string Codigo::eliminarEspacios(string linea) {
    string temp = ""; 
    for (int i=0; i<linea.length(); i++){
        if (linea.at(i) != ' '){
            temp+= linea.at(i);
        }
    } 
    return temp; 
}

int main(int argc, char const *argv[]) {
    string path = "";
    string option =* (argv + 1);
    if(option == "-i") {
        path =* (argv + 2);
    } else {
        cout << "opcion '" + option + "' no encontrada" << endl;
        return 0;
    }

    ifstream archivo;

    archivo.open(path);//direccion del archivo a leer
    if(archivo.fail()) {
        cout << "Error, no se encontro el archivo" << endl;
        return 0;
    } else {
      string s;
      string line;

      int tam = 0;
      while(getline(archivo, line)) {
        ++tam;
      }

      archivo.close();
      archivo.open(path);

      string de_archivo[tam];
      int j = 0;

      while(getline(archivo, line)) {
          s += line;
          if(s.at(0)==' '){
              while(s.at(0)==' '){
              s = s.substr(1,s.length());
              }
          }
        de_archivo[j] = s;
        s = "";
        ++j;
      }

    archivo.close();

    Codigo a;

    a.analizarComplejidad(de_archivo, tam);
    return 0;
  }
}
