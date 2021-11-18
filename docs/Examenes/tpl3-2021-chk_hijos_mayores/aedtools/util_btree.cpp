// GITVERSION: aed-2021-137-g25d89fc3
// $Id$
/* 
   COMIENZO DE DESCRIPCION 
   Utilitarios varios. 
   keywords: arbol binario
   FIN DE DESCRIPCION 
*/
// -----------------------------------------------------------------
#include <vector>
#include <iostream>
#include <fstream>
#include "./util.hpp"
#include "./util_btree.hpp"

using nlohmann::json;

namespace aed {

  // -----------------------------------------------------------------
  void make_random_btree(btree<int> &t,btree<int>::iterator n,
                         int m,int level,double siblings) {
    btree<int>::iterator c;
    double lambda,nivel;
    n=t.insert(n,irand(m));
    nivel=double(level);
    lambda = 1.0/(siblings/nivel+1.0);
    for (int j=0;j<2;j++) {
      if  (j==0) {
        c=n.left();}
      else {
        c=n.right();
      }
      if (drand()>lambda) {
        make_random_btree(t,c,m,level+1,siblings);
      }
    }
  }

  // -----------------------------------------------------------------
  void make_random_btree(btree<int> &t,int m,double siblings) {
    t.clear();
    make_random_btree(t,t.begin(),m,0,siblings);
  } 

  // -----------------------------------------------------------------
  void node_level_stat(btree<int> &t,btree<int>::iterator n,int level,
                       vector<int> &nod_lev) {
    if (n==t.end()) return;
    unsigned int lev = (unsigned int)level;
    assert(nod_lev.size()>=lev);
    if (nod_lev.size()==lev) nod_lev.push_back(0);
    nod_lev[level]++;
    node_level_stat(t,n.left(),level+1,nod_lev);
    node_level_stat(t,n.right(),level+1,nod_lev);
  }

  // -----------------------------------------------------------------
  void node_level_stat(btree<int> &t,vector<int> &nod_lev) {
    nod_lev.clear();
    node_level_stat(t,t.begin(),0,nod_lev);
    cout << "level/#nodes: ";
    for (unsigned int j=0;j<nod_lev.size();j++) {
      cout << j << "/" << nod_lev[j] << ", ";
    }
    cout << endl;
  }

  // Recursive function that applies the map
  void apply(btree<int> &T,btree<int>::iterator n, map_fun_t &z) {
    if (n==T.end()) return;
    *n = z.f(*n);
    apply(T,n.left(),z);
    apply(T,n.right(),z);
  }

  // Wrapper
  void apply(btree<int> &T,map_fun_t &z) {
    apply(T,T.begin(),z);
  }

  json btree2json(btree<int> &T,btree<int>::iterator n) {
    json J;
    if (n==T.end()) return J;
    auto cl=n.left(),cr=n.right();
    if (cl==T.end() && cr==T.end()) {
      J = *n;
    } else {
      J.push_back(*n);
      J.push_back(btree2json(T,cl));
      J.push_back(btree2json(T,cr));
    }
    return J;
  }

  json btree2json(btree<int> &T) {
    json J;
    auto n=T.begin();
    if (n==T.end()) return J;
    return btree2json(T,n);
  }

  btree<int>::iterator
  json2btree(json &jn,btree<int> &T,btree<int>::iterator &n) {
    if (jn.is_null()) {
      // Do nothing
    } else if (!jn.is_array()) {
      // A leaf
      int xn = jn;
      n=T.insert(n,xn);
    } else {
      // At least one child is 
      int xn = jn[0];
      n = T.insert(n,xn);
      auto cl = n.left(), cr=n.right();
      json2btree(jn[1],T,cl);
      json2btree(jn[2],T,cr);
    }
    return n;
  }

  void json2btree(json &jn,btree<int> &T) {
    T.clear();
    if (jn.is_null()) return;
    auto n=T.begin();
    json2btree(jn,T,n);
  }

  int btree2dot(btree<int> &T,btree<int>::iterator n,int id,ostream &out) {
    if (n==T.end()) return id;
    out << id << " [label=\"" << *n << "\"];\n";
    int idc=id+1;
    btree<int>::iterator cv[2];
    cv[0]=n.left(),cv[1]=n.right();
    if (cv[0]==T.end() && cv[1]==T.end()) return idc;
    for (int j=0; j<2; j++) {
      if (cv[j]!=T.end()) {
        out << id << " -> " << idc << ";\n";
        idc=btree2dot(T,cv[j],idc,out);
      } else {
#if 0        
        out << id << " -> " << idc << " [style=\"invis\"];\n";
        out << idc << " [label=\"\",style=\"invis\"];\n";
#endif
        out << id << " -> " << idc << ";\n";
        out << idc << " [label=\"\",shape=\"point\"];\n";
        idc++;
      }
    }
    return idc;
  }

  void btree2dot(btree<int> &T,const char *file) {
    ofstream out(file? file : "tree.dot");
    out << "digraph G {\n";
    btree2dot(T,T.begin(),0,out);
    out << "}\n";
    out.close();
  }
  
  
} // end namespace

// -----------------------------------------------------------------
