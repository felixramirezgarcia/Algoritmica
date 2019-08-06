/**
   @file Ordenaci�n por selecci�n
*/

   
#include <iostream>
using namespace std;
#include <ctime>
#include <cstdlib>
#include <climits>
#include <cassert>







inline static 
void seleccion(int T[], int num_elem);

static void seleccion_lims(int T[], int inicial, int final);


void seleccion(int T[], int num_elem)
{
  seleccion_lims(T, 0, num_elem);
}

static void seleccion_lims(int T[], int inicial, int final)
{
  int i, j, indice_menor;
  int menor, aux;
  for (i = inicial; i < final - 1; i++) {
    indice_menor = i;
    menor = T[i];
    for (j = i; j < final; j++)
      if (T[j] < menor) {
	indice_menor = j;
	menor = T[j];
      }
    aux = T[i];
    T[i] = T[indice_menor];
    T[indice_menor] = aux;
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
      seleccion(T, n);
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
