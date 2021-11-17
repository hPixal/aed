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
    set<T> set_intersection(set<T> &A,set<T> &B){
        set<T> C;
        auto it = A.begin();

        while (it != A.end())
        {

            if (B.find(*it) != B.end())
            {
                C.insert(*it);   
            }
            it++;
        }
        return C;
    }

template<typename T>
    bool disjuntos(vector<set<T>>&v){
        auto itv = v.begin();
        auto itv2 = v.begin();
        
        advance(itv,2);
        while (itv2 != v.end())
        {   
            if(set_intersection(*itv,*itv2).size() != 0){
                return false;
            }
            itv++; itv2++;
        }
        
        return true;
    }

int main(){
    set<int> a; set<int> b; set<int> c;
    for (size_t i = 0; i < 10; i++)
    {
        a.insert(i*10);
        b.insert(i*2);
    }

    vector<set<int>> vec;
    vec.push_back(a);
    vec.push_back(c);
    vec.push_back(b);

    if(!disjuntos(vec)){
        cout << "no son disjuntos ñeri " << endl;
    }
    return 0;
}