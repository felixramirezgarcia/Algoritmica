#include <iostream>
#include <fstream>
#include <map>
#include <cmath>
#include <vector>
#include <queue>
#include <limits>
#include <chrono>

using namespace std;
using namespace std::chrono;

//Estructura que representa la ruta solucion al problema
struct Ruta{
  int nivel;                         //Representa el nivel actual del nodo
  double cotaLocal;                  //Representa la cota local del nodo.
  vector<int> circuito;              //Representa el circuito solución.
  vector<int> noVisitadas;           //Representa las ciudades no visitidas.
};

//Funcion para comparar la cota local de dos rutas
class compararCotaLocal{
public:
  bool operator()(const Ruta & ruta1, const Ruta & ruta2){
    return ruta1.cotaLocal > ruta2.cotaLocal;
  }
};

//Función para leer el archivo con las coordenadas:
void cargarRuta(string & fichero, map<int,pair<double,double>> & mapa){
  ifstream datos;
  string s;
  pair<double,double> position;
  int n,act;

  datos.open(fichero.c_str());
  if(datos.is_open()) {
 	datos >> s; 
	datos >> n;
    int i=0;

    while(i<n){
        datos >> act >> position.first >> position.second;
        mapa[act] = position;
        i++;
    }
    datos.close();
 }
 else{
   cout << "Lectura erronea del fichero " << fichero << endl;
   exit(-1);
 }
}

//Función para calcular la distancia entre dos puntos
double Longitud(pair<double,double> punto1, pair<double,double> punto2){
	return sqrt(pow(punto2.first-punto1.first,2) + pow(punto2.second-punto1.second,2));
}

//Función para calcular la matriz de distancias
void CalcularMatrizDistancias(double** matriz, int n, map<int,pair<double,double>> & mapa){
	for(int i = 1; i < n; ++i)
		for(int j = 1; j < n; ++j)
			matriz[i][j] = Longitud(mapa[i], mapa[j]);
}

//Método para calcular el coste de una solución
double CalcularSolucion(vector<int> Ruta, double** matriz){
  double coste = 0;
  for(unsigned int i = 0; i < Ruta.size()-1; ++i)   coste += matriz[Ruta[i]][Ruta[i+1]];
  coste += matriz[Ruta.front()][Ruta.back()];

  return coste;
}

//Funcion para calcula la cota global inicial
double CalcularCotaGlobalInicial(vector<int> & inexplorados, double** matriz){
	//Variables para el calculo de la distancia
	vector<int> aux, auxTemp, inexplorados_tmp;
	double mejor = -1.0, distianciaTemp, distanciaMin;
	int ciudadActual, ciudadSiguiente;

	//Calculamos la distancia desde diferentes puntos de partida
	for(int i = 0; i < inexplorados.size(); ++i){
		distianciaTemp = 0.0;
		inexplorados_tmp = inexplorados;
		ciudadActual = inexplorados_tmp[i];
		auxTemp.push_back(ciudadActual);   //Incorporamos la ciudad al conjunto de seleccionados
		inexplorados_tmp.erase(inexplorados_tmp.begin()+i); //Eliminamos la ciudad de los inexplorados

        //Mientras existan ciudades por visitar
		while(!inexplorados_tmp.empty()){
			//Aplicamos la funcion solucion del vecino mas cercano
			distanciaMin = matriz[ciudadActual][inexplorados_tmp[0]];
			ciudadSiguiente = 0;
			for(int j = 1; j < inexplorados_tmp.size(); ++j)
				if(matriz[ciudadActual][inexplorados_tmp[j]] < distanciaMin){
					ciudadSiguiente = j;
					distanciaMin = matriz[ciudadActual][inexplorados_tmp[j]];
				}
			//Las ciudades seleccionadas son factibles al no pertenecer al conjunto de las inexploradas
			distianciaTemp += distanciaMin;
			auxTemp.push_back(inexplorados_tmp[ciudadSiguiente]);
			ciudadActual = inexplorados_tmp[ciudadSiguiente];
			inexplorados_tmp.erase(inexplorados_tmp.begin()+ciudadSiguiente);
		}

		//Sumamos la distancia entre la primera y la ultima ciudad
		distianciaTemp += matriz[auxTemp.front()][auxTemp.back()];

		//Si la solucion es mejor
		if((mejor == -1.0) || (distianciaTemp < mejor)){
			mejor = distianciaTemp;
			aux = auxTemp;
		}

		auxTemp.clear(); // Vaciamos la solucion temporal
	}

	return mejor;
}

