// GITVERSION: aed-3.1-86-g4727a4c9
#ifndef EVAL_HPP
#define EVAL_HPP
#include "aedtools/evalbase.hpp"
#include <forward_list>
#include <sstream>
using namespace std;

namespace aed {

  
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
  
  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*> PROM_NIVEL
  
  typedef void (*prom_nivel_t)(tree<int> &T, list<float> &P);
  class eval1_t : public eval_base_t {
  public:
    prom_nivel_t F;
    eval1_t() { dumptests=0; F=NULL; ejerc=1; testfile="./pn.json"; }
    void run_case(json &data,json &outuser) {
      tree<int> T;
      // this->lisp2tree2(data["T"],T);
      lisp2tree(data["T"],T);
      list<float> P;
      F(T,P);
      outuser["P"] = P;
    }

    int check_case(json &datain,
                   json &outref,json &outuser) 
    {
      list<float> Pu = outuser["P"];
      list<float> Pr = outref["P"];
      if (Pu.size()!=Pr.size()) return false;
      for(auto itu=Pu.begin(),itr=Pr.begin();itu!=Pu.end();++itu,++itr) {
        if (fabs(*itr-*itu)>1e-5) return false;
      }
      return true;
    }
    
    void generate_case(randomg_t &rnd,json &datain) {
      tree<int> T;
      int m = 5+rnd.rand()%10; int n = 5+rnd.rand()%10;
      make_random_tree2(T,100,m,n,rnd);
      datain["T"] = tree2lisp(T);
      // cout << datain["T"] << endl;
      // T.lisp_print();
      // cout << endl;
      // exit(0);
    }
  };
  
  
  
  
  
  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*> FUNCIONES AUXILIARES
  
//  template<typename TContainer>
//  int string2container(TContainer &v, const string &str) {
//    stringstream ss(str);
//    string aux;
//    while(ss>>aux) v.push_back(aux);
//    return v.size();
//  }
  
//  template<typename TContainer>
//  int string2container(TContainer &v, const string &str) {
//    stringstream ss(str);
//    string aux;
//    while(getline(ss,aux,'|')) v.push_back(aux);
//    return v.size();
//  }
//  template<typename TContainer>
//  string container2string(const TContainer &v) {
//    string s, d(1,'|');
//    for(const auto &x:v)
//      s += (s.empty()?string(""):d)+x;
//    return s;
//  }
//  
//  string get_first(const string &pair) {
//    size_t pos = pair.find(':');
//    return pair.substr(0,pos);
//  }
//  string get_second(const string &pair) {
//    size_t pos = pair.find(':');
//    return pair.substr(pos+1);
//  }
  
  void sort(vector<int> &v) { sort(v.begin(),v.end()); }
  void sort(list<int> &l) { l.sort(); }
  
  template<typename TMapa>
  void make_graph(TMapa &M, std::vector<int> nodos,
                  std::vector<std::pair<int,int>> aristas) 
  {
    for(auto p:aristas) {
      M[p.first].push_back(p.second);
      M[p.second].push_back(p.first);
    }
    for(int x:nodos) sort(M[x]);
  }
  
  template<typename TMapa>
  void read_graph(TMapa &M, const json &data, std::string name) {
    std::vector<int> nodos = data[name+"_nodos"];
    std::vector<std::pair<int,int>> aristas; // = data["aristas"];
    json aux = data[name+"_aristas"];
    for(std::vector<int> v:aux)
      aristas.push_back(make_pair(v[0],v[1]));
    make_graph(M,nodos,aristas);
  }
  
  template<typename TMapa>
  void write_graph(const TMapa &M, json &data, std::string name) {
    using T = typename TMapa::key_type;
    std::vector<T> nodos, auxp(2);
    std::vector<std::vector<T>> aristas;
    for(const auto &p:M) {
      nodos.push_back(p.first);
      for(const auto &v:p.second) {
        if (v>p.first) {
          auxp[0]=p.first; auxp[1]=v;
          aristas.push_back(auxp);
        }
      }
    }
    data[name+"_nodos"] = nodos;
    data[name+"_aristas"] = aristas;
  }
  
//  void random_shuffle(vector<int> &v, randomg_t &rnd) {
//    for(size_t i=0;i<v.size();i++) {
//      int j = rnd.rand()%v.size();
//      std::swap(v[i],v[j]);
//    }
//  }
  
  template<typename TMapa>
  std::string map2str(const TMapa &M) {
    std::stringstream ss;
    ss << "(";
    for(const auto &p:M) {
      ss << p.first << "->" << p.second << ",";
    }
    std::string ret = ss.str();
    ret[ret.size()-1]=')';
    return ret;
  }
  
  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*> ES CIRCUITO
  
  typedef bool (*es_circuito_t)(map<int,list<int> > &G, list<int> &L);
  class eval2_t : public eval_base_t {
    
    
  public:
    es_circuito_t F;
    eval2_t() { dumptests=0; F=NULL; ejerc=2; testfile="./ec.json"; }
    void run_case(json &data,json &outuser) {
      std::map<int,list<int>> M;
      read_graph(M,data,"G");
      std::list<int> L = data["L"];
      bool ret = F(M,L);
      outuser["ret"] = ret?1:0;
    }

    int check_case(json &datain,
                   json &outref,json &outuser) {
      return outref==outuser;
    }
    
