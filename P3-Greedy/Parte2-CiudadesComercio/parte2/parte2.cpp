#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <cmath>
#include <string>

using namespace std;

// Estructura para representar la ciudad
struct Ciudad{
	int indice;
	double x;
	double y;
} ciudad;

// Funcion para cargar las ciudades en el vector de ciudades desde el fichero
void leerFichero(const char fichero[], vector<Ciudad> &ciudades){
	// Crea el flujo
	ifstream f(fichero);
	// Para almacenar la cantidad de ciudades
	int num_ciudades = 0;
	// Para leer el string inicial (no interesa)
	string basura;

	// Si el flujo es correcto
	if(f){
		// Ignoramos los caracteres "DIMENSION:"
		f >> basura;
		// Almacenamos el numero de ciudades
		f >> num_ciudades;
		
		// Almacenamos cada ciudad en el vector
		for(int i = 0; i < num_ciudades; i++){
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

// Funcion para borrar hasta 3 ciudades del conjunto de ciudades origen
void borrarCiudades(vector<Ciudad> &ciudades, int punto1, int punto2, int punto3){
	int contador = 1, i = 0;

	while((i < ciudades.size()) && (contador <= 3)){
		if((ciudades[i].indice == punto1) || (ciudades[i].indice == punto2) || (ciudades[i].indice == punto3)){
			ciudades.erase(ciudades.begin() + i);
			contador++;
		}
		else
			i++;
	}
}

// Funcion para obtener el recorrido parcial de tres ciudades alejadas
void obtenerRecorridoParcial(vector<Ciudad> &ciudades, vector<Ciudad> &recorrido_solucion){
	int punto_este = 0, punto_oeste = 0, punto_norte = 0;
	int minimo_x = 9999999, maximo_x = 0, maximo_y = 0;

	for(int i = 0; i < ciudades.size(); i++){
		if(ciudades[i].x < minimo_x){	//Ciudad más al oeste
			minimo_x = ciudades[i].x;
			punto_oeste = i;
		}
		if(ciudades[i].y > maximo_y){
			maximo_y = ciudades[i].y;	//Ciudad más al norte
			punto_norte = i;
		}
		if(ciudades[i].x > maximo_x){
			maximo_x = ciudades[i].x;	//Ciudad más al este
			punto_este = i;
		}
	}

	// Insertamos la ciudad seleccionada en el conjunto solucion
	recorrido_solucion.push_back(ciudades[punto_oeste]);
	recorrido_solucion.push_back(ciudades[punto_norte]);
	recorrido_solucion.push_back(ciudades[punto_este]);
	recorrido_solucion.push_back(ciudades[punto_oeste]);
	
	// Eliminamos esas ciudades del conjunto de ciudades
	borrarCiudades(ciudades, punto_norte+1, punto_oeste+1, punto_este+1);
}

// Funcion para calcular el recorrido total del circuito
double costeTotal (vector<Ciudad> & ciudades) {
	double recorrido = 0;

	// Se obtiene el coste acumulativo hasta la ultima ciudad (sin contar el regreso)
	for(int i = 1; i < ciudades.size(); i++){
		// Usamos la formula Heuclidea entre dos ciudades y acumulamos
		recorrido += sqrt(pow((ciudades[i-1].x)-(ciudades[i].x), 2)+pow((ciudades[i-1].y)-(ciudades[i].y), 2));
	}

	return recorrido;
}

// Funcion para seleccionar una ciudad entre las restantes
void seleccionarCiudad(vector<Ciudad> &ciudades, vector<Ciudad> &recorrido_solucion){
	Ciudad ciudad_actual;
	vector<Ciudad> recorrido_parcial;
	double min_distancia = 99999999999;
	int indice_ciudad = 0, indice_posicion_insertar = 0;

	// Para cada una de las ciudades restantes
	for(int i = 0; i < ciudades.size(); i++){
		ciudad_actual = ciudades[i];

		// Comprobamos si el recorrido parcial con esa ciudad tiene menor distancia
		for(int j = 1; j < recorrido_solucion.size() - 1; j++){	
			recorrido_parcial = recorrido_solucion;
			recorrido_parcial.insert(recorrido_parcial.begin() + j, ciudad_actual);
			double d = costeTotal(recorrido_parcial);

			// Si la distancia es menor almacenamos el indice de la ciudad y su posicion a insertar en las ciudades solucion
			if(d < min_distancia){
				min_distancia = d;
				indice_ciudad = i;
				indice_posicion_insertar = j;
			}

			// Limpiamos memoria
			recorrido_parcial.clear();
		}
	}

	// Insertamos la ciudad con menor recorrido en el recorrido parcial 
	recorrido_solucion.insert(recorrido_solucion.begin() + indice_posicion_insertar, ciudades[indice_ciudad]);
	ciudades.erase(ciudades.begin() + indice_ciudad);
}


// Funcion que obtiene la ruta solucion
void obtenerRuta(vector<Ciudad> &ciudades, vector<Ciudad> &recorrido_solucion){
	// Creamos el recorrido parcial de las tres ciudades
	obtenerRecorridoParcial(ciudades, recorrido_solucion);

	// Traspasamos las ciudades desde el vector hasta recorrido_solucion
	while(ciudades.size()){
		seleccionarCiudad(ciudades, recorrido_solucion);
	}
}

int main(int argc, char* argv[]){
    if(!argv[1]){
        cout << "Falta el parametro" << endl;
        return -1;
    }

	vector<Ciudad> ciudades, recorrido_solucion;
	// Cargamos las ciudades del fichero
	leerFichero(argv[1], ciudades);
	// Obtenemos la ruta solucion con menor recorrido
	obtenerRuta(ciudades, recorrido_solucion);

	// Imprimimos las ciudades en orden 
	for(int i = 0; i < recorrido_solucion.size(); i++)
		cout << recorrido_solucion[i].indice << " " << recorrido_solucion[i].x << " " << recorrido_solucion[i].y << endl;

	// Imprimimos el reccorrido total
	cout << endl << endl << costeTotal(recorrido_solucion) << endl;

	return 0;
}