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
ListarAOO. Escribir procedimientos para listar un  ́arbol 
ordenado orientado siguiendo los  ́ordenesprefijo y postfijo.
*/

void preorder(tree<int> &t, list<int> &l,tree<int>::iterator &it){
    l.insert(l.end(),*it);
    auto c = it.lchild();
    while(c!=t.end()){
        preorder(t,l,c);
        c = c.right();
    }
}

void preorder(tree<int> &t, list<int> &l){
    auto it = t.begin();
    if(it == t.end()){
        l.push_back(*it);
        return;
    }
    preorder(t,l,it);
}

void posorder(tree<int> &t, list<int> &l,tree<int>::iterator it){
    auto c = it.lchild();
    while(c!=t.end()){
        posorder(t,l,c);
        c = c.right();
    }
    l.insert(l.end(),*it);    
}

void posorder(tree<int> &t, list<int> &l){
    auto it = t.begin();
    if(it == t.end()){
        l.push_back(*it);
        return;
    }
    posorder(t,l,it);
}

//preorder funciona bien, pos  order no funciona

int main(){
    tree<int> t;
    make_random_tree(t,10,2);
    list<int> pre;
    posorder(t,pre);
    print_tree(t);
    for(auto x : pre){
        cout << x << " ";
    }
    
    return 0;
}