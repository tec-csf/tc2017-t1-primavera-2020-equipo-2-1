#include <iostream> // cin y cout
#include <fstream>  // archivos
#include <string>   // substr()
#include <cstdio>   // printf()
#include <stack>
#include <vector>
using namespace std;
class Translate{
    public:
string limpiador(string s){
    for(int i=0;i<3;i++){
    int cont=0;
    int flag;
    bool flak=false;
    int length=s.length();
    while(cont<length-1){
        if(length-cont==0){
            s+=')';
            cout<<"termina"<<endl;
            return s;
        }
        else{
        if(s.at(cont)==')'){
                 if(s.at(cont+1)=='('&&s.at(cont+2)=='('){
                s.erase(s.begin()+cont+1);
                s.erase(s.begin()+(cont));
                s.insert(s.begin()+(cont),'*');
                length=s.length();
                }
                else if(s.at(cont+1)=='('){
                s.insert(s.begin()+(cont+1),'*');
                }
        }
        length=s.length();
        ++cont;
        }
        }
    }
    return s;
    
    
    
}
};