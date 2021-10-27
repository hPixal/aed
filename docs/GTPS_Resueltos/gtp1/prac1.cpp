#include <iostream>
#include <list>
using namespace std;

/*
BasicSort. Escribir una función void basic_sort(list<int> &L), que ordena los elementos de L
de menor a mayor. Para ello emplear el siguiente algoritmo simple: utilizando una lista auxiliar L2,
tomar el menor elemento de L, eliminarlo de L e insertarlo al final de L2 hasta que L este vacı́a.
Luego insertar los elementos de L2 en L. Complexity O(2n)
*/

void fillvec(list<int> &au,list<int> &l){
    //Prerequisites
    list<int>::iterator it = l.begin();
    int aux = *l.begin();
    auto auxit= l.begin();

    //Find minor    
    while (it != l.end())
    {
        if (aux > *it)
        {
            aux = *it;
            auxit = it;
        }
        ++it;
    }

    //Push old minor to au and delete it from l
    au.push_back(aux);
    l.erase(auxit);

    //Recursive block
    if (l.size() == 0)
    { return; } else
    { fillvec(au,l); }
    
}

void basort(list<int> &l){
    list<int> auxlist;
    fillvec(auxlist,l);
    l.swap(auxlist);
}


void show(list<int> const &l){
    cout << "[ ";
    for(auto it = l.begin(); it != l.end(); it++)
    {
        cout << " " << *it << " ";
    }
    cout << " ]" << endl;
    
    
}

int main(){
    list<int> myTest = {5,2,4,3,1,3,6,8};
    basort(myTest);
    show(myTest);
    return 0;
}
