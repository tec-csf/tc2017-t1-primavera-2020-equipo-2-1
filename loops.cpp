/*  Andrés Barragán
    Codigo que analiza la complejidad de un algoritmo con "for" y "while" inlcuido.*/

#include <iostream>
#include <stack>
#include <string>
using namespace std;

class Analizar{
    stack<string> pilaLoopsCondiciones_end; 
    stack<string> pilaLoopsCondiciones;
    string comparadoresCompuestos[4] = {"==", "<=", ">=", "!="};
    char comparadoresSimples[3] = {'<', '>', '!'};
    string operadoresCompuestos[4] = {"++", "--", "&&", "||"};
    char operadoresSimples[7] = {'=', '+', '-', '*', '/', '%', '['};

    public: 
        void analizarComplejidad(string *codigo, int numeroLineas){
            string polinomio; 
            int numeroLoops = pilaLoopsCondiciones.size(); 

            for(int i=0; i<numeroLineas; i++){//Como obtener el size de un arreglo
                string complejidadLinea = ""; 
                if (codigo[i].substr(0,4).compare("void") == 0){
                    cout<<"("<<i+1<<")\t"<<codigo[i]<<endl; 
                }
                else if(codigo[i].substr(0,4).compare("for(") == 0 || codigo[i].substr(0,5).compare("for (") == 0){
                    complejidadLinea = forLoop(codigo[i]); 
                    cout<<"("<<i+1<<")\t"<<codigo[i]<<"\tOE: "<<complejidadLinea<<endl;

                    if (polinomio.length()>0 && polinomio.at(polinomio.length()-1) !='('){
                        polinomio+= "+"; 
                    }
                    polinomio+= complejidadLinea + "+(" + pilaLoopsCondiciones.top() + ")(";
                    pilaLoopsCondiciones.pop(); 
                }
                else if (codigo[i].substr(0, 6).compare("while(") == 0 || codigo[i].substr(0, 7).compare("while (") == 0){
                    complejidadLinea = whileLoop(codigo, numeroLineas, i); 
                    cout<<"("<<i+1<<")\t"<<codigo[i]<<"\tOE: "<<complejidadLinea<<endl;

                    if (polinomio.length()>0 && polinomio.at(polinomio.length()-1) !='('){
                        polinomio+= "+"; 
                    }
                    polinomio+= complejidadLinea + "+(" + pilaLoopsCondiciones.top() + ")("; 
                    pilaLoopsCondiciones.pop(); 
                }
                else if (codigo[i].at(0) == '}'){
                    cout<<"("<<i+1<<")\t"<<codigo[i]<<endl; 
                    if (pilaLoopsCondiciones_end.size() > 0){
                        polinomio+= ")"; 
                        pilaLoopsCondiciones_end.pop();
                    }
                }
                else {
                    complejidadLinea = to_string(identificarOE(codigo[i])); 
                    cout<<"("<<i+1<<")\t"<<codigo[i]<<"\tOE: "<<complejidadLinea<<endl;

                    if (polinomio.length()>0 && polinomio.at(polinomio.length()-1) !='('){
                        polinomio+= "+"; 
                    }
                    polinomio+= complejidadLinea; 
                }
            }

            cout<<endl; 
            cout<<polinomio<<endl;
        }

    private: 
        string forLoop(string linea){
            string expresion = ""; 
            string iteraciones = "";
            string salto = "";
            int i = 0;
            int pos_asignacion, pos_puntoComa1, pos_comparacion, pos_puntoComa2; 
            bool complejidad_logaritmica = false; 

            while(linea.at(i) != '='){
                i++; 
            }
            pos_asignacion = i+1; 
            while(linea.at(i) != ';'){
                i++;
            }
            pos_puntoComa1 = i+1; 
            while(!isIn(linea.at(i), comparadoresSimples) && !isIn(linea.substr(i, 2), comparadoresCompuestos)){
                i++;
            }
            if(linea.at(i+1) == '='){
                i++;
            }
            pos_comparacion = i+1;
            while(linea.at(i) != ';'){
                i++;
            }
            pos_puntoComa2 = i+1;

            if (identificarOE(linea.substr(pos_puntoComa2, linea.length() - pos_puntoComa2 - 1))>1){
                int a = 0; 
                int b = linea.length()-1; 
                
                while(linea.at(b) != ')'){
                    b--; 
                }
                a = b; 
                while(linea.at(a) != '=' && linea.at(a) != '-' && linea.at(a) != '+' && linea.at(a) != '*' && linea.at(a) != '/'){
                    a--;
                }
                if(linea.at(a) == '*' || linea.at(a) == '/' || linea.at(a-1) == '*' || linea.at(a-1) == '/'){
                    complejidad_logaritmica = true; 
                } else {
                    a++;
                    salto.append(linea.substr(a, b-a)); 
                }
            }

            if (complejidad_logaritmica){
                pilaLoopsCondiciones.push("logn"); 
                pilaLoopsCondiciones_end.push("logn");
                return "logn";
            }

            expresion+= to_string(identificarOE(linea.substr(0, pos_puntoComa1))) + "+(" + to_string(identificarOE(linea.substr(pos_puntoComa1, pos_puntoComa2 - pos_puntoComa1))) + ")(";
            iteraciones+= "(" + linea.substr(pos_comparacion, pos_puntoComa2 - pos_comparacion - 1) + "-(" + linea.substr(pos_asignacion, pos_puntoComa1 - pos_asignacion - 1) + "))";
            expresion+= iteraciones + "+1)"; 
            if (salto.length()>0){
                expresion+= "/" + salto;
            }
            expresion+= "+(" + to_string(identificarOE(linea.substr(pos_puntoComa2, linea.length() - pos_puntoComa2 - 1))) + ")" + iteraciones;
            if (salto.length()>0){
                expresion+= "/" + salto; 
                iteraciones+= ")/" + salto; 
            }

            pilaLoopsCondiciones.push(iteraciones); 
            pilaLoopsCondiciones_end.push(iteraciones);

            return expresion;
        }

