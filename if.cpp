class subif{
  public:
string analizar_complejidad(string &line, string &poli, vector<string> &fuente, int &num_linea, stack<string>& loops_condiciones, stack<string>& loops_condiciones_end) {
//
//
// Codigo que
// analiza
// complejidad
// de otros casos
//
//
if(line.find("if")){
  complejidad_linea = if_condicion(fuente, num_linea);
  return contador_OE(line);
}
//
//
// mas Codigo
// que no nos interesa ahora
//
}

string if_condicion(vector<string>& fuente, int num_linea) {
  vector<string> poli_ifs;
  stack<char> capas;
  string poli_temp, poli_complejo;
  bool atorado = true;



  capas.push('{');
  // inicio analisis del if
  while(!capas.empty()) {
    fuente[num_linea + 1].analizar_complejidad_if(poli_temp); // funcion auxiliar
    if(fuente[num_linea + 1].find('{')) {
      capas.push('{');
    }
    else if(fuente[num_linea + 1].find('}')) {
      capas.pop('}');
    }
    ++num_linea;
  } // fin; hasta aqui tendremos un string (poli_temp) con la complejidad de todo el if

  poli_ifs.__emplace_back(poli_temp); // se guarda al vector

  while(atorado) { //estara atorado hasta que ya no haya if elses
    // si hay un else if, hara lo siguiente:
    if(fuente[num_linea].find("else if") || fuente[num_linea + 1].find("else if")) {
      poli_temp = "";
      capas.push('{');
     // inicio analisis del if else
      while(!capas.empty()) {
        fuente[num_linea + 1].analizar_complejidad_if(poli_temp); // funcion auxiliar (NO RECURSIVO PRQUE ESTA CAÑON)
        if(fuente[num_linea + 1].find('{')) {
          capas.push('{');
        }
        else if(fuente[num_linea + 1].find('}')) {
          capas.pop('}');
        }
        ++num_linea;
      }// fin; hasta aqui tendremos un string (poli_temp) con la complejidad de todo el if

      poli_ifs.__emplace_back(poli_temp);// se guarda al vector
    }
    // si no hay else if, checara esto
    else if(fuente[num_linea].find("else") || fuente[num_linea + 1].find("else")) {
      poli_temp = "";
      capas.push('{');
      while(!capas.empty()) {
        fuente[num_linea + 1].analizar_complejidad_if(poli_temp); // funcion auxiliar
        if(fuente[num_linea + 1].find('{')) {
          capas.push('{');
        }
        else if(fuente[num_linea + 1].find('}')) {
          capas.pop('}');
        }
        ++num_linea;
      }
      poli_ifs.__emplace_back(poli_temp);
    } else {
      poli_complejo = el_mas_complejo(vector poli_ifs); // QUIROZ? que este metodo regrese el poliniomio mas complejo
      return poli_complejo;
    }
  }
}
