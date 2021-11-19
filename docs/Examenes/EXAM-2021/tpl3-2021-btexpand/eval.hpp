// GITVERSION: aed-2021-137-g25d89fc3
#ifndef EVAL_HPP
#define EVAL_HPP
#include "aedtools/evalbase.hpp"
#include "aedtools/str_convs.hpp"
#include <forward_list>
#include <sstream>
using namespace std;

namespace aed {

  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
  //   FUNCTIONS FOR THIS EXAM
  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>

  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
  // END FUNCTIONS FOR THIS EXAM
  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
  
  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
#undef EJERC
#undef EVAL
#define EJERC 1
#define EVAL eval1_t
  
  typedef void (*btexpand_t)(btree<int> &B,int root,mapfun_t);
  class eval1_t : public eval_base_t {
  public:
    btexpand_t F;
    eval1_t() { dumptests=0; F=NULL; ejerc=EJERC; testfile="./btx.json"; }
    void run_case(json &data, json &outuser) {
      check_dni();

      int root=data["root"];
      string sf = data["f"];
      mapfun_t f=NULL;
      if (sf=="f1") f=f1;
      else if (sf=="f2") f=f2;
      else if (sf=="f3") f=f3;
      assert(f);
      btree<int> B;
      F(B,root,f);
      outuser["B"] = btree2lisp(B);
    }
    
    int check_case(json &datain,
                   json &outref,json &outuser) {
      return outref==outuser;
    }

    void generate_case(randomg_t &rnd,json &datain) {
      btree<int> T;
      int jfun= rnd.rand()%3+1;
      mapfun_t f=NULL;
      if (jfun==1) f=f1;
      if (jfun==2) f=f2;
      if (jfun==3) f=f3;
      assert(f);
      datain["f"] = "f"+to_string(jfun);
      datain["root"] = 1+rnd.rand()%5;
    }
  };
  
  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
  using Eval = eval_t<eval1_t,btexpand_t>;
}
#undef CSTR

#endif
