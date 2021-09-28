#define USECHRONO
#include <cassert>
#include <climits>
#include <cstdlib>
#include <stack>
#include "eval.hpp"

using namespace aed;
using namespace std;

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
bool check(list<int> &L1, list<int>::iterator p, 
            list<int>::iterator q){
  auto it = L1.begin();
  while(it != L1.end()){
    if(it == p){
      return true;
    }
    if(it == q){
      return false;
    }
    it++;
  }
  return false;
}
void extract_range(list<int> &L1, list<int>::iterator p, 
                   list<int>::iterator q, list<int> &L2) 
{
  L2.clear();
  if( p==L1.end() || !check(L1,p,q)){
    return;
  }

  while(p!=q){
    L2.push_back(*p);
    L2.erase(p);
    ++p;
  }
  return;
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>


int add_elements(list<int>& L, stack<int> &S) {
  auto it = L.begin();
  while(!S.empty()){
    auto it = L.begin();
    
    while(it != L.end()){
      if (S.top() <= *it)
      {
        L.insert(it,S.top());
        S.pop();
        break;
      }
      ++it;
      if(it == L.end()){
        L.push_back(S.top());
        S.pop();
      }
    }
  }

  list<int> aux = L;
  auto auxit = aux.begin();

  int cont = 0;
 for (int i =-9; i < 11; ++i){
   auto it = L.begin();
   int aux = 0;
   while(it != L.end()){
     if(i == *it){
       if(aux < 1){
         ++aux;
       }else{
         ++cont;
         break;
       }
     }
     ++it;
   }
 }


  return cont;
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
bool coprimos(list<int>&L) {
  // COMPLETAR...
  return true;
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int main() {
  Eval ev;
  int vrbs = 0;
  int seed = 123;
  int h1=0,h2=0,h3=0;

  //ev.eval<1>(extract_range,vrbs);
  //h1 = ev.evalr<1>(extract_range,seed,vrbs);
  
  ev.eval<2>(add_elements,vrbs);
  h2 = ev.evalr<2>(add_elements,seed,vrbs);
  
  //ev.eval<3>(coprimos,vrbs);
  //h3 = ev.evalr<3>(coprimos,seed,vrbs);

  printf("S=%03d -> H1=%03d H2=%03d H3=%03d\n",
         seed,h1,h2,h3);
  
  return 0;
}