        string whileLoop(string *codigo, int numero_lineas, int i){
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

            while(codigo[i-1].at(a) != '='){
                a--; 
            }
            pos_asignacion = a+1; 

            while(!isIn(codigo[i].at(b), comparadoresSimples) && !isIn(codigo[i].substr(b, 2), comparadoresCompuestos)){
                b++;
            }
            if(codigo[i].at(b+1) == '='){
                b++;
            }
            pos_comparacion = b+1; 
            while(codigo[i].at(b) != ')'){
                b++; 
            }
            pos_parentesis = b+1; 

            variable_incremental = codigo[i-1].at(pos_asignacion-2); 
            for(int j=i; j<numero_lineas; j++){
                if(codigo[j].at(0) == variable_incremental || (j>i && codigo[j].length()>2 && codigo[j].at(codigo[j].length()-2) == variable_incremental)){
                    linea_variableIncremental = j; 
                    break;
                }
                if(codigo[j].at(codigo[j].length()-1) == '{'){
                    parentesis.push(1); 
                }
                if(codigo[j].at(0) == '}'){
                    parentesis.pop();
                }
                if(j>i && parentesis.size() == 0){
                    linea_variableIncremental = j-1;
                    break; 
                }
            }
            
            if (identificarOE(codigo[linea_variableIncremental])>1){
                int operacion = codigo[linea_variableIncremental].length()-2; 
                
                while(!isIn(codigo[linea_variableIncremental].at(operacion), operadoresSimples)){
                    operacion--;
                }
                if(codigo[linea_variableIncremental].at(operacion) == '*' || codigo[linea_variableIncremental].at(operacion) == '/' || codigo[linea_variableIncremental].at(operacion-1) == '*' || codigo[linea_variableIncremental].at(operacion-1) == '/'){
                    complejidad_logaritmica = true; 
                } else {
                    operacion++;
                    salto.append(codigo[linea_variableIncremental].substr(operacion, (codigo[linea_variableIncremental].length()-1)-operacion)); 
                }
            }

            if (complejidad_logaritmica){
                pilaLoopsCondiciones.push("logn"); 
                pilaLoopsCondiciones_end.push("logn");
                return "logn";
            }

            expresion+= "(" + to_string(identificarOE(codigo[i])) + ")("; 
            iteraciones+= "(" + codigo[i].substr(pos_comparacion, pos_parentesis - pos_comparacion - 1) + "-(" + codigo[i-1].substr(pos_asignacion, pos_puntoComa - pos_asignacion) + "))";
            expresion+= iteraciones + "+1)";
            if (salto.length()>0){
                expresion+= "/" + salto; 
                iteraciones+= ")/" + salto; 
            }

            pilaLoopsCondiciones.push(iteraciones); 
            pilaLoopsCondiciones_end.push(iteraciones);

            return expresion;
        }

        int identificarOE(string linea){
            int num = 0; 
            for(int i=0; i<linea.length(); i++){
                if((i < (linea.length() - 1)) && (isIn(linea.substr(i, 2), comparadoresCompuestos) || isIn(linea.substr(i, 2), operadoresCompuestos))){
                    i++;
                    num++; 
                }
                else if(isIn(linea.at(i), comparadoresSimples) || isIn(linea.at(i), operadoresSimples)){
                    num++; 
                }
            }
            return num; 
        }

        bool isIn(string sub, string *array){
            for(int i=0; i<4; i++){
                if(sub.compare(array[i]) == 0){
                    return true; 
                }
            }
            return false; 
        }
        bool isIn(char car, char *array){
            for(int i=0; i<7; i++){
                if(car == array[i]){
                    return true;
                }
            }
            return false; 
        }
};

int main(){
    Analizar a; 
    string testCode[11] = {"void A(int n){", "int i, j, k, s;", "s=0;", "for(i=1; i<n-1; i++){", "for(j=i+1; j<n; j++){", "for(k=1; k<j; k++){", "s=s+2;", "}", "}", "}", "}"};
    string testCode2[9] = {"void imprime_arrego(int arreglo[], int n)", "{", "int i=0;", "while (i<n)", "{", "printf(\"El elemento \%d es \%d \\n\", i, arreglo[i]);", "++i;", "}", "}"};

    a.analizarComplejidad(testCode2, 9);

    return 0; 
}
