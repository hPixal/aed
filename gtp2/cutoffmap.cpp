#include <iostream>
#include <map>
#include <list>
#include <vector>
using namespace std;

/*
cutoffmap. Implemente una funci ́on
void cutoffmap(map<int, list<int>> &M, int p, int q)que elimina todas las 
claves que NO est ́an en el rango[p,q). En las asignaciones que 
quedantambi ́en debe eliminar los elementos de la lista que no est ́an en el 
rango. Si la lista queda vac ́ıaentonces la asignaci ́on debe ser eliminada. 
Por ejemplo: siM = {1->(2,3,4), 5->(6,7,8),8->(4,5), 3->(1,3,7)}, entonces
cutoffmap(M,1,6)debe dejarM={1->(2,3,4), 3->(1,3)}.
Notar que la clave5ha sido eliminada si bien est ́a dentro del rango 
porque su lista quedar ́ıa vac ́ıa.Restricciones: el programa no debe usar 
contenedores auxiliares.
*/

void cutoffmap(map<int, /*list<int>*/ int > &M, int p, int q){
    /* vector<map<int,int>::iterator> del;
    for(auto it = M.begin() ; it != M.end() ; it++){
        if (it->first < p or it->first > q)
            del.push_back(it);
    }

    for(auto x : del){
        M.erase(x);
    } */
    
   auto it = M.begin();
   while( it != M.end()){
        if (it->first < p or it->first > q)
           { auto del = it; ++it; M.erase(del); } 
        else 
           { ++it; }
    }
    
}

int main( ){
    map<int, int> test;
    test[0] = 60;
    test[1] = 10;
    test[2] = 20;
    test[3] = 30;
    test[5] = 50;
    test[4] = 40;

    cutoffmap(test, 1, 4);

    auto it = test.begin();
    while (it != test.end())
    {
        cout << it->first << " " <<  it->second << endl;
        ++it;
    }
    
    
    return 0;
}