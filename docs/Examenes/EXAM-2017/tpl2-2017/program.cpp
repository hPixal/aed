#define USECHRONO
#include "eval.hpp"
#include <cassert>
#include <climits>
#include <cstdlib>
#include <stack>
#include <map>

using namespace aed;
using namespace std;

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>

float getProm(list<int> &l){
  float acum = 0;
  for(auto x : l){
    acum+=x;
  }
  acum = acum/int(l.size());
  return acum;
}

void prom_nivel(tree<int> &tr,tree<int>::iterator it,int level,map<int,list<int>> &prom) {
  if(it == tr.end()) return;
  if(prom.find(level) == prom.end())
  { prom[level] = list<int>() = {*it}; }else
  { prom[level].push_back(*it); }

  auto child = it.lchild();
  while(child != tr.end()){
    prom_nivel(tr,child,level+1,prom);
    child = child.right();
  }
}

void prom_nivel(tree<int> &T, list<float> &P) {
  auto it = T.begin(); P.clear();
  map<int,list<int>> prom;
  if(T.empty()) return;
  prom_nivel(T,it,0,prom); 
  for (size_t i = 0; i < prom.size(); i++)
  {
    P.push_back(getProm(prom[i]));
  }
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
bool isThere(list<int> &l, int val){
  bool it_is = false;
  for(auto x : l){
    if(x == val) it_is = true;
  }
  return it_is;
}

bool es_circuito(map<int,list<int>> &gr,list<int>&l,map<int,list<int>>::iterator itg,list<int>::iterator itl){
  if(itl == l.end()) return true;
  itg = gr.find(*itl);
  if(itg == gr.end()) return false;
  
  
  if(isThere(itg->second,*itl)) return es_circuito(gr,l,itg,itl++); 
  return false;

}

bool es_circuito(map<int,list<int>>&gr,list<int>&l){
  if(gr.empty()) return false;
  auto itl = l.begin();
  return es_circuito(gr,l,gr.begin(),itl);
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
void map_graph(map<int,vector<int> > &Gin,map<int,int> &P,
               map<int,vector<int> > &Gout) {
  // COMPLETAR AQUI...
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int main() {
  Eval ev;
  int vrbs = 0;
  int seed = 123;
  int h1=0,h2=0,h3=0;

  do {
    ev.eval<1>(prom_nivel,vrbs);
    h3 = ev.evalr<1>(prom_nivel,seed,vrbs);
    
    ev.eval<2>(es_circuito,vrbs);
    h1 = ev.evalr<2>(es_circuito,seed,vrbs);
    
    //ev.eval<3>(map_graph,vrbs);
    //h2 = ev.evalr<3>(map_graph,seed,vrbs);

    printf("S=%03d -> H1=%03d H2=%03d H3=%03d\n",
           seed,h1,h2,h3);
    
    printf("\n\nIngrese un valor para la semilla:");
  } while (cin>>seed);

  return 0;
}
