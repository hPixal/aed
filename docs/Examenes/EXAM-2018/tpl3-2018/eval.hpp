// GITVERSION: aed-3.1-303-gae0893b2
#ifndef EVAL_HPP
#define EVAL_HPP
#include "aedtools/evalbase.hpp"
#include "aedtools/str_convs.hpp"
#include <forward_list>
#include <sstream>
#include <algorithm>
using namespace std;

namespace aed {

  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
  //   FUNCTIONS FOR THIS EXAM
  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>

  class map_fun_t {
  public:
    virtual int f(int)=0;
  };
  
  typedef btree<int>::iterator bnode_t;
  void apply(btree<int> &T,bnode_t n,map_fun_t &mf) {
    if (n==T.end()) return;
    *n = mf.f(*n);
    apply(T,n.left(),mf);
    apply(T,n.right(),mf);
  }
  
  void apply(btree<int> &T,map_fun_t &mf) {
    apply(T,T.begin(),mf);
  }

  class rest_val_t : public map_fun_t {
  public:
    int val;
    int f(int x) { return x-val; }
  };

  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
  // END FUNCTIONS FOR THIS EXAM
  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>

  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*> MAKE-FULL
#undef EJERC
#undef EVAL
#define EJERC 1
#define EVAL eval1_t
  typedef void (*make_full_t)(btree<int> &T);
  class EVAL : public eval_base_t {
  public:
    make_full_t F;
    EVAL() { dumptests=0; F=NULL; ejerc=EJERC; testfile="./mf.json"; }
    void run_case(json &data,json &outuser) {
      // Extract the input tree from DATA
      btree<int> T;
      string sT = data["T"];
      lisp2btree(sT,T);
      // Call the user function
      F(T);
      // Store the user output
      outuser["T"] = lisp_print(T);
    }
    
    int check_case(json &datain,
                   json &outref,json &outuser) {
      // WARNING: In this case we can't compare plainly the
      // data stored in the JSON because they are simply
      // strings and may not be unique.
      return outref==outuser;
    }

    void generate_case(randomg_t &rnd,json &datain) {
      btree<int> T;
      int m = 9;
      double s = 1.5;
      make_random_btree(T,m,s,rnd);
      datain["T"] = lisp_print(T);
    }
  };

  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*> MAX-SUBBTREE
#undef EJERC
#undef EVAL
#define EJERC 2
#define EVAL eval2_t
  typedef int (*max_subbtree_t)(btree<int>&T);
  class EVAL : public eval_base_t {
  public:
    max_subbtree_t F;
    EVAL() { dumptests=0; F=NULL; ejerc=EJERC; testfile="./ms.json"; }
    void run_case(json &data,json &outuser) {
      // Extract the input tree from DATA
      btree<int> T;
      string sT = data["T"];
      lisp2btree(sT,T);
      // Store the user output
      outuser["retval"] = F(T);
    }
    
    int check_case(json &datain,
                   json &outref,json &outuser) {
      // WARNING: In this case we can't compare plainly the
      // data stored in the JSON because they are simply
      // strings and may not be unique.
      return outref==outuser;
    }

    void generate_case(randomg_t &rnd,json &datain) {
      btree<int> T;
      int m = 9;
      double s = 1.5;
      make_random_btree(T,m,s,rnd);
      rest_val_t r;
      r.val = 5;
      // cout << "before apply: " << lisp_print(T) << endl;
      apply(T,r);
      // cout << "after apply: " << lisp_print(T) << endl;
      datain["T"] = lisp_print(T);
    }
  };

  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*> MOST-CONNECTED
#undef EJERC
#undef EVAL
#define EJERC 3
#define EVAL eval3_t
  typedef int (*most_connected_t)(vector< set<int> > &VS);
  class EVAL : public eval_base_t {
  public:
    most_connected_t F;
    EVAL() { dumptests=0; F=NULL; ejerc=EJERC; testfile="./mc.json"; }
    void run_case(json &data,json &outuser) {
      // Extract the input tree from DATA
      vector< set<int> > VS;
      json &jVS = data["VS"];
      for (auto jvsj:jVS) {
        set<int> s = jvsj;
        VS.push_back(s);
      }
      // Call the user function
      outuser["retval"] = F(VS);
    }
    
    void generate_case(randomg_t &rnd,json &datain) {
      int nset = 5+rnd.rand()%10;
      for (int j=0; j<nset; j++) {
        set<int> s;
        int m= 1+rnd.rand()%3;
        for (int k=0; k<m; k++)
          s.insert(rnd.rand()%10);
        datain["VS"].push_back(s);
      }
    }
  };
  
  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
  using Eval = eval_t<eval1_t,make_full_t,
                      eval2_t,max_subbtree_t,
                      eval3_t,most_connected_t>;
}
#undef CSTR

#endif
