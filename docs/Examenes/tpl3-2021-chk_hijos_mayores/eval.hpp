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

  void force(btree<int> &T,btree<int>::iterator n,
             mapfun_t f,randomg_t &rnd) {
    if (n==T.end()) return;
    auto cl=n.left();
    auto cr=n.right();
    unsigned int prob=50;
    if (cl!=T.end() && rnd.rand()%100<prob) *cl=f(*n);
    if (cr!=T.end() && rnd.rand()%100<prob) *cr=f(*n);
    force(T,cl,f,rnd);
    force(T,cr,f,rnd);
  }
  
  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
  // END FUNCTIONS FOR THIS EXAM
  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
  
  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
#undef EJERC
#undef EVAL
#define EJERC 1
#define EVAL eval1_t
  
  typedef bool (*chk_hijos_mayores_t)(btree<int> &T);
  class eval1_t : public eval_base_t {
  public:
    chk_hijos_mayores_t F;
    eval1_t() { dumptests=0; F=NULL; ejerc=EJERC; testfile="./chkhm.json"; }
    void run_case(json &data, json &outuser) {
      check_dni();

      btree<int> T;
      lisp2btree(data["T"],T);
      outuser = F(T);
    }
    
    int check_case(json &datain,
                   json &outref,json &outuser) {
      return outref==outuser;
    }

    void generate_case(randomg_t &rnd,json &datain) {
      btree<int> T;
      make_random_btree(T,10,1.5,rnd);
    
      datain["T"] = btree2lisp(T);
    }
  };
  
  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
  using Eval = eval_t<eval1_t,chk_hijos_mayores_t>;
}
#undef CSTR

#endif
