#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <vector>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <climits>
#include <cassert>
#include <string>
#include <fstream>
#include <chrono>
#include "item.h"
#define MAX_PESO (10)

using namespace std;
using namespace std::chrono;

high_resolution_clock::time_point tantes, tdespues;
duration<double> transcurrido;




int main(int argc, char *argv[])
{

    if(argc < 2){
		cerr << "Número de argumentos inválido. Pruebe con ./programa <tamanio>" << endl;
		exit(1);
	}

    int n = atoi(argv[1]) ;
    vector<int> items;

    //Inicializar los items con el mismo valor y peso
    for (int i = 1; i <= n ; i++)
    {
        Item it (i,i);
    }
    

    tantes = high_resolution_clock::now();
	
	tdespues = high_resolution_clock::now();

   
    transcurrido = duration_cast<duration<double>>(tdespues - tantes);
	cout <<  n << " " << transcurrido.count() << endl;

    return 0 ;
}