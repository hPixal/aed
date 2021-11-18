#define USECHRONO
#undef HAVE_MPI

typedef int (*mapfun_t)(int);

int f1(int x) { return x-3; }
int f2(int x) { return x-2; }
int f3(int x) { return (x>20? -1 : 2*x); }

#include "eval.hpp"
#include <cassert>
#include <climits>
#include <cstdlib>
#include <stack>
using namespace aed;
using namespace std;

// COMPLETAR DNI y NOMBRE AQUI:
// Nombre: Gareis Nahuel
int DNI=43538493;

void btexpand(btree<int> &B,int val,mapfun_t f,btree<int>::iterator it) {
  if(val<0) return;
  it = B.insert(it,val);
  
  btree<int>::iterator nextr = it.right();
  btree<int>::iterator nextl = it.left();

  auto right = f(val+1);
  auto left = f(val);
  if(right > -1) btexpand(B,right,f,nextr);
  if(left > -1) btexpand(B,left,f,nextl);
}

void btexpand(btree<int> &B,int root,mapfun_t f) {
  B.clear();
  btexpand(B,root,f,B.begin());
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int main() {
  Eval ev;
  int vrbs=0;
  ev.eval<1>(btexpand,vrbs);
  return 0;
}
