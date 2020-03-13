// -*- lsst-c++ -*-
/*
*/

#include <iostream>
#include <stack>
#include <string>
#include <regex>
#include <queue>
#include <regex>
#include <list>
#include <cstdlib>
#include <vector>
#include <string.h> //<- Substring manager
#include<stdio.h> 
#include<stdlib.h> 
#include<bits/stdc++.h>
#include <cstdlib>

using namespace std;

template<class T, class S>
class Monomio{
    public:
    S var;
    T coef;
    T exp;
    S mon;
    Monomio <T,S>*next;

    Monomio(T coeficiente, S variable, T exponente){
        coef=coeficiente;
        exp=exponente;
        var=variable;
        mon= to_string(coeficiente)+var+"^"+to_string(exp);
        next=NULL;

    }
        Monomio(){
        coef=NULL;
        exp=NULL;
        var=NULL;
        mon=NULL;
        next=NULL;

    }
};

template<class T, class S>
class Polinomio{


public:


Monomio<T,S> *head;
list <char> arithmetics;

    Polinomio(){
        head=NULL;
        cout.precision(2); 


    }


    void crearPoly(string str){
        regex reg (R"([0\.]+[0-9]*[a-z][\^]?[0-9]?|[0\.]+[0-9]+|[0-9]?logn+|[0-9]*[a-z][\^]?[0-9]?|[0-9]+)");

        smatch match;

        int i=0;

    while(regex_search(str,match,reg)){
            crearListaOperaciones(str,match.str(),i);
            crearMonomio(match.str());
            str=match.suffix().str();
            i++;

    }

    }

    void crearListaOperaciones(string pol, string s, int pos){

        
        for(int i=0; i<s.size();i++){
            if(s.at(i)=='^'){
                s.insert(i,"\\");
                i++;
            }
        }

        s="[+|-]?"+s+"[+|-]?";

        regex reg (s);

         sregex_iterator currentMatch(pol.begin(),pol.end(), reg);
        sregex_iterator lastMatch;

    while(currentMatch != lastMatch){
            smatch match = *currentMatch;
            if(pos==0&& match.str().at(0)!='-'){
                arithmetics.push_back('+');
                return;
            } else if(pos==0&& match.str().at(0)=='-'){
                arithmetics.push_back('-');
                return;
            }

            if(pos!=0&& (match.str().at(0)!='-'&& match.str().at(0)!='+'))
            {
                arithmetics.push_back('*');
                return;
            }
            else {
                arithmetics.push_back(match.str().at(0));
                return;
            }
            
        currentMatch++;
    }

    }

    void crearMonomio(string m){
        
        S tempcoef;
        S tempvar;
        S temppot;
        regex coef (R"(^[0\.]+[0-9]+|[0-9]+)");
        regex var (R"([a-z]*logn|[a-z])");
        regex pot(R"([\^][0-9]*)");

        tempcoef=isChar(coef,0,m);
        tempvar=isChar(var,2,m);
        temppot=isChar(pot,1,m);

        Monomio<T,S> *nuevo=new Monomio<T,S> (stof( tempcoef ),tempvar,stof( temppot ));
        insertar(nuevo);
    }

    S isChar(regex reg, int type, string mon){
    
    sregex_iterator currentMatch(mon.begin(), mon.end(), reg);
        sregex_iterator lastMatch;

    while(currentMatch != lastMatch){
            smatch match = *currentMatch;

            if(type==0||type==2){
                return match.str();
            }
            else if(type==1){
                return match.str().substr(1, match.str().size());
            }
            
        currentMatch++;
    }

    if(type==0||type==1){
        return "1";

    } else {
        return "";
    }

    }
    

    void insertar (Monomio<T,S> *nuevo){

       // cout<<"Insertar"<<endl;
        if (head==NULL){
            head=nuevo;
        }else{
            Monomio <T,S>*temp = head;
            while(temp->next!=NULL){
                temp=temp->next;
            }
            temp->next=nuevo;
        }

    }

