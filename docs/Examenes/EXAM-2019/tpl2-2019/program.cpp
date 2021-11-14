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

void fill_ordprev(tree<int> &tr,tree<int>::iterator pos,
                  list<int> &l, list<int>::iterator &it){
    if(pos == tr.end()) return;

    auto child = pos.lchild();
    while(child != tr.end()){
        *child = *it; it++;

        if(it != l.end()){ 
            fill_ordprev(tr,child,l,it);
            if(it == l.end()) break;
        }
        
        child++;
    }
}



void fill_ordprev(tree<int> &tr,list<int> &l){
    auto pos = tr.begin(); *pos = *l.begin();
    auto beg = ++l.begin();
    fill_ordprev(tr,tr.begin(),l,beg);
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
void a_lo_ancho(graph& G, tree<char>& T){
  // COMPLETAR AQUI...
}

void intersect_map(map<int,list<int>> &A, map<int,list<int>> &B,map<int,list<int>> &C){
  // COMPLETAR AQUI...
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
    
    ev.eval<3>(intersect_map,vrbs);
    h3 = ev.evalr<3>(intersect_map,seed,vrbs);
    
    printf("S=%03d -> H1=%03d H2=%03d H3=%03d\n",
           seed,h1,h2,h3);
    
    cout << endl << "Siguiente seed: ";
  } while (cin>>seed);

  return 0;
}
