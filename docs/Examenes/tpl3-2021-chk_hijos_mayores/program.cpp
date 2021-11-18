#define USECHRONO
#undef HAVE_MPI

typedef int (*mapfun_t)(int);

int f1(int x) { return x+1; }
int f2(int x) { return x-1; }
int f3(int x) { return 2*x; }
int f4(int x) { return x; }

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

bool check(btree<int> &T, btree<int>::iterator pos){

  auto right = pos; auto left = pos;
  right = right.right(); left = left.left();

  if( right == T.end() && left == T.end() ) return true;
  if( right != T.end() && left != T.end() ){ if((*right + *left) > *pos) return (check(T,left) && check(T,right)); }
  if( right != T.end()){ if((*right) > *pos) return check(T,right); }
  if( left != T.end()){ if((*left) > *pos)return check(T,left); }
  
  return false;
}

bool chk_hijos_mayores(btree<int> &T){
  if(T.empty()) return false;
  bool rtrn = false;
  if(T.begin() != T.end()){
    rtrn = check(T,T.begin());
  }
  return rtrn;
}
//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int main() {
  Eval ev;
  int vrbs=0;
  ev.eval<1>(chk_hijos_mayores,vrbs);

  return 0;
}
