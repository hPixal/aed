#define USECHRONO
#undef HAVE_MPI
#include "eval.hpp"
#include <cassert>
#include <climits>
#include <cstdlib>
#include <stack>
using namespace aed;
using namespace std;

// COMPLETAR DNI y NOMBRE AQUI:
// Nombre: Matías Nicolas Schalpeter
int DNI=43827272;
void recorrer_arbol(tree<int> &T,tree<int>::iterator it_arbol, list<tree<int>::iterator> &nodos_arbol){
  if(it_arbol==T.end()) return;
  nodos_arbol.push_back(it_arbol);
  tree<int>::iterator child=it_arbol.lchild();
  while(child!=T.end()) recorrer_arbol(T,child++,nodos_arbol);
}
  int maxeqsiblings(tree<int> &T) {
    list<tree<int>::iterator> nodos_T;
    recorrer_arbol(T,T.begin(),nodos_T);
    int maxneqparcial=0;
    int maxneqdefinitivo=0;
    auto it_nodos=nodos_T.begin();
    int anterior;
    while(it_nodos!=nodos_T.end()){
      auto it_arbol=*it_nodos;
      auto c=it_arbol.lchild();
      if(c!=T.end()) anterior=*c;
      while(c!=T.end()){
        auto c2=it_arbol.lchild();
        while(c2!=T.end()){
          if(*c2==*c){
            maxneqparcial+=1;
          }
          ++c2;
        }
        if(maxneqparcial>maxneqdefinitivo){
          maxneqdefinitivo=maxneqparcial;
        }
        maxneqparcial=0;
        c++;
      }
      ++it_nodos;
    }
    return maxneqdefinitivo;
  }
  
  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
  int main() {
    Eval ev;
    int vrbs=0;
    ev.eval<1>(maxeqsiblings,vrbs);
    return 0;
  }
  
