#include <iostream>
#include <map>
#include <list>
using namespace std;

/*
InverseMaps. Dos correspondenciasM1yM2son inversas una de la otra si 
tienen el mismo n ́umerode asignaciones y para cada par de 
asignaci ́onx->yenM1existe el pary->xenM2. Escribir unpredicadobool 
areinverse(map<int,int> &M1, map<int,int> &M2); que determina si 
lascorrespondenciasM1yM2son inversas.
*/

bool areinverse(map<int,int> &M1, map<int,int> &M2);


int main(){


    return 0;
}

bool areinverse(map<int,int> &M1, map<int,int> &M2){
    if(M1.size() != M2.size()){
        return false;
    }
    auto it1 = M1.begin(); auto it2 = M2.begin();
    while (it1 != M1.end())
    {
        if (it1->first != it2->second || it1->second != it2->first)
        {
            return false;
        }
        it1++; it2++;
    }
    return true;
}