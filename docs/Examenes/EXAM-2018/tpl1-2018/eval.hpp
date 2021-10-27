// GITVERSION: aed-3.1-231-g31efca31
#ifndef EVAL_HPP
#define EVAL_HPP
#include "evalbase.hpp"
#include <forward_list>
#include <sstream>
#include <algorithm>
using namespace std;

namespace aed {

  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
  //   FUNCTIONS FOR THIS EXAM
  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>

  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
  // END FUNCTIONS FOR THIS EXAM
  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>

// 1. powerlist
// 2. findperm
// 3. ruta-k
// 4. isnilpot
// 5. prombtree
// 6. is-perfect-split
  
  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*> SIGN_SPLIT
#undef EJERC
#undef EVAL
#define EJERC 1
#define EVAL eval1_t
  typedef void (*sign_split_t)(list<int> &L,vector< list<int> > &VL);
  class EVAL : public eval_base_t {
  public:
    sign_split_t F;
    EVAL() { dumptests=0; F=NULL; ejerc=EJERC; testfile="./sspl.json"; }
    void run_case(json &data,json &outuser) {
      list<int> L = data["L"];
      vector< list<int> > VL;
      json VLj;
      F(L,VL);
      for (auto q:VL) {
        json LL = q;
        VLj.push_back(LL);
      }
      outuser["VL"] = VLj;
    }
    
    int check_case(json &datain,
                   json &outref,json &outuser) {
      return outref==outuser;
    }
    
    void generate_case(randomg_t &rnd,json &datain) {
      list<int> L;
      int n = 10+rnd.rand()%10;
      for(int i=0;i<n;i++) {
        int x = (rnd.rand()%10)-5;
        L.push_back(x);
      }
      datain["L"] = L;
    }
  };

  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*> SIGN_JOIN
#undef EJERC
#undef EVAL
#define EJERC 2
#define EVAL eval2_t
  typedef void (*sign_join_t)(vector< list<int> > &VL,list<int> &L);
  class EVAL : public eval_base_t {
  public:
    sign_join_t F;
    EVAL() { dumptests=0; F=NULL; ejerc=EJERC; testfile="./sjn.json"; }
    void run_case(json &data,json &outuser) {
      vector< list<int> > VL;
      json VLj = data["VL"];
      for (auto q:VLj) {
        list<int> L1 = q;
        VL.push_back(L1);
      }
      list<int> L;
      F(VL,L);
      outuser["L"] = L;
    }
    
    int check_case(json &datain,
                   json &outref,json &outuser) {
      return outref==outuser;
    }
    
    void generate_case(randomg_t &rnd,json &datain) {
      vector< list<int> > VL;
      int n = 3+rnd.rand()%3;
      for (int jl=0;jl<n;jl++) {
        list<int> L1;
        for (int i=0;i<n;i++) {
          int x = (rnd.rand()%10)-5;
          L1.push_back(x);
        }
        VL.push_back(L1);
      }
      datain["VL"] = VL;
    }
  };

    //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*> SORT-STACK
#if 0  
#undef EJERC
#undef EVAL
#define EJERC 3
#define EVAL eval3_t
  typedef void (*sortStack_t)(stack<int>&S);
  class EVAL : public eval_base_t {
  public:
    sortStack_t F;
    EVAL() { dumptests=0; F=NULL; ejerc=EJERC; testfile="./sstk.json"; }
    void run_case(json &data,json &outuser) {
      list<int> LS = data["S"],LSout;
      LS.reverse();
      stack<int> S,S2;
      for (auto q:LS) S.push(q);
      F(S);
      S2 = S;
      while (!S2.empty()) {
        LSout.push_back(S2.top());
        S2.pop();
      }
      outuser["Sout"] = LSout;
    }
    
    int check_case(json &datain,
                   json &outref,json &outuser) {
      return outref==outuser;
    }
    
    void generate_case(randomg_t &rnd,json &datain) {
      int n = 5+rnd.rand()%5;
      list<int> L;
      for (int j=0;j<n;j++) L.push_back(rnd.rand()%20);
      datain["S"] = L;
    }
  };
#endif
  
    //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*> REVERSE-STACK
#undef EJERC
#undef EVAL
#define EJERC 3
#define EVAL eval3_t
  typedef void (*reverseStack_t)(stack<int>&S);
  class EVAL : public eval_base_t {
  public:
    reverseStack_t F;
    EVAL() { dumptests=0; F=NULL; ejerc=EJERC; testfile="./srev.json"; }
    void run_case(json &data,json &outuser) {
      list<int> LS = data["S"],LSout;
      LS.reverse();
      stack<int> S,S2;
      for (auto q:LS) S.push(q);
      F(S);
      S2 = S;
      while (!S2.empty()) {
        LSout.push_back(S2.top());
        S2.pop();
      }
      outuser["Sout"] = LSout;
    }
    
    int check_case(json &datain,
                   json &outref,json &outuser) {
      return outref==outuser;
    }
    
    void generate_case(randomg_t &rnd,json &datain) {
      int n = 5+rnd.rand()%5;
      list<int> L;
      for (int j=0;j<n;j++) L.push_back(rnd.rand()%20);
      datain["S"] = L;
    }
  };
  
  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
  using Eval = eval_t<
    eval1_t,sign_split_t,
    eval2_t,sign_join_t,
    eval3_t,reverseStack_t>;
}
#undef CSTR

#endif
