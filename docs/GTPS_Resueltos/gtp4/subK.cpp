#include <iostream>
#include <version>
#include <vector>
#include <map>
#include <list>
#include <set>
//#include "tree.hpp"
#include "btree.hpp"
//#include "util_btree.hpp"
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

list<set<int>> subk(set<int> &S, int k){
    list<set<int>> rtrn;
    
    auto it = S.begin();
    set<int> aux;
    while (it != S.end())
    {
        for (int i = 0; i < k; i++)
        {
            if(it == S.end()){
                for(auto x : aux){
                    rtrn.begin()->insert(x); 
                }
                return rtrn;
            }

            aux.insert(*it);
            it++;
        }
        rtrn.push_back(aux);
        aux.clear();
    }
    return rtrn;
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

////////////////////////////////////////////////////////////////////////////
/*Extra: crear un set aleatorio */
////////////////////////////////////////////////////////////////////////////

set<int> create_set(int elem){
    set<int> rtrn;
    while ( int(rtrn.size()) != elem)
    {
        int aux = rand() % (elem+100);
        if (rtrn.find(aux) == rtrn.end())
        {
            rtrn.insert(aux);
        }
    }
    return rtrn;
}

int main(){
    btree<int> example;
    create_btree(example,2);

    set<int> test = create_set(10);
    
    list<set<int>> out = subk(test,2);

    for(list<set<int>>::iterator x = out.begin(); x != out.end(); x++){
        for(set<int>::iterator y = x->begin() ; y != x->end() ; y++){
            cout << *y << endl;
        }
        cout << endl;
    }
    

    // if(balanced(tr)) cout << "funciona" << endl;
    return 0;
}
