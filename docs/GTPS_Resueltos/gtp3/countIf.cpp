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

bool odd(int num){
    return (num % 2 == 0);
}

void count_if(tree<int> &tr,tree<int>::iterator pos, int& count,bool (*pred)(int x)){
    if (pos == tr.end()) return;

    auto child = pos.lchild();

    while (child != tr.end()){
        if (pred(*child)) count++; 
        count_if(tr,child,count,pred);
        child++;
    } 
}

int count_if(tree<int> &tr,bool (*pred)(int x)){
    auto it = tr.begin(); int count = 0;
    if(pred(*it)) count++;
    count_if(tr,it,count,(*pred));
    return count;
}

int br_count_if (tree<int> &T,bool (*pred)(int x), tree<int> :: iterator n){
    int contador = 0;
    if(pred(*n)){
      contador++;
    }
    auto hijo = n.lchild();
    while(hijo != T.end()){
      contador += br_count_if(T,pred,hijo);
      hijo++;
    }
    return contador;
  }
    
  int br_count_if(tree<int> &T,bool (*pred)(int x)){
    tree<int>::iterator raiz = T.begin();
    int nodos = br_count_if(T,pred,raiz);
    return nodos;
  }
  

int main(){
    tree<int> tr;
    make_random_tree(tr,10,3);
    list<int> pre;
    print_tree(tr);

    int count = count_if(tr,odd);
    cout << "the count is : " << count << br_count_if(tr,odd);

    return 0;
}