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
typedef map<string,list<string>> mapsl;

void classify_relative(tree<int> &T,
                       int n1,int n2,int &m1, int&m2) {
  // COMPLETAR AQUI....
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
void prom_path(tree<int> &tr,tree<int>::iterator pos, int count,vector<int> &allPaths){
    if (pos == tr.end()) return;

    auto child = pos.lchild();
    
    while(child != tr.end()){

        if(child.lchild() == tr.end())
        { allPaths.push_back(count); } 

        prom_path(tr,child++,count++,allPaths);
    }
}


float prom_path(tree<int> &tr){
    vector<int> allPaths; auto pos = tr.begin();
    prom_path(tr,pos,0,allPaths);
    
    float prom = 0;
 
    for(auto x : allPaths){
        cout << x << endl;
        prom += x;
    }

    return (prom/allPaths.size());
    
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
bool filtra_deps(mapsl &G, mapsl &rtrn,string search) {
    if(G.find(search) == G.end() ) return true;
    bool end = false;

    while(!end){
        auto aux = G.find(search);
        if(aux != G.end()){ rtrn[aux->first] = aux->second; end = true; } 

        for(auto it = aux->second.begin(); it != aux->second.end() ; it++){
            end = filtra_deps(G,rtrn,*it);
        }
    }

    return true;
}

mapsl filtra_deps(mapsl &G, list<string> &L) {
    mapsl rtrn; auto lit = L.begin();
    while (lit != L.end())
    {
        filtra_deps(G,rtrn,*lit);
        lit++;
    }
    return rtrn;
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int main() {
  Eval ev;
  int vrbs = 0;
  int seed = 123;
  int h1=0,h2=0,h3=0;

  do {

    ev.eval<1>(classify_relative,vrbs);
    h1 = ev.evalr<1>(classify_relative,seed,vrbs);

    ev.eval<2>(prom_path,vrbs);
    h2 = ev.evalr<2>(prom_path,seed,vrbs);

    ev.eval<3>(filtra_deps,vrbs);
    h3 = ev.evalr<3>(filtra_deps,seed,vrbs);

    printf("S=%03d -> H1=%03d H2=%03d H3=%03d\n",
           seed,h1,h2,h3);
    
    printf("\n\nIngrese un valor para la semilla:");
  } while (cin>>seed);

  return 0;
}
