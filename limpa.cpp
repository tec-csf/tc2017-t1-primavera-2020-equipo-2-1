#include <iostream> // cin y cout
#include <fstream>  // archivos
#include <string>   // substr()
#include <cstdio>   // printf()
#include <stack>
#include <vector>
using namespace std;

string limpiador(){
    string s="1+(1)((5-(0))+1)+(1)(5-(0))+((5-(0)))(1+(2)((5-1-(0))+1)+(1)(5-1-(0))+((5-1-(0)))(243)+2+4+3)";
    for(int i=0;i<3;i++){
    int cont=0;
    int flag;
    bool flak=false;
    int length=s.length();
    cout<<i<<" "<<s<<endl;
    while(cont<length-1){
        if(length-cont==0){
            s+=')';
            cout<<"termina"<<endl;
            return s;
        }
        else{
        if(s.at(cont)=='('){
            if(i==2){
                 if(s.at(cont+2)==')'&&(s.at(cont-1)=='+'||s.at(cont-1)=='-')){
                s.erase(s.begin()+cont);
                s.erase(s.begin()+(cont+1));
                }  
            }
            if(s.at(cont+1)=='('){
                flag=cont+1;
                flak=true;
            }
        }
        else if(s.at(cont)==')'){
            if(s.at(cont+1)==')'&&flak){
                s.erase(s.begin()+flag);
                s.erase(s.begin()+cont);
                flak=false;
                length=s.length();
    
                
            }
        }
        length=s.length();
        ++cont;
    }
    }
    }
}

int main(){
 /*string h="hola";
 h.erase(h.begin());
 cout<<h<<endl;*/
 string s;
 s=limpiador();
 cout<<s<<endl;
}