    string eraseAllSubStr(string mainStr, const string toErase)
{
	size_t pos = string::npos;

	while ((pos  = mainStr.find(toErase) )!= string::npos)
	{
		// If found then erase it from string
		mainStr.erase(pos, toErase.length());
	}
    return mainStr;
}
    string formatoMultiplo(string s){
        string aux="";
        float x=1;
        s=s.substr(1,s.size()-1);

        s=eraseAllSubStr(s,"^"+to_string(x));
        
        s=eraseAllSubStr(s,".000000");
       
        s=eraseAllSubStr(s,"00000");
        s=eraseAllSubStr(s,"0000");
        s=eraseAllSubStr(s,"000");

        for (int i =0; i<s.size();i++){

            if(s.at(i)=='1' && (i<(s.size()-1)&&checkNext(s.at(i+1)))){

                i=i+1;
            } else if(s.at(i)=='1' &&(i<(s.size()-1)&&s.at(i+1)=='1')){

            }

            aux=aux+s.at(i);

        }

        return aux;

    }

    bool checkNext(char s){
        char abecedario [] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','x','y','z'};

        for (int i=0;i<25;i++){
            if(abecedario[i]==s){
                return true;
            }
        }
        return false;
    }


    string dividir(Polinomio <T,S> poly2){

        Monomio <T,S> *temp1=head;
        Monomio <T,S> *temp2=poly2.head;
        string poly="";
        T tempcoef;
        T exp;
        string variable="";
        string signo="";
        auto it=arithmetics.begin();
        auto it2=poly2.arithmetics.begin();

    while(temp1!=NULL){

            while(temp2!=NULL){
//Signos DIVISION
//-----------------------------------------------------------------------------
                tempcoef=temp1->coef/temp2->coef;
                if(*it==*it2){
                    //cout<<"Signo"<<endl;
                    if(*it=='+'){
                        signo="+";
                    }else if(*it=='-'){
                        signo="+";
                    }
                }else if(*it!=*it2){
                        if(*it=='+'||*it=='-'){
                            signo="-";
                        }else if(*it=='*'){
                            signo=" ";
                        }
                }
//tipo de variable DIVISION
//----------------------------------------------------------------------------------------
                if(signo.at(0)==' '){
                    variable=temp1->var;
                    exp=temp1->exp;
                    signo="";
                    poly=poly+signo+variable+"^"+to_string(exp);
                }else{
                    if(temp1->var=="" && temp2->var==""){
                    exp=1;
                    variable="";
                    poly=poly+signo+to_string(tempcoef);
                }
                
                else if(temp1->var==temp2->var){
                    variable = temp1->var;
                    exp=temp1->exp-temp2->exp;
                    if(exp==0){
                        poly=poly+signo+to_string(tempcoef);
                    }
                    else{
                        poly=poly+signo+to_string(tempcoef)+variable+"^"+to_string(exp);
                    }
                    
                } else if(temp1->var!=temp2->var&&(temp1->var!="" && temp2->var!="")){
                    variable=temp1->var+"^"+to_string(exp)+temp2->var;
                    poly=poly+signo+to_string(tempcoef)+variable+"^"+to_string(exp);
                }else if(temp1->var!="" && temp2->var==""){
                    exp=temp1->exp;
                    variable=temp1->var;
                    poly=poly+signo+to_string(tempcoef)+variable+"^"+to_string(exp);

                }else if(temp1->var=="" && temp2->var!=""){
                    exp=temp2->exp;
                    variable=temp2->var;
                    poly=poly+signo+to_string(tempcoef)+variable+"^"+to_string(exp);
                }
                
                }
                temp2=temp2->next;
                it2++;
                variable="";
            }
        it2=poly2.arithmetics.begin();
        temp2=poly2.head;
        temp1=temp1->next;
        it++;


        }

        poly=formatoMultiplo(poly);
        return poly;

    }

    

