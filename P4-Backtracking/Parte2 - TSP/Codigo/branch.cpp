#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <queue>
#include <chrono>

using namespace std;
using namespace std::chrono;

// Estructura que almacena informacion de una ciudad
struct Ciudad {
    int indice;  // Almacena el indice de la ciudad
    double x;    // Almacena coordenada x
    double y;    // Almacena coordenada y
} ciudad;

// Estructura que almacena informacion de un nodo
struct NodosVivos {
	int nivelNodo;           // Almacena el nivel al que corresponde el nodo
	double cotaLocal;		 // Almacena la cota local del nodo
    vector<int> sinVisitar;  // Almacena la lista de ciudades sin visitar
	vector<int> visitadas;   // Almacena la lista de ciudades visitadas
};

// Estructura que sobrescribe el operador () de una cola con prioridad
// Los nodos con mayor prioridad estaran en el tope
class ComparadorNodosCola {
	public:
		bool operator()(const NodosVivos nodoA, const NodosVivos nodoB) {
			return nodoA.cotaLocal > nodoB.cotaLocal;
		}
};

int numeroNodos = 0;	// Almacena el numero de nodos visitados
int numeroPodas = 0; 	// Almacena el numero de podas realizadas
int maxCola = 0;		// Almacena el tamaño maximo alcanzada de la cola con prioridad
duration<double> transcurrido;	// Almacena el tiempo transcurrido
double cotaGlobal; 		        // Almacena el coste hasta el nodo hoja
vector<Ciudad> ciudades_fich;   // Almacena las ciudades con sus coordenadas
int cantidadCiudades = 0;		// Almacena la cantidad de ciudades leidas

//--------------------------------------------------------------------//

// Lee las ciudades del fichero
void leerFichero(const char fichero[], vector<Ciudad> & ciudades){
    
    ifstream f(fichero); // Flujo para obtener datos
    string basura;       // Para almacenar caracteres previos a la dimension

    if(f) {
        f >> basura;
        f >> cantidadCiudades;

        for(int i = 0 ; i < cantidadCiudades ; i++) {
            f >> ciudad.indice;
            f >> ciudad.x;
            f >> ciudad.y;
            ciudades.push_back(ciudad);
        }
    }
    f.close();
}

// Calcula la distancia entre dos ciudades
double distanciaEntreCiudades(Ciudad a, Ciudad b) {
	return sqrt( pow( a.x - b.x, 2) + pow( a.y - b.y, 2) );
}

// Calcula el coste total de una ruta
double costeTotal(vector<int>  ruta) {

	double coste = 0;
	
	// Se obtiene el coste acumulativo hasta la ultima ciudad
	for(int i = 0 ; i < ruta.size()-1 ; i++)
		coste += distanciaEntreCiudades(ciudades_fich[ruta[i]-1], ciudades_fich[ruta[i+1]-1]);

	// Se retorna el coste mas el coste a la primera ciudad
	return coste + distanciaEntreCiudades(ciudades_fich[ruta[0]], ciudades_fich[ruta.back()]);
}

// Calcula la cota local optimista del nodo
void calcularCotaLocalOptimista(NodosVivos & nodo) {

	double cota;

	// Calcula el minimo coste entre todas las ciudades
	double minimo = distanciaEntreCiudades(ciudades_fich[0], ciudades_fich[1]);
	for(int i = 0 ; i < cantidadCiudades ; i++) {
		for(int j = i ; j < cantidadCiudades ; j++) {
			// Si la ciudad es diferente
			if(i != j) {
				double d = distanciaEntreCiudades(ciudades_fich[i], ciudades_fich[j]);
				if(d < minimo) minimo = d;
			}
		}
	}

	// Suma el minimo multiplicado por el numero de ciudades sin visitar
	cota += minimo*nodo.sinVisitar.size();

	// Suma el coste de todas las visitadas
	for(int i = 0 ; i < nodo.nivelNodo ; i++)
		cota += distanciaEntreCiudades(ciudades_fich[nodo.visitadas[i]-1], ciudades_fich[nodo.visitadas[i+1]-1]);
	
	// Se actualiza la cotaLocal del nodo
	nodo.cotaLocal = cota;
}

// Muestra resultados por pantalla
void escribirResultados(vector<int> solucion) {
	cout << "Ruta: ";
	for(int i = 0 ; i < cantidadCiudades ; i++) cout << ciudades_fich[solucion[i]-1].indice << " - ";
	cout << endl;
	cout << "Costo solucion: " << costeTotal(solucion) << endl;
	cout << "Nodos expandidos: " << numeroNodos << endl;
	cout << "Numero de podas: " << numeroPodas << endl;
	cout << "Tamaño max cola: " << maxCola << endl;
	cout << "Tiempo de ejecucion: " << transcurrido.count() << endl << endl;

	for(int i = 0 ; i < cantidadCiudades+1 ; i++) 
		cout << ciudades_fich[solucion[i]-1].indice << " " << ciudades_fich[solucion[i]-1].x << " " << ciudades_fich[solucion[i]-1].y << endl;
	cout << endl << endl;
}

