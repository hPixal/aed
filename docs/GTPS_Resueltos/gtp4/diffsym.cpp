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
    bool isRepeated(list< set<T> > &L , T eval){
        auto itl = L.begin(); 
        int count = 0;
        while (itl != L.end())
        {
            auto itc = itl->begin();
            while (itc!=itl->end())
            {
                if(*itc == eval) count++;
                if(count == 2) return true;
                itc++;
            }
            itl++;
        }
        return false;
    }

template<typename T>
    void diffsym(list< set<T> > &L, set<T> &ad){
        auto itl = L.begin();
        while (itl != L.end())
        {
            auto itc  = itl->begin();
            while (itc!=itl->end())
            {
                if(!isRepeated(L,*itc)) ad.insert(*itc);
                itc++;
            }
            itl++;
        }
    }

int main(){
    set<int> a; set<int> b; set<int> c;
    for (size_t i = 0; i < 10; i++)
    {
        a.insert(i*10);
        b.insert(i*10);
    }

    list<set<int>> vec;
    vec.push_back(a);
    vec.push_back(b);

    diffsym(vec,c);

    for(auto x : c){
        cout << x << endl;
    }

    return 0;