    string multiplicar(Polinomio <T,S> poly2){

        Monomio <T,S> *temp1=head;
        Monomio <T,S> *temp2=poly2.head;
        string poly="";
        T tempcoef;
        T exp;
        string variable="";
        string signo="";
        auto it=arithmetics.begin();
        auto it2=poly2.arithmetics.begin();
        int counter=0;


        while(temp1!=NULL){
 
            while(temp2!=NULL){
//Signos MULTIPLICACION
//-----------------------------------------------------------------------------
                tempcoef=temp1->coef*temp2->coef;
                if(*it==*it2){
                    if(*it=='+'){
                        signo="+";
                    }else if(*it=='-'){
                        signo="+";
                    }
                }else if(*it!=*it2){
                        if(*it2=='+'||*it2=='-'){
                            signo="-";
                        }else if(*it2=='*'){
                            signo=" ";
                        }
                }
//tipo de variable MULTIPLICACION
//----------------------------------------------------------------------------------------
                if(signo.at(0)==' '){
                    variable=temp2->var;
                    exp=temp2->exp;
                    signo="";
                    poly=poly+variable+"^"+to_string(exp);
                }else{
                    if(temp1->var=="" && temp2->var==""){
                    exp=1;
                    variable="";
                    poly=poly+signo+to_string(tempcoef)+variable+"^"+to_string(exp);

                }
                else if(temp1->var==temp2->var){
                    variable = temp1->var;
                    exp=temp1->exp+temp2->exp;
                    poly=poly+signo+to_string(tempcoef)+variable+"^"+to_string(exp);

                } else if(temp1->var!=temp2->var&&(temp1->var!="" && temp2->var!="")){
                    exp=temp1->exp;
                    variable=temp1->var+"^"+to_string(exp)+temp2->var;
                    exp=temp2->exp;
                    poly=poly+signo+to_string(tempcoef)+variable+"^"+to_string(exp);

                }else if(temp1->var!="" && temp2->var==""){
                    exp=1;
                    variable=temp1->var;
                    poly=poly+signo+to_string(tempcoef)+variable+"^"+to_string(exp);

                }else if(temp1->var=="" && temp2->var!=""){
                    exp=1;
                    variable=temp2->var;
                    poly=poly+signo+to_string(tempcoef)+variable+"^"+to_string(exp);
                }
                
                }
            
                temp2=temp2->next;
                it2++;

                variable="";
                counter++;
            }
        
        it2=poly2.arithmetics.begin();
        
        temp2=poly2.head;
        
        temp1=temp1->next;
        
        it++;
        


        }
        
        poly=formatoMultiplo(poly);
        return poly;

    }

    ~Polinomio(){

    }

};

//SYMBOLAB
//---------------------------------------------------------------------------------------------------------------------------

class Symbolab{


    public:
    stack<string> pilaPolys;
    stack<int> capa;
    stack<char> simbolos;

    Symbolab(){
    }

    string checarComplejidad(string s){

        string bigO [] = {"O(1)","O(logn)","O(n)","O(nlogn)","O(n^2)","O(n^3)","O(n^4)","O(n^5)","O(n^6)","O(n^7)","O(n^8)","O(n^9)"};
        string casos [] ={"[0-9]","logn","n","nlogn","[n][\^][2]","[n][\^][3]","[n][\^][4]","[n][\^][5]","[n][\^][6]","[n][\^][7]","[n][\^][8]","[n][\^][9]"};
        for(int i=11;i>=0;i--){
            regex reg (casos[i]);
            smatch match;

        while(regex_search(s,match,reg)){
            
            return bigO[i];
        }
    }
    return"No encontramos la complejidad en nuestra comprendio de BigO";
    }

string findAndReplaceAll(string data,string toSearch,string replaceStr)
{
	// Get the first occurrence
	size_t pos = data.find(toSearch);
 
	// Repeat till end is reached
	while( pos != std::string::npos)
	{
		// Replace this occurrence of Sub String
		data.replace(pos, toSearch.size(), replaceStr);
		// Get the next occurrence from the current position
		pos =data.find(toSearch, pos + replaceStr.size());
	}
    return data;
}

    string checkDivision(string s){
        string temp1="";
        string temp2="";
        string fraccion="";
        for(int i =0; i<s.size();i++){
            if(s.at(i)=='/'){
                temp1=s.substr(1,i-1);
                temp2=s.substr(i+1,1);
                Polinomio <float, string> denominador;
                denominador.crearPoly(temp1);
                Polinomio <float, string> numerador;
                numerador.crearPoly(temp2);
                fraccion=denominador.dividir(numerador);
                return fraccion;
                break;
            }
        }
        return s;
    }
 
