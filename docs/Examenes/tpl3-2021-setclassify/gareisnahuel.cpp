#define USECHRONO
#undef HAVE_MPI
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

set<int> set_union(set<int> &A,set<int> &B){
    set<int> C;
    C.insert(A.begin(), A.end());
    C.insert(B.begin(), B.end());
    return C;
}
    
set<int> set_intersection(set<int> &A,set<int> &B){
    set<int> C;
    set<int>::iterator itA = A.begin(); 
    while(itA != A.end()){ 
        if(B.find(*itA) != B.end()){ 
            C.insert(*itA); 
        }
        ++itA; 
    }
    return C;
}
set<int> set_difference(set<int> &A,set<int> &B){
    set<int> C;
    set<int>::iterator itA = A.begin(); 
    while(itA != A.end()){ 
        if(B.find(*itA) == B.end()){ 
            C.insert(*itA); 
        }
        ++itA; 
    }
    return C;
}//
/*
void equal(vector<set<int>> &VS, int &count){
  
  for(auto it = VS.begin(); it != VS.end() ; it++){

    for(auto S0 = VS.begin(); S0 != VS.end() ; S0++){
      auto aux = set_difference(*it,S0);
      auto aux2= set_difference(S0,*it);

      if(aux.empty() && aux2.empty()) count++;
    }
  }
  count--;
}//


void superset(vector<set<int>> &VS, int &count){
  
  for(auto it = VS.begin(); it != VS.end() ; it++){
    for(auto S0 = VS.begin(); S0 != VS.end() ; S0++){
      auto aux = set_difference(S0,*it);
      auto aux2 = set_difference(*it,S0);
      if( !(aux.empty()) != !(aux2.empty()) ) count++;
    }
  }
}//

void disjoint(vector<set<int>> &VS, int &count){
  
  for(auto it = VS.begin(); it != VS.end() ; it++){
    for(auto S0 = VS.begin(); S0 != VS.end() ; S0++){
      auto aux = set_intersection(S0,*it);
      if( aux.empty() ) count++;
    }
  }
}//

void subset(vector<set<int>> &VS, int &count){
  
  for(auto it = VS.begin(); it != VS.end() ; it++){
    for(auto S0 = VS.begin(); S0 != VS.end() ; S0++){
      auto aux = set_intersection(S0,*it);
      if (!(aux.size() == S0->size()) != !(aux.size() == it->size() && it->size() != S0->size()))
      {
        count++;
      }
    }
  }
}//
*/
void set_classify(vector<set<int>> &VS,set<int> &S0,
                  int &asuperset,int &asubset,int &adisjoint,
                  int &aequal,int &aother) {
  asuperset = 0; asubset = 0; adisjoint = 0; aequal = 0;
  aother = 0;
/*
  superset(VS,asuperset);
  subset(VS,asubset);
  disjoint(VS,adisjoint);
  equal(VS,aequal);
*/
  
  for(auto it = VS.begin(); it != VS.end() ; it++){
      auto auxsub = set_difference(*it,S0);
      auto auxsub2 = set_difference(S0,*it);
      
      auto auxad = set_intersection(S0,*it);
      
      auto auxsuper = set_difference(S0,*it);
      auto aux2super = set_difference(*it,S0);
      
      auto auxeq = set_difference(*it,S0);
      auto aux2eq= set_difference(S0,*it);
      
      if ((auxsub.size() == 0) && (auxsub2.size() != 0) )
      {
        asubset++;
      }else if( auxad.empty() )
      { 
        adisjoint++;
      }else if( (auxsuper.empty()) xor (aux2super.empty()) )
      { 
        asuperset++;
      }else if(auxeq.empty() && aux2eq.empty()){ 
        aequal++;
      }else{
       aother++;
      }
  }

}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int main() {
  Eval ev;
  int vrbs=0;
  ev.eval<1>(set_classify,vrbs);
  return 0;
}
