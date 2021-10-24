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
// Nombre: Gareis, Nahuel Julián
int DNI=43538493;

void xparity(list<int> &L,int parity,vector<list<int>> &VL) {
  auto it = L.begin();
  list<int> auxlist;
  while(it != L.end()){
    if(parity == 0 && ((*it % 2) >0 ) ){
      if(!auxlist.empty())
        VL.push_back(auxlist);
      auxlist.clear(); 
    }else if(parity == 1 && ((*it % 2) == 0 ) ){
      if(!auxlist.empty())
        VL.push_back(auxlist);
      auxlist.clear(); 
    } else if (parity == 0 && ((*it % 2) == 0))
    {
      auxlist.push_back(*it);
    }else if( parity == 1 && ((*it % 2) > 0 )){
      auxlist.push_back(*it);
    }
    ++it;
  }
  if(!auxlist.empty())
                    VL.push_back(auxlist);
}
//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int main() {
  Eval ev;
  int vrbs = 0;
  ev.eval<1>(xparity,vrbs);
  return 0;
}
