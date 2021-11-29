#define USECHRONO
#undef HAVE_MPI
#include "eval.hpp"
#include <cassert>
#include <climits>
#include <cstdlib>
#include <stack>
#include <list>
#include <map>
using namespace aed;
using namespace std;
typedef map<int,list<int>> graph;
// COMPLETAR DNI y NOMBRE AQUI:
// Nombre: Saccani Segundo
int DNI=44034849;


  
  bool chk_enlace( graph &G,map<int,int> &M, int pc1, int pc2,int enlace){
    map<int,bool> G1,G2;
    G1[pc1]=true;
    while(G1!=G2){
      G2=G1;
      map<int,bool>::iterator itG1=G1.begin();
      while(itG1!=G1.end()){
        list<int>::iterator itList=G[itG1->first].begin();
        while(itList!=G[itG1->first].end()){
          if(M[*itList]>=enlace){
            G1[*itList]=true;
          }
          itList++;
        }
        itG1++;
      }
    }
    return G1[pc2];
  }

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int main() {
  Eval ev;
  int vrbs=0;
  ev.eval<1>(chk_enlace,vrbs);
  
  return 0;
}