    string mainframe(string s){

    string auxD="";
    string temp1="";
    string temp2="";
    string operations="";
    string auxiliar1;
    string global1="";
    string global0="";
    int auxcapa=0;

    stack<string> copia=pilaPolys;

    while (!copia.empty())
    {

    if(capa.top()==1){

        if(simbolos.top()=='*'){
            auxD=checkDivision(copia.top());
            copia.pop();
            copia.push(auxD);
            temp1=copia.top();
            copia.pop();
            auxD=checkDivision(copia.top());
            copia.pop();
            copia.push(auxD);
            temp2=copia.top();
            Polinomio <float,string> in;
            in.crearPoly(temp1);
            Polinomio <float,string> out;
            out.crearPoly(temp2);
            operations=out.multiplicar(in);
            copia.pop();
            copia.push(operations);
            simbolos.pop();
            capa.pop();
    } else if(simbolos.top()=='+'){

        copia.pop();
        auxcapa=capa.top();
        capa.pop();
        
        string regexs=temp2+temp1;
           auxiliar1=findAndReplaceAll(copia.top(),regexs,operations);

            if(auxiliar1.compare(copia.top())==0&&capa.top()!=0){
                capa.push(auxcapa);
                global1=global1+simbolos.top()+operations;
                
           simbolos.pop();
           capa.pop();
            }else if(auxiliar1.compare(copia.top())!=0&& global1.compare("")!=0||capa.top()==0){
                global1=global1+simbolos.top()+operations;
     
                simbolos.pop();


           for(int i=0; i<copia.top().size();i++){

               if(copia.top().at(i+1)=='('){
                   auxiliar1=copia.top().substr(0,i);
                   break;
               }
           }

           copia.top()=auxiliar1+global1+")";
           global1="";           
           }else{
                copia.pop();
                copia.push(auxiliar1);
                simbolos.pop();           
           }        
    }
    }else if(capa.top()==0){

        if(simbolos.top()=='*'){

            auxD=checkDivision(copia.top());
            copia.pop();
            copia.push(auxD);
            temp1=copia.top();
            copia.pop();
            auxD=checkDivision(copia.top());
            copia.pop();
            copia.push(auxD);
            temp2=copia.top();
            Polinomio <float,string> in;
            in.crearPoly(temp1);
            Polinomio <float,string> out;
            out.crearPoly(temp2);
            operations=out.multiplicar(in);
            copia.pop();
            copia.push(operations);
            simbolos.pop();
            capa.pop();
        }else if(simbolos.top()=='+'){

            global0=global0+simbolos.top()+copia.top();
            copia.pop();
            if(copia.empty()){

            for(int i=0; i<s.size();i++){

               if(s.at(i+1)=='('){
                   auxiliar1=s.substr(0,i);
                   global0=auxiliar1+global0;
                   break;
               }         
            }
            }
            simbolos.pop();
            capa.pop();
        }
        }

    }
    if(global0.compare("")==0){
        return s;
    }
    else{
        return global0;
    }
        
    }
    
