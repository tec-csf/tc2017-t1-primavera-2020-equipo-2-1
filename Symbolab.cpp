#include <iostream>
#include <stack>
#include <string>
#include <regex>
#include <queue>
#include <regex>
#include <list>
#include <cstdlib>
#include <vector>

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
            
            //cout << match.str() << "\n";

            crearListaOperaciones(str,match.str(),i);
            crearMonomio(match.str());
            str=match.suffix().str();
            i++;

    }
        //cout<<endl;
        
        //print(arithmetics);
    }

    void crearListaOperaciones(string pol, string s, int pos){

        //cout<<pol<<endl;
        
        for(int i=0; i<s.size();i++){
            if(s.at(i)=='^'){
                s.insert(i,"\\");
                i++;
            }
        }

        s="[+|-]?"+s+"[+|-]?";

        //cout<<s<<endl;

        regex reg (s);
        //cout<<reg<<endl;
         sregex_iterator currentMatch(pol.begin(),
            pol.end(), reg);
        sregex_iterator lastMatch;

    while(currentMatch != lastMatch){
            smatch match = *currentMatch;
            //cout << match.str() <<"\n";
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
       // cout<<endl;
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

         //cout<<tempcoef+ " "<<tempvar+" "<<temppot<<endl;

        Monomio<T,S> *nuevo=new Monomio<T,S> (stof( tempcoef ),tempvar,stof( temppot ));
        insertar(nuevo);
        //couter++;



     


    }

    S isChar(regex reg, int type, string mon){
    
    sregex_iterator currentMatch(mon.begin(), mon.end(), reg);
        sregex_iterator lastMatch;

    while(currentMatch != lastMatch){
            smatch match = *currentMatch;
            //cout << match.str() <<"\t";

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
 
	// Search for the substring in string in a loop untill nothing is found
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
                    //cout<<"Var"<<endl;
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

                //poly="";
                variable="";

                //cout<<"change"<<endl;
            }
        it2=poly2.arithmetics.begin();
        temp2=poly2.head;
        temp1=temp1->next;
        it++;


        }
        //cout<<poly<<endl;
        poly=formatoMultiplo(poly);
        return poly;
        //cout<<poly<<endl;

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
                    //cout<<"Signo"<<endl;
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
                    //cout<<"Var"<<endl;
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

                //poly="";
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
        //cout<<poly<<endl;

    }
    
    



    void print(list<char> const &list)
{
    for (auto it = list.cbegin(); it != list.cend(); it++)
    {
        std::cout << *it << '\n';
    }
}
    
   void printList(){
       std :: list<char>::iterator it=arithmetics.begin();
       it++;
       int count=0;
			Monomio <T,S>*temp=head;
			while(temp!=NULL){
				cout<<temp->mon<<*it;
				temp=temp->next;
                it++;
			}
			cout<<endl;
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
 
    string lucifer(string s){


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
    //copia.top()=checkDivision(copia.top());
    //cout<<"Init "<<copia.top()<<simbolos.top()<<capa.top()<<endl;

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
        //cout<<"Test1"<<endl;
        //PrintStack(pilaPolys,simbolos,capa);
    } else if(simbolos.top()=='+'){

        copia.pop();
        auxcapa=capa.top();
        capa.pop();
        
        string regexs=temp2+temp1;
          // cout<<"Test2"<<endl;
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
        //cout<<"Test1"<<endl;
        //PrintStack(pilaPolys,simbolos,capa);

        }else if(simbolos.top()=='+'){

            global0=global0+simbolos.top()+copia.top();
        
            copia.pop();
          // cout<<"Test2"<<endl;
           
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



    }//end while
        if(global0.compare("")==0){
            return s;
        }
        else{
            return global0;
        }
        

//PrintStack(pilaPolys,simbolos,capa);
    }//end of lucifer
    


    stack<string> separarMulti(string polinomio, int current, int size, int type){
    stack <string> operaciones;
    queue <string> interOperaciones;
    queue <int> auxiliar;
     int parentesisCounter= 0;
    string poly="";
    int layer=type;
    char savesym;


    for(int j=current;j<size;j++){
    //
        
        if(polinomio.at(j)=='('){
            
            savesym=polinomio.at(j-1);
            //cout<<savesym;
            capa.push(layer);

            
            if(savesym=='+'|savesym=='-'){
                simbolos.push(savesym);
                            
            }else if(savesym==')'){
                    simbolos.push('*');
            }
           // cout<<simbolos.top()<<savesym;
            ++parentesisCounter;
            while (parentesisCounter>0 && j<size)
            {               
                //cout<<parentesisCounter; 
                poly=poly+polinomio.at(j);
                //cout<<poly<<endl;
                

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
                    
                    
                    //cout<<"DEBUGGER"<<endl;
                     if(parentesisCounter==0){
                        //cout<<layer;
                        poly=poly+polinomio.at(j);
                        operaciones.push(poly);
                        poly="";
                        --j;
                        j=size;
                    }
                } 

                
                        
            }
            //cout<<poly<<endl;
        }
    }

    return operaciones;
    }


    
