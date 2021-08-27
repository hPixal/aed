#include <iostream>
#include <list>
#include <vector>
using namespace std;

/*
Ascendente2. Escribir una funci´on void ascendente2(list<int> &L, vector<list<int>> &VL)
que, dada una lista L, genera un vector de listas VL de tal forma de que cada sublista es ascendente
*/

auto getMax(list<int>::iterator beg,list<int>::iterator &end){
    auto aux = *beg;
    auto auxit = beg;

    for (auto it = beg; it != end; ++it){
        if (aux < *it)
        {   aux = *it;
            auxit = it; }
    }

    return auxit;
}

void BubbleSort(list<int> &l){
    for(auto it = l.begin(); it != l.end(); ++it){
        int aux1; int aux2; auto itend = l.end();
        auto auxit = getMax(it,itend);

        aux1 = *it;
        aux2 = *auxit;

        *it = aux2;
        *auxit = aux1;
    }
}

void ascendente2(list<int> &l, vector<list<int>> &vl){
    l.clear();
    for(auto it = vl.begin(); it != vl.end() ; ++it){
        l.merge(*it);
    }
    BubbleSort(l);
}

void show(const list<int> &s){

    cout << "[ ";
    for( auto it  = s.begin() ; it != s.end() ; ++it){
        cout << " " << *it << " ";
    }
    cout << " ]";
}


int main(){
    vector<list<int>> vl;
    list<int> l1 = {9, 5, 3, 1};
    list<int> l2 = {6, 8, 10, 4};
    vl.push_back(l1);
    vl.push_back(l2);

    list<int> salida;

    ascendente2(salida,vl);
    show(salida);
    
    return 0;
}