#include <iostream>
#include <version>
#include <map>
#include <list>
#include "tree.hpp"
#include "str_convs.hpp"
#include "util_tree.hpp"
//#include "str_convs.hpp"
using namespace aed;
using namespace std;

/*
    Este archivo es solo de ejemplo. Usalo para resolver los ejercicios, ya que este
    en esta carpeta especifica y con este nombre especifico, es el unico con el que 
    funciona la utilería de la catedra. Se puede usar como plantilla para luego cam
    biarle el nombre a uno más apropiado y entregarlo como resolción.
*/

node_t list2tree(tree<int> &T, node_t n, list<int> &L,list<int>::iterator &p) {
    // Inserta el nodo
    n = T.insert(n,*(p++)); // por ejemplo, en begin(), inserta ese mismo nodo con un valor p
    int nchild = *(p++); // Ahora trabajaremos con el hijo de ese nodo, le insertamos la siguiente etiqueta

    // Reconstruye los hijos
    node_t child = n.lchild();  
    
    for (int j=0; j<nchild; j++) {
        child = list2tree(T,child,L,p);
        child++;
    }
    return n;
}

void list2tree(tree<int> &tr,list<int> &l) {
    auto beg = l.begin();
    list2tree(tr,tr.begin(),l,beg);
}

int main(){
    tree<int> tr;
    //make_random_tree(tr,10,3);
    list<int> pre = { 6, 5, 4, 0, 8, 0, 5, 2, 4, 0, 4, 0, 7, 0, 9, 0 };
    list2tree(tr,pre);
    print_tree(tr);
    


    return 0;
}