#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

class Item {

    private:
        int valor;
        int peso;

    public:
        Item(int valor, int peso) { //constructor
           this->valor = valor;
           this->peso = peso;
        }

        void mostrar() {
            cout << "Valor " << this->valor << " peso: "<< this->peso << endl;
        }

};