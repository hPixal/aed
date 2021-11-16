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

////////////////////////////////////////////////////////////////////////////

    void countHeight(const btree<int>::iterator &end, btree<int>::iterator node,int &count){
        if(node == end) return;
        count++;
        countHeight(end,node.right(),count);
        countHeight(end,node.left(),count);        
    }

////////////////////////////////////////////////////////////////////////////

    int countHeight(const btree<int>::iterator &end, btree<int>::iterator node){
        if(node == end) return 0;
        int rtrn = 0;
        countHeight(end,node,rtrn);
        return rtrn;
    }

////////////////////////////////////////////////////////////////////////////


    bool balanced(btree<int> &A){
        int right = 0; int left = 0;

        right = countHeight(A.end(),A.begin().right());
        left = countHeight(A.end(),A.begin().left());

        return (right == left || right == left-1 || right == left+1 );
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


    if(balanced(tr)) cout << "funciona" << endl;
    return 0;
}
