#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>
#include <stack>

#include "clase.hpp"

using namespace std;


int main(){
    Codigo a;
    string testCode[11] = {"void A(int n){", "int i, j, k, s;", "s=0;", "for(i=1; i<n-1; i++){", "for(j=i+1; j<n; j++){", "for(k=1; k<j; k++){", "s=s+2;", "}", "}", "}", "}"};
    string testCode2[9] = {"void imprime_arrego(int arreglo[], int n)", "{", "int i=0;", "while (i<n)", "{", "printf(\"El elemento \%d es \%d \\n\", i, arreglo[i]);", "++i;", "}", "}"};

    a.analizarComplejidad(testCode2, 9);

    return 0;
}