void PrintStack(stack<string> s, stack<char> t, stack<int> r) 
{ 
    // If stack is empty then return 
    if (s.empty())  
        return; 
      
  
    string x =s.top();
    int y=r.top();
    char z =t.top();
  
    // Pop the top element of the stack 
    s.pop();
    r.pop();
    t.pop();
    // Recursively call the function PrintStack 
    

    // Print the stack element starting 
    // from the bottom 
    cout <<x<<y<<z<<endl; 
      PrintStack(s,t,r); 
    // Push the same element onto the stack 
    // to preserve the order 

    r.push(y);
    s.push(x);
    t.push(z);
    
} 


void restructurarPila(){
    while(pilaPolys.size()!=capa.size()){
        capa.pop();
    }
}

//hello
//s.at(i)=='e'
//s.at(i)="";

string automatizar (string s){

    string test;
    pilaPolys=separarMulti(s,0,s.size(),0);
    restructurarPila();
    //PrintStack(pilaPolys,simbolos,capa);
    test=lucifer(s);
    
    cout<<test<<endl;
    cout<<checarComplejidad(test)<<endl;
    
    return "s";

}
string automatizarAux (string s){

    string test;
    pilaPolys=separarMulti(s,0,s.size(),0);
    restructurarPila();
    test=lucifer(s);
    //cout<<test<<endl;
    //cout<<checarComplejidad(test)<<endl;
    
    return checarComplejidad(test);

}

int compararComplejidad(string *a,int size){

    string big [] = {"O(1)","O(logn)","O(n)","O(nlogn)","O(n^2)","O(n^3)","O(n^4)","O(n^5)","O(n^6)","O(n^7)","O(n^8)","O(n^9)"};

    string bigO[size];

    int higher=NULL;
    int save=0;

    for(int i=0; i<size;i++){
        bigO[i]=automatizarAux(a[i]);
        cout<<bigO[i]<<endl;
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

int main(){

    Symbolab s;
    string str= "0+1+1+(2)(n-1-1+1/2)+(2)(n-1-1/2)+(n-1-1/2)(logn+(logn)(1+(1)(j-1+1)+(1)(j-1)+(j-1)(2))).";
    //cout<<s.at(1)<<endl;
    //n+1+(n+1)(1+(1)(n+1)+(1)(n-1+1)+(n+1)(1+(1)(n+1)+(1)(n-1))).
    string x;
    x=s.automatizar(str);
    //cout<<"DEBUG"<<x<<endl;

    //s.PrintStack(s.pilaPolys,s.simbolos,s.capa);
    
  //0+0+1+1+(2)(n-1-(1)+1)+(1)(n-1-(1))+(n-1-(1))(2+(1)(n-(i+1)+1)+(1)(n-(i+1))+(n-(i+1))(1+(1)(j-(1)+1)+(1)(j-(1))+(j-(1))(2)))
  //0+0+1+1+(2)(n-1-1+1)+(1)(n-1-1)+(n-1-1)(2+(1)(n-i+1+1)+(1)(n-i+1)+(n-i+1)(1+(1)(j-1+1)+(1)(j-1)+(j-1)(2)))  
    return 0;
}