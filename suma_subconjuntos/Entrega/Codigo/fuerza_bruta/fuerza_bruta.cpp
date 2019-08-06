#include <bits/stdc++.h>
#include <vector>
#include <iostream>
#include <map>
#include <stdlib.h>
#include <time.h>
#include <cmath>

using namespace std;

map<int, vector<int>> allPossibleSubset(vector<int> arr,int n)
{
    map<int, vector<int>> result;
    vector<int> v;
    int k = 0;
	double count = pow(2,n);

	for (int i = 0; i < count; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if ((i & (1 << j)) > 0){
                v.push_back(arr[j]);
            }
		}
		result.insert(pair<int,vector<int>>(k,v));
        v.clear();
        k++;
	}

    return result;
}

int main(int argc, char* argv[])
{
    if(argc != 2){
        cout << "Faltan parametros" << endl;
        return -1;
    }

	int n = atoi(argv[1]);
	vector<int> arr;

	for(int i=1;i<=n;i++){
        arr.push_back(i);
    }
		
	map<int, vector<int>> result = allPossibleSubset(arr,n);

    vector<int> aux;
    int ale = rand()%(n);
    cout << "El tamaño es " << n << " y la suma a buscar es: " << ale << endl;
    cout << "Los subconjuntos solucion (si existen) son: " << endl;

    for( const auto& pair : result )
    { 
        int suma = 0;
        for( size_t i = 0 ; i < pair.second.size() ; ++i ){
            suma += pair.second[i];
            aux.push_back(pair.second[i]);
        }   
        if(suma == ale){
            for(int l = 0; l < aux.size(); l++)
            {
                cout << aux[l] << " ";
            }
            cout << endl;  
            aux.clear();  
        }else{
            aux.clear();
        }
    }

	return 0;
}