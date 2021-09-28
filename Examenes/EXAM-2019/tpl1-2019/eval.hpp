// GITVERSION: tpl-recup-2018-11-22-39-g5ad2259f
#ifndef EVAL_HPP
#define EVAL_HPP
#include "aedtools/evalbase.hpp"
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
  
  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*> SIGN_SPLIT
#undef EJERC
#undef EVAL
#define EJERC 1
#define EVAL eval1_t
  typedef list<vector<int>> (*Pareto_t)(list<vector<int>> &P);
  class EVAL : public eval_base_t {
  public:
    Pareto_t F;
    EVAL() { dumptests=0; F=NULL; ejerc=EJERC; testfile="./par.json"; }
    void run_case(json &data,json &outuser) {
      list<vector<int>> P = data["L"];
      list<vector<int> > Pout = F(P);
      json Pj;
      for (auto p:Pout) {
        json aux = p;
        Pj.push_back(aux);
      }
      outuser["Lout"] = Pj;
    }
    
    int check_case(json &datain,
                   json &outref,json &outuser) {
      return outref==outuser;
    }
    
    void generate_case(randomg_t &rnd,json &datain) {
      list<vector<int>> P;
      int ndim = rnd.rand()%2+2; //2 o 3 dimensiones asi es mas facil
      int n = 5+rnd.rand()%10;
      for(int i=0;i<n;i++) {
        vector<int> p(ndim);
        for(int j=0;j<ndim;j++){
          p[j] = (rnd.rand()%(n/2))+1;
        }
        P.push_back(p);
      }
      datain["L"] = P;
    }
  };

  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*> MERGE-KWAY

#undef EJERC
#undef EVAL
#define EJERC 2
#define EVAL eval2_t
  typedef void (*merge_kway_t)(vector< queue<int> > &qords,
                               queue<int> &merged);
  class EVAL : public eval_base_t {
  public:
    merge_kway_t F;
    EVAL() { dumptests=0; F=NULL; ejerc=EJERC; testfile="./mkw.json"; }
    void run_case(json &data,json &outuser) {
      vector< queue<int> > VQ;
      json VLj = data["VQ"];
      for (auto &L : VLj) {
        queue<int> Q;
        for (auto z:L) Q.push(z);
        VQ.push_back(Q);
      }
      queue<int> Q;
      F(VQ,Q);
      list<int> lq;
      while (!Q.empty()) {
        lq.push_back(Q.front());
        Q.pop();
      }
      outuser["Q"] = lq;
    }
    
    int check_case(json &datain,
                   json &outref,json &outuser) {
      return outref==outuser;
    }
    
    void generate_case(randomg_t &rnd,json &datain) {
      // vector< queue<int> > VQ;
      // Nbr of queues in VQ
      datain.clear();
      int n = 3+rnd.rand()%3;
      for (int jl=0;jl<n;jl++) {
        list<int> L1;
        for (int i=0;i<n;i++) {
          int x = (rnd.rand()%10);
          L1.push_back(x);
        }
        L1.sort();
        json jl1 = L1;
        datain["VQ"].push_back(jl1);
      }
    }
  };

  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
#undef EJERC
#undef EVAL
#define EJERC 3
#define EVAL eval3_t
  typedef bool (*is_balanced_t)(string &c);
  class EVAL : public eval_base_t {
  public:
    is_balanced_t F;
    EVAL() { dumptests=0; F=NULL; ejerc=EJERC; testfile="./ib.json"; }
    void run_case(json &data,json &outuser) {
      string expr = data["expresion"];
      outuser["retval"] = F(expr);
    }
	  
    int check_case(json &datain,
                   json &outref,json &outuser) {
      return outref==outuser;
    }
	  
    void generate_case(randomg_t &rnd,json &datain) {
      int natom = 3+rnd.rand()%7;
      vector<string> exprs(natom);
      for (int j=0; j<natom; j++) 
        exprs[j] = to_string(rnd.rand()%100);
      while (exprs.size()>1) {
        // Chose a pair of balanced parentheses (i.e. [], {}, or ())
        int z = rnd.rand()%3;
        string par,oper;
        if (z==0) par="()";
        else if (z==1) par="[]";
        else if (z==2) par="{}";
        // Choose a random algebraic operator 
        z = rnd.rand()%4;
        if (z==0) oper="+";
        else if (z==1) oper="-";
        else if (z==2) oper="*";
        else if (z==3) oper="/";
        int ne = exprs.size();
        // Choose two random items from the current set of expressions
        int j1=rnd.rand()%ne, j2=j1;
        while (j2==j1) j2 = rnd.rand()%ne;
        string
          e1 = exprs[j1],
          e2 = exprs[j2];
        // Delete them from the array
        exprs.erase(exprs.begin()+j1);
        exprs.erase(exprs.begin()+j2);
        // The correct expression  should be: par[0]+e1+oper+e2+par[1]
        // We apply a random mutation
        string b=par.substr(0,1),e=par.substr(1,1);
        int M=30;
        int r=rnd.rand()%M;
        if (r==0) b = ""; // delete begin parentheses
        else if (r==1) b = par[1]; // replace begin by close
        else if (r==2) e = ""; // delete end
        else if (r==3) e = par[0]; // start is end
        else if (r==4) b = "{"; // start is end
        else if (r==5) e = "}"; // start is end
        exprs.push_back(b + e1 + oper + e2 + e);
      }
      datain["expresion"] = exprs[0];
    }
  };
  
  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
  using Eval = eval_t<eval1_t,Pareto_t,
                      eval2_t,merge_kway_t,
                      eval3_t,is_balanced_t>;
}
#undef CSTR
#define sort SORT_NO_DISPONIBLE

#endif
