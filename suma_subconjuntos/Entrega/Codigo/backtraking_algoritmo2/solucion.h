#include <iostream>
#include <vector>
#include <cstdlib>

//estados 2(nulo),1,0,-1(end)
using namespace std;

class solucion {
private:
    vector<int> x;
    vector<int> orig;
    int m,s,r;
    //m es la suma
    //s es la suma de lo que llevamos
    //r es la suma de los que nos qeda.
public:
    solucion(int tama, int suma) { //constructor
        s=r=0;
        m=suma;
        for(int i=1; i<=tama; i++) {
            orig.push_back(i);
            x.push_back(2);//2=NULO
            r+=i;
        }
    }
    void mostrar() {
        cout<<"tamaño es "<<size()<<" la suma es: "<<m<<" s="<<s<<" r="<<r<<endl;
    }
    int size() const {
        x.size();
    }
    void iniciacomp(int k) {
        x[k]=2;//2=NULO
    }
    void sigvalcomp(int k) {
        x[k]--;
        if(x[k]==1) {//si lo cogemos el valor en k, se lo sumamos a s y se lo restamos a r.
            s+=orig[k];
            r-=orig[k];
        }
        if(x[k]==0) {//si no cogemos le valor en k, se lo restamos a s, ( ya que lo habiamos introducido antes en la x[k]==1).
            //No es necesario sumarselo a r ya que no esta en los aun no seleccioandos.
            s-=orig[k];
        }
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
        return (((s+x[k]<=m) and (s+r>=m)) or (s==m));
    }
    void VueltaAtras(int k) {
        if(k!=size()) {//si k==size() ya no vamos a calcular k+1
            r+=orig[k];//mantiene el en r el siguiente valor ya que en el back_recursivo(k+1) se ha restado
            x[k] = 2;//y pone k a nulo ya que en le back_recursivo(k+1) se ha modificado.
        }
    }

};