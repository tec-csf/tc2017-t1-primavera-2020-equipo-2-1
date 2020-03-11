from sympy import*
archivo=open('polinomio.txt','r')
simplificar=archivo.readline();
archivo.close()
def polinomio (elPolinomio):
    n= symbols('n')
    return(expand(elPolinomio))
resultado=str(polinomio(simplificar))
archivo2=open('polinomio.txt','w')
archivo2.write(resultado)
archivo2.close()