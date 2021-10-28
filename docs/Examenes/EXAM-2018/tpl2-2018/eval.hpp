// GITVERSION: aed-3.1-266-g32e98a78
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

  template<typename TKey, typename TValue>
  void str2map(std::map<TKey,TValue> &M, const std::string &s) {
    TKey clave; TValue valor;
    for(size_t i=1, p0=1;i<s.size();i++) { 
      if (s[i]==','||s[i]==')') {
        string spar = s.substr(p0,i-p0);
        spar.replace(spar.find("->"),2," ");
        std::stringstream ss(spar);
        ss>>clave>>valor;
        M[clave] = valor;
        p0=i+1;
      }
    }
  }
  
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

  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*> CLASSIFY_RELATIVE
#undef EJERC
#undef EVAL
#define EJERC 1
#define EVAL eval1_t
  typedef void (*classify_relative_t)(tree<int> &T,int n1,int n2,int &m1, int&m2);
  class EVAL : public eval_base_t {
  public:
    classify_relative_t F;
    EVAL() { dumptests=0; F=NULL; ejerc=EJERC; testfile="./cr.json"; }
    void run_case(json &data,json &outuser) {
      tree<int> T;
      // Unpack the data. First the tree
      lisp2tree(data["T"],T);
      // The node labels
      int n1 = data["n1"];
      int n2 = data["n2"];
      // Call the suer function
      int m1,m2;
      F(T,n1,n2,m1,m2);
      // Store the user output
      outuser["m1"] = m1;
      outuser["m2"] = m2;
    }
    
    int check_case(json &datain,
                   json &outref,json &outuser) {
      return outref==outuser;
    }

    // Relabel the nodes with a consecutive index in preorder.
    // As a side effect the labels are unique,
    // Recursive function. Receives n as the index of the root
    // and returns n+(nbr of nodes)
    void preorder_renum(tree<int> &T,tree<int>::iterator q,int &n) {
      if (q==T.end()) return;
      // Assign the given index to the node and increment
      *q = n++;
      // Apply recursively to the nodes
      auto c=q.lchild();
      while (c!=T.end()) preorder_renum(T,c++,n);
    }

    // Wrapper
    int preorder_renum(tree<int> &T) {
      int n=0;
      preorder_renum(T,T.begin(),n);
      return n;
    }
    
    void generate_case(randomg_t &rnd,json &datain) {
      tree<int> T;
      int m = 5+rnd.rand()%10; int nn = 5+rnd.rand()%10;
      // Generate a random tree
      make_random_tree2(T,100,m,nn,rnd);
      // Relabel in preorder (just to have unique labels)
      int n = preorder_renum(T);
      // Get two random labels
      int
        n1 = rnd.rand()%n,
        n2 = rnd.rand()%n;
      // Load in the Json data
      datain["T"] = tree2lisp(T);
      datain["n1"] = n1;
      datain["n2"] = n2;
    }
  };

  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*> PROM_PATH
#undef EJERC
#undef EVAL
#define EJERC 2
#define EVAL eval2_t
  static std::string float2string(float f) {
    std::stringstream ss; ss << std::setprecision(2) << std::fixed << f; return ss.str();
  }
  
  typedef float (*prom_path_t)(tree<int> &T);
  class EVAL : public eval_base_t {
  public:
    prom_path_t F;
    EVAL() { dumptests=0; F=NULL; ejerc=EJERC; testfile="./pp.json"; }
    void run_case(json &data,json &outuser) override {
      tree<int> T;
      lisp2tree(data["T"],T);
      float f = F(T);
      outuser["p"] = float2string(f);
    }

    void generate_case(randomg_t &rnd,json &datain) override {
      tree<int> T;
      int m = 5+rnd.rand()%10; int n = 5+rnd.rand()%10;
      make_random_tree2(T,100,m,n,rnd);
      datain["T"] = lisp_print(T);
    }
  };

  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*> MAP_GRAPH
#undef EJERC
#undef EVAL
#define EJERC 3
#define EVAL eval3_t
  typedef void (*filtra_deps_t)(std::map<std::string,std::list<std::string> > &G,
                                std::list<std::string> &L);
  class EVAL : public eval_base_t {
    
  public:
    filtra_deps_t F;
    EVAL() { dumptests=0; F=NULL; ejerc=EJERC; testfile="./fd.json"; }
    void run_case(json &data,json &outuser) override {
      auto G = str2graph<std::list<std::string>>(data["G"]);
      std::list<std::string> L = str2cont<std::list<std::string>>(data["L"]);
      F(G,L);
      outuser["G"] = graph2str(G);
    }
    
    int check_case(json &data, json &outuser, json &outref) override {
      // rearmo los grafos para que no importe el orden en el string
      auto G1 = str2graph<std::list<std::string>>(outuser["G"]);
      for(auto &p:G1) p.second.sort();
      auto G2 = str2graph<std::list<std::string>>(outref["G"]);
      for(auto &p:G2) p.second.sort();
      return G1==G2;
      
    }

    void generate_case(randomg_t &rnd,json &datain) {
      // lista de paquetes
      std::vector<std::string> v(5+rnd.rand()%10,"aaa");
      for(size_t i=0;i<v.size();i++) v[i][0]=v[i][1]=v[i][2]='a'+i;
      random_shuffle(rnd,v);
      // grafo de dependencias
      std::map<std::string,std::list<std::string>> G;
      for(size_t i=0;i<v.size();i++) { 
        auto &D = G[v[i]];
        for(size_t j=0;j<v.size();j++) { 
          if (rnd.rand()%4==0) D.push_back(v[j]);
        }
      }
      // selección para L
      random_shuffle(rnd,v); v.resize(1+rnd.rand()%(v.size()/2));
      datain["G"] = graph2str(G);
      datain["L"] = cont2str(v);
    }
  };
  
  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
  using Eval = eval_t<eval1_t,classify_relative_t,
                      eval2_t,prom_path_t,
                      eval3_t,filtra_deps_t>;
}
#undef CSTR

#endif
