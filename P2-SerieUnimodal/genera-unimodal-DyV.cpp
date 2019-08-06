#include <chrono>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <climits>
#include <cassert>
#include <vector>

using namespace std;
using namespace std::chrono;

double uniforme(){
    double u;
    u = (double) rand();
    u = u/(double)(RAND_MAX+1.0);
    return u;
}

std::vector<int> genera (int n) {
    std::vector<int> T(n);
    srand(time(0));
    double u=uniforme();
    int p=1+(int)((n-2)*u);
    T[p]=n-1;
    for (int i=0; i<p; i++) T[i]=i;
    for (int i=p+1; i<n; i++) T[i]=n-1-i+p;
    return T;
}

int buscarDyV(const std::vector<int> &v, int inicio, int fin) {
    int tamanio = fin - inicio + 1;

    if(tamanio > 2) {
        int mitad = (tamanio/2) + inicio;
        int izquierda = v[mitad-1];
        int derecha = v[mitad+1];
        int valor_mitad = v[mitad];

		//caso base 1, valor central es el mayor
        if(valor_mitad>izquierda && valor_mitad>derecha) 
			return valor_mitad; 
        else {
			//coger la primera mitad desde valor_mitad
            if(valor_mitad > derecha) {
                return buscarDyV(v,inicio,mitad);
            }
			//coger la segunda mitad desde valor_mitad
            if(valor_mitad < derecha) {
                return buscarDyV(v,mitad+1,fin);
            }	
        }
    }
	//caso base 2, vector con n <= 2
    else {
		//cuando quedan dos, coje el mayor
        if(tamanio==2) { 
            if(v[inicio]>v[fin]) 
				return v[inicio];
            else 
				return v[fin];
        }
		//si queda uno, lo devuelve
        else 
            return v[inicio];
    }
}

int main(int argc, char * argv[]){

	if (argc != 2)
    {
        std::cerr << "Formato " << argv[0] << " <num_elem>" << "\n";
        return -1;
    }

	//Inicializar variables chrono
    high_resolution_clock::time_point tantes, tdespues;
    duration<double> transcurrido;
	//Rellenar vector 
    int n = atoi(argv[1]);
    std::vector<int> T = genera(n);
	int p;

	/*
	//Descomentar para imprimir la lista (valores de n pequenios)
	std::cout << "La lista de elementos es: " << endl;
	for(int i = 0 ; i < n ; i++){
		std::cout << T[i] << " " ;
	}
	std::cout << endl;
	*/

    tantes = high_resolution_clock::now();
    p = buscarDyV(T,0,n-1);
    tdespues = high_resolution_clock::now();

	/*
	Descomentar para imprimir el resultado
	std::cout << "El numero con el mayor valor es: " << p << endl;
	*/

    transcurrido = duration_cast<duration<double> >(tdespues - tantes);
	//Para aniadir al fichero de salida con la macro
    std::cout << n << " " <<  transcurrido.count() << endl;

    return 0;
}
