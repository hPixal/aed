// $Id$
/* 
   COMIENZO DE DESCRIPCION 
   Utilitarios varios. 
   keywords: arbol orientado
   FIN DE DESCRIPCION 
*/
// -----------------------------------------------------------------
#ifndef AED_TREETOOLS_H
#define AED_TREETOOLS_H

#include "./util.hpp"

namespace aed {

  // -------------------------------------------------------------
  template <typename elem_t>
  typename tree<elem_t>::iterator
  list2tree (tree<elem_t> &T,
	    typename tree<elem_t>::iterator n,
	    const std::list<elem_t> &L,
	    typename std::list<elem_t>::const_iterator  &p,
	    elem_t BP,elem_t EP) {
    if (*p != BP) n=T.insert(n,*p);
    else {
      typename std::list<elem_t>::const_iterator q=p; q++;
      assert(*q != BP && *q != EP);
      n = T.insert(n,*q++);
      typename tree<elem_t>::iterator r = n.lchild();
      while (*q != EP) {
	r = list2tree(T,r,L,q,BP,EP);
	r++;
      }
      p=q;
    }
    p++;
    return n;
  }

  // -------------------------------------------------------------
  template <class T>
  typename tree<T>::iterator
  list2tree(tree<T> &A,const std::list<T> &L,T BP,T EP) {
    typename std::list<T>::const_iterator p = L.begin();
    return list2tree(A,A.begin(),L,p,BP,EP);
  }

  // -------------------------------------------------------------
  template <class T>
  void tree2list(tree<T> &A,
		 typename tree<T>::iterator n,
		 std::list<T> &L,T BP,T EP) {
    typedef typename tree<T>::iterator node_t;

    if (n==A.end()) return;
    node_t c = n.lchild();
    if (c==A.end()) {
      L.insert(L.end(),*n); 
    } else {
      L.insert(L.end(),BP); 
      L.insert(L.end(),*n); 
      while (c!=A.end()) {
	tree2list(A,c++,L,BP,EP);
      }
      L.insert(L.end(),EP);
    }
  }

  // -------------------------------------------------------------
  template <class T>
  void tree2list(tree<T> &A,std::list<T> &L,T BP,T EP) {
    tree2list(A,A.begin(),L,BP,EP);
  }

  // -------------------------------------------------------------
  void make_random_tree(tree<int> &T,int M,int siblings);

  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
  // Makes a random tree with `s' siblings and `m' nodes
  void make_random_tree2(tree<int> &T,tree<int>::iterator n,
                         int M, int m,int s);
  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
  // Wrapper
  void make_random_tree2(tree<int> &T,int M, int m,int s);

  // -------------------------------------------------------------
  typedef tree<int> tree_t;
  typedef tree<int>::iterator node_t;
  void print_tree(tree<int> &T,node_t n,std::string pre,std::string c);
  void print_tree(tree<int> &T);

  void list2treev(tree<int> &T,int TERM,int BP,
                  int EP,va_list elems);

  void list2treev(tree<int> &T,int TERM,int BP,int EP,...);

}
#endif
// ---------------------------------------------------------------
