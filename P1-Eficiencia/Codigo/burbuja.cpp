/**
   @file Ordenaci�n por burbuja
*/

//  g++ burbuja.cpp -o burbuja && ./macro.sh burbuja
   
#include <iostream>
using namespace std;
#include <ctime>
#include <cstdlib>
#include <climits>
#include <cassert>


/* ************************************************************ */ 
/*  M�todo de ordenaci�n por burbuja  */

/**
   @brief Ordena un vector por el m�todo de la burbuja.

   @param T: vector de elementos. Debe tener num_elem elementos.
             Es MODIFICADO.
   @param num_elem: n�mero de elementos. num_elem > 0.

   Cambia el orden de los elementos de T de forma que los dispone
   en sentido creciente de menor a mayor.
   Aplica el algoritmo de la burbuja.
*/
inline static 
void burbuja(int T[], int num_elem);



/**
   @brief Ordena parte de un vector por el m�todo de la burbuja.

   @param T: vector de elementos. Tiene un n�mero de elementos 
                   mayor o igual a final.Es MODIFICADO.

   @param inicial: Posici�n que marca el incio de la parte del
                   vector a ordenar.
   @param final: Posici�n detr�s de la �ltima de la parte del
                   vector a ordenar. 
		   inicial < final.

   Cambia el orden de los elementos de T entre las posiciones
   inicial y final - 1de forma que los dispone en sentido creciente
   de menor a mayor.
   Aplica el algoritmo de la burbuja.
*/
static void burbuja_lims(int T[], int inicial, int final);



/**
   Implementaci�n de las funciones
**/

inline void burbuja(int T[], int num_elem)
{
  burbuja_lims(T, 0, num_elem);
}


static void burbuja_lims(int T[], int inicial, int final)
{
  int i, j;
  int aux;
  for (i = inicial; i < final - 1; i++)
    for (j = final - 1; j > i; j--)
      if (T[j] < T[j-1])
	{
	  aux = T[j];
	  T[j] = T[j-1];
	  T[j-1] = aux;
	}
}




int main(int argc, char * argv[])
{
  
    if (argc != 2)
    {
      cerr << "Formato " << argv[0] << " <num_elem>" << endl;
      return -1;
    }





    int n = atoi(argv[1]);

    int * T = new int[n];
    assert(T);

    srandom(time(0));



    
    clock_t tantes, tdespues, ttotal[10]; 
    // Para ejecutar 5 veces el programa
    for(int i = 0 ; i < 5 ; ++i){
      for (int j = 0; j < n; j++) T[j] = random();
      tantes = clock();
      burbuja(T, n);
      tdespues = clock();
      ttotal[i] = (tdespues-tantes);
    } 

   clock_t peor = 0;
   for(int i = 0 ; i < 5 ; i++) {
     if(ttotal[i] > peor ) peor = ttotal[i];
   }
   
   cout << n << " " << ((double)(peor))/(CLOCKS_PER_SEC*(double)5) << endl;

   delete [] T;

    return 0;
}
