#include <iostream> // cin y cout
#include <fstream>  // archivos
#include <string>   // substr()
#include <cstdio>   // printf()
#include <stack>
#include <vector>
using namespace std;

string limpiador(){
    string s="0+1+1+(2)(((n-1-(1))+1)/2)+(2)((n-1-(1))/2)+((n-1-(1))/2)(logn+(logn)(1+(1)((j-(1))+1)+(1)(j-(1))+((j-(1)))(2)))";
    
    for(int i=0;i<2;i++){
    int cont=0;
    int flag;
    bool flak=false;
    int length=s.length();
    while(cont<length-1){
        if(length-cont==0){
            s+=')';
            return s;
        }
        else{

        if(s.at(cont)=='('){
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