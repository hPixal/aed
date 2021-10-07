#include <iostream>
#include <map>
#include <list>
#include <vector>
using namespace std;

/*
Aplica. Escribir una funci ́on
void apply_map(list<int> &L, map<int,int> &M,list<int> &ML) que, dada una 
listaLy una correspondenciaMretorna porMLuna lista con losresultados de 
aplicarMa los elementos deL. Si alg ́un elemento deLno est ́a en el dominio de
 M,entonces el elemento correspondiente de ML no es incluido. 
 Por ejemplo, siL = (1,2,3,4,5,6,7,1,2,3) y 
 M = {(1,2),(2,3),(3,4),(4,5),(7,8)}, entonces, despu ́es dehacer
 apply_map(L,M,ML), debe quedarML = {(2,3,4,5,8,2,3,4)}.
*/

void apply_map(list<int> &L, map<int,int> &M,list<int> &ML);

const bool isIn(int chk, map<int,int> &look){
    auto it = look.begin();
    while (it != look.end())
    {
        if (it->first == chk)
        {
            return true;
        }
    }
    return false;
}

int main(){
    map<int, int> test;

    cout << test[1]  << " " << endl;

    return 0;
}

void apply_map(list<int> &L, map<int,int> &M,list<int> &ML){
    ML.clear(); auto it = L.begin();

    while (it != L.end())
    {
        if (isIn(*it,M))
        {
            ML.push_back(M[*it]); 
        }
        ++it;
    }
    
}

