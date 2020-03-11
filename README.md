# Tarea *1*. *Complejidad Computacional*

---

##### Integrantes:
1. *Andrés Barragán Salas* - *A01026567* - *CSF*
2. *Héctor Arturo Quinde García* - *A01339451* - *CSF*
3. *Abraham Garca Del Corral* - *A01023256* - *CSF*
4. *Rodrigo Quiroz Reyes* - *A01026546* - *CSF*
5. *Gerardo Anglada de Landa* - *A01021917* - *CSF*

---
## 1. Aspectos generales

Las orientaciones de la tarea se encuentran disponibles en la plataforma **Canvas**.

Este documento es una guía sobre qué información debe entregar como parte de la tarea, qué requerimientos técnicos debe cumplir y la estructura que debe seguir para organizar su entrega.


### 1.1 Requerimientos técnicos

A continuación se mencionan los requerimientos técnicos mínimos de la tarea, favor de tenerlos presente para que cumpla con todos.

* El código debe desarrollarse en C++, cumpliendo con el último estándar [C++17](https://isocpp.org/std/the-standard).
* Toda la programación debe realizarse utilizando Programación Genérica.
* Deben utilizarse las [C++ Core Guidelines](https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md).
* Todo el código debe estar correctamente documentado, siguiendo los lineamientos que aparecen en [Documenting C++ Code](https://developer.lsst.io/cpp/api-docs.html).
* Todo el código de la tarea debe alojarse en este repositorio de GitHub.
* Debe configurar su repositorio para que utilice el sistema de Integración Continua [Travis CI](https://travis-ci.org/).

### 1.2 Estructura del repositorio

El proyecto debe seguir la siguiente estructura de carpetas:
```
- / 			        # Raíz del repositorio
    - README.md			# Archivo con la información general de la actividad (este archivo)
    - sources  			# Códigos fuente con la solución
    - examples			# Archivos de ejemplo que pueden utilizarse para verificar que la solución funciona.
```

## 2. Solución

La solución implementada constituye un programa que analiza linea por linea la complejidad de un código. Sobre cada iteración un metodo se encarga de analizar si la linea pertenece a una de las 3 estructuras implementadas (*"for"*, *"while"* e *"if"*) o si es simplemente una línea con operaciones elementales. En primera instancia se imprimira cada línea de código seguida de sus operaciones elementales correspondientes, las cuales pueden ser expresadas como números enteros, o como polinomios (casos *"for"* y *"while"*). Además de imprimir la tabla, simultaneamente la función almacena las operaciones elementales del código en una variable "polinomio", la cuál, será impresa para y posteriormente analizada por otro código, el cual se encargara de simplificar y obtener la complejidad *"Big O"* del polinomio, y la del código como resultado.  

### 2.1 Pasos a seguir para utilizar la aplicación

Primeramente, el repositorio debe de ser clonado. Para ello, se debe de correr el siguiente comando en la terminal del ordenador que se está utilizando, habiendose ubicado previamente en la ubicación donde se desea guardar el repositorio: 
   
    $ git clone https://github.com/tec-csf/tc2017-t1-primavera-2020-equipo-2-1.git

Una vez clonado el repositorio, se tiene acceso a los códigos fuente que analizan la complejidad del código y los codigos *".cpp"* que pueden ser utilizados de ejemplo para probar el código. Para realizar lo anterior se pueden seguir los siguientes comandos en orden (tomado en cuenta que el compilador g++/clang se encuentra instalado en su ordenador): 

    $ g++ funciones.cpp complejidad.cpp -o complejidad

    $ ./complejidad -o ./examples/ejemplo1.cpp

De esta manera, la solución implementada mostrara el código que se ha analizado, una tabla con sus respectivas operaciones elementales, el polinomio correspondiente a dicho código y orden de complejidad *"Big O"*. Notese que existen 3 ejemplos para probar el codigo, para utilizarlos simplemente se puede cambiar el numero a de *"ejemplo#.cpp"* por 1, 2 o 3. 

## 3. Referencias

    http://www.cplusplus.com/reference/regex/

La librería *"regex"* por "regular expression" fue una herramienta útil en el momento en el que se trabajo sobre el polinomio para identificar patrones dentro del "string" que se envíaba como parametro, de este manera se logró que las operaciones entre monomios y polinomios pudiera ser efectuada.

    http://www.cplusplus.com/reference/stack/stack/
    
La librería de *"stack"* fue muy útil en este caso debido a que las pilas, debido a su funcionamiento, resultaron ser muy utiles en los casos donde se quería conocer las lineas que se encontraban entro de las llaves ({}) que encerraban el contenido de una estructura, ya sea (*"for"*, *"while"* o *"if"*). 
