#ifndef AED_TREE_H
#define AED_TREE_H
#include <iostream>
#include <cstddef>
#include <cstdlib>
#include <cassert>

namespace aed {
  // ---------------------------------------------------------------
  template<class T>
  class tree {
  public:
    class iterator;
    class const_iterator;
  private:
    class cell {
      friend class tree;
      friend class iterator;
      T t;
      cell *right, *left_child;
      cell() : right(NULL), left_child(NULL) {}
    };
    // -------End Class cell --------------------------------------
    // -----------------------------------------------------------------

    cell *header;

    // -----------------------------------------------------------------
    iterator tree_copy_aux(iterator nq,
			   const tree<T> &TT,const_iterator nt) {
      nq = insert(nq,*nt);
      const_iterator ct = nt.lchild();
      iterator cq = nq.lchild();
      while (ct!=TT.end()) {
	cq = tree_copy_aux(cq,TT,ct);
	ct = ct.right();
	cq = cq.right();
      }
      return nq;
    }
    // -----------------------------------------------------------------
  public:
    static int cell_count_m;
    static int cell_count() { return cell_count_m; }
    // -----------------------------------------------------------------
    // -------Begin Class iterator--------------------------------------
    class iterator {
    private:
      friend class tree;
      cell *ptr,*prev,*father;
      friend class const_iterator;
      iterator(cell *p,cell *prev_a,cell *f_a) : ptr(p), 
	prev(prev_a), father(f_a) { }
      T *data() { return &(ptr->t); }
    public:
      iterator(const iterator &q) {
	ptr = q.ptr;
	prev = q.prev; 
	father = q.father;
      }
      T &operator*() { return *data(); }
      T *operator->() { return data(); }
      bool operator!=(iterator q) { return ptr!=q.ptr; }
      bool operator==(iterator q) { return ptr==q.ptr; }
      iterator() : ptr(NULL), prev(NULL), father(NULL) { }

      iterator lchild() { return iterator(ptr->left_child,NULL,ptr); }
      iterator right() { return iterator(ptr->right,ptr,father); }