//Función para calcular la cota local de un nodo
void calcularCotaLocalNodo(Ruta & ruta, double **matriz, int tam){
  double cotaLocal = 0.0;
  //Calculamos la distancia del circuito hasta el nodo
  for(int i = 0; i<ruta.nivel; ++i)
    cotaLocal += matriz[ruta.circuito[i]][ruta.circuito[i+1]];

  //Calcular el circuito minimo para las ciudades no visitadas
  double minimo;
  for(int i = 0; i<ruta.noVisitadas.size(); ++i){
    minimo = 999999999;
    for(int j = 1; j < tam+1; ++j)
      if(ruta.noVisitadas[i] != j && matriz[ruta.noVisitadas[i]][j] < minimo)
        minimo = matriz[ruta.noVisitadas[i]][j];
    cotaLocal += minimo;
  }

  //añadimos el recorrido mas corto para salir de la ciudad seleccionada
  minimo = 999999999;
  for(int i = 1; i < tam+1; ++i)
    if(i != ruta.circuito[ruta.nivel] && matriz[i][ruta.circuito[ruta.nivel]] < minimo)
      minimo = matriz[i][ruta.circuito[ruta.nivel]];
  cotaLocal += minimo;

  ruta.cotaLocal = cotaLocal;
}

//Función para crear el nodo raiz del arbol 
Ruta CrearNodoRaiz(int tam, double** matriz){
  Ruta rutaInicial;
  rutaInicial.nivel = 0;
  rutaInicial.circuito.resize(tam);
  //Empezando por la primerz ciudad
  rutaInicial.circuito[rutaInicial.nivel] = 1; 
  //Rellenamos el vector de las no visitadas
  for(int i = 2; i <= tam; ++i)
    rutaInicial.noVisitadas.push_back(i);
  calcularCotaLocalNodo(rutaInicial, matriz, tam);

  return rutaInicial;
}

//Función para construir el hijo de un nodo
Ruta CrearNodoHijo(const Ruta & nodoPadre, int ciudad, int tam, double** matriz){
  Ruta nodoHijo = nodoPadre;
  nodoHijo.nivel = nodoPadre.nivel + 1;
  nodoHijo.circuito[nodoHijo.nivel] = ciudad;
  bool encontrado = false;
  //Recirremos la no visitadas hasta encontrar la ciudad
  for(auto it = nodoHijo.noVisitadas.begin(); it != nodoHijo.noVisitadas.end() && !encontrado; ++it)
    if(*it == ciudad){
      //Cuando la encuentra la eliminamos de las no visitadas
      encontrado = true;
      nodoHijo.noVisitadas.erase(it);
    }
  calcularCotaLocalNodo(nodoHijo, matriz, tam);

  return nodoHijo;
}

//Función B&B para el Viajante de Comercio:
void BanchAndBound(int tam, double** matriz, vector<int> & candidatos){
  int ciudad, nodos_exp = 0, num_podas = 0;
  int tam_max = numeric_limits<int>::min();
  double distancia = 0.0;
  Ruta e_node, hijo, mejorRuta;
  priority_queue<Ruta, vector<Ruta>, compararCotaLocal> Q;
  double CG = CalcularCotaGlobalInicial(candidatos, matriz);
  e_node = CrearNodoRaiz(tam, matriz);
  Q.push(e_node);

  while(!Q.empty() && (Q.top().cotaLocal < CG)){
    e_node = Q.top();
    Q.pop();
    nodos_exp++;
    for(int i = 0; i<e_node.noVisitadas.size(); ++i){
      ciudad = e_node.noVisitadas[i];
      hijo = CrearNodoHijo(e_node, ciudad, N, matriz);
      if(hijo.nivel == N-1){
        distancia = CalcularSolucion(hijo.circuito, matriz);
        if(distancia < CG){
          CG = distancia;
          mejorRuta = hijo;
        }
      }
      else if(hijo.cotaLocal < CG)
        Q.push(hijo);
      else
        num_podas++;
      if((int) Q.size() > tam_max) tam_max = (int) Q.size();
    }
  }
  //Imprimir resultados:
  cout << "circuito: ";
  for(int i = 0; i<mejorRuta.circuito.size(); ++i)
    cout << "[" << mejorRuta.circuito[i] << "]";
  cout << endl;
  cout << "Distancia: " << CG << endl;
  cout << "Nodos expandidos: " << nodos_exp << endl;
  cout << "Podas realizadas: " << num_podas << endl;
  cout << "Tamaño máximo de la cola: " << tam_max << endl;
}


int main(int argc, char* argv[]){

    if(argc < 2){
        cout << "Modo de empleo: " << argv[0] << " <archivo.tsp>" << endl;
        exit(-1);
    }

    high_resolution_clock::time_point tantes, tdespues;
    duration<double> duracion;
    string archivo(argv[1]);
    map<int,pair<double,double>> puntos;

    //Leer los puntos:
    cargarRuta(archivo, puntos);
    int N = puntos.size();

    //Reservar matriz de distancia:
    double** D = new double*[N+1];
    for(int i = 0; i<N+1; ++i)  D[i] = new double[N+1];

    //Calcular matriz de Distancias
    CalcularMatrizDistancias(D, N+1, puntos);

    //Crear el vector de candidatos para el greedy:
    vector<int> cand;
    for(int i = 1; i<=N; ++i)
        cand.push_back(i);

    tantes = high_resolution_clock::now();
    BanchAndBound(N, D, cand);
    tdespues = high_resolution_clock::now();

    duracion = duration_cast<duration<double>>(tdespues - tantes);
    cout << "Tiempo transcurrido: " << duracion.count() << " segundos" << endl;

    for(int i = 0; i<N+1; ++i)
    delete[] D[i];
    delete[] D;

    exit(0);
}