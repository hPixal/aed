#include <iostream>
#include <list>
using namespace std;

/*
SelectionSort. Escribir una función void selection_sort(list<int> &L), que ordena los
elementos de L de menor a mayor. Para ello debe tomarse el menor elemento de L e intercambiarlo
(swap) con el primer elemento de la lista. Luego intercambiar el menor elemento de la lista
restante, con el segundo elemento, y ası́ sucesivamente. Esta función debe ser IN PLACE.
*/

auto getMinor(list<int>::iterator beg,list<int>::iterator &end){
    auto aux = *beg;
    auto auxit = beg;

    for (auto it = beg; it != end; ++it){
        if (aux > *it)
        {   aux = *it;
            auxit = it; }
    }

    return auxit;
}

void BubbleSort(list<int> &l){
    for(auto it = l.begin(); it != l.end(); ++it){
        int aux1; int aux2; auto itend = l.end();
        auto auxit = getMinor(it,itend);

        aux1 = *it;
        aux2 = *auxit;

        *it = aux2;
        *auxit = aux1;
    }
}

void show(list<int> const &l){
    cout << "[ ";
    for(auto it = l.begin(); it != l.end(); it++)
    { cout << " " << *it << " "; }
    cout << " ]" << endl;
}


int main(){
    list<int> myTest = {5,2,4,3,1,3,6,8};
    BubbleSort(myTest);
    show(myTest);
    return 0;
}