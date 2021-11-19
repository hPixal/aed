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
  
  typedef void (*set_classify_t)(vector<set<int>> &VS,set<int> &S0,
                  int &,int &,int &,int &,int &);
  class eval1_t : public eval_base_t {
  public:
    set_classify_t F;
    eval1_t() { dumptests=0; F=NULL; ejerc=EJERC; testfile="./sc.json"; }
    void run_case(json &data, json &outuser) {
      check_dni();
      vector<set<int>> VS;
      for (auto &jS : data["VS"]) {
        set<int> SS = jS;
        VS.push_back(SS);
      }
      set<int> S=data["S"];
      int superset,subset,disjoint,equal,other;
      F(VS,S,superset,subset,disjoint,equal,other);
      outuser["superset"]=superset;
      outuser["subset"]=subset;
      outuser["subset"]=subset;
      outuser["disjoint"]=disjoint;
      outuser["equal"]=equal;
      outuser["other"]=other;
    }
    
    int check_case(json &datain,
                   json &outref,json &outuser) {
      return outref==outuser;
    }

    void generate_case(randomg_t &rnd,json &datain) {
      int M=5,nset=4+rnd.rand()%6;
      json &jVS = datain["VS"];
      for (int k=0; k<nset; k++) {
        int m0=2+rnd.rand()%3;
        set<int> S0;
        for (int j=0; j<m0; j++) S0.insert(rnd.rand()%M);
        jVS.push_back(json(S0));
      }
      datain["S"] = jVS[0];
      // cout << S << endl;
      jVS.erase(jVS.begin());
      // cout << jVS << endl;
    }
  };
  
  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
  using Eval = eval_t<eval1_t,set_classify_t>;
}
#undef CSTR

#endif
