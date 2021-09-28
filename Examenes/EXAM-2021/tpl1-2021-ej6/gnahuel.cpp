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
// Nombre: Gareis Nahuel Julian
int DNI=43538493;

bool is_strange(list<int>& List);

list<int> getbiggest(vector<list<int>> &l){
  auto it = l.begin();
  auto rtrn = l.begin();
  while(it != l.end()){
    if (it->size() > rtrn->size() && is_strange(*it))
    {
      rtrn = it;
    }
    ++it;
  }
  it = l.begin();
  while(it != l.end()){
    if ((it->size() == rtrn->size() ) && is_strange(*it))
    {
      return *it;
    }
    ++it;
  }
  return *rtrn;
}
  
  int getMax(list<int>& List){
    auto it = List.begin();
    int max = *List.begin();
    while (it != List.end())
    {
      if (*it > max)
      {
        max = *it;
      }
      ++it;
    }
    return max;
  }
    
    bool is_strange(list<int>& List){
      int max = getMax(List);
      auto itl1 = List.begin();
      auto itl2 = List.begin();
      
      while(itl1 != List.end()){
        itl2 = List.begin();
        while (itl2 != List.end())
        {
          if (abs(*itl1-*itl2)>max)
          {
            return false;
          }      
          itl2++;
        }
        itl1++;
      }
      return true;
    }
      
      void strange_sublist(list<int>& L,list<int>& SL)
      {
        SL.clear();
        if(is_strange(L))
        { return swap(L,SL); }
        
        auto itl1 = L.begin();
        auto itl2 = L.begin();
        auto itl3 = L.begin();
        
        
        list<int> auxlist;
        vector<list<int>> auxvec;
        
        while(itl1 != L.end())
        {
          itl2 = L.begin();
          while (itl2 != L.end())
          {
            itl3 = L.begin();
            while(itl3 != L.end())
            {
              if(*itl1 < abs(*itl2 - *itl3)){
                auxlist.push_back(*itl3);
              }
              itl3++;
            }
            if (!auxlist.empty())
            {
              auxvec.push_back(auxlist);
              auxlist.clear();
            }
            itl2++;
          }
          itl1++;
        }
        SL = getbiggest(auxvec);
      }

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int main() {
  Eval ev;
  int vrbs = 0;
  ev.eval<1>(strange_sublist,vrbs);
  return 0;
}
