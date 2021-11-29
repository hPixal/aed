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


list<int> findPath(tree<int> &tr, tree<int>::iterator it ,int &num,list<int> rtn, bool &found) 
{
    if(it == tr.end() || found) return rtn; 
    rtn.push_back(*it);

    if(*it == num){
        found = true; return rtn; 
    } 

    it = it.lchild();

    while (it!=tr.end())
    {
        rtn = findPath(tr,it,num,rtn,found);
        it = it.right();
    }

    if(!found)rtn.pop_back();
    return rtn;
}

list<int> findPath(tree<int> &tr, int num) 
{
    list<int> rtn;
    if(*tr.begin() == num ){ rtn.push_back(*tr.begin()); return rtn; }
    if(tr.empty()) return rtn; bool found = false;
    rtn=findPath(tr,tr.begin(),num,rtn,found);
    if(found) return rtn;
    rtn.clear();
    return rtn;
}

pair<int,int> getProximity(list<int> &l1, list<int> &l2){
    bool startCount = 0; int count = 0;
    int m1 = 0; int m2 = 0;
    int closest = -999;

    for(auto x : l1){
        for(auto y : l2){
            if( x == y ){
                closest = x;
            }
        }
    }

    for(auto x : l1){
        if(startCount) count++;
        if(x==closest) startCount = 1;
    }
    m1 = count;

    startCount = 0; count = 0;
    for(auto x : l2){
        if(startCount) count++;
        if(x==closest) startCount = 1;
    }
    m2 = count;

    return make_pair(m1,m2);
}

void classify_relative(tree<int> &T,int n1,int n2,int &m1, int&m2){
    if(n1 == n2){ m1 = 0; m2 = 0; return; }
    auto l1  = findPath(T,n1); auto l2 = findPath(T,n2);
    tie(m1,m2) = getProximity(l1,l2);
}


/*
bool getPath(tree<int> &tr,tree<int>::iterator pos,int &n,int count,int &rtrn){
    if (pos == tr.end()) return false;

    auto child = pos.lchild();
    bool found = false;
    int count2 = count + 1;


    while(child != tr.end() || found){

        if(*child == n)
        { found = true; rtrn = count; } 

        found = getPath(tr,child++,n,count2,rtrn);
    }
    return found;
}

void classify_relative(tree<int> &tr,int n1,int n2,int &m1,int &m2){
    m1 = -1; m2 = -1;
    getPath(tr,tr.begin(),n1,1,m1);
    getPath(tr,tr.begin(),n2,1,m2);
}

*/
//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
void prom_path(tree<int> &tr,tree<int>::iterator pos, int count,vector<int> &allPaths){
    if (pos == tr.end()) return;

    auto child = pos.lchild();
    
    while(child != tr.end()){

        if(child.lchild() == tr.end())
        { allPaths.push_back(count+1); } 

        prom_path(tr,child,count+1,allPaths);
        child = child.right();
    }
}


float prom_path(tree<int> &tr){
    vector<int> allPaths; auto pos = tr.begin();
    prom_path(tr,pos,0,allPaths);
    
    float prom = 0;
 
    for(auto x : allPaths){
        //cout << x << endl;
        prom += x;
    }
    if(!allPaths.empty()) prom = prom/int(allPaths.size());
    return prom;
    
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
