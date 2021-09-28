// GITVERSION: tpl2-2019-61-g71f85448
#ifndef EVAL_HPP
#define EVAL_HPP
#include "aedtools/evalbase.hpp"
#include "aedtools/str_convs.hpp"
#include <forward_list>
#include <sstream>
#include <algorithm>
#include <set>
#include <vector>
#include <map>
#include <list>
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
  
  template<typename T>
  std::string btree2lisp(btree<T> &A, typename btree<T>::iterator it) {
    std::stringstream ss;
    if (it.left()==A.end() and it.right()==A.end()) ss << *it;
    else {
      ss << "(" << *it;
      
      if (it.left()==A.end()) ss << " .";
      else ss << " " << btree2lisp(A,it.left());
      
      if (it.right()==A.end()) ss << " .";
      else ss << " " << btree2lisp(A,it.right());
      
      ss << ")";
    }
    return ss.str();
  }
  
  template<typename T>
  std::string btree2lisp(btree<T> &A) {
    // if (A.begin()==A.end()) return "()";
    if (A.begin()==A.end()) return "";
    // return std::string("("+tree2lisp(A,A.begin())+")");
    return btree2lisp(A,A.begin());
  }
  
  std::string charlist(list<char> &L) {
    std::stringstream ss;
    ss<<"{";
    for(auto c:L) ss<<c<<","<<endl;
    ss<<"}";
    return ss.str();
  }
  

  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
  // END FUNCTIONS FOR THIS EXAM
  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
  
  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*> SIGN_SPLIT
#undef EJERC
#undef EVAL
#define EJERC 1
#define EVAL eval1_t
  
  typedef list<int> (*mediaMovilEntera_t)(list<int>& L, int S);
  class eval1_t : public eval_base_t {
  public:
    mediaMovilEntera_t F;
    eval1_t() { dumptests=0; F=NULL; ejerc=1; testfile="./mme.json"; }
    void run_case(json &data,json &outuser) {
      list<int> L = data["L"];
      int S = data["v"];
      list<int> R = F(L,S);
      outuser["R"] = R;
    }
    
    int check_case(json &datain,
                   json &outref,json &outuser) 
    {
      return outuser==outref;
    }
    
    void generate_case(randomg_t &rnd,json &datain) {
      list<int> L;
      int n = 5+rnd.rand()%10, S=0;
      for(int i=0;i<n;i++) {
        int x = rnd.rand()%20;
        if (rnd.rand()%2==0) S+=x;
        L.push_back(x);
      }
      datain["L"] = L;
      datain["v"] = std::min<int>(L.size(),2+rnd.rand()%5);
    }
  };
  
#undef EJERC
#undef EVAL
#define EJERC 2
#define EVAL eval2_t
  
  typedef int (*nSumaK_t)(set<int>& S, int n);
  class eval2_t : public eval_base_t {
  public:
    nSumaK_t F;
    eval2_t() { dumptests=0; F=NULL; ejerc=2; testfile="./nsk.json"; }
    void run_case(json &data,json &outuser) {
      set<int> S = data["S"];
      int k = data["k"];
      int ret = F(S,k);
      outuser["ret"] = ret;
    }
    
    int check_case(json &datain,
                   json &outref,json &outuser) 
    {
      return outref==outuser;
    }
    
    void generate_case(randomg_t &rnd,json &datain) {
      set<int> S;
      int c = 2+rnd.rand()%6, n=0;
      for(int i=0;i<c;i++) {
        int x = rnd.rand()%11-5;
        S.insert(x);
        if (rnd.rand()%2) n += x;
      }
      if (rnd.rand()%2==0) n+=rnd.rand()%11-5;
      datain["S"] = S;
      datain["k"] = n;
    }
  };
  
