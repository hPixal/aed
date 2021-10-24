#include <iostream>
#include <map>
#include <list>
using namespace std;

/*
mergeMap. Dadas dos correspondenciasAyB, que asocian enteros con listas 
ordenadas de enteros,escribir una funci ́on
void merge_map(map<int, list<int>> &A, map<int, list<int>> &B,map<int, list<int>> &C)
que devuelve enCuna correspondencia que asigna al elementoxlafusi ́on 
ordenada de las dos listasA[x]yB[x]. Sixno es clave deA, entoncesC[x]debe 
serB[x]yviceversa. Sugerencia: utilice la funci ́onmergeimplementada en uno 
de los ejercicios anteriores
*/

void merge_map(map<int, list<int>> &A, map<int, list<int>> &B,map<int, list<int>> &C);

void merge(list<int> &L1, list<int> &L2, list<int>& L);

int main(){

    return 0;
}

void merge(list<int> &L1, list<int> &L2, list<int>& L){
    L.insert(L.end(),L1.begin(),L1.end());
    L.insert(L.end(),L2.begin(),L2.end());
    L.sort();
}

void merge_map(map<int, list<int>> &A, map<int, list<int>> &B,map<int, list<int>> &C){
    auto it1 = A.begin();
    while (it1 != A.end())
    {
        list<int> insert;
        merge(it1->second,B[it1->first],insert);
        C[it1->first] = insert;
        it1++; 
    }
}