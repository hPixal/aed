#include <iostream>
#include <version>
#include <vector>
#include <map>
#include <list>
#include "tree.hpp"
#include "btree.hpp"
#include "util_tree.hpp"
//#include "str_convs.hpp"
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

template<typename T>
    void bin2ord(btree<T> &bin, tree<T> &ord, T lambda,
    typename btree<T>::iterator itB, typename tree<T>::iterator itO){
        if(itB == bin.end()) return;
        
        *itO = *itB;

        typename tree<T>::iterator oLeft,oRight;
        if(itB.right() != bin.end() || itB.left() != bin.end()){
            oLeft = itO.lchild();
            oLeft = ord.insert(oLeft,lambda);
            oRight = oLeft; oRight++;
            oRight = ord.insert(oRight,lambda);
        }

        bin2ord(bin,ord,itB.left(),oLeft);
        bin2ord(bin,ord,itB.right(),oRight);
    }

////////////////////////////////////////////////////////////////////////////

template<typename T>
    void bin2ord(btree<T> &bin, tree<T> &ord, T lambda){
        if(bin.end() == bin.begin()) return;
        ord.clear();

        ord.insert(ord.begin(),lambda);
        bin2ord(bin,ord,lambda,bin.begin(),ord.begin());
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
    btree<int> tr; tree<int> ordTree;
    create_btree(tr,4);
    bin2ord(tr,ordTree,-1);
    print_tree(ordTree);
    return 0;
}