//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>  
#undef EJERC
#undef EVAL
#define EJERC 3
#define EVAL eval3_t
  
  typedef int (*nCaminosK_t)(map<int,set<int>>& G, int a, int b, int k);
  class eval3_t : public eval_base_t {
  public:
    nCaminosK_t F;
    eval3_t() { dumptests=0; F=NULL; ejerc=3; testfile="./nck.json"; }
    void run_case(json &data,json &outuser) {
      map<int,set<int>> G = str2graph<std::set<int>>(data["G"]);
      int a = data["a"];
      int b = data["b"];
      int k = data["k"];
      int ret = F(G,a,b,k);
      outuser["ret"] = ret;
    }
    
    int check_case(json &datain,
                   json &outref,json &outuser) 
    {
      return outref==outuser;
    }
    
    void generate_case(randomg_t &rnd,json &datain) {
      int Nvertex = 3+rnd.rand()%3;
      map<int,set<int>> G;
      set<int> vertices;
      while(G.empty()){
        for(int i=0;i<Nvertex;i++){
          if(rnd.rand()%10>=5){
            for(int j=0;j<Nvertex;j++){
              if(rnd.rand()%10>=5){
                vertices.insert(i);
                vertices.insert(j);
                G[i].insert(j);
                G[j].insert(i);
              }
            }
          }
        }
      }
      
      auto it = vertices.begin();
      advance(it,rnd.rand()%vertices.size());
      int a = *it; 
      
      it = vertices.begin();
      advance(it,rnd.rand()%vertices.size());
      int b = *it;
      
      int k = rnd.rand()%G.size();

      datain["a"] = a;
      datain["b"] = b;
      datain["G"] = graph2str(G);
      datain["k"] = k;      
    }
  };

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>  
#undef EJERC
#undef EVAL
#define EJERC 4
#define EVAL eval4_t
  
  typedef void (*make_heap_t)(btree<int> &T);
  class EVAL : public eval_base_t {
  public:
    make_heap_t F;
    EVAL() { dumptests=0; F=NULL; ejerc=4; testfile="./mkh.json"; }
    void run_case(json &data,json &outuser) {
      btree<int> T;
      lisp2btree(data["T"],T);
      F(T);
      outuser["T"] = btree2lisp(T);
    }
    
    int check_case(json &datain,
                   json &outref,json &outuser) {
      return outref==outuser;
    }
    
    void generate_case(randomg_t &rnd,json &datain) {
      btree<int> T;
      make_random_btree(T,10,0.6,rnd);
      datain["T"] = btree2lisp(T);
    }
  };


  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>  
#undef EJERC
#undef EVAL
#define EJERC 5
#define EVAL eval5_t
  
  typedef void (*sortStack_t)(stack<int>& s);
  class EVAL : public eval_base_t {
  public:
    sortStack_t F;
    EVAL() { dumptests=0; F=NULL; ejerc=EJERC; testfile="./ssk.json"; }
    void run_case(json &data,json &outuser) {
      stack<int> S,S2;
      json Sj = data["S"];
      for (auto q : Sj) S2.push(q);
      while (!S2.empty()) {
        S.push(S2.top()); S2.pop();
      }
      F(S);
      // cout << S.size() << endl;
      json z = json::array();
      while (!S.empty()) {
        z.push_back(S.top());
        S.pop();
      }
      outuser["S"] = z;
      // cout << "z: " << z << endl;
    }
    
    int check_case(json &datain,
                   json &outref,json &outuser) {
      return outref==outuser;
    }
    
    void generate_case(randomg_t &rnd,json &datain) {
      int n = 5+rnd.rand()%5;
      list<int> S;
      for (int j=0; j<n; j++) S.push_back(rnd.rand()%20);
      datain["S"] = S;
    }
  };

  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
  using Eval = eval_t<eval1_t,mediaMovilEntera_t,
                      eval2_t,nSumaK_t,
                      eval3_t,nCaminosK_t,
                      eval4_t,make_heap_t,
                      eval5_t,sortStack_t>;
}
#undef CSTR

#endif