    stack<string> separarMulti(string polinomio, int current, int size, int type){
    stack <string> operaciones;
    queue <string> interOperaciones;
    queue <int> auxiliar;
     int parentesisCounter= 0;
    string poly="";
    int layer=type;
    char savesym;

    for(int j=current;j<size;j++){

        if(polinomio.at(j)=='('){
            
            savesym=polinomio.at(j-1);
            capa.push(layer);

            if(savesym=='+'|savesym=='-'){
                simbolos.push(savesym);
                            
            }else if(savesym==')'){
                    simbolos.push('*');
            }

            ++parentesisCounter;
            while (parentesisCounter>0 && j<size)
            {               
                poly=poly+polinomio.at(j);
                if(polinomio.at(j)==')'&& type==0) {
                    
                    --parentesisCounter;

                    if(parentesisCounter==0){ 
                        operaciones.push(poly);
                        poly="";
                        --j;
                    while(!interOperaciones.empty()){
                        operaciones.push(interOperaciones.front());
                        interOperaciones.pop();
                    }

                    }        
                }
                ++j;

                if (polinomio.at(j)=='(' && parentesisCounter>0){
                    ++parentesisCounter;
                    
                    stack<string>aux=separarMulti(polinomio, j, size, 1);
 
                    while (!aux.empty())
                    {
                       interOperaciones.push(aux.top());
                       aux.pop();
                    }                
                }
                
                if(polinomio.at(j)==')'&& layer==1)  {
                    --parentesisCounter;
                    
                     if(parentesisCounter==0){
                        poly=poly+polinomio.at(j);
                        operaciones.push(poly);
                        poly="";
                        --j;
                        j=size;
                    }
                }                         
            }
        }
    }

    return operaciones;
    }

void restructurarPila(){
    while(pilaPolys.size()!=capa.size()){
        capa.pop();
    }
}

string automatizar (string s){

    string test;
    pilaPolys=separarMulti(s,0,s.size(),0);
    restructurarPila();
    test=mainframe(s);
    
    cout<<test<<endl;
    cout<<checarComplejidad(test)<<endl;
    
    return test;

}
string automatizarAux (string s){

    string test;
    pilaPolys=separarMulti(s,0,s.size(),0);
    restructurarPila();
    test=mainframe(s);

    
    return checarComplejidad(test);

}

int compararComplejidad(string *a,int size){

    string big [] = {"O(1)","O(logn)","O(n)","O(nlogn)","O(n^2)","O(n^3)","O(n^4)","O(n^5)","O(n^6)","O(n^7)","O(n^8)","O(n^9)"};

    string bigO[size];

    int higher=NULL;
    int save=0;

    for(int i=0; i<size;i++){
        bigO[i]=automatizarAux(a[i]);
    }


    for(int i=0;i<size;i++){

        for (int j=0;j<sizeof(big)/sizeof(big[0]);j++)
        if(bigO[i].compare(big[j])==0){
            if(higher==NULL){
                higher=j;
                save=i;
            } else if(j>higher){
                higher=j;
                save=i;
            }
        }

    }
    return save;
}

};

class Binomio
{
    public: 
    string binomio;
    char bin[900];
    string values[900][3];
    double numbers [900][2];
    char r;
    bool elevate = false;
    double temp;
    int t=0;
    
    //
    void setBinomio(string b)
    {
        binomio = b;
    };

    //metodo para separar el binomio
    void separador()
    {
        //rellena los valores númericos con 1, si no encuentra coeficientes o exponentes implica que estos = 1.
        //rellena los valores alfabeticos con null, implica que solo es una cantidad numerica
        for(int h=0; h<20; h++)
        {
            values[h][1]="null";
            numbers[h][0]=1;
            numbers[h][1]=1;
        };

        //variables temporales
        string terminos, coeficientes, exponentes, temporal;


        //convierte el arreglo de string a char para ser manejable
        strcpy(bin, binomio.c_str());

        //corre unicamente el largo del binomio
        for(int i = 0; i<binomio.size(); i++)
        {   
            //variable r para manerjar el dato actual del binomio
            r = bin[i];

            //checa si el char es un numero
            if(isdigit(r)||r=='.')
            {
                //variable elevate para determinar si es un coeficiente o exponente

                //false == coeficiente
                if(elevate==false)
                {
                    temporal=binomio.substr(i,1);
                    coeficientes = coeficientes + temporal;
                };

                //true == exponente
                if(elevate==true)
                {
                    temporal=binomio.substr(i,1);
                    exponentes = exponentes + temporal;
                };
            };

            //checa si char es valor alfabetico
            if(isalpha(r))
            {
                temporal=binomio.substr(i,1);
                terminos = terminos + temporal;
            };

            //cambia el valor de elevate
            if(r=='^')
            {
                elevate=true;
            };
            //detecta suma resta o acaba el binomio
            if(r=='-' || r=='+' || i==binomio.size()-1)
            {
                //si es el primer char del binomio implica que es negativo
                if(i==0)
                {
                    values[0][0] = "-";
                };

                if(i!=0)
                {
                    //Stoi = string -> int

                    //catcher de error si el coeficiente está vacio
                    if(coeficientes != "")
                    {
                        numbers[t][0] = stod(coeficientes);
                    }
                    //catcher de error si el exponente está vacio
                    if(exponentes != "")
                    {
                        numbers[t][1] = stod(exponentes);
                    }
                    //catcher de error si el termino está vacio
                    if(terminos!="")
                    {
                        values[t][1] = terminos;
                    };

                    //checa si no es el ultimo valor
                    if(i!=binomio.size())
                    {
                        temporal=binomio.substr(i,1);
                        values[t+1][0] = temporal;
                    };

                    //si es negativo convierte el número a uno negativo
                    if(values[t][0]=="-")
                    {
                        temp = numbers[t][0];
                        temp = temp*-1;
                        numbers[t][0] = temp;

                    };

                    //reset
                    coeficientes = "";
                    exponentes = "";
                    exponentes = "";
                    terminos = "";
                    elevate = false;

                    //cambio de polinomio
                    t++;
                    
                };//i!=0
            };//acaba el detector
        };//acaba for loop principal
    };// acaba metodo separador

