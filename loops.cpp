/*  Codigo para leer for loops, aún no contiene la función de leer codigo y lo lee utilizando un arreglo
    con el "codigo" dentro - Andrés*/

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
    char operadoresSimples[6] = {'=', '+', '-', '*', '/', '%'};

    public: 
        void analizarComplejidad(string *codigo, int numeroLineas){
            string polinomio; 
            int numeroLoops = pilaLoopsCondiciones.size(); 

            for(int i=0; i<numeroLineas; i++){//Como obtener el size de un arreglo
                string complejidadLinea = ""; 
                if(codigo[i].substr(0,4).compare("for(") == 0){
                    complejidadLinea = forLoop(codigo[i]); 
                    cout<<"("<<i+1<<")\t"<<codigo[i]<<"\tOE: "<<complejidadLinea<<endl;

                    if (polinomio.length()>0 && polinomio.at(polinomio.length()-1) !='('){
                        polinomio.append("+"); 
                    }
                    polinomio.append(complejidadLinea);
                    polinomio.append("+(");
                    polinomio.append(pilaLoopsCondiciones.top());
                    pilaLoopsCondiciones.pop(); 
                    polinomio.append(")(");   
                }
                else if (codigo[i].at(0) == '}'){
                    if (pilaLoopsCondiciones_end.size() > 0){
                        polinomio.append(")"); 
                        pilaLoopsCondiciones_end.pop();
                    }
                }
                else {
                    complejidadLinea = to_string(identificarOE(codigo[i])); 
                    cout<<"("<<i+1<<")\t"<<codigo[i]<<"\tOE: "<<complejidadLinea<<endl;

                    if (polinomio.length()>0 && polinomio.at(polinomio.length()-1) !='('){
                        polinomio.append("+"); 
                    }
                    polinomio.append(complejidadLinea); 
                }
            }

            cout<<endl; 
            cout<<polinomio<<endl;
        }

    private: 
        string forLoop(string linea){
            string expresion = ""; 
            string iteraciones = "";
            int i = 0;
            int pos_asignacion, pos_puntoComa1, pos_comparacion, pos_puntoComa2; 

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

            expresion.append(to_string(identificarOE(linea.substr(0, pos_puntoComa1))));
            expresion.append("+("); 
            expresion.append(to_string(identificarOE(linea.substr(pos_puntoComa1, pos_puntoComa2 - pos_puntoComa1))));
            expresion.append(")("); 
            iteraciones.append(linea.substr(pos_comparacion, pos_puntoComa2 - pos_comparacion - 1));
            iteraciones.append("-(");
            iteraciones.append(linea.substr(pos_asignacion, pos_puntoComa1 - pos_asignacion - 1));
            iteraciones.append(")");
            expresion.append(iteraciones); 
            expresion.append("+1)+(");
            expresion.append(to_string(identificarOE(linea.substr(pos_puntoComa2, linea.length() - pos_puntoComa2 - 1))));
            expresion.append(")("); 
            expresion.append(iteraciones); 
            expresion.append(")");

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
            for(int i=0; i<6; i++){
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

    a.analizarComplejidad(testCode, 11);

    return 0; 
}