using namespace std;
#include "solucion.h"

void back_recursivo(solucion &sol,int k) {
    if(k==sol.size())   sol.procesasolucion();
    else {
        sol.iniciacomp(k);
        sol.sigvalcomp(k);
        while(!sol.todosgenerados(k)) {
            if(sol.factible(k)) {
                back_recursivo(sol,k+1);
                sol.VueltaAtras(k+1);//para que en las siguientes iteraciones no se tnega en cuenta k+1
            }
            sol.sigvalcomp(k);
        }
    }
}

int main(int argc, char *argv[]) {

    if(argc != 2){
        cout << "Faltan parametros" << endl;
        return -1;
    }

    int n = atoi(argv[1]);
    int suma = rand()%(n);
    solucion s(n,suma);
    int aux=0;
    s.mostrar();
    back_recursivo(s,aux);
    return 0;
}