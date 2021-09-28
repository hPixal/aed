// GITVERSION: aed-2021-26-g6b49601e
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
  
  typedef void (*xparity_t)(list<int> &L,int parity,vector<list<int>> &VL);
  class eval1_t : public eval_base_t {
  public:
    xparity_t F;
    eval1_t() { dumptests=0; F=NULL; ejerc=EJERC; testfile="./sp.json"; }
    void run_case(json &data, json &outuser) {
      check_dni();

      list<int> L = data["L"];
      int parity = data["parity"];
      vector<list<int>> VL;
      F(L,parity,VL);
      json VLj;
      for (auto &L : VL) VLj.push_back(json(L));
      outuser["VL"] = VLj;
    }
    
    int check_case(json &datain,
                   json &outref,json &outuser) {
      return outref==outuser;
    }

    void generate_case(randomg_t &rnd,json &datain) {
      vector<int> v;
      int n = 8+rnd.rand()%8;
      int x = rnd.rand()%2;
      for (int j=0; j<n; j++) {
        int z = rnd.rand()%20;
        if (rnd.rand()%5>=2) z += -(z%2) + x%2;
        x=z;
        v.push_back(z);
      }
      datain["L"] = v;
      datain["parity"] = rnd.rand()%2;
    }
  };
  
  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
  using Eval = eval_t<eval1_t,xparity_t>;
}
#undef CSTR

#endif
