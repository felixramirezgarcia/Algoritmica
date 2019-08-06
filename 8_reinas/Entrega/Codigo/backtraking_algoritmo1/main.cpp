#include<bits/stdc++.h> 
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
#define N (30)

using namespace std;
using namespace std::chrono;

high_resolution_clock::time_point tantes, tdespues;
duration<double> transcurrido;

void pintarSolucion(int tablero[N][N]) 
{ 
    static int k = 1; 
    printf("%d-\n",k++); 
    for (int i = 0; i < N; i++) 
    { 
        for (int j = 0; j < N; j++) 
            printf(" %d ", tablero[i][j]); 
        printf("\n"); 
    } 
    printf("\n"); 
} 
  
bool comprobar(int tablero[N][N], int fila, int col) 
{ 
    int i, j; 
  
    /* Comprobar esta fila a la izquierda */
    for (i = 0; i < col; i++) 
        if (tablero[fila][i]) 
            return false; 
  
    /* Comprobar la diagonal superior en el lado izquierdo */
    for (i=fila, j=col; i>=0 && j>=0; i--, j--) 
        if (tablero[i][j]) 
            return false; 
  
    /* Comprobar la diagonal inferior del lado izquierdo */
    for (i=fila, j=col; j>=0 && i<N; i++, j--) 
        if (tablero[i][j]) 
            return false; 
  
    return true; 
} 
  
bool solveNQUtil(int tablero[N][N], int col , int n) 
{ 
    /* caso base: Si todas las reinas están colocadas devuelve verdadero */
    if (col == n) 
    { 
        //pintarSolucion(tablero); 
        return true; 
    } 
  
    /* Considere esta columna e intente colocar 
    esta reina en todas las filas una por una  */
    bool res = false; 
    for (int i = 0; i < n; i++) 
    { 
        /* Comprueba si la reina puede ser colocada en 
        tablero[i][col] */
        if ( comprobar(tablero, i, col) ) 
        { 
            /* Coloca la reina en tablero[i][col] */
            tablero[i][col] = 1; 
            /* Aplicamos recursividad */
            res = solveNQUtil(tablero, col + 1, n) || res; 
  
            /* Si colocar a la reina en el tablero[i][col] 
            no conduce a una solución, entonces 
            quita reina del tablero[i][col]  */
            tablero[i][col] = 0;
        } 
    } 

    return res; 
} 
  
void solveNQ(int n) 
{ 
    int tablero[N][N]; 
    memset(tablero, 0, sizeof(tablero)); 
  
    if (solveNQUtil(tablero, 0, n) == false) 
    { 
        printf("No existe solucion"); 
        return ; 
    } 
  
    return ; 
} 
  
int main(int argc, char *argv[]) 
{ 
    if(argc < 2){
		cerr << "Número de argumentos inválido. Pruebe con ./programa <número_comensales>" << endl;
		exit(1);
	}

    int n = atoi(argv[1]) ;

    if(n>N){
        n=N;
    }

    tantes = high_resolution_clock::now();
	solveNQ(n); 
	tdespues = high_resolution_clock::now();

    transcurrido = duration_cast<duration<double>>(tdespues - tantes);
	cout <<  n << " " << transcurrido.count() << endl;

    
    return 0; 
} 