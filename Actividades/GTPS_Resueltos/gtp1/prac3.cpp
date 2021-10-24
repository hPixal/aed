#include <iostream>
#include <list>
using namespace std;

/*
Concatena. Escriba procedimientos para concatenar: a) dos listas L1 y L2 usando insert; b) una
lista LL de n sublistas usando insert; c) una lista LL de n sublistas usando splice. Cada
procedimiento debe retornar el resultado en una lista nueva.
*/

template<typename T> 
    list<T> listconcat(list<T> l1,list<T> &l2){
        list<T> newl; newl.swap(l1);
        for(auto it = l2.begin() ; it != l2.end();++it){
            newl.push_back(*it);
        }
        return newl;
    }

template<typename T>
    void inserconcat(list<T> &l1, list<T> &l2){
        l1.insert(l1.end(),l2.begin(),l2.end());
    }

void show(list<int> const &l){
    cout << "[ ";
    for(auto it = l.begin(); it != l.end(); it++)
    { cout << " " << *it << " "; }
    cout << " ]" << endl;
}

int main(){
    list<int> t1 = { 1, 2, 3 };
    list<int> t2 = { 4 ,5 ,6 };

    auto t3 = listconcat(t1,t2);
    show(t3);

    //show(t1);
    //cout << "aaaaaaaa" ;
    inserconcat(t1,t2);
    show(t1);

    return 0;
}
