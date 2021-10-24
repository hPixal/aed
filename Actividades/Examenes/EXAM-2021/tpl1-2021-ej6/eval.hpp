// GITVERSION: aed-2021-11-gee3de77a
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
  
  typedef void (*strange_sublist_t)(list<int> &L,list<int> &SL);
  class eval1_t : public eval_base_t {
  public:
    strange_sublist_t F;
    eval1_t() { dumptests=0; F=NULL; ejerc=EJERC; testfile="./sl.json"; }
    void run_case(json &data, json &outuser) {
      check_dni();

      list<int> L = data["L"];
      list<int> SL;
      F(L,SL);
      json VLj;
      //for (auto &L : L) VLj.push_back(json(L));
      //outuser["VL"] = VLj;
      outuser["SL"] = SL;
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
        int z = -10 + rnd.rand()%21;
        if (rnd.rand()%5>=2) z += -(z%2) + x%2;
        x=z;
        v.push_back(z);
      }
      datain["L"] = v;
    }
  };
  
  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
  using Eval = eval_t<eval1_t,strange_sublist_t>;
}
#undef CSTR

#endif
