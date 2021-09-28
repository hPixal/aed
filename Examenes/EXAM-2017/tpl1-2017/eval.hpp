// GITVERSION: aed-3.1-44-g8bbf219a
#ifndef EVAL_HPP
#define EVAL_HPP
#include <cassert>
#include <cstdlib>
#include "aedtools/evalbase.hpp"
using namespace std;

namespace aed {

  list<int>::iterator string_to_iterator(list<int> &L, string str) {
    if (str=="begin") return L.begin();
    if (str=="end") return L.end();
    assert(str.find("begin+")==0);
    list<int>::iterator it = L.begin();
    advance(it,atoi(str.substr(6).c_str()));
    return it;
  }
  
  string iterator_to_string(list<int> &L, list<int>::iterator it) {
    if (it==L.end()) return "end";
    int n = std::distance(L.begin(),it);
    if (n==0) return "begin";
    return string("begin+")+to_string(n);
  }
  
  list<int>::iterator my_advance(list<int> &L, int n) {
    list<int>::iterator it = L.begin();
    std::advance(it,n);
    return it;
  }
  
  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
  using extract_range_t = void (*)(list<int> &, list<int>::iterator, list<int>::iterator, list<int> &);
  class eval1_t : public eval_base_t {
  public:
    extract_range_t F;
    eval1_t() { dumptests=0; F=NULL; ejerc=1; testfile="./xr.json"; }
    void run_case(json &data,json &outuser) {
      list<int> L1 = data["L1"], L2;
      list<int>::iterator p = string_to_iterator(L1,data["p"]);
      list<int>::iterator q = string_to_iterator(L1,data["q"]);
      F(L1,p,q,L2);
      outuser["L1"] = L1;
      outuser["L2"] = L2;
    }

    int check_case(json &datain,
                   json &outref,json &outuser) {
      return outref==outuser;
    }
    
    void generate_case(randomg_t &rnd,json &datain) {
      int n=3+rnd.rand()%12;
      list<int> L1;
      for(int i=0;i<n;i++) L1.push_back(rnd.rand()%10);
      list<int>::iterator p = my_advance(L1,rnd.rand()%(n+1));
      list<int>::iterator q = my_advance(L1,rnd.rand()%(n+1));
      datain["L1"] = L1;
      datain["p"] = iterator_to_string(L1,p);
      datain["q"] = iterator_to_string(L1,q);
      if (p!=L1.end()) datain["*p"] = *p;
      if (q!=L1.end()) datain["*q"] = *q;
    }
  };

  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
  using add_elements_t = int (*)(list<int>&, stack<int> &);
  class eval2_t : public eval_base_t {
  public:
    add_elements_t F;
    eval2_t() { dumptests=0; F=NULL; ejerc=2; testfile="./ae.json"; }
    void run_case(json &data,json &outuser) {
      list<int> L = data["L"];
      list<int> lS = data["S"];
      stack<int> S; for(int x:lS) S.push(x);
      int ret = F(L,S);
      outuser["L"] = L;
      outuser["ret"] = ret;
    }
    
    int check_case(json &datain,
                   json &outref,json &outuser) {
      return outref==outuser;
    }
    
    void generate_case(randomg_t &rnd,json &datain) {
      int nl=3+rnd.rand()%10;
      int ns=2+rnd.rand()%5;
      list<int> L, S;
      for(int i=0;i<nl;i++) L.push_back(rnd.rand()%19-9);
      for(int i=0;i<ns;i++) S.push_back(rnd.rand()%19-9);
      L.sort();
      datain["L"] = L;
      datain["S"] = S;
    }
  };

  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
  typedef bool (*coprimos_t)(list<int> &L);
  class eval3_t : public eval_base_t {
  public:
    coprimos_t F;
    eval3_t() { dumptests=0; F=NULL; ejerc=3; testfile="./cpr.json"; }
    void run_case(json &data,json &outuser) {
      list<int> L = data["L"];
      bool b = F(L);
      outuser["ret"] = b?"true":"false";
    }
    
    int check_case(json &datain,
                   json &outref,json &outuser) {
      return outref==outuser;
    }
    
    void generate_case(randomg_t &rnd,json &datain) {
      list<int> L;
      int n = 3 + rnd.rand()%5;
      for (int j=0; j<n; j++) {
        L.push_back(2+rnd.rand()%50);
      }
      datain["L"] = L;
    }
  };
  
  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
  using Eval = eval_t<eval1_t,extract_range_t,
                      eval2_t,add_elements_t,
                      eval3_t,coprimos_t>;
}
#undef CSTR

#define sort NO_SE_VALE_USAR_EL_SORT_DE_LA_STL
#define stable_sort NO_SE_VALE_USAR_EL_SORT_DE_LA_STL

#endif
