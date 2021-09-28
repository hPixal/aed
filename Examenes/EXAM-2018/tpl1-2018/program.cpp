#define USECHRONO
#undef HAVE_MPI
#include "eval.hpp"
#include <cassert>
#include <climits>
#include <cstdlib>
#include <stack>
#include <map>

using namespace aed;
using namespace std;

void sign_split(list<int> &L,vector< list<int> > &VL) {
  auto it = L.begin();
    int aux = *it;
    list<int> auxlist;

    while (it != L.end())
    {
        if (aux<0 && *it < 0 || aux>=0 && *it >= 0)
        {
            auxlist.push_back(*it);
            aux = *it;
        }else{
            VL.push_back(auxlist);
            auxlist.clear();
        }
    }
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>

int sign(int x){
  if(x>=0){
    return 1;
  }
  return -1;
}

void sign_join(vector< list<int> > &VL,list<int> &L) {
  auto it = VL.begin();
  
  int s = 1;
  // it = vector de listas || it2 = lista dentro del vector
  while( it != VL.end() ){
    auto it2 = VL.begin();

    while (it2!=VL.end()){
      auto listaux = *it2;
      auto itlist = listaux.begin();

      while(itlist != listaux.end()){

        if (sign(*itlist) == s)
        {
          L.push_back(*itlist);
          listaux.erase(itlist);
        }else{
          *it2 = listaux; 
          break;
        }
        ++itlist;
      }
      ++it2;
    }
    s=-s;
    ++it;
  }
}

void reverseStack(stack<int>&S){
  // COMPLETAR AQUI....
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int main() {
  Eval ev;
  int vrbs = 0;
  int seed = 123;
  int h1=0,h2=0,h3=0;

  do {

    //ev.eval<1>(sign_split,vrbs);
    //h1 = ev.evalr<1>(sign_split,seed,vrbs);

    ev.eval<2>(sign_join,vrbs);
    h2 = ev.evalr<2>(sign_join,seed,vrbs);

    ev.eval<3>(reverseStack,vrbs);
    h3 = ev.evalr<3>(reverseStack,seed,vrbs);

    printf("S=%03d -> H1=%03d H2=%03d H3=%03d\n",
           seed,h1,h2,h3);
    
    printf("\n\nIngrese un valor para la semilla:");
  } while (cin>>seed);

  return 0;
}
