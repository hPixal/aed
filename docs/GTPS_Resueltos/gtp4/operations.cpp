#include <iostream>
#include <version>
#include <vector>
#include <map>
#include <list>
#include <set>
#include "btree.hpp"
using namespace aed;
using namespace std;
//#include "tree.hpp"
//#include "util_tree.hpp"
//#include "str_convs.hpp"

//typedef btree<int>::iterator bnode;

/*
    Este archivo es solo de ejemplo. Usalo para resolver los ejercicios, ya que este
    en esta carpeta especifica y con este nombre especifico, es el unico con el que 
    funciona la utilería de la catedra. Se puede usar como plantilla para luego cam
    biarle el nombre a uno más apropiado y entregarlo como resolción.
*/
template<typename T>
    void set_union(set<T> &A,set<T> &B,set<T> &C){
        C.insert(B.begin(),B.end());
        C.insert(A.begin(),A.end());
    
    }

template<typename T>
    void set_intersection(set<T> &A,set<T> &B,set<T> &C){
        auto it = A.begin();
        
        while (it != A.end())
        {

            if (B.find(*it) != B.end())
            {
                C.insert(*it);   
            }
            it++;
        }
        
    }

template<typename T>
    void set_difference(set<T> &A,set<T> &B,set<T> &C){
        auto it = A.begin();
        
        while (it != A.end())
        {

            if (B.find(*it) == B.end())
            {
                C.insert(*it);   
            }
            it++;
        }
    }

int main(){
    set<int> a; set<int> b; set<int> c;
    for (size_t i = 0; i < 10; i++)
    {
        a.insert(i*10);
        b.insert(i*2);
    }
    set_difference(a,b,c);
    
    for(auto x : c){
        cout << x << endl;
    }

    return 0;