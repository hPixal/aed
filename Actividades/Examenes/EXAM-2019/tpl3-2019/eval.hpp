// GITVERSION: tpl2-2019-52-g9b8020c4
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
  
  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
  template<typename T>
  std::string tree2lisp(tree<T> &A) {
    // if (A.begin()==A.end()) return "()";
    if (A.begin()==A.end()) return "";
    // return std::string("("+tree2lisp(A,A.begin())+")");
    return tree2lisp(A,A.begin());
  }
  
  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
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
  
  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
  template<typename T>
  std::string btree2lisp(btree<T> &A) {
    // if (A.begin()==A.end()) return "()";
    if (A.begin()==A.end()) return "";
    // return std::string("("+tree2lisp(A,A.begin())+")");
    return btree2lisp(A,A.begin());
  }
  
  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
  std::string charlist(list<char> &L) {
    std::stringstream ss;
    ss<<"{";
    for(auto c:L) ss<<c<<","<<endl;
    ss<<"}";
    return ss.str();
  }
  
  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
  void mutate(btree<int> &B,btree<int>::iterator n,
              randomg_t &rnd,double prob) {
    if (n==B.end()) return;
    if (rnd.drand()<prob) {
      btree<int> tmp;
      auto l = n.left(), r = n.right(), q=tmp.begin();
      q = tmp.splice(q,l);
      l = B.splice(l,r);
      r = B.splice(r,q);
    }
    mutate(B,n.left(),rnd,prob);
    mutate(B,n.right(),rnd,prob);
  }

  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
  void mutate(btree<int> &B,randomg_t &rnd,double prob) {
    mutate(B,B.begin(),rnd,prob);
  }
  
  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
  // END FUNCTIONS FOR THIS EXAM
  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
  
  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*> SIGN_SPLIT
#undef EJERC
#undef EVAL
#define EJERC 1
#define EVAL eval1_t
  typedef int (*spaceship_t)(btree<int> &T1,btree<int> &T2);
  class EVAL : public eval_base_t {
  public:
    spaceship_t F;
    EVAL() { dumptests=0; F=NULL; ejerc=EJERC; testfile="./ss.json"; jsonvrbs=1; }
    void run_case(json &data,json &outuser) {
      btree<int> T1,T2;
      lisp2btree(data["T1"],T1);
      lisp2btree(data["T2"],T2);
      outuser["retval"] = F(T1,T2);
    }
    //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
    static int fix(int x) { return (x>0? 1 : x<0? -1 : 0); }

    //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
    int check_case(json &datain,
                   json &outref,json &outuser) {
      int
        ref = outref["retval"],
        user = outuser["retval"];
      return fix(ref)==fix(user);
    }

    //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
    void generate_case(randomg_t &rnd,json &datain) {
      btree<int> T1,T2;
      make_random_btree(T1,10,0.4,rnd);
      T2=T1;
      mutate(T2,rnd,0.3);
      datain["T1"] = btree2lisp(T1);
      datain["T2"] = btree2lisp(T2);
    }
  };

#undef EJERC
#undef EVAL
#define EJERC 2
#define EVAL eval2_t
  typedef btree<char> (*makeHuffmanTree_t)(list<pair<btree<char>,float>> & bosque);
  class EVAL : public eval_base_t {
  public:
    makeHuffmanTree_t F;
    EVAL() { dumptests=0; F=NULL; ejerc=EJERC; testfile="./mHt.json"; }
    void run_case(json &data,json &outuser) {
      list<string> CS  = data["C"];
      list<char> C;
      for(auto s:CS) C.push_back(*s.begin());
      list<int> W = data["W"];
      list<pair<btree<char>,float>> bosque;
      auto iC = C.begin();
      auto iW = W.begin();
      while(iC!=C.end()){
        btree<char> T;T.insert(T.begin(),*iC);
        bosque.push_back({T,*iW});
        iC++;
        iW++;
      }
      btree<char> T = F(bosque);
      outuser["Tout"] = btree2lisp(T);
    }
    
    int check_case(json &datain,
                   json &outref,json &outuser) {
      return outref==outuser;
    }
    
    void generate_case(randomg_t &rnd,json &datain) {
      list<string> C;
      list<int> W;
      int Wt = 0.0;
      int i=-1;
      while(Wt<70 && i<25){
        i++;
        if((rnd.rand()%10)<5){
          int w = ((rnd.rand()%6) + 1)*5;
          W.push_back(w);
          string s; s.insert(s.begin(),char('a'+i));
          C.push_back(s);
          Wt += w;
        }
      }
      W.push_back(100-Wt);
      string s; s.insert(s.begin(),char('a'+1+i));
      C.push_back(s);
      datain["C"] = C;
      datain["W"] = W;
    }
  };

#undef EJERC
#undef EVAL
#define EJERC 3
#define EVAL eval3_t
  typedef int (*minCostSets_t)(set<int>& U, vector<set<int>>& S,
                               map<set<int>, int>& costos);
  class EVAL : public eval_base_t {
  public:
    minCostSets_t F;
    EVAL() { dumptests=0; F=NULL; ejerc=EJERC; testfile="./mcs.json"; }
    void run_case(json &data,json &outuser) {
        set<int> U = data["U"];
        vector<set<int>> S = data["S"];
        vector<int> vC = data["costos"];
        map<set<int>,int> C;
        int i=0;
        for(set<int>& s:S){
          C[s] = vC[i];
          i++;
        }
        
        int res = F(U, S, C);
        
        outuser["ret"] = res;
    }
    
    int check_case(json &datain,
                   json &outref,json &outuser) {
      return outref==outuser;
    }
    
    void generate_case(randomg_t &rnd,json &datain) {
      set<int> U;
      vector<int> Uaux;
      
      for(int i=0; i<10; i++) {
        if(rnd.rand()%10>=5) continue;
        U.insert(i);
        Uaux.push_back(i);
      }
      int NU = U.size();
      // generar cantS subconjuntos de U tomados de a k elementos
      // TODO hay que validar que contenga todos los elementos?
      set<set<int>> S;
      int cantS = 4+rnd.rand()%5;
      for(int i=0; i<cantS; i++) {
        set<int> Si;
        for(int j=0; j<NU; j++) {
          if(rnd.rand()%10>=5) continue;
          Si.insert(Uaux[j]);
        }  
        S.insert(Si);
      }
      cantS = S.size();
      // generar un mapa de costos asociados a cada subconjunto
      vector<int> C;
      vector<set<int>> vS(S.begin(),S.end());
      for(int i=0; i<cantS; i++) {
          C.push_back((1+rnd.rand()%10)*(1+rnd.rand()%10));
      }
      
      // insertar el caso de conjuntos vacios y comparar con INT_MAX
      datain["U"] = U;
      datain["S"] = vS;
      datain["costos"] = C;
    }
  };
  
  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
  using Eval = eval_t<eval1_t,spaceship_t,
                      eval2_t,makeHuffmanTree_t,
                      eval3_t,minCostSets_t>;

}
#undef CSTR

#endif
