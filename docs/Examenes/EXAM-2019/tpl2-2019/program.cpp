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

void fill_ordprev(tree<int> &tr,tree<int>::iterator pos, list<int> &l, 
                  list<int>::iterator &lit)
{
  if (lit == l.end() || pos == tr.end()){ return; } 
  *pos = *lit; pos = pos.lchild();
  
  while(pos!= tr.end() && lit != l.end()){
    lit++;
    fill_ordprev(tr,pos,l,lit);
    pos = pos.right(); 
  }
}


void fill_ordprev(tree<int> &tr,list<int> &l){
  if(l.empty()) return;
  auto it = tr.begin(); auto lit = l.begin();
  fill_ordprev(tr,it,l,lit);
}
//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>

  tree<char>::iterator a_lo_ancho(graph& G,graph::iterator itg, tree<char>& tr, tree<char>::iterator itr,map<char,bool> &added){
  if(added.find(itg->first) != added.end()) return itr;
  if(itg == G.end()) return tr.end();
  
  itr = tr.insert(itr,itg->first);
  added[itg->first] = true;

  auto child = itr.lchild();
  
  for( auto itv = itg->second.begin(); itv != itg->second.end(); itv++ ){
    auto aux = G.find(*itv);
    if(aux != G.end()){
      auto compare = a_lo_ancho(G,aux,tr,child,added);
        if(compare == tr.end()) return tr.end();
        if(compare != child) {child = compare; child++; }
    }
  }
  return child;
}

void a_lo_ancho(graph& G, tree<char>& tr){
  if(G.empty()) return; map<char,bool> added;
  auto itg = G.begin(); auto itr = tr.begin();
  a_lo_ancho(G,itg,tr,itr,added);
}

void intersect_map(map<int,list<int>> &A, map<int,list<int>> &B,map<int,list<int>> &C){
  
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>

int main() {

  Eval ev;
  int vrbs = 0;
  int seed = 123;
  int h1=0,h2=0,h3=0;

  cout << "seed: 123" << endl;
  do {
    ev.eval<1>(fill_ordprev,vrbs);
    h1 = ev.evalr<1>(fill_ordprev,seed,vrbs);

    ev.eval<2>(a_lo_ancho,vrbs);
    h2 = ev.evalr<2>(a_lo_ancho,seed,vrbs);
    
    //ev.eval<3>(intersect_map,vrbs);
    //h3 = ev.evalr<3>(intersect_map,seed,vrbs);
    
    printf("S=%03d -> H1=%03d H2=%03d H3=%03d\n",
           seed,h1,h2,h3);
    
    cout << endl << "Siguiente seed: ";
  } while (cin>>seed);

  return 0;
}
