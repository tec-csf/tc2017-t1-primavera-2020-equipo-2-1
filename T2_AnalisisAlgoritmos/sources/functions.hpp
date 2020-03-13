#include <iostream> // cin y cout
#include <cstdlib>  // rand() y srand()
#include <fstream>  // archivos
#include <string>   // substr()
#include <cstdio>   // printf()
#include <ctime>    // time() [para rands] y clock()
#include <stack>
#include <vector>

using namespace std;

// type name(parameters);
// void asterisk(std::string word, std::string &text, int i);

// Only if there is a class
class Name
{
  // variables (todo estos son privados)

  // method declaration (definition will be made in cpp)
  public:

    // CONSTRUCTORES
    Name(string new_name);
    Name(string new_name, int val);

    // Destructor (SOLO UNO)
    ~Name();

    // type name(parameters);
    // void asterisk(std::string word, std::string &text, int i);


  protected:
    // type name(parameters);
    // void asterisk(std::string word, std::string &text, int i);

  private:
    // type name(parameters);
    // void asterisk(std::string word, std::string &text, int i);
};
