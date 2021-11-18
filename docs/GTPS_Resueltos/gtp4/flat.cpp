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

bool flat(vector< set<int> > &sw, int n){
    set<int> current;
    for(auto itsw = sw.begin() ; itsw != sw.end() ; itsw++){

        for (int i = 0; i < n; i++)
        {
            if(itsw->find(i) != itsw->end() && current.find(i) == current.end()) 
            current.insert(i);
        }
    }
    return (int(current.size()) == n);
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
        int aux = rand() % (elem+2);
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

    set<int> test = create_set(5);
    set<int> test2 = create_set(5);
    set<int> test3 = create_set(5);
    vector<set<int>> bigtest;
    bigtest.push_back(test);
    bigtest.push_back(test2);
    bigtest.push_back(test3);

    if(flat(bigtest,6)) cout << "creo que anda" << endl;
    cout << endl;
    for(auto x : test ){
        cout << x << " ";;
    }
    cout << endl;
    for(auto x : test2 ){
        cout << x << " ";
    }
    cout << endl;
    for(auto x : test3 ){
        cout << x << " ";;
    }
    cout << endl;
    // if(balanced(tr)) cout << "funciona" << endl;
    return 0;
}