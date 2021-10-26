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

void count_level(tree<int> &tr, tree<int>::iterator pos,int l,int lcount,int &count){
    if (pos == tr.end()) return;
    
    if(lcount == l){
        while(pos != tr.end()){
            count++; pos++;
        }
    }else{
        auto child = pos.lchild();
        while(child != tr.end()){
            count_level(tr,child++,l,lcount++,count);
        }
    }
}

int count_level(tree<int> &tr, int l){
    if(l == 0) return 1;
    auto pos = tr.begin(); int count = 0;
    count_level(tr,pos,l,0,count);
    return count;
}

int main(){
    tree<int> tr;
    make_random_tree(tr,10,3);
    list<int> pre;
    print_tree(tr);
    cout << count_level(tr,10);
    return 0;
}