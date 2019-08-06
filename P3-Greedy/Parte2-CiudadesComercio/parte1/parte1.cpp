#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <cmath>
#include <string>

using namespace std;

// Struct usado para almacenar la informacion de las ciudades
struct Ciudad{
    int indice;
    double x;
    double y;
} ciudad;

// Método para cargar las ciudades desde un fichero
void leerFichero(const char fichero[], vector<Ciudad> &ciudades){
    // Crea el flujo
	ifstream f(fichero);
	// Para almacenar la cantidad de ciudades
    int dimension;
	// Para leer el string inicial (no interesa)
	string basura;

	// Si el flujo es correcto
    if(f){
		// Se ignora el string "DIMENSION:"
		f >> basura;
		// Se lee la cantidad de lineas
        f >> dimension;
		// Por cada linea, se almacena el indice, la coordenada 'x' y la coordenada 'y'
        for(int i = 0; i < dimension; i++){
			// Se almacena en un struct
            f >> ciudad.indice;
            f >> ciudad.x;
            f >> ciudad.y;
			// Se añade al vector de struct
          	ciudades.push_back(ciudad);
        }
    }
	// Se cierra el flujo
    f.close();
}

// Metodo que calcula la distancia total (coste) de la ruta
double costeTotal (vector<Ciudad> & ruta) {

	double coste = 0;
	
	// Se obtiene el coste acumulativo hasta la ultima ciudad (sin contar el regreso)
	for( int i = 0 ; i < ruta.size()-1 ; i++ ) {
		coste += sqrt( pow( ruta[i].x - ruta[i+1].x, 2) + pow( ruta[i].y - ruta[i+1].y, 2) );
	}

	// Se devuelve el coste acumulado mas el coste a la ciudad origen
	return coste + sqrt( pow( ruta[ruta.size()-1].x - ruta[0].x, 2) + pow( ruta[ruta.size()-1].y - ruta[0].y, 2) );;
}

// Metodo que calcula el vecino mas cercano
void calcularCMC(vector<Ciudad> &ciudades, vector<Ciudad> &ciudades_solucion){

	int mejor = 99999999;

	// Se inicializa la solucion final a la origen
	for(int i = 0 ; i < ciudades.size() ; i++) {
		ciudades_solucion.push_back(ciudades[i]);
	}

	// Se recorren 'x' veces variando la ciudad origen
	for( int l = 0 ; l < ciudades.size() ; l++) { 

		// Vector para almacenar la ruta que se comprueba
		vector<Ciudad> rutaTemp;
		// Vector para almacenar las ciudades no visitadas
		vector<Ciudad> sinVisitar = ciudades;
		// Variable que almacena la ultima ciudad visitada (para reducir espacio en formula)
		Ciudad ultima;
		// Variables que contienen la distancia actual y la distancia minima hasta el momento
		double d, min;
		// Variable que almacena la posicion de la ciudad candidata a minimo
		int pos_candidata;

		// Se añade la primera ciudad origen (visitada por defecto)
		rutaTemp.push_back(sinVisitar[0]);
		// Se elimina la ciudad visitada
		sinVisitar.erase(sinVisitar.begin());

		// Mientras haya ciudades sin visitar
		while(sinVisitar.size()) {

			// Se actualiza la ultima visitada
			ultima =rutaTemp.back();
			// Se marca la distancia minima a un valor grande para que coja por defecto la primera ciudad sin visitar
			min = 99999999;
			// Se establece la primera ciudad sin visitar como la candidata
			pos_candidata = 0;

			// Para la ultima ciudad visitada, se calcula la ciudad mas cercana
			for(int i = 0 ; i < sinVisitar.size() ; i++) {

				// Se calcula el minimo
				d = sqrt( pow( ultima.x - sinVisitar[i].x, 2) + pow( ultima.y - sinVisitar[i].y, 2) );
				
				// Si la parte decimal es menor a 0.5 se usa la entera, sino se suma 1
				int entero = d/1;
				double decimal = d - entero;
				int d_trunc = ( decimal < 0.5) ? entero : entero+1;

				// Si la distancia es menor que el minimo actual, se actualiza
				if (d_trunc < min) {
					min = d_trunc;
					pos_candidata = i;	
				}
			}

			// Añade la ciudad candidata a la solucion
			rutaTemp.push_back(sinVisitar[pos_candidata]);
			// Elimina la ciudad elegida de no visitadas
			sinVisitar.erase(sinVisitar.begin()+pos_candidata);
		}
		// La ultima ciudad vuelve al principio
		rutaTemp.push_back(ciudades[0]);

		// Se calcula el nuevo coste de distancia de la ruta
		double coste = costeTotal(rutaTemp);
		// Si mejora el coste
		if(coste < mejor) {
			// Se actualiza el coste
			mejor = coste;
			// Se vacia la ruta solucion anterior
			ciudades_solucion.clear();
			// Se establece la nueva ruta optima
			for(int i = 0 ; i < rutaTemp.size() ; i++) ciudades_solucion.push_back(rutaTemp[i]);
		}

		// Se intercambia la ciudad origen
		Ciudad aux = ciudades[0];
		ciudades[0] = ciudades[l+1];
		ciudades[l+1] = aux;
	}
}

int main(int argc, char* argv[]){

    if(!argv[1]){
        cout << "Faltan parametros" << endl;
        return -1;
    }

	// ciudades almacena las ciudades leidas del fichero
	// recorrido_solucion almacena las ciudades en orden de visita (optimizadas por vecino mas cercano)
	vector<Ciudad> ciudades, recorrido_solucion;

	// se lee el fichero de ciudades
	leerFichero(argv[1], ciudades);
	// a partir de ciudades se almacena en recorrido_solucion las ciudades ordenadas por CMC
	calcularCMC(ciudades, recorrido_solucion);
	// a partir de una solucion del CMC se busca una optimizacion (en funcion del costo total)

	// Se saca el resultado de la ruta mas optima
	for(int i = 0 ; i < recorrido_solucion.size() ; ++i) 
		cout << recorrido_solucion[i].indice << " " << recorrido_solucion[i].x << " " << recorrido_solucion[i].y << endl;

	// Se obtiene el coste de la ruta optima
	cout << endl << endl << costeTotal(recorrido_solucion) << endl;

	return 0;
}
