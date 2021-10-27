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

int spaceship(btree<int> &T1,btree<int> &T2) {
  // COMPLETAR AQUI...
  return 0;
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
// Función auxiliar provista por la cátedra
list<pair<btree<char>,float>>::iterator getMin(list<pair<btree<char>,float>> & bosque){
  auto it = bosque.begin();
  list<pair<btree<char>,float>>::iterator itMini = it;
  it++;
  while(it!=bosque.end()){
    if(it->second<itMini->second){
      itMini = it;
    }
    it++;
  }
  return itMini;    
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
btree<char> makeHuffmanTree(list<pair<btree<char>,float>> & bosque){
  // COMPLETAR AQUI...
  return btree<char>();
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int minCostSets(set<int>& U, vector<set<int>>& S,
                map<set<int>, int>& costos) {
  // COMPLETAR AQUI...
  return 0;
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int main() {

  Eval ev;
  int vrbs = 0;
  int seed = 123;
  int h1=0,h2=0,h3=0;

  // Para el examen final
  cout << "seed: 123" << endl;
  do {
    ev.eval<1>(spaceship,vrbs);
	  h1 = ev.evalr<1>(spaceship,seed,vrbs);
    
	  ev.eval<2>(makeHuffmanTree,vrbs);
	  h2 = ev.evalr<2>(makeHuffmanTree,seed,vrbs);
    
    ev.eval<3>(minCostSets,vrbs);
    h3 = ev.evalr<3>(minCostSets,seed,vrbs);

    printf("S=%03d -> H1=%03d H2=%03d H3=%03d\n",
           seed,h1,h2,h3);
    
    cout << endl << "Siguiente seed: ";
  } while (cin>>seed);

  return 0;
}
