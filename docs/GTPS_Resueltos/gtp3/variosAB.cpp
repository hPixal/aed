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



/*
    Este archivo es solo de ejemplo. Usalo para resolver los ejercicios, ya que este
    en esta carpeta especifica y con este nombre especifico, es el unico con el que 
    funciona la utilería de la catedra. Se puede usar como plantilla para luego cam
    biarle el nombre a uno más apropiado y entregarlo como resolción.
*/

////////////////////////////////////////////////////////////////////////////

template<typename T>
    bool checkIfSame(btree<T> t1, btree<T> t2, typename btree<T>::iterator n1, typename btree<T>::iterator n2){
        if(n2 == t2.end()) return true;
        if(*n1 != *n2) return false;

        if( checkIfSame(t1,t2,n1.right(),n2.right()) !=
            checkIfSame(t1,t2,n1.left() ,n2.left() ) ){
               return false;
           }
        return true;
    }

template<typename T>
    bool checkIfSame(btree<T> t1, btree<T> t2){
        if(t1.size() != t2.size()) return false;
        return checkIfSame(t1,t2,t1.begin(),t2.begin());
    }

////////////////////////////////////////////////////////////////////////////

template<typename T>
    bool checkIfMirror(btree<T> t1, btree<T> t2, typename btree<T>::iterator n1, typename btree<T>::iterator n2){
        if(n2 == t2.end()) return true;
        if(*n1 != *n2) return false;

        if( checkIfMirror(t1,t2,n1.right(),n2.left()) !=
            checkIfMirror(t1,t2,n1.left() ,n2.right() ) ){
               return false;
           }
        return true;
    }

template<typename T>
    bool checkIfMirror(btree<T> t1, btree<T> t2){
        if(t1.size() != t2.size()) return false;
        return checkIfMirror(t1,t2,t1.begin(),t2.begin());
    }

////////////////////////////////////////////////////////////////////////////

template<typename T>
    void mirrorCopy(const btree<T> &orig,btree<T> &mcpy,typename btree<T>::iterator nodeOrig,typename btree<T>::iterator add){
        if(nodeOrig == orig.end()) return;
        add = mcpy.insert(add,*nodeOrig);

        btree<T>::iterator nextr = add.right();
        btree<T>::iterator nextl = add.left();

        mirrorCopy(orig,mcpy,nodeOrig.left(),nextr);
        mirrorCopy(orig,mcpy,nodeOrig.right(),nextl);
        
    }

template<typename T>
    void mirrorCopy(const btree<T> &orig, btree<T> &mcpy){
        mcpy.clear(); auto itor = orig.begin(); 
        auto itcp = mcpy.begin();
        
    }

////////////////////////////////////////////////////////////////////////////
/*Extra: crear un arbol binario */
////////////////////////////////////////////////////////////////////////////

template<typename T>
    void create_btree(btree<int> &tr,typename btree<T>::iterator it,int level,int count){
        if(count > level) return;
        it = tr.insert(it,count/*int(rand()%40)*/);

        typename btree<T>::iterator nextr = it.right();
        typename btree<T>::iterator nextl = it.left();

        create_btree(tr,nextr,level,count+1);
        create_btree(tr,nextl,level,count+1);
    }

template<typename T>
    void create_btree(btree<T> &tr,int level){
        tr.clear();
        create_btree(tr,tr.begin(),level,0);
    }

int main(){
    btree<int> tr;
    create_btree(tr,2);

    btree<int> tr2;
    create_btree(tr2,2);

    btree<int> tr3;
    create_btree(tr3,3);

    if(checkIfSame(tr3,tr)){
        cout << "They are equal. " << endl;
    }else{
        cout << "They aren't equal. " << endl;
    }
    
    return 0;
}