#include <iostream>
#include <list>
#include <algorithm>
using namespace std;
/*
Ascendente1. Escribir una funci´on void ascendente1(list<int> &L, list<list<int>> &LL)
que, dada una lista L, genera una lista de listas LL de tal forma de que cada sublista es ascendente
*/
void ascendente1(list<int> &l, list<list<int>> &ll){
    auto it = ll.begin();
    sort(l.begin(),l.end());
    ll.push_back(l);
    advance(it,ll.size()-1);
}


int main(){

    return 0;
}