// Calcula una solucion por el VMC
void calcularVMC(vector<int> & ciudades_solucion) {

	vector<int> ciudades;

	// Se inicializa la solucion final a la origen
	for(int i = 1 ; i <= cantidadCiudades ; i++) {
		ciudades_solucion.push_back(i);
		ciudades.push_back(i);
	}

	// Vector para almacenar la ruta que se comprueba
	vector<int> rutaTemp;
	// Vector para almacenar las ciudades no visitadas
	vector<int> sinVisitar = ciudades;
	// Variable que almacena la ultima ciudad visitada (para reducir espacio en formula)
	int ultima;
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
		ultima = ciudades_fich[rutaTemp.back()-1].indice;
		// Se marca la distancia minima a un valor grande para que coja por defecto la primera ciudad sin visitar
		min = 99999999;
		// Se establece la primera ciudad sin visitar como la candidata
		pos_candidata = 0;
		// Para la ultima ciudad visitada, se calcula la ciudad mas cercana
		for(int i = 0 ; i < sinVisitar.size() ; i++) {
			// Se obtiene la distancia
			d = distanciaEntreCiudades(ciudades_fich[ultima-1], ciudades_fich[sinVisitar[i]-1]);
			// Si mejora
			if(d < min) {
				min = d;
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

	// Se establece la nueva ruta optima
	ciudades_solucion.clear();
	for(int i = 0 ; i < rutaTemp.size() ; i++) ciudades_solucion.push_back(rutaTemp[i]);
	
}

// Obtiene el hijo de un nodo (un hijo es una ciudad no visitada del nodo)
void hijo(NodosVivos nodo, int ciudad, int i, NodosVivos & hijo) {
	// Se incializa el nodo hijo con la misma inforamcion que el padre
	hijo = nodo;
	// Se actualiza el nivel del hijo a partir del padre
	hijo.nivelNodo = nodo.nivelNodo + 1;
	// Se añade la ciudad visitada
	hijo.visitadas[hijo.nivelNodo] = ciudad;
	// Se elimina de las no visitadas
	hijo.sinVisitar.erase(hijo.sinVisitar.begin()+i);
}

// Metodo que calcula la ruta mas optima por Branch And Bound
void branchAndBound(vector<int> ciudades, NodosVivos &optimo) {

	// Se crea el primer nodo del arbol (raiz)
	NodosVivos nodo;
	// Se inicializa el nodo padre
	nodo.nivelNodo = 0;
	nodo.visitadas.resize(cantidadCiudades);
	nodo.visitadas[0] = 1;
	// Se añaden las ciudades que no se han visitado
	for(int i = 2 ; i <= cantidadCiudades ; i++) nodo.sinVisitar.push_back(i);

	// Se obtiene la cota local (optimista) del nodo padre
	calcularCotaLocalOptimista(nodo);
	// Declaracion cola con prioridad de nodos vivos
	priority_queue<NodosVivos, vector<NodosVivos>, ComparadorNodosCola> colaNodos;
	// Se añade el nodo padre a la cola con prioridad
	colaNodos.push(nodo);
	// Mientras haya nodos en la cola con prioridad y mejore el coste
	while(!colaNodos.empty() && colaNodos.top().cotaLocal < cotaGlobal) {

		// Se obtiene el nodo del tope de la cola (tiene menor cotaLocal, es el mas prometedor)
		nodo = colaNodos.top();
		// Se aumenta el contador de nodo expandido
		numeroNodos++;
		// Se elimina el nodo del tope de la cola
		colaNodos.pop();

		// Para cada ciudad no visitada del nodo
		for(int i = 0 ; i < nodo.sinVisitar.size() ; i++) {
			// Se genera un hijo del nodo
			NodosVivos nodoHijo;
			hijo(nodo, nodo.sinVisitar[i], i, nodoHijo);
			// Se obtiene la cota local (optimista) del nodo hijo
			calcularCotaLocalOptimista(nodoHijo);
			// Si el nodo generado es nodo hoja 
			if(nodoHijo.nivelNodo == cantidadCiudades-1) {
				// Si la cota mejora, es solucion
				if(costeTotal(nodoHijo.visitadas) <= cotaGlobal){
					cotaGlobal = nodoHijo.cotaLocal;
					optimo = nodoHijo;
					optimo.visitadas.push_back(optimo.visitadas[0]);
				}
			}
			// Si no es hoja pero mejora la cota
			else if(nodoHijo.cotaLocal < cotaGlobal) colaNodos.push(nodoHijo);
			// Si no, se poda (no hace nada)
			else numeroPodas++;

			// Se actualiza el indicador de tamaño de cola
			if(colaNodos.size() > maxCola) maxCola = colaNodos.size();
		}
	}
}

int main(int argc, char ** argv) {

    if(argc < 2){
		cout << "Pasa por parametro el archivo de ciudades" << endl;
		return 1;
	}

    // Se lee el fichero
    leerFichero(argv[1], ciudades_fich);

    // Se obtiene la primera solucion
    vector<int> solucion;
    calcularVMC(solucion);

	// Inicializa la cota global
	cotaGlobal = costeTotal(solucion);
	// Se elimina la ultima posicion para el B&B
	solucion.pop_back();

	// Estructura donde se almacena la solucion del branch and bound
	NodosVivos optimo;

	// Se obtiene tiempo inicial
	high_resolution_clock::time_point tantes = high_resolution_clock::now();
	
	// Algoritmo de Branch And Bound
    branchAndBound(solucion, optimo);

	// Se calcula el tiempo de calculo total
	high_resolution_clock::time_point tdespues = high_resolution_clock::now();
	transcurrido = duration_cast<duration<double> >(tdespues - tantes);

	// Se muestran los resultados
	escribirResultados(optimo.visitadas);

	// Fin
    return 0;
}