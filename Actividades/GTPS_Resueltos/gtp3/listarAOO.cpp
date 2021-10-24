#include <iostream>
#include <list>
#include <map>
#include "aedtools/tree.hpp"
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
    l.insert(l.end(),*it);
    auto c = it.lchild();
    while(c!=t.end()){
        preorder(t,l,c);
        c = c.right();
    }
    l.insert(l.end(),*c);    
}

void posorder(tree<int> &t, list<int> &l){
    auto it = t.begin();
    if(it == t.end()){
        l.push_back(*it);
        return;
    }
    preorder(t,l,it);
}

int main(){
    tree<int> a;
    


    return 0;
}