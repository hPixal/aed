// GITVERSION: aed-2021-20-g2e7da217
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
#define EJERC 3
#define EVAL eval1_t
  
  typedef void (*primos_t)(list<int> &L,stack<int> &S);
  class eval1_t : public eval_base_t {
  public:
    primos_t F;
    eval1_t() { dumptests=1; F=NULL; ejerc=EJERC; testfile="./sp.json"; }
	
    void run_case(json &data, json &outuser) {
    check_dni();
	  list<int> L = data["L"];
	  stack<int> S;
    F(L,S);

	  json z = json::array();
	  while (!S.empty()) {
		  z.push_back(S.top());
		  S.pop();
	  }
	  outuser["S"] = z;
    
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
    }
  };
  
  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
  using Eval = eval_t<eval1_t,primos_t>;
}
#undef CSTR

#endif
