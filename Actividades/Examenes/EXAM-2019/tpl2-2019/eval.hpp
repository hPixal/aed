// GITVERSION: tpl2-2019-15-g9107c30f
#ifndef EVAL_HPP
#define EVAL_HPP
#include "aedtools/evalbase.hpp"
#include "aedtools/str_convs.hpp"
#include <forward_list>
#include <sstream>
#include <algorithm>
using namespace std;

namespace aed {

  typedef map<char,list<char>> graph;
  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
  //   FUNCTIONS FOR THIS EXAM
  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>

  template<typename T>
  std::string tree2lisp(tree<T> &A, typename tree<T>::iterator it) {
    std::stringstream ss;
    if (it.lchild()==A.end()) ss << *it;
    else {
      ss << "(" << *it;
      for(auto it2=it.lchild();it2!=A.end();++it2)
        ss << " " << tree2lisp(A,it2);
      ss << ")";
    }
    return ss.str();
  }
  
  template<typename T>
  std::string tree2lisp(tree<T> &A) {
    // if (A.begin()==A.end()) return "()";
    if (A.begin()==A.end()) return "";
    // return std::string("("+tree2lisp(A,A.begin())+")");
    return tree2lisp(A,A.begin());
  }

  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
  // END FUNCTIONS FOR THIS EXAM
  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
  
  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*> SIGN_SPLIT
#undef EJERC
#undef EVAL
#define EJERC 1
#define EVAL eval1_t
  typedef void (*fill_ordprev_t)(tree<int> &T,list<int> &L);
  class EVAL : public eval_base_t {
  public:
    fill_ordprev_t F;
    EVAL() { dumptests=0; F=NULL; ejerc=EJERC; testfile="./fo.json"; }
    void run_case(json &data,json &outuser) {
      tree<int> T;
      lisp2tree(data["T"],T);
      list<int> L = data["L"];
      F(T,L);
      outuser["Tout"] = tree2lisp(T);
    }
    
    int check_case(json &datain,
                   json &outref,json &outuser) {
      return outref==outuser;
    }
    
    void generate_case(randomg_t &rnd,json &datain) {
      tree<int> T;
      int m = 5+rnd.rand()%10; int n = 5+rnd.rand()%10;
      make_random_tree2(T,100,m,n,rnd);
      int sz = 10+rnd.rand()%10;
      list<int> L;
      for (int j=0; j<sz; j++) L.push_back(rnd.rand()%20);
      datain["T"] = tree2lisp(T);
      datain["L"] = L;
    }
  };
  
#undef EJERC
#undef EVAL
#define EJERC 2
#define EVAL eval2_t
  typedef void (*a_lo_ancho_t)(graph& G, tree<char>& T);
  class EVAL : public eval_base_t {
  public:
    a_lo_ancho_t F;
    EVAL() { dumptests=0; F=NULL; ejerc=EJERC; testfile="./ao.json"; }
    void run_case(json &data,json &outuser) {
      tree<char> T;
      auto G = str2graph<std::list<char>>(data["G"]);
      F(G,T);
      outuser["Tout"] = tree2lisp(T);
    }
    
    int check_case(json &datain,
                   json &outref,json &outuser) {
      return outref==outuser;
    }
    
    void generate_case(randomg_t &rnd,json &datain) {
      int prob = 2+rnd.rand()%8;
      int Nvertex = 3+rnd.rand()%10;
      graph G;
      while(G.empty()){
        for(int i=0;i<Nvertex;i++){
          for(int j=i+1;j<Nvertex;j++){
            if(rnd.rand()%10>=prob){
              char vi = 'a'+i;
              char vj = 'a'+j;
              G[vi].push_back(vj);
              G[vj].push_back(vi);
            }        
          }
        }      
      }
      datain["G"] = graph2str(G);
    }
  };

#undef EJERC
#undef EVAL
#define EJERC 3
#define EVAL eval3_t
  typedef void (*intersect_map_t)(map<int,list<int>> &A, 
                                map<int,list<int>> &B,
                                map<int,list<int>> &C);
  class EVAL : public eval_base_t {
  public:
    intersect_map_t F;
    EVAL() { dumptests=0; F=NULL; ejerc=EJERC; testfile="./im.json"; }
    void run_case(json &data,json &outuser) {
      auto A = str2graph<std::list<int>>(data["A"]);
      auto B = str2graph<std::list<int>>(data["B"]);
      map<int,list<int>> C;
      F(A,B,C);
      outuser["C"] = graph2str(C);
    }
    
    int check_case(json &datain,
                   json &outref,json &outuser) {
      auto G1 = str2graph<std::list<int>>(outuser["C"]);
      //for(auto &p:G1) p.second.sort();
      auto G2 = str2graph<std::list<int>>(outref["C"]);
      //for(auto &p:G2) p.second.sort();
      return G1==G2;
    }
    
    void generate_case(randomg_t &rnd,json &datain) {
      int prob = 5;
      int Nvertex = 3+rnd.rand()%10;
      map<int,list<int>> A,B;
      while(A.empty()){
        for(int i=0;i<Nvertex;i++){
          if(rnd.rand()%10>=5){
            for(int j=0;j<Nvertex;j++){
              if(rnd.rand()%10>=prob){
                A[i].push_back(j);
              }
            }
          }
        }
      }
      while(B.empty()){
        for(int i=0;i<Nvertex;i++){
          if(rnd.rand()%10>=5){
            for(int j=0;j<Nvertex;j++){
              if(rnd.rand()%10>=prob){
                B[i].push_back(j);
              }
            }
          }
        }
      }
      datain["A"] = graph2str(A);
      datain["B"] = graph2str(B);
    }
  };
  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
  using Eval = eval_t<eval1_t,fill_ordprev_t,
                      eval2_t,a_lo_ancho_t,
                      eval3_t,intersect_map_t>;
}
#undef CSTR

#endif
