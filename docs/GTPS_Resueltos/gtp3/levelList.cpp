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

void orden_de_nivel(tree<int> &tr, tree<int>::iterator pos,int l,int lcount,list<int> &level){
    if (pos == tr.end()) return;
    
    if(lcount == l){
        while(pos != tr.end()){
            level.push_back(*pos); pos++;
        }
    }else{
        auto child = pos.lchild();
        while(child != tr.end()){
            orden_de_nivel(tr,child++,l,lcount++,level);
        }
    }
}

list<list<int>> orden_de_nivel(tree <int> &tr){
    list<list<int>> rtrn; auto beg = tr.begin(); int count = 0;
    while(true){    
        list<int> aux;
        orden_de_nivel(tr,beg,count,0,aux);
        if(aux.empty()) return rtrn;
        rtrn.push_back(aux);
        count++;
    }
}

int main(){
    tree<int> tr;
    make_random_tree(tr,10,3);
    list<int> pre;
    print_tree(tr);

    auto l = orden_de_nivel(tr);
    for(auto x : l){
        for ( auto y : x){
            cout << " { " << y << " } ";
        }
        cout << endl;
    }
    //cout << count_level(tr,10);
    return 0;
}