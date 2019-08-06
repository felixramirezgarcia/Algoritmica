#include <iostream>
using namespace std;
#include <ctime>
#include <cstdlib>
#include <climits>
#include <cassert>


static int maximo(int v[], int num_elem){
  int mayor = 0;
      
  for (int i=0; i<num_elem; i++){
      if (v[i]> mayor){
          mayor=v[i];
      }
  }

  return mayor;
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
    int a = maximo(T, n);
    tdespues = clock();
    ttotal[i] = (tdespues-tantes);
  } 

  clock_t peor = 0;
  for(int i = 0 ; i < 5 ; i++) {
    if(ttotal[i] > peor ) peor = ttotal[i];
  }
  cout << n << " " << 100.0*((double)(peor))/(CLOCKS_PER_SEC*(double)5) << endl;

  delete [] T;

  return 0;
}
