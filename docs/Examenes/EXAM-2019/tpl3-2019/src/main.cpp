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

int spaceship(btree<int> &T1,btree<int>::iterator it1,btree<int> &T2,btree<int>::iterator it2) {
  if (it1==T1.end() && it2==T2.end()) return 0;
  if (it1==T1.end() && it2!=T2.end()) return -1;
  if (it1!=T1.end() && it2==T2.end()) return +1;

  int rv;
  rv = *it1-*it2; if (rv) return rv;
  rv = spaceship(T1,it1.left(),T2,it2.left()); if (rv) return rv;
  rv = spaceship(T1,it1.right(),T2,it2.right()); if (rv) return rv;

  return 0;
}


int spaceship(btree<int> &T1,btree<int> &T2) {
  int rv = spaceship(T1,T1.begin(),T2,T2.begin());
  return rv>0? 1 : rv<0? -1 : 0;
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
  while(bosque.size()>1){
  auto it = getMin(bosque);

  btree<char> Tl;
  auto aux1 = it->first.begin();
  Tl.splice(Tl.begin(),aux1);
  int w = it->second;
  bosque.erase(it);  

  it = getMin(bosque);
  btree<char> Tr;
  auto aux2 = it->first.begin();
  Tr.splice(Tr.begin(),aux2);
  w += it->second;
  bosque.erase(it);  

  btree<char> Tnew; Tnew.insert(Tnew.begin(),'.');
   aux1 = Tl.begin();
   Tnew.splice(Tnew.begin().left(),aux1);
   aux2 = Tr.begin();
   Tnew.splice(Tnew.begin().right(),aux2);
  
   bosque.push_back({Tnew,w});
   }
  return bosque.begin()->first;
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
