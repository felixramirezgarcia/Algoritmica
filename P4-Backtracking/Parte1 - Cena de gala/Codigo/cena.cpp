#include <vector>
#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;

high_resolution_clock::time_point tantes, tdespues;
duration<double> transcurrido;

int conveniencia_max = 0;
bool completo = false;
vector<int> cotaNivel;
vector<int> cotaTemp;

// Metodo que inicializa una matriz m de tamaño n
int **rellenarMatriz(int n){
	int **m;
	m = new int*[n];

    //Declarar las listas de invitados
	for (int i = 0 ; i < n ; i++) m[i] = new int[n];

    srand(time(NULL));

	for (int i = 0; i < n ; i++){
		for (int j = i ; j < n ; j++){
            // Rellenamos la diagonal de la matriz a 0
			if (i==j) m[i][j] = 0;
			// Rellenamos la m simetrica
			else{
				int aleatorio = 1 + ( rand() % (100) );
				m[i][j] = aleatorio;
				m[j][i] = aleatorio;
			}
		}
	}
	return m;
}

// Metodo para mostrar la matriz
void imprimirMatriz(int **m, int n){
    for (int i = 0 ; i < n ; i++){
        for (int j = 0 ; j < n ; j++){
			cout << "| " << m[i][j] << " |";
        }
        cout << endl;
    }    					
	cout << endl;
}

// Metodo que imprime la solucion encontrada
void imprimirSolucion(int *solucion,int n){
	for (int j = 0 ; j < n ; j++) cout << "| " << solucion[j] << " |";
	cout << endl;
}

// Metodo que calcula la convenciencia
int convenienciaActual(int n, int solucion[], vector<bool> &sentados, int **matriz, int nivel){
    
    // Almacenamos en un vector los indices de los invitados 
	vector<int> invitados; 
	int conveniencia = 0;

    // Se comprueba si hay mas de uno sentado
	int cont = 0 ;
	for(int i = 0 ; i < sentados.size() ; i++) if(sentados[i]) cont++;
	
	// Si hay mas de una persona sentada
	if(cont > 1) {
		// Recorremos todos los invitados
		for(int i = 0 ; i < n ; i++){
			// Si el invitado está sentado
			if(sentados[i]){
				for(int j = 0 ; j < n ; j++) {
					// Buscamos donde se encuentra en la solucion
					if(solucion[j] == i) invitados.push_back(j);
				}
			}
		}

		// Recorremos la lista de invitados y sumamos la conveniencia del invitado de la izquierda
		for(int i = 1 ; i < invitados.size() ; i++) conveniencia += matriz[invitados[i-1]][invitados[i]]; 

        // Se añade la vuelta a la primera persona sentada
		if(nivel == n) conveniencia += matriz[0][invitados.back()]; 
		
	}
	// Devolvemos el doble del resultado para acumular la suma de los invitados sentados a la derecha
	return (conveniencia*2);
}

void algoritmo_backtracking (int n_invitados, int nivel, int invitado, int &conveniencia_actual, int solucion_actual[],
    vector<bool> &sentados, int **m, int solucion_final[]) {

    // Se añade al invitado a la lista de sentados
	sentados[invitado] = true;
    // Se añade a la solucion
	solucion_actual[nivel - 1] = invitado;
	conveniencia_actual = 0;

    // Atributo para determinar cuando podar o no
	bool poda = false;

    // Recorremos todos los invitados
	for (int n_invitado = 0 ; n_invitado < n_invitados ; n_invitado++) { 
		// Si el invitado a evaluar no esta sentado 
		if (!sentados[n_invitado]) {
			// Calculamos la conveniencia actual
			conveniencia_actual = convenienciaActual(n_invitados, solucion_actual, sentados, m, nivel);
			// Hasta llegar a la primera hoja, se añade la cota inicial
			if (!completo) { 
				cotaNivel.push_back(conveniencia_actual);
				cotaTemp.push_back(conveniencia_actual);
			}
            // Si ya se hizo la primera rama completa
			else {
				// Si la conveniencia no mejora se poda
				if(conveniencia_actual < cotaNivel[nivel-1]) poda = true;
				else cotaTemp[nivel-1] = conveniencia_actual;	
			}

            // Si no se poda
			if(!poda) {

				// Aumentamos recursivamente un nivel para evaluar los hijos
				algoritmo_backtracking(n_invitados, nivel+1, n_invitado, conveniencia_actual, solucion_actual, sentados, m, solucion_final);

				// Si estamos en el ultimo nivel(nodo hoja)
				if (nivel == (n_invitados - 1)) { 
                    // Se ha indica que se ha llegado al final de la primera rama
					completo = true;
					// Si la conveniencia es mejor que la maxima actual se actualiza la solucion final y la cota
					if (conveniencia_actual >= conveniencia_max) {
						nivel++;
						for(int d = 0 ; d < cotaNivel.size() ; d++) cotaNivel[d] = cotaTemp[d];
						for(int i = 0; i < n_invitados; i++) solucion_final[i] = solucion_actual[i];
						conveniencia_max = conveniencia_actual;
					}
				}
			}
			else poda = false;
			// Levantamos al invitado
			sentados[n_invitado] = false;
		}
	}
}

int main(int argc, char const *argv[]){

	if(argc < 2){
		cerr << "Número de argumentos inválido. Pruebe con ./programa <número_invitados>" << endl;
		exit(1);
	}

	int n = atoi(argv[1]);
    int conveniencia_actual = 0;
    int solucion[n], solucion_final[n];
    vector<bool> sentados(n, false);

    // Generamos la matriz simetrica de invitados aleatoriamente
	int **m = rellenarMatriz(n);



    //cout << "La matriz generada es : " << endl;
    //imprimirMatriz(m, n);

    tantes = high_resolution_clock::now();
    algoritmo_backtracking(n, 1, 0, conveniencia_actual, solucion, sentados, m, solucion_final);
	tdespues = high_resolution_clock::now();

    //cout << "La solucion final es : " << endl;
    //imprimirSolucion(solucion_final,n);

    transcurrido = duration_cast<duration<double>>(tdespues - tantes);
	cout <<  n << " " << transcurrido.count() << endl;

	return 0;
}