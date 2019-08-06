/**
   @file C�lculo de la sucesi�n de Fibonacci
*/


#include <iostream>
using namespace std;
#include <ctime>


/**
   @brief Calcula el t�rmino n-�simo de la sucesi�n de Fibonacci.

   @param n: n�mero de orden del t�rmino buscado. n >= 1.

   @return: t�rmino n-�simo de la sucesi�n de Fibonacci.
*/
int fibo(int n)
{
  if (n < 2)
    return 1;
  else
    return fibo(n-1) + fibo(n-2);
}


int main(int argc, char * argv[])
{
  if (argc!=2){
    cout <<"Falta el argunmento" << endl;
    return -1;
  }

  int n = atoi(argv[1]);;
  int f;
 
    
    clock_t tantes, tdespues, ttotal[10]; 
    // Para ejecutar 5 veces el programa
    for(int i = 0 ; i < 5 ; ++i){
      tantes = clock();
      f = fibo(n);
      tdespues = clock();
      ttotal[i] = (tdespues-tantes);
    } 

   clock_t peor = 0;
   for(int i = 0 ; i < 5 ; i++) {
     if(ttotal[i] > peor ) peor = ttotal[i];
   }
   
   cout << n << " " << ((double)(peor))/(CLOCKS_PER_SEC*(double)5) << endl;

  return 0;
}
