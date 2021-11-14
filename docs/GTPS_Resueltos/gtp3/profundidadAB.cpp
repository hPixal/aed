#include <iostream>
#include <version>
#include <vector>
#include <map>
#include <list>
#include "btree.hpp"
//#include "str_convs.hpp"
//#include "util_tree.hpp"
using namespace aed;
using namespace std;

typedef btree<int>::iterator bnode;

/*
    Este archivo es solo de ejemplo. Usalo para resolver los ejercicios, ya que este
    en esta carpeta especifica y con este nombre especifico, es el unico con el que 
    funciona la utilería de la catedra. Se puede usar como plantilla para luego cam
    biarle el nombre a uno más apropiado y entregarlo como resolción.
*/

////////////////////////////////////////////////////////////////////////////

template <typename T>
    void cant_nodos_prof(const btree<T> &A,const int &prof, int &count,
                         typename btree<T>::iterator pos,int current_level){
        if(pos == A.end()) return;

        if(current_level+1 == prof){
            if( pos.right() != A.end() ) count++;
            if( pos.left() != A.end() ) count++;
            return;
        }

        cant_nodos_prof(A,prof,count,pos.right(),current_level+1);
        cant_nodos_prof(A,prof,count,pos.left(),current_level+1);
    }   

template <typename T>
    int cant_nodos_prof(const btree<T> &A, const int &prof){
        auto begin = A.begin(); int count = 0;
        cant_nodos_prof(A,prof,count,begin,0);
        return count;
    }

////////////////////////////////////////////////////////////////////////////
/*Extra: crear un arbol binario */
////////////////////////////////////////////////////////////////////////////

void create_btree(btree<int> &tr,bnode it,int level,int count){
    if(count > level) return;
    it = tr.insert(it,count/*int(rand()%40)*/);

    bnode nextr = it.right();
    bnode nextl = it.left();

    create_btree(tr,nextr,level,count+1);
    create_btree(tr,nextl,level,count+1);
}

void create_btree(btree<int> &tr,int level){
    tr.clear();
    create_btree(tr,tr.begin(),level,0);
}

int main(){
    btree<int> tr;
    create_btree(tr,4);

    cout << " The amount of nodes in the given level is: "
         << cant_nodos_prof(tr,3) << endl;
    return 0;
}