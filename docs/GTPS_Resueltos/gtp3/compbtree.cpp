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

//template<typename T>
    void countLeafs(typename btree<int>::iterator &end, typename btree<int>::iterator node,int &count){
        if(node == end){ count++; return;} 
        countLeafs(end,node.right(),count);
        countLeafs(end,node.left(),count);        
    }

//template<typename T>
    int countLeafs(typename btree<int>::iterator &end, typename btree<int>::iterator node){
        if(node == end) return 0;
        int rtrn = 0;
        countLeafs(end,node,rtrn);
        return rtrn;
    }

////////////////////////////////////////////////////////////////////////////

//template<typename T>
    bool is_minor(btree<int> &at,btree<int> &bt){
        int a = 0; int b = 0;
        int Ai = 0; int Bi = 0;
        int Ad = 0; int Bd = 0;
        auto aEnd = at.end(); auto bEnd = bt.end();
        btree<int>::iterator aBeg = at.begin(); 
        btree<int>::iterator bBeg = bt.begin();


        a = countLeafs(aEnd,aBeg);
        b = countLeafs(bEnd,bBeg);

        Ad = countLeafs(aEnd,aBeg.right());
        aBeg = at.begin();
        Ai = countLeafs(aEnd,aBeg.left());

        
        Bd = countLeafs(bEnd,bBeg.right());
        bBeg = bt.begin();
        Bi = countLeafs(bEnd,bBeg.left());

        return ( a < b || Ai < Bi || Ad < Bd );
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
    create_btree(tr,4); create_btree(tr2,3);
    if(is_minor(tr2,tr)){
        cout << "FBI OPEN UP" << endl;
    }
    return 0;
}
