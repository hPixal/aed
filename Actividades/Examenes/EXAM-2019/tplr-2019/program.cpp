#define USECHRONO
#undef HAVE_MPI
#include "eval.hpp"
#include <cassert>
#include <climits>
#include <cstdlib>
#include <stack>
#include <map>

#include <set>
#include <vector>
#include <list>
#include <numeric>

using namespace aed;
using namespace std;

//VALIDO TPL 1
list<int> mediaMovilEntera(list<int>& L, int v){
  return list<int>();
}

//VALIDO TPL 3
int nSumaK(set<int> &S, int k) {
  return 0;
}


//VALIDO TPL 2
int nCaminosK(map<int,set<int>> &G, int a, int b, int k) {
  return 0;
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
//VALIDO TPL 3
void make_heap(btree<int> &T) {
}

//VALIDO TPL 1
void sortStack(stack<int>& s) {
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int main() {
  Eval ev;
  int vrbs = 0;
  int seed = 123;
  int h1=0,h2=0,h3=0,h4=0,h5=0;

  // Para el examen final
  cout << "seed: 123" << endl;
  do {
    ev.eval<1>(mediaMovilEntera,vrbs);
    h1 = ev.evalr<1>(mediaMovilEntera,seed,vrbs);
    
    ev.eval<2>(nSumaK,vrbs);
    h2 = ev.evalr<2>(nSumaK,seed,vrbs);

    ev.eval<3>(nCaminosK,vrbs);
    h3 = ev.evalr<3>(nCaminosK,seed,vrbs);
    
    ev.eval<4>(make_heap,vrbs);
    h4 = ev.evalr<4>(make_heap,seed,vrbs);

    ev.eval<5>(sortStack,vrbs);
    h5 = ev.evalr<5>(sortStack,seed,vrbs);
    
    printf("S=%03d -> H1=%03d H2=%03d H3=%03d H4=%03d H5=%03d\n",
           seed,h1,h2,h3,h4,h5);
    
    cout << endl << "Siguiente seed: ";
  } while (cin>>seed);
  
  return 0;
}
