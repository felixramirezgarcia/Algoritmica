#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

class solucion {    //estado 2(nulo),1,0,-1(fin)

    private:
        vector<int> x;
        vector<int> orig;
        int m;//suma

    public:
        solucion(int tama, int suma) { //constructor
            m=suma;
            for(int i=1; i<=tama; i++) {
                orig.push_back(i);
                x.push_back(2);//2=NULO
            }
        }

        void mostrar() {
            cout << "tamaño es " << orig.size() << " y la suma a buscar es: "<< m << endl;
        }

        int size() const {
            x.size();
        }

        void iniciacomp(int k) {
            x[k]=2;//2=NULO
        }

        void sigvalcomp(int k) {
            x[k]--;
        }

        bool todosgenerados(int k) {
            return x[k]==-1;//devuelve true si estamos ya en el ultimo.
        }

        int decision(int k) {
            return x[k];
        }

        void procesasolucion() {
            for(int i=0; i<size(); i++) {
                if(x[i]==1) { //elemento selecionado
                    //cout<<orig[i]<<"  ";
                }
            }
            //cout<<endl;
        }

        bool factible(int k) {
            int s=0,r=0,aux=0;
            for(int i=0; i<=k; i++) {
                if(x[i]==1) { //elemento selecionado
                    s+=orig[i];
                }
            }
            for(int i=k+1; i<orig.size(); i++) {
                r+=orig[i];
            }
            if(k+1<orig.size()) aux=orig[k+1];
            return (((s+r>=m) and s+aux<=m) or (s==m));
        }

};