      // Prefix:
      iterator operator++() {
	*this = right();
	return *this;
      }
      // Postfix:
      iterator operator++(int) {
	iterator q = *this;
	*this = right();
	return q;
      }
      operator const_iterator() const {
        return *(const_iterator *)this;
      }
    };
    // -------End Class iterator--------------------------------------
    class const_iterator : public iterator {
    public:
      const T &operator*() { return *(this->data()); }
      const T *operator->() { return this->data(); }
    };
    // -------------------------------------------------------------
    // constructor por defecto tree
    tree() {
      header = new cell;
      cell_count_m++;
      header->right = NULL;
      header->left_child = NULL;
    }
    // -------------------------------------------------------------
    // constructor copia tree
    tree(const tree<T> &TT) { 
      if (&TT != this) {
	header = new cell;
	cell_count_m++;
	header->right = NULL;
	header->left_child = NULL;
	if (TT.begin()!=TT.end()) 
	  tree_copy_aux(begin(),TT,TT.begin()); 
      }
    }
    // -------------------------------------------------------------
    // destructor tree
    ~tree() { clear(); delete header; cell_count_m--; }
    // -------------------------------------------------------------
    tree<T>& operator=(const tree<T>& Q) { 
      clear();
      if (Q.begin()!=Q.end()) 
	tree_copy_aux(begin(),Q,Q.begin());
      return *this;
    }
    bool equal(const_iterator nt,const tree<T>& Q,
               const_iterator nq) const {
      if ((nt==end()) xor (nq==Q.end())) return false;
      if (nt==end()) return true;
      if (*nt!=*nq) return false;
      iterator
        ct = nt.lchild(),
        cq = nq.lchild();
      while (ct!=end() && cq!=Q.end()) {
        if (!equal(ct,Q,cq)) return false;
        ct++; cq++;
      }
      return ct==end() && cq==Q.end();
    }
    // -------------------------------------------------------------
    bool operator==(const tree<T>& Q) const {
      return equal(begin(),Q,Q.begin());
    }
    // -------------------------------------------------------------
    iterator insert(iterator p,T t) {
      assert(!(p.father==header && p.ptr));
      cell *c = new cell;
      cell_count_m++;
      c->right = p.ptr;
      c->t = t;
      p.ptr = c;
      if (p.prev) p.prev->right = c;
      else p.father->left_child = c;	
      return p;
    }
    // -------------------------------------------------------------
    iterator erase(iterator p) {
      if(p==end()) return p;
      iterator c = p.lchild();
      while (c!=end()) c = erase(c);
      cell *q = p.ptr;
      p.ptr = p.ptr->right;
      if (p.prev) p.prev->right = p.ptr;
      else p.father->left_child = p.ptr;
      delete q;
      cell_count_m--;
      return p;
    }
    // -------------------------------------------------------------
    iterator splice(iterator to,iterator &from) {
      assert(!(to.father==header && to.ptr));
      cell *c = from.ptr;
      if (from.prev) from.prev->right = c->right;
      else from.father->left_child = c->right;
      from.ptr=from.ptr->right;
      c->right = to.ptr;
      to.ptr = c;
      if (to.prev) to.prev->right = c;
      else to.father->left_child = c;	
      return to;
    }
    // -------------------------------------------------------------
    iterator find(T t) { return find(t,begin()); }
    // -------------------------------------------------------------
    iterator find(T t,iterator p) {
      if(p==end() || p.ptr->t == t) return p;
      iterator q,c = p.lchild();
      while (c!=end()) {
	q = find(t,c);
	if (q!=end()) return q;
	else c++;
      }
      return iterator();
    }
    // -------------------------------------------------------------
    void clear() { erase(begin()); }
    // -------------------------------------------------------------
    iterator begin() const { return iterator(header->left_child,NULL,header); }
    // -------------------------------------------------------------
    iterator end() const { return iterator(); }
    // -------------------------------------------------------------
    void print_prev(iterator p) { 
      if (p==end()) return;
      std::cout << "(" << p.ptr << "," << p.ptr->t << ")" << std::endl;
      iterator c = p.lchild();
      while (c!=end()) print_prev(c++);
    }
    // -------------------------------------------------------------
    void print_prev() { print_prev(begin()); }
    // -------------------------------------------------------------
    void print_post(iterator p) { 
      if (p==end()) return;
      iterator c = p.lchild();
      while (c!=end()) print_post(c++);
      std::cout << "(" << p.ptr << "," << p.ptr->t << ")" << std::endl;
    }
    // -------------------------------------------------------------
    void print_post() { print_post(begin()); }
    // -------------------------------------------------------------
    void lisp_print(iterator n) {
      if (n==end()) return;
      iterator c = n.lchild();
      bool is_leaf = c==end();
      if (is_leaf) std::cout << *n;
      else {
	std::cout << "(" << *n;
	while (c!=end()) {
	  std::cout << " ";
	  lisp_print(c++);
	}
	std::cout << ")";
      }
    }
    // -------------------------------------------------------------
    void lisp_print() { lisp_print(begin()); }
    //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
    bool empty() { return begin()==end(); }
    //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
    int size(iterator n) {
      int count=1;
      iterator c = n.lchild();
      while (c!=end()) 
        count += size(c++);
      return count;
    }
    //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
    int size() {
      if (!empty()) return size(begin());
    }
    // -------------------------------------------------------------
    void swap(tree<T> &T2) { cell *aux=header; header=T2.header; T2.header=aux; }
  };
  // ---------------------------------------------------------------
  template<class T>
  int tree<T>::cell_count_m = 0;
  // -----------------------------------------------------------------
  template<class T>
  void swap(tree<T> &T1, tree<T> &T2) { T1.swap(T2); }
}
#endif
// -----------------------------------------------------------------
