// GITVERSION: aed-3.1-266-g32e98a78
/* 
   COMIENZO DE DESCRIPCION 
   Utilitarios varios. 
   keywords: arbol binario
   FIN DE DESCRIPCION 
*/
// -----------------------------------------------------------------
#ifndef AED_BTREE_H
#define AED_BTREE_H
#include <iostream>
#include <cstddef>
#include <cstdlib>
#include <cassert>
#include <list>
using namespace std;
namespace aed {
  template <class T>
  class btree {
  public:
    class iterator;
    class const_iterator;
  private:
    class cell {
      friend class btree;
      friend class iterator;
      T t;
      cell *right, *left;
      cell() : right(NULL), left(NULL) {}
    };
    cell *header;
    enum side_t{NONE,R,L};
    iterator tree_copy_aux(iterator nq,
			    const btree<T> &Z,const_iterator nt) {
      nq=insert(nq,*nt);
      const_iterator k;
      k=nt.left();
      if (k!=Z.end()) tree_copy_aux(nq.left(),Z,k);
      k=nt.right();
      if (k!=Z.end()) tree_copy_aux(nq.right(),Z,k);
      return nq;
    }

    bool equal_p(const btree<T> &T1,btree<T>::const_iterator n1,
                 const btree<T> &T2,btree<T>::const_iterator n2) const {
      if ((n1==T1.end()) xor (n2==T2.end())) return false; 
      if (n1==T1.end()) return true;
      if (*n1 != *n2) return false;
      return equal_p(T1,n1.right(),T2,n2.right()) &&
        equal_p(T1,n1.left(),T2,n2.left());
    }

  // ---------------------------------------------------------------
  public:
    static int cell_count_m;
    static int cell_count () {return cell_count_m;}
    class iterator {
    private:
      friend class btree;
      cell *ptr, *father;
      friend class const_iterator;
      side_t side;
      iterator(cell *p, side_t side_a, cell *f_a)
        : ptr(p), father(f_a), side(side_a) { }
      T *data() { return &(ptr->t); }

    public:
      iterator(const iterator &q) {
	ptr=q.ptr;
	side=q.side;
	father=q.father;
      }
      T &operator*() {return *data();}
      T *operator->() {return data();}
      bool operator!=(iterator q) {return (ptr!=q.ptr);}
      bool operator==(iterator q) {return (ptr==q.ptr);}
      iterator() : ptr(NULL),father(NULL),side(NONE) { }
      iterator left() { return iterator(ptr->left,L, ptr);}
      iterator right() {return iterator(ptr->right,R,ptr);}
      operator const_iterator() const {
        return *(const_iterator *)this;
      }
    };
    class const_iterator : public iterator {
    public:
      const T &operator*() { return *(this->data()); }
      const T *operator->() { return this->data(); }
    };
    
    // -------------------------------------------------------------
    // constructor por defecto
    btree() {
      header=new cell;
      cell_count_m++;
      header->right=NULL;
      header->left=NULL;
    }
    // -------------------------------------------------------------
    // constructor copia
    btree<T> (const btree<T> &H) { 
      if (&H!=this) {
	header=new cell;
	cell_count_m++;
	header->right=NULL;
	header->left=NULL;
	if (H.begin()!=H.end()) 
	  tree_copy_aux(begin(),H,H.begin()); 
      }
    }
    // -------------------------------------------------------------
    // Operador de asignacion
    btree &operator=(btree<T> &TT) { 
      clear();
      copy(begin(),TT,TT.begin()); 
      return *this;
    }

    bool operator==(const btree<T> &Q) const {
      return equal_p(*this,this->begin(),Q,Q.begin());
    }

    bool operator!=(const btree<T> &Q) const {
      return !(*this==Q);
    }
    
    // -------------------------------------------------------------
    // destructor
    ~btree() {clear();delete header;cell_count_m--; }
    // Assignement operator
    btree<T>& operator=(const btree<T>& Q) { 
      clear();
      if (Q.begin()!=Q.end()) 
	tree_copy_aux(begin(),Q,Q.begin());
      return *this;
    }
    // -------------------------------------------------------------
    iterator insert(iterator p,T t) {
      assert(p==end());
      cell *c=new cell;
      cell_count_m++;
      c->t=t;
      if (p.side==R) {
        p.father->right=c;}
      else { 
        p.father->left=c; 
      }
      p.ptr=c;
      return p;
    }
    // -------------------------------------------------------------
    iterator erase(iterator p) {
      if (p==end()) return p;
      erase(p.right());
      erase(p.left());
      if (p.side==R) {
        p.father->right=NULL;}
      else {
        p.father->left=NULL; 
      }
      delete p.ptr;
      cell_count_m--;
      p.ptr=NULL;
      return p;
    }
    // -------------------------------------------------------------
    iterator splice(iterator to,iterator &from) {
      if (from==end()) return to;
      cell *c=from.ptr;
      from.ptr=NULL;
      if (from.side==R) from.father->right=NULL;
      else from.father->left=NULL;

      if (to.side==R) to.father->right=c;
      else to.father->left=c; 

      to.ptr=c;
      return to;
    } 
    // -------------------------------------------------------------
    iterator copy(iterator nq,btree<T> &TT,iterator nt) {
      if (nt==TT.end()) return nq;
      nq = insert(nq,*nt);
      iterator m = nt.left();
      if (m != TT.end()) copy(nq.left(),TT,m);
      m = nt.right();
      if (m != TT.end()) copy(nq.right(),TT,m);
      return nq;
    }
    // -------------------------------------------------------------
    iterator find(T t) { return  find(t,begin()); }
    // -------------------------------------------------------------
    iterator find(T t,iterator p) {
      if (p==end () || (p.ptr->t)==t) return p;
      iterator l,r;
      l=find(t,p.left());
      if (l!=end()) return l;
      r=find(t,p.right());
      if (r!=end()) return r;
      return end();
    }
    // -------------------------------------------------------------
    void clear() { 
      erase(begin()); 
    }
    // -------------------------------------------------------------
    iterator begin() const { 
      return (iterator(header->left,L,header)); 
    }

    //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
    int size(const_iterator n) const {
      if (n==end()) return 0;
      else return 1+size(n.left())+size(n.right());
    }

    //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
    int size() const { return size(begin()); }
    
    // -------------------------------------------------------------
    void lisp_print(iterator n) {
      iterator r,l;
      if (n==end()) { cout << "." ;return;}
      bool is_leaf;
      r=n.right();
      l=n.left();
      is_leaf=(r==end() && l==end());
      if (is_leaf==true) {
        cout << *n;}
      else { cout << "(" << *n << " ";
	lisp_print(l);
	cout << " ";
	lisp_print(r) ;
	cout << ")";
      }
    }
    // -------------------------------------------------------------
    void lisp_print() { 
      lisp_print(begin()); 
    } 
    // -------------------------------------------------------------
    iterator end() const { 
      return iterator();
    } 
  // -------------------------------------------------------------
  }; // end class btree
  template <class T>
  int btree<T>::cell_count_m=0;
} // end namespace
#endif
// -----------------------------------------------------------------
