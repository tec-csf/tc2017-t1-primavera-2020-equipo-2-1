// Numeros aleatorios, rand c++
#include <iostream>
#include <stdlib.h> // Aqui esta el rand

int main() {
  srand(time(NULL)); // 'Seed' para que el rand cambie
  int answer = rand() % 8; // Modulo 8 da un numero entre 0 y 7 (8 numeros)

  std::cout << "LA BOLA MAGICA 🎱 DICE: \n\n";

  if (answer == 0)
    std::cout << "Clarín.\n";
  else if (answer == 1)
    std::cout << "No estoy seguro, corre de nuevo.\n";
  else if (answer == 2)
    std::cout << "Mejor no te contesto.\n";
  else if (answer == 3)
    std::cout << "La cosa no se ve bien.\n";
  else if (answer == 4)
    std::cout << "Concéntrate y córrelo de nuevo.\n";
  else if (answer == 5)
    std::cout << "Probablemente.\n";
  else if (answer == 6)
    std::cout << "Córrelo en una hora.\n";
  else if (answer == 7)
    std::cout << "Mis fuentes dicen que no.\n";
  else
    std::cout << "Definitivamente no.\n";

  return 0;
}
