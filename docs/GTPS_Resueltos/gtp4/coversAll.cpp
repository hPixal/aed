#include <iostream>
#include <version>
#include <vector>
#include <map>
#include <list>
#include <set>
//#include "tree.hpp"
#include "btree.hpp"
//#include "util_tree.hpp"
//#include "str_convs.hpp"
using namespace aed;
using namespace std;

//typedef btree<int>::iterator bnode;

/*
    Este archivo es solo de ejemplo. Usalo para resolver los ejercicios, ya que este
    en esta carpeta especifica y con este nombre especifico, es el unico con el que 
    funciona la utilería de la catedra. Se puede usar como plantilla para luego cam
    biarle el nombre a uno más apropiado y entregarlo como resolción.
*/

////////////////////////////////////////////////////////////////////////////


template<typename T>
    bool coversAll(vector<set<T>>&v, set<T>& W){
        
        auto it = v.begin(); set<T> tmp;
        while (it != v.end())
        {
            auto aux = *it->begin();
            while (aux != *it->end())
            {
                if(tmp.find(*aux) == tmp.end()) tmp.insert(*aux);
                aux++;
            }
            it++;
        }

        if(tmp.size()!=W.size()) return false;
        
        auto chk = tmp.begin();
        while(chk != tmp.end()){
            if(W.find(*chk) == W.end()) return false;
            chk++;
        }

        return true;
    }

////////////////////////////////////////////////////////////////////////////
/*Extra: crear un arbol binario */
////////////////////////////////////////////////////////////////////////////

int main(){


    // if(balanced(tr)) cout << "funciona" << endl;
    return 0;
}