    void generate_case(randomg_t &rnd,json &datain) {
      // nodos
      int nnodos = 3+rnd.rand()%15;
      vector<int> vnodos(nnodos);
      for(size_t i=0;i<vnodos.size();i++) vnodos[i] = i;
      datain["G_nodos"] = vnodos;
      // aristas
      vector< vector<int> > varistas;
      vector<int> p(2);
      for(int i=0;i<nnodos;i++) { 
        for(int j=i+1;j<nnodos;j++) { 
          if (rnd.rand()%5!=0) {
            p[0]=i; p[1]=j; varistas.push_back(p);
          }
        }
      }
      datain["G_aristas"] = varistas;
      // camino
      vector<int> L;
      for(int i=0;i<nnodos;i++) { 
        if (rnd.rand()%2==0) L.push_back(i);
      }
      if (L.empty()) L.push_back(rnd.rand()%nnodos);
      else random_shuffle(rnd,L);
      datain["L"] = L;
    }
  };
  
  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*> MAP_GRAPH
#if 0  // NOVARA  
  typedef void (*map_graph_t)(map<int,vector<int> > &Gin,map<int,int> &P,
                            map<int,vector<int> > &Gout);
  class eval3_t : public eval_base_t {
    
    void make_graph(std::map<int,list<int>> &M, std::vector<int> nodos,
                    std::vector<std::pair<int,int>> aristas) 
    {
      for(auto p:aristas) {
        M[p.first].push_back(p.second);
        M[p.second].push_back(p.first);
      }
      for(int x:nodos) M[x].sort();
    }
    
  public:
    map_graph_t F;
    eval3_t() { dumptests=0; F=NULL; ejerc=3; testfile="./map_graph.json"; }
    void run_case(json &data,json &outuser) {
      std::map<int,vector<int>> Gin,Gout;
      read_graph(Gin,data,"Gin");
      std::map<int,int> P;
      str2map(P,data["P"]);
      F(Gin,P,Gout);
      write_graph(Gout,outuser,"Gout");
    }

    int check_case(json &datain,
                   json &outref,json &outuser) {
      return outref==outuser;
    }
    
    void generate_case(randomg_t &rnd,json &datain) {
      // nodos
      int nnodos = 3+rnd.rand()%15;
      vector<int> vnodos(nnodos);
      for(size_t i=0;i<vnodos.size();i++) vnodos[i] = i;
      datain["Gin_nodos"] = vnodos;
      // aristas
      vector< vector<int> > varistas;
      vector<int> p(2);
      for(int i=0;i<nnodos;i++) { 
        for(int j=i+1;j<nnodos;j++) { 
          if (rnd.rand()%3!=0) {
            p[0]=i; p[1]=j; varistas.push_back(p);
          }
        }
      }
      datain["Gin_aristas"] = varistas;
      // mapeo
      map<int,int> P;
      for(int i=0;i<nnodos;i++) P[i] = rnd.rand()%nnodos;
      datain["P"] = map2str(P);
    }
  };
#else
  // MAS EVAL CLASS
  typedef map<int,vector<int> > graph_t;
  typedef map<int,vector<int> > graph_t;
  void json2graph(json &J,graph_t &G) {
    for (json::iterator q = J.begin(); q != J.end(); ++q) {
      int k = (*q)["key"];
      vector<int> ng = (*q)["ngbrs"];
      G[k] = ng;
    }
  }

  void graph2json(graph_t &G,json &J) {
    auto q = G.begin();
    while (q!=G.end()) {
      json z;
      z["key"] = q->first;
      z["ngbrs"] = q->second;
      J.push_back(z);
      q++;
    }
  }

  typedef void (*map_graph_t)(graph_t &Gin,map<int,int> &P,graph_t &Gout);
  class eval3_t : public eval_base_t {
  public:
    map_graph_t F;
    eval3_t() { dumptests=0; F=NULL; ejerc=3; testfile="./mg.json"; }
    void run_case(json &data,json &outuser) {
      graph_t Gin, Gout;
      // Read Gin
      json2graph(data["Gin"],Gin);
      // Read P. It is passed as a vector
      vector<int> wP = data["P"];
      int m = wP.size();
      map<int,int> P;
      for (int j=0; j<m; j++) P[j] = wP[j];
      F(Gin,P,Gout);
      // Write Gout
      graph2json(Gout,outuser);
    }

    int check_case(json &datain,
                   json &outref,json &outuser) {
      return outref==outuser;
    }

    void generate_case(randomg_t &rnd,json &datain) {
      graph_t Gin;
      // Nbr of graph vertices
      int n=3+rnd.rand()%3;
      int nedges=0.5*n*n;
      // Be sure all the keys in [0,n) are present
      for (int j=0; j<n; j++) Gin[j];
      for (int l=0; l<nedges; l++) {
        int
          j=rnd.rand()%n,
          k=rnd.rand()%n;
        if (j!=k) {
          Gin[j].push_back(k);
          Gin[k].push_back(j);
        }
      }
      // Be sure that any vrtx has at least one ngbr
      // (in order to make it easier)
      for (int j=0; j<n; j++) 
        if (Gin.find(j)==Gin.end()) {
          int k = (j+1)%n;
          Gin[j].push_back(k);
          Gin[k].push_back(j);
        }
        
      for (int j=0; j<n; j++) {
        vector<int> &v = Gin[j];
#if 0
        auto z = std::unique(v.begin(),v.end());
        v.erase(z,v.end());
        sort(v.begin(),v.end());
#endif
        set<int> s;
        for (auto q:v) s.insert(q);
        v.clear();
        for (auto q:s) v.push_back(q);
      }
        
      json J;
      graph2json(Gin,J);
      datain["Gin"] = J;
      vector<int> P(n);
      for (int j=0; j<n; j++) P[j] = j;
      this->random_shuffle(rnd,P,0,n);
      datain["P"] = P;
    }
  };
#endif
  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
  using Eval = eval_t<eval1_t,prom_nivel_t,
                      eval2_t,es_circuito_t,
                      eval3_t,map_graph_t>;
}
#undef CSTR

#endif
