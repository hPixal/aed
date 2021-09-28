#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
using namespace std;

bool is_strange(list<int>& List){
  auto first = List.begin(); 
  auto last = List.end();
  auto var = max_element(first,last);
  auto max = *var;

  auto itl1 = List.begin();
  auto itl2 = List.begin();
  
  while(itl1 != List.end()){
    itl2 = List.begin();
    while (itl2 != List.end())
    {
      if (abs(abs(*itl1)-abs(*itl2))>max)
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
  if(L.empty()){
    return;
  }
  SL = {*(L.begin())};
  auto it1 = L.begin();
  while( it1 != prev(L.end())){
    list<int> auxlist = {*it1};
    auto itl2 = next(it1);
    while(itl2 != L.end()){
      auxlist.push_back(*itl2);
      if(is_strange(auxlist) && auxlist.size() > SL.size()){
        SL=auxlist;
      }
      ++itl2;
    }
    it1++;
  }
}

int main(){
    vector<list<int>> prueba;
    list<int> a = {0,4,-2,4,1};
    list<int> b = {-1,-4,-4,-3,-1};
    list<int> c = {1,-9,9,1,-3,-7,6,-8,-4,-2,-4};
    list<int> d = {0,3,-2,4,-5};
    list<int> f = {-5,-5,-1,-3,-2};
    /*
    prueba.push_back(a);
    prueba.push_back(b);
    prueba.push_back(c);
    prueba.push_back(d);
    prueba.push_back(f);
    */
    list<int> prueba2;
    strange_sublist(c,f);
    //sign_join(prueba,prueba2);
    return 0;
}