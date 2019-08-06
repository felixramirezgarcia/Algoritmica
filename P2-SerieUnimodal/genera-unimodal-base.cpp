#include <chrono>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <climits>
#include <cassert>
#include <vector>


using namespace std;
using namespace std::chrono;

/*
	Devuelve el pivote, si no lo encuentra devuelve -1.
*/
int buscar(int *T, int n){
	int pivote = -1;
	int anterior = T[0];
	
	for(int i = 0 ; i < n && pivote == -1 ; ++i){
		if(anterior > T[i]){
			pivote = anterior;
		}
		anterior = T[i];	
	}
	
	return pivote;
}

/*
generador de ejemplos para el problema de la serie unimodal de n�meros. 
Se genera un �ndice aleatorio entre 1 y n-2, se asigna el mayor entero (n-1) a ese �ndice,
a los �ndices anteriores a p se le asignan valores en orden creciente (0,1,...,p-1) y a los �ndices mayores que
p se le asignan valores en orden decreciente (n-2, n-3,...,p)
Genera un n�mero uniformemente distribuido en el intervalo [0,1) a partir de uno de los generadores disponibles en C.
*/
double uniforme(){
	double u;
	u = (double) rand();
	u = u/(double)(RAND_MAX+1.0);
	
	return u;
}

int main(int argc, char * argv[]){
	
	int n = 100;


	if (argc != 2){
    	cerr << "Formato " << argv[0] << " <num_elem>" << endl;
    	return -1;
	}

	n = atoi(argv[1]);

	
	int * T = new int[n];
	assert(T);

	/*
		Se genera un pivote (p) y en su posici�n se inserta n-1 
	*/
	srand(time(0));
	double u=uniforme();
	int p=1+(int)((n-2)*u);
	T[p]=n-1;
	
	/*
		Se rellena el vector ascendentemente hasta el pivote
	*/
	for (int i=0; i<p; i++) T[i]=i;
	
	/*
		Rellena el vector en orden descendente despues del pivote
	*/
	for (int i=p+1; i<n; i++) T[i]=n-1-i+p;
	
	// Print
	//for (int j=0; j<n; j++) {cout << T[j] << " ";}
	
	//Inicializar variables chrono
    high_resolution_clock::time_point tantes, tdespues;
    duration<double> transcurrido;
    int res;

    tantes = high_resolution_clock::now();
    res = buscar(T,n);
    tdespues = high_resolution_clock::now();
	//cout << "\nEl pivote esta en: " << res << endl;

	transcurrido = duration_cast<duration<double> >(tdespues - tantes);
	//Para aniadir al fichero de salida con la macro
    std::cout << n << " " <<  transcurrido.count() << endl;

}
