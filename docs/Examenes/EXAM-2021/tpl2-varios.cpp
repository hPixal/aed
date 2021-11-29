#include <iostream>
#include <version>
#include <vector>
#include <map>
#include <list>
#include <set>
#include <math.h>
#include "tree.hpp"
//#include "btree.hpp"
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

void applymap(tree<int> &T, tree<int>::iterator n, map<int,int> &M) {
  *n=M[(*n)];
  auto c=n.lchild();
  while (c!=T.end()){
    if (M.find(*c)==M.end()){
      c = T.erase(c);
    } else {
      applymap(T,c,M);
      ++c;
    }
  }
}

void applymap(tree<int> &T,map<int,int> &M) {
  if (M.find(*T.begin())==M.end()){
    T.erase(T.begin());
    return;
  }
  applymap(T,T.begin(),M);
}

int main(){

    return 0;
}
