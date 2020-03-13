#include <iostream> // cin y cout
#include <cstdlib>  // rand() y srand()
#include <fstream>  // archivos
#include <string>   // substr()
#include <cstdio>   // printf()
#include <ctime>    // time() [para rands] y clock()
#include <stack>
#include <vector>

#include "functions.hpp"
using namespace std;

// Aquí van las funciones de hpp, pero ya con código
//CONSTRUCTORES
Class::Class(string new_name)
  : name(new_name) {}

Class::Class(string new_name, int val);
  : name(new_name), var(val) {}

// Destructor
Class::~Class() {
  cout << "Goodbye " << title; // Optional
}

type Class::method(arguments) {
  /* code */
}
