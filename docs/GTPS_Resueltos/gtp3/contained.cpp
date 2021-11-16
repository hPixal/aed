#include <iostream>
#include <version>
#include <vector>
#include <map>
#include <list>
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

template<typename T>
    void contained(btree<T> &A, btree<T> &B, bool &cond,
    typename btree<T>::iterator a1,typename btree<T>::iterator b1){
        if(a1 == A.end()){ cond = true; return; }
        if(*a1 != *b1){ cond = false; return; }
        contained(A,B,cond,a1.right(),b1.right());
        contained(A,B,cond,a1.left(),b1.left());
    }


template<typename T>
    bool contained(btree<T> &A, btree<T> &B){
        if(A.begin() == A.end() ) return (B.begin() == B.end());

        bool exit = false;
        contained(A,B,exit,A.begin(),B.begin());

        return exit;
    }

////////////////////////////////////////////////////////////////////////////
/*Extra: crear un arbol binario */
////////////////////////////////////////////////////////////////////////////

void create_btree(btree<int> &tr,btree<int>::iterator it,int level,int count){
    if(count > level) return;
    it = tr.insert(it,count/*int(rand()%40)*/);

    btree<int>::iterator nextr = it.right();
    btree<int>::iterator nextl = it.left();

    create_btree(tr,nextr,level,count+1);
    create_btree(tr,nextl,level,count+1);
}

void create_btree(btree<int> &tr,int level){
    tr.clear();
    create_btree(tr,tr.begin(),level,0);
}

int main(){
    btree<int> tr; btree<int> tr2;
    create_btree(tr,3); create_btree(tr2,4);

    if(contained(tr,tr2)) cout << "funciona" << endl;
    return 0;
}
