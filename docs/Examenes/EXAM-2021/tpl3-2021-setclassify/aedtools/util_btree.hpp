// GITVERSION: aed-2021-137-g25d89fc3
/* 
   COMIENZO DE DESCRIPCION 
   Utilitarios varios. 
   keywords: arbol binario
   FIN DE DESCRIPCION 
*/
// -------------------------------------------------------------------
#ifndef AED_BTREETOOLS_H
#define AED_BTREETOOLS_H
#include "./btree.hpp"
#include "./util.hpp"
#include "aedtools/json.hpp"
#include <vector>

namespace aed {
  // -----------------------------------------------------------------
  template <typename elem_t>
  typename btree<elem_t>::iterator
  list2btree(btree<elem_t> &T,
	      typename btree<elem_t>::iterator n,
	      const list<elem_t> &L,
	      typename list<elem_t>::const_iterator &p,
	      elem_t BP,elem_t EP,elem_t NE) {
    typename list<elem_t>::const_iterator q;
    if (*p==NE) { }
    else if (*p!=BP) {
      n=T.insert(n,*p);}
    else {
      q=p;q++;
      assert(*q!=BP && *q!=EP && *q!=NE);
      n=T.insert(n,*q++);
      list2btree(T,n.left(),L,q,BP,EP,NE);
      list2btree(T,n.right(),L,q,BP,EP,NE);
      p=q;
    }
    p++;
    return n;
  }
  // -----------------------------------------------------------------
  template <class T>
  typename btree<T>::iterator list2btree(btree<T> &A,const list<T> &L,
              T BP,T EP,T NE) {
    typename list <T>::const_iterator p;
    p=L.begin();
    return (list2btree(A,A.begin(),L,p,BP,EP,NE));
  }
  // -----------------------------------------------------------------
  void make_random_btree(btree<int> &t,btree<int>::iterator n,
			 int m,int level,double siblings);
  // -----------------------------------------------------------------
  void make_random_btree(btree<int> &t,int m,double siblings);
  // -----------------------------------------------------------------
  void node_level_stat(btree<int> &t,btree<int>::iterator n,
		        int level,vector<int> &nod_lev);
  // -----------------------------------------------------------------
  void node_level_stat (btree<int> &t,vector<int> &nod_lev);

  // -----------------------------------------------------------------
  template <class T>
  void apply (btree <T> &Q,typename btree<T>::iterator n,T (*f)(T)) {
    if (n==Q.end()) return;
    *n=f(*n) ;
    apply(Q,n.left(),f);
    apply(Q,n.right(),f);
  }
  // -----------------------------------------------------------------
  template <class T>
  void apply(btree<T> &Q,T (*f)(T)) {
    apply(Q,Q.begin(),f); 
  }

  // Another flavor of apply with a class
  // This is the class of mapping functions
  class map_fun_t {
  public:
    virtual int f(int)=0;
  };

  // Wrapper
  void apply(btree<int> &T,map_fun_t &z);

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

  nlohmann::json btree2json(btree<int> &T);
  void json2btree(nlohmann::json &jn,btree<int> &T);
  void btree2dot(btree<int> &T,const char *file);
  
} // namespace
#endif
