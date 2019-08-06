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
#define MAX_N (30)

using namespace std;
using namespace std::chrono;

high_resolution_clock::time_point tantes, tdespues;
duration<double> transcurrido;

int tablero[MAX_N] ;
int total = 0 ;

void imprimirTablero(int tablero[MAX_N], int n)
{
    int i, j ;
    printf("+") ;
    for (i=0; i<n; i++) {
        printf("-") ;
        if (i < n-1)
            printf("+") ;
    }
    printf("+\n") ;
    for (i=0; i<n; i++) {
        printf("|") ;
        for (j=0; j<n; j++) {
            if (j == tablero[i])
                printf("O") ;
            else
                printf(" ") ;
            if (j < n-1)
                printf("|") ;
        }
        printf("┃\n") ;
        if (i < n-1) {
            printf("+") ;
            for (j=0; j<n; j++) {
                printf("-") ;   
                if (j < n-1) 
                    printf("+") ;       
            }
            printf("+\n") ;
        }
    }
    printf("+") ;
    for (i=0; i<n; i++) {
        printf("-") ;
        if (i < n-1)
            printf("+") ;
    }
    printf("+\n\n") ;
}

#define abs(n) ((n)<(0)?(-(n)):(n))

void comprobar(int tablero[MAX_N], int n)
{
    int col[MAX_N] ;
    int i, j ;
    for (i=n-1; i>=0; i--) {
        col[i] = tablero[i] ;
        for (j=i+1; j<n; j++) {
            if (col[i] <= col[j]) 
                col[j]++ ;
        }
    }

    for (i=0; i<n; i++)
        for (j=i+1; j<n; j++)
            if (abs(col[i]-col[j]) == abs(j-i))
                return ;

    total++ ;
    //imprimirTablero(col, n) ;
}

void lugar(int i, int n)
{
    if (i == n) {
        comprobar(tablero, n) ;
    } else {
        int which ;
        for (which=0; which < n-i; which++) {
            tablero[i] = which ;
            lugar(i+1, n) ;
        }
    }
}

int main(int argc, char *argv[])
{

    if(argc < 2){
		cerr << "Número de argumentos inválido. Pruebe con ./programa <número_comensales>" << endl;
		exit(1);
	}

    int n = atoi(argv[1]) ;

    tantes = high_resolution_clock::now();
	lugar(0, n) ;
	tdespues = high_resolution_clock::now();

    if (total == 0)
        fprintf(stderr, "No hay soluciones para un tablero de %dx%d ..\n", n, n) ;
    else
        fprintf(stderr, "Hay %d soluciones%s para el tablero de %dx%d\n", 
                total, total > 1 ? "s" : "", n, n) ;

    transcurrido = duration_cast<duration<double>>(tdespues - tantes);
	cout <<  n << " " << transcurrido.count() << endl;

    return 0 ;
}