    void sumar()
    {

        // values[i][1] == termino
        // values[i][2] == si ya se sumó
        // numbers[i][0] == coeficientes
        // numbers[i][1] == exponentes

        int temp = 1;
        int suma = 0;
        int counter2 = 0;

        //variable para determinar su uso
        for(int b=0;b<t;b++)
        {
            values[b][2]="sin uso";
        };

        for(int i=0; i<t;i++)
        {
            for(int b = i+1; b<t; b++)
            {
                if(values[i][1]==values[b][1] && numbers[i][1]==numbers[b][1])
                {
                    if(values[i][2]=="sin uso" || values[i][2]=="en uso" && values[i][2]!="usado")
                    {
                        suma=numbers[i][0]+numbers[b][0];
                        numbers[i][0] = suma;
                        values[b][1]="muerto";
                        values[i][2]=="en uso";
                        values[b][2]=="usado";
                    };
                };
            };
        };
    };//end metodo sumar

    void imprimir_resultado()
    {
        for(int i = 0; i-t;i++)
        {
            if(values[i][2]=="en uso"||values[i][2]=="sin uso")
            {
                if(numbers[1][0]<0)
                {
                    //cout<<numbers[1][0]<<values[i][1]<<"^"<<numbers[i][1]<<" ";
                };
                if(numbers[1][0]>0)
                {
                    if(i!=0&&values[i][1] !="muerto"&&numbers[i][0]!=0&&numbers[i][1]!=0)
                    {
                        if(numbers[i][0]>0)
                        {
                            cout<<"+";
                        };

                    };

                    if(numbers[i][0]!=1&&values[i][1] !="muerto"&&numbers[i][0]!=0&&numbers[i][1]!=0)
                    {
                        cout<<numbers[i][0]<<"";
                    };

                    if(numbers[i][0]==1 && values[i][1] =="null"&&values[i][1] !="muerto"&&numbers[i][0]!=0&&numbers[i][1]!=0)
                    {
                        cout<<numbers[i][0]<<"";    
                    };

                    if(values[i][1]!="null"&&values[i][1] !="muerto"&&numbers[i][0]!=0&&numbers[i][1]!=0)
                    {
                        cout<<values[i][1]<<"";
                    };

                    if(numbers[i][1]!= 1&&values[i][1] !="muerto"&&numbers[i][0]!=0&&numbers[i][1]!=0)
                    {
                        cout<<"^"<<numbers[i][1]<<" ";
                    };
                };
            };

        };
        cout<<" "<<endl;
    };

};


int main(){

    Symbolab s;
    string str= "0+1+1+(2)(n-1-(1)+1)/2)+(2)(n-1-(1)/2)+(n-1-(1)/2)(logn+(logn)(1+(1)(j-(1)+1)+(1)(j-(1)+(j-(1))(2)))";
    string x;    
    x=s.automatizar(str);
    Binomio ejemplo;
    ejemplo.setBinomio(x);
    ejemplo.separador();
    ejemplo.sumar();
    ejemplo.imprimir_resultado();
    return 0;
}