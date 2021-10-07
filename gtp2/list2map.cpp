#include <map>
#include <list>
#include <iostream>
using namespace std;

/*
list2map. Escribir una funci ́on que dadas las listas de 
claves(k1,k2,k3, ...)y valores(v1,v2,v3, ...)retorna el mapMcon las 
asignaciones correspondientes{ k1->v1, k2->v2, k3->v3, ...}. Utilice 
la signaturavoid list2map(map<int,int> &M,list<int> &Keys, list<int> &Vals). 
Nota: si hay claves repetidas, s ́olo debe quedar laasignaci ́on 
correspondiente a la  ́ultima clave en la lista. Si hay menos valores que 
claves utilizarcero como valor. Si hay m ́as valores que claves, ignorarlos.
*/

void list2map(map<int,int> &M,list<int> &Keys, list<int> &Vals);

int main(){

    return 0;
}

void list2map(map<int,int> &M,list<int> &Keys, list<int> &Vals){
    M.clear();
    
    if (Keys.size() == Vals.size())
    {
        auto itk = Keys.begin();
        auto itv = Vals.begin();

        while (itk != Keys.end())
        {
            M[*itk] = *itv;
            ++itk; ++itv;
        }
    }
}