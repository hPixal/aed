// GITVERSION: aed-3.1-44-g8bbf219a
#ifndef EVALBASE_HPP
#define EVALBASE_HPP

#include <cstdio>
#include <cstdlib>
#include <cstdint>
#ifdef USECHRONO
# include <sys/time.h>
#endif
#include <cmath>
#include <string>
#include <map>
#include <list>
#include <vector>
#include <set>
#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include "aedtools/json.hpp"
#include "aedtools/tree.hpp"
#include "aedtools/util_tree.hpp"
#include "aedtools/btree.hpp"
#include "aedtools/util_btree.hpp"
using namespace std;
using nlohmann::json;

#ifndef UINT32_MAX
#define UINT32_MAX (4294967295U)
#endif

#define CSTR(s) (s).c_str()
namespace aed {

  // Simple hasher class for the examples
  class hasher_t  {
  private:
    // BJ hash (Bob Jenkins). From
    // http://www.chasanc.com/old/hashing_func.htm
    typedef uint32_t u4; /* unsigned 4-byte type */
    typedef uint8_t u1;   /* unsigned 1-byte type */
    u4 state;

    /* The mixing step */
#define mix(a,b,c)                              \
    {                                           \
      a=a-b;  a=a-c;  a=a^(c>>13);              \
      b=b-c;  b=b-a;  b=b^(a<<8);               \
      c=c-a;  c=c-b;  c=c^(b>>13);              \
      a=a-b;  a=a-c;  a=a^(c>>12);              \
      b=b-c;  b=b-a;  b=b^(a<<16);              \
      c=c-a;  c=c-b;  c=c^(b>>5);               \
      a=a-b;  a=a-c;  a=a^(c>>3);               \
      b=b-c;  b=b-a;  b=b^(a<<10);              \
      c=c-a;  c=c-b;  c=c^(b>>15);              \
    }

    /* The whole new hash function */
    u4 bjhash(u1* k,u4 length, u4 initval)
    // register u1 *k;        /* the key */
    // u4           length;   /* the length of the key in bytes */
    // u4           initval;  /* the previous hash, or an arbitrary value */
    {
      u4 a,b,c;  /* the internal state */
      u4          len;    /* how many key bytes still need mixing */

      /* Set up the internal state */
      len = length;
      a = b = 0x9e3779b9;  /* the golden ratio; an arbitrary value */
      c = initval;         /* variable initialization of internal state */

      /*---------------------------------------- handle most of the key */
      while (len >= 12)
        {
          a=a+(k[0]+((u4)k[1]<<8)+((u4)k[2]<<16) +((u4)k[3]<<24));
          b=b+(k[4]+((u4)k[5]<<8)+((u4)k[6]<<16) +((u4)k[7]<<24));
          c=c+(k[8]+((u4)k[9]<<8)+((u4)k[10]<<16)+((u4)k[11]<<24));
          mix(a,b,c);
          k = k+12; len = len-12;
        }

      /*------------------------------------- handle the last 11 bytes */
      c = c+length;
      switch(len)              /* all the case statements fall through */
        {
        case 11: c=c+((u4)k[10]<<24);
        case 10: c=c+((u4)k[9]<<16);
        case 9 : c=c+((u4)k[8]<<8);
          /* the first byte of c is reserved for the length */
        case 8 : b=b+((u4)k[7]<<24);
        case 7 : b=b+((u4)k[6]<<16);
        case 6 : b=b+((u4)k[5]<<8);
        case 5 : b=b+k[4];
        case 4 : a=a+((u4)k[3]<<24);
        case 3 : a=a+((u4)k[2]<<16);
        case 2 : a=a+((u4)k[1]<<8);
        case 1 : a=a+k[0];
          /* case 0: nothing left to add */
        }
      mix(a,b,c);
      /*-------------------------------------------- report the result */
      return c;
    }

  public:
    hasher_t() { reset(); }
    void reset() { state = 0L; }
    uint32_t hash(vector<int> w) { hash(&w[0],w.size()); return state; }
    uint32_t hash(list<int> &L) {
      list<int>::iterator q = L.begin();
      while (q!=L.end()) hash(*q++);
      return state;
    }
    uint32_t hash(set<int> &S) {
      set<int>::iterator q = S.begin();
      while (q!=S.end()) hash(*q++);
      return state;
    }
    uint32_t hash(vector< list<int> > &VL) {
      int N = VL.size();
      for (int j=0; j<N; j++) {
        list<int> &L = VL[j];
        hash(L.size());
        hash(L);
      }
      return state;
    }

    uint32_t hash(int w) {
      state = bjhash((u1*)&w,sizeof(int),state);
      return state;
    }

    uint32_t hash(int *w,int n) {
      for (int j=0; j<n; j++) hash(w[j]);
      return state;
    }

    uint32_t hash(string s) {
      const char *sp = s.c_str();
      state = bjhash((u1*)sp,s.size(),state);
      return state;
    }
    
    // This is not completely bullet proof but it mixes the
    // pre and post order, so that two trees that have the
    // same preorder don't have the same hash. Hashes the
    // node before and after the childs. 
    void hash(tree<int> &T,tree<int>::iterator n) {
      if (n==T.end()) return;
      hash(*n);
      tree<int>::iterator c=n.lchild();
      while (c!=T.end()) hash(*c++);
      hash(*n);
    }

    uint32_t hash(tree<int> &T) {
#if 0
      // Hashes a tree. Since there is a univoque
      // relation between the tree and its (pre+post) order
      // then we build them and hash them. Doesn't work
      // because preorder is defined in eval_base_t
      list<int> L;
      preorder(T,L); hash(L);
      postorder(T,L); hash(L);
#endif
      hash(T,T.begin());
      return state;
    }
    
    uint32_t val() {
      return state;
    }

  };

  // Simple random generator class for the examples
  class randomg_t  {
  private:
    hasher_t hasher;
    uint32_t state;
  public:
    randomg_t() { reset(0); }
    void reset(uint32_t seed=0) { hasher.reset(); state=seed; }
    uint32_t rand() { 
      hasher.hash(state++); 
      return hasher.val();
    }
    double drand() { return double(rand())/UINT32_MAX; }
  };

  class chrono_t {
    double gettod() const {
#ifdef USECHRONO
      struct timeval tv;
      gettimeofday(&tv,0);
      return tv.tv_sec + 1e-6 * tv.tv_usec;
#else
      return NAN;
#endif
    }
  private:
    /// structures for `libc' time function calls.
    double start_time;
    double elaps;
    int active;
  public:
    chrono_t() { reset(); }
    /// return elapsed CPU time from start
    double elapsed() const {return elaps;};
    /// reset start time to actual time
    void reset() { elaps=0.0; active=0; };
    void start() { start_time = gettod(); active=1; }
    double stop() {
      if (active) {
        elaps += gettod()-start_time;
        active=0;
      }
      return elaps;
    }
  };
  
  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
  class eval_base_t {

  public:
    eval_base_t() : facmax(NAN), fac(NAN) {}
    //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
    static void dump(list<int> &L,string s="") {
      cout << s;
      if (s!="") cout << ": ";
      list<int>::iterator q = L.begin();
      while (q!=L.end()) cout << *q++ << " ";
      cout << endl;
    }

    //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
    static void dump(vector<int> &V,string s="") {
      cout << s; 
      vector<int>::iterator q = V.begin();
      while (q!=V.end()) cout << *q++ << " ";
      cout << endl;
    }

    //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
    static void dump(vector< list<int> > &VL,string s="") {
      int N = VL.size();
      // cout << "vector length " << N << endl;
      for (int j=0; j<N; j++) {
        cout << s << "[" << j << "]: ";
        dump(VL[j]);
      }
    }

    //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
    static void dump(list< list<int> > &LL,string s="") {
      list< list<int> >::iterator p= LL.begin();
      int j=0;
      while (p!=LL.end()) {
        list<int> &L = *p++;
        cout << s << "[" << j++ << "]: ";
        dump(L);
      }
    }
    
    //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
    static void dump(set<int> &S,string s="") {
      cout << s; 
      set<int>::iterator q = S.begin();
      while (q!=S.end()) cout << *q++ << " ";
      cout << endl;
    }

    //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
    static void dump(vector< set<int> > &VS,string s="") {
      int N = VS.size();
      for (int j=0; j<N; j++) {
        cout << s << "[" << j << "]: ";
        dump(VS[j]);
      }
    }

    //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
    static void dump(map<int,int> &M,string s="") {
      cout << s << endl; 
      map<int,int>::iterator itm = M.begin();
      while (itm != M.end()){
        cout << "M[" << itm->first <<"] = "<< itm->second << endl;
        itm++;
      }
      cout << endl;
    }

    template<class T>
    static void dump(map<int, list<T> >& M,string s="M") {
      cout << s << " = {";
      typename map<int, list<T> >::iterator p = M.begin();
      while (p!=M.end()) {
        cout << p->first << "->[";
        list<T> &L = p->second;
        typename list<T>::iterator q = L.begin();
        while (q!=L.end()) {
          // cout << (*q ? "true" : "false");
          cout << *q;
          q++;
          if (q!=L.end()) cout << ", ";
        }
        cout << "]";
        p++;
        if (p!=M.end()) cout << ", ";
      }
      cout << "}" << endl;
    }
    
  private:
    // Used to fool gcc and avoid optimization in bogomips
    static double BGDUMMY;

    list< list<int> > colas(list<int> &L) {
      list< list<int> > R;
      if (L.empty()) return R;
      list<int>::iterator it = L.begin();
      while (it != L.end()) {
        R.push_back(list<int>(it, L.end()));
        ++ it;
      }

      return R;
    }

    // Retorna todos los elementos de la lista
    // e.g.: "1 2 3 4 3 2 1" -> (1 2 3 4 3 2 1)
    void s2l(string s, list<int> &L) {
      istringstream is(s);
      int n;
      while (is >> n)
        L.push_back(n);
    }

    void s2v(string s, vector<int> &V) {
      istringstream is(s);
      int n;
      while (is >> n) V.push_back(n);
    }

    void prl(list<int> &L) {
      if (L.empty()) return;
      list<int>::iterator il = L.begin();
      for (; &*il != &*L.rbegin(); il ++)
        cout << *il << " ";
      cout << *il;
    }


    void s2m(string s, map<int, list<bool> > &M) {
      M.clear();
      istringstream is(s);

      int k, n, v;
      while (is >> k >> n) {
        list<bool> L;

        for (int i = 0 ; i < n ; i ++) {
          is >> v;
          L.push_back(v);
        }
        M[k] = L;
      }
    }

    void s2m(string s, map<int, list<int> > &M) {
      M.clear();
      istringstream is(s);
      int k, n, v;
      while (is >> k >> n) {
        list<int> L;
        for (int i = 0 ; i < n ; i ++) {
          is >> v;
          L.push_back(v);
        }
        M[k] = L;
      }
    }

    void s2m(string s, map<int, int> &M) {
      M.clear();
      istringstream is(s);
      int k, n;
      while (is >> k >> n) {
        M[k] = n;
      }
    }

    // string -> vector de listas
    // (n1 L1 n2 L2 ...)
    // "3 1 2 3 4 5 4 3 2"  -> [(1 2 3) (5 4 3 2)]
    void s2vl(string s, vector< list<int> > &v) {
      istringstream is(s);
      int n1, n2;
      while (is >> n1) {
        v.push_back(list<int>());
        for (int i = 0 ; i < n1 ; i ++) {
          is >> n2;
          v.back().push_back(n2);
        }
      }
    }

    string l2s(list<int> &L) {
      ostringstream os;
      list<int>::iterator q = L.begin();
      while (q!=L.end()) os << *q++ << " ";
      return os.str();
    }

    string ll2s(list< list<int> > &LL) {
      ostringstream os;
      list< list<int> >::iterator p=LL.begin();
      while (p!=LL.end()) {
        list<int> &L = *p++;
        os << L.size() << " " << l2s(L) << " ";
      }
      return os.str();
    }

    string g2s(map<int, list<int> > &G) {
      ostringstream os;
      map<int, list<int> >::iterator p=G.begin();
      while (p!=G.end()) {
        list<int> &L = p->second;
        os << p->first << " " << L.size() << " " << l2s(L) << "   ";
        p++;
      }
      return os.str();
    }
    
    void s2ll(string s, list< list<int> > &ll) {
      ll.clear();
      vector< list<int> > vl;
      s2vl(s,vl);
      int N = vl.size();
      for (int j=0; j<N; j++) ll.push_back(vl[j]);
    }

    void s2vs(string s, vector< set<int> > &v) {
      istringstream is(s);
      int n1, n2;
      while (is >> n1) {
        v.push_back(set<int>());
        for (int i = 0 ; i < n1 ; i ++) {
          is >> n2;
          v.back().insert(n2);
        }
      }
    }

    string vs2s(vector< set<int> > &VS) {
      ostringstream os;
      int NS = VS.size();
      for (int j=0; j<NS; j++) 
        os << VS[j].size() << " " << set2str(VS[j]) << " ";
      return os.str();
    }


    string set2str(set<int> &S) {
      ostringstream os;
      set<int>::iterator q = S.begin();
      while (q!=S.end()) os << *q++ << " ";
      return os.str();
    }

    void acum_hasta(list<int> &L, int n) {
      int acum = 0;
      list<int>::iterator it = L.begin();
      while (it != L.end()) {
        acum += *it;
        it = L.erase(it);
        if (acum >= n) {
          L.insert(it, acum);
          acum = 0;
        }
      }
      if (acum > 0) L.push_back(acum);
    }

    int readnum(string &s, unsigned int &n) {
      int k = 0;
      bool negativo = false;
      if (s[n] == '-') {
        negativo = true;
        n ++;
      }

      while (s[n] >= '0' && s[n] <= '9') {
        k *= 10;
        k += s[n] - '0';
        ++ n;
      }
      if (negativo) k *= -1;
      return k;
    }

    void tokenize(string &s,vector<string> &vs) {
      istringstream is(s);
      string token;
      while (is >> token) vs.push_back(token);
    }
    
    void lisp2tree(string s, tree<int> &T, unsigned int &i, 
                   tree<int>::iterator it) {
      while (i < s.size()) {
        while (s[i] == ' ') ++ i;
        
        if (s[i] == '(') {
          ++ i;
          while (s[i] == ' ') ++ i;
          it = T.insert(it, readnum(s, i));
          lisp2tree(s, T, i, it.lchild());
          ++ it;
        } else if (s[i] == ')') {
          ++ i;
          return;
        } else {
          it = T.insert(it, readnum(s, i));
          ++ it;
        }
      }
    }

    void preorder(tree<int> &T,tree<int>::iterator n,list<int> &L) {
      L.insert(L.end(),*n);
      tree<int>::iterator c = n.lchild();
      while (c!=T.end()) {
        preorder(T,c,L);
        c = c.right();
      }
    }

    void preorder(tree<int> &T,list<int> &L) {
      if (T.begin()==T.end()) return;
      preorder(T,T.begin(),L);
    }

    void postorder(tree<int> &T,tree<int>::iterator n,list<int> &L) {
      tree<int>::iterator c = n.lchild();
      while (c!=T.end()) {
        postorder(T,c,L);
        c = c.right();
      }
      L.insert(L.end(),*n);
    }

    void postorder(tree<int> &T,list<int> &L) {
      if (T.begin()==T.end()) return;
      postorder(T,T.begin(),L);
    }

  public:    
    template<typename Q>
    string lisp_print(tree<Q> &T,typename tree<Q>::iterator n) {
      ostringstream os;
      if (n==T.end()) return "";
      typename tree<Q>::iterator c = n.lchild();
      bool is_leaf = c==T.end();
      if (is_leaf) os << *n;
      else {
        os << "(" << *n;
        while (c!=T.end()) {
          os << " ";
          os << lisp_print(T,c++);
        }
        os << ")";
      }
      return os.str();
    }
    // -------------------------------------------------------------
    template<typename Q>
    string lisp_print(tree<Q> &T) { return lisp_print(T,T.begin()); }

    //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
    template<typename Q>
    string lisp_print(btree<Q> &T,typename btree<Q>::iterator n) {
      ostringstream os;
      if (n==T.end()) return " . ";
      typename btree<Q>::iterator
        nl = n.left(),
        nr = n.right();
      if (nl==T.end() && nr==T.end()) os << " " << *n << " ";
      else os << "(" << *n << " "
              << lisp_print(T,nl) << " "
              << lisp_print(T,nr) << ")";
      return os.str();
    }
    // -------------------------------------------------------------
    template<typename Q>
    string lisp_print(btree<Q> &T) { return lisp_print(T,T.begin()); }

    template<typename T>
    bool lisp2tree(std::stringstream &ss, aed::tree<T> &t, typename aed::tree<T>::iterator it) {
      char aux;
      std::streampos pos = ss.tellg();
      while (ss>>aux) {
        if (aux == ')') {
          return true;
        } else {
          if (aux!='(') ss.seekg(pos);
          T data; if (!(ss>>data)) return false;
          it = t.insert(it, data);
          if (aux=='(') if (!lisp2tree(ss, t, it.lchild())) return false;
          ++ it;
        }
        pos = ss.tellg();
      }
      return true;
    }
    
    
    template<typename T>
    bool lisp2tree(std::string s, aed::tree<T> &t) {
      assert(t.begin()==t.end());
      for(size_t i=0;i<s.size();i++) { // insertar espacios para que al leer strings no tome los ")" por estar pegados a las claves
        if(s[i]==')') s.insert(i++," ");
      }
      std::stringstream ss; ss<<s;
      return lisp2tree(ss,t,t.begin());
    }
    
    
    
    template<typename T>
    bool lisp2btree(std::stringstream &ss, aed::btree<T> &t, typename aed::btree<T>::iterator it, char nullchar) {
      char aux;
      std::streampos pos = ss.tellg();
      int nchild = 0;
      while (ss>>aux) {
        if (aux == ')') {
          return true;
        } else if (aux==nullchar) {
          if (++nchild==3) return false;
        } else {
          if (aux!='(') ss.seekg(pos);
          T data; if (!(ss>>data)) return false;
          if (nchild==0) {
            t.insert(it.left(), data);
            if (aux=='(') lisp2btree(ss, t, it.left(),nullchar);
          } else if (nchild==1) {
            t.insert(it.right(), data);
            if (aux=='(') lisp2btree(ss, t, it.right(),nullchar);
          } else return false;
          ++nchild;
        }
        pos = ss.tellg();
      }
      return true;
    }
    
    
    template<typename T>
    bool lisp2btree(std::string s, aed::btree<T> &t, char nullchar='.') {
      assert(t.begin()==t.end());
      for(size_t i=0;i<s.size();i++) { // insertar espacios para que al leer strings no tome los ")" por estar pegados a las claves
        if(s[i]==')') s.insert(i++," ");
      }
      std::stringstream ss; ss<<s;
      char aux; T data; if (!(ss>>aux>>data)||aux!='(') return false;
      t.insert(t.begin(),data);
      return lisp2btree(ss,t,t.begin(),nullchar);
    }
    
  private:    
    void preorder(btree<int> &T,btree<int>::iterator n,list<int> &L) {
      if(n==T.end()) return;
      L.insert(L.end(),*n);
      preorder(T,n.left(),L);
      preorder(T,n.right(),L);
    }

    void preorder(btree<int> &T,list<int> &L) {
      if (T.begin()==T.end()) return;
      preorder(T,T.begin(),L);
    }

    void postorder(btree<int> &T,btree<int>::iterator n,list<int> &L) {
      if(n==T.end()) return;
      postorder(T,n.left(),L);
      postorder(T,n.right(),L);
      L.insert(L.end(),*n);
    }

    void postorder(btree<int> &T,list<int> &L) {
      if (T.begin()==T.end()) return;
      postorder(T,T.begin(),L);
    }

    //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
    void make_random_btree(btree<int> &t,btree<int>::iterator n,
                           int m,int level,double siblings,
                           randomg_t &rnd) {
      btree<int>::iterator c;
      double lambda,nivel;
      n=t.insert(n,rnd.rand()%m);
      nivel=double(level);
      lambda = 1.0/(siblings/nivel+1.0);
      for (int j=0;j<2;j++) {
        if  (j==0) {
          c=n.left();}
        else {
          c=n.right();
        }
        unsigned int MAX = 100000;
        double x = double(rnd.rand()%MAX)/MAX;
        if (x>lambda) make_random_btree(t,c,m,level+1,siblings,rnd);
      }
    }

    // -----------------------------------------------------------------
    void make_random_btree(btree<int> &t,int m,double siblings,
                           randomg_t &rnd) {
      t.clear();
      make_random_btree(t,t.begin(),m,0,siblings,rnd);
    } 

    void hash(hasher_t &hasher,tree<int> &T) {
      list<int> L;
      preorder(T,L);
      list<int>::iterator q=L.begin();
      while (q!=L.end()) hasher.hash(*q++);

      L.clear();
      postorder(T,L);
      q=L.begin();
      while (q!=L.end()) hasher.hash(*q++);
    }

    void hash(hasher_t &hasher,btree<int> &T) {
      list<int> L;
      preorder(T,L);
      list<int>::iterator q=L.begin();
      while (q!=L.end()) hasher.hash(*q++);

      L.clear();
      postorder(T,L);
      q=L.begin();
      while (q!=L.end()) hasher.hash(*q++);
    }

    void hash(hasher_t &hasher,set<int> &S) {
      set<int>::iterator q = S.begin();
      while (q!=S.end()) hasher.hash(*q++);
    }

    double bogomips() {
      randomg_t rnd;
      double factor = 1.0;
      int N = 100000000*factor;
      chrono_t chrono;
      chrono.start();
      for (int j=0; j<N; j++) BGDUMMY = rnd.rand();
      chrono.stop();
      double elapsed = chrono.elapsed();
      // printf("elapsed %f\n",elapsed);
      double refelapsed = 2.6119*factor; // In my laptop
      return refelapsed/elapsed;
    }

  public:

    //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
    // Recursive aux function for make_random_tree2(T,M,m,s,rnd);
    void make_random_tree2(tree<int> &T,tree<int>::iterator n,
                           int M, int m,int s,
                           randomg_t &rnd) {
      if (!m) return;
      // Toma los m nodos y los divide en `ss' siblings donde s es aleatorio
      // en [1,s]
      int ss = rnd.rand()%s+1;
      // Inserta un nodo en la raiz
      n = T.insert(n,rnd.rand()%M);
      m--; // toma en cuenta que ya inserto 1
      // Reparte los nodos que quedan aleatoriamente en los ss hijos
      vector<int> v(ss,0);
      for (int j=0; j<m; j++) v[rnd.rand()%ss]++;
      // A esta altura tenemos un vector v[] con s enteros
      // cuya suma es `m'.  Algunos pueden ser nulos, pero no importa
      // porque en ese caso la llamada recursiva no va a hacer nada. 
      for (unsigned int j=0; j<v.size(); j++) 
        make_random_tree2(T,n.lchild(),M,v[j],s,rnd);
    }

    //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
    // Makes a random tree with `s' siblings and `m' nodes.
    // The value at the node is in [0,M)
    void make_random_tree2(tree<int> &T,int M, int m,int s,
                           randomg_t &rnd) {
      T.clear();
      make_random_tree2(T,T.begin(),M,m,s,rnd);
    }

    void lisp2tree(string s, tree<int> &T) {
      unsigned int i = 0;
      lisp2tree(s, T, i, T.begin());
    }

    const char *i2s(int ok) { return (ok ? "OK" : "MAL"); }

    virtual void run_case(json &data,json &output)=0;

    // Unpacks data and runs the user function. Compares
    // the value returned by user with the ref value
    // Return 1/0 if the result is OK
    virtual int check_case(json &data,
                           json &outref,json &outuser)=0;

    // Uses `rnd' to generate a test case
    virtual void generate_case(randomg_t &rnd,json &data)=0;
    
    int ejerc,dumptests;
    string testfile;
    double facmax, fac;
    void evfun(int vrbs=0,int ucase=-1) {
      cout << "----------------\nEvaluando ejercicio " 
           << ejerc << endl;
      ifstream in(testfile);
      json tests;
      in >> tests;
      int caso = 0, okt = 0;
      auto p = tests.begin();
      while (p!=tests.end()) {
        if (ucase>=0 && ucase!=caso) { caso++; return; }

        json outuser, &datain=(*p)["datain"], &outref=(*p)["output"];
        run_case(datain,outuser);
        int ok = check_case(datain,outref,outuser);
      
        if (!ok || vrbs) {
          printf("\nEJ%d|CASO %0d-- Datos: \n",ejerc,caso);
          cout <<  datain.dump() << endl;
          printf("--------- Output(user): \n");
          cout <<  outuser.dump() << endl;
          printf("--------- Output(ref): \n");
          cout <<  outref.dump() << endl;
        }
        if (vrbs || !ok)
          cout << "EJ" << ejerc << "|Caso " 
               << caso << ". Estado: " << i2s(ok) << endl;
        okt += ok; 
        p++; caso++;
      }
      
      int total = caso;
      printf("ESTADO EJ%d Total %d, ok %d, mal %d. Todos bien? %s\n",
             ejerc,total,okt,total-okt,i2s(okt==total));
    }

    //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
    int evrandom(int seed,int vrbs=0,int hardness=0) {
      double mips = NAN;
      if (hardness==5) {
#ifndef USECHRONO
        cout << "Usando hardness>=5 y no fue compilado con USECHRONO" << endl;
        abort();
#endif
        mips=bogomips();
      }
      int ncasos=50;
      hasher_t hasher;
      randomg_t rnd;
      rnd.reset(seed);
      chrono_t chrono;
      if (!std::isnan(facmax)) {
        // Tricky: hardness==5 means hardness=4 and normalize
        int h = (hardness>= 5? 4 : hardness);
        fac = pow(facmax,h/4.0);
      }

      json tests;
      chrono.reset();
      for (int caso=0; caso<ncasos; caso++) {
        if (vrbs>=2 && !hardness)
          printf("Ejerc %d. Caso %d\n",ejerc,caso);

        json datain,outuser;
        generate_case(rnd,datain);
        chrono.start();
        run_case(datain,outuser);
        chrono.stop();
        if (dumptests) {
          json thiscase;
          thiscase["datain"] = datain;
          thiscase["output"] = outuser;
          tests.push_back(thiscase);
        }
        hasher.hash(outuser.dump());
      }

      if (dumptests) cout << tests.dump(3) << endl;

      if (hardness) {
        cout << "EJ" << ejerc << ". Hardness "
             << hardness << ", elapsed " << chrono.elapsed() << "[s]";
        if (hardness==5) 
          cout << " (mips " << mips << ", relative "
               << chrono.elapsed()*mips << "[s])";
        cout << endl;
      }
      int H = hasher.val()%1000;
      if (vrbs && !hardness)
        printf("EJ%d: SEED=%03d, HASH=%03d\n",ejerc,seed,H);
      return H;
    }
    
    //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
    static void dump(stack<int> S,string s="") {
      cout << s; 
      while (!S.empty()){
        cout << S.top() << " ";
        S.pop();
      }
      cout << endl;
    }

    //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
    static void dump(queue<int> Q,string s="") {
      cout << s; 
      while (!Q.empty()){
        cout << Q.front() << " ";
        Q.pop();
      }
      cout << endl;
    }
	
    //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
    void s2sta(string s, stack<int> &S){
      istringstream is(s);
      int n;
      while (is >> n)
        S.push(n);
    }
	
    void random_shuffle(randomg_t &rnd,vector<int> &v,int k1,int k2) {
      int n = k2-k1;
      if (n<=1) return;
      int n1 = n/2, n2 = n-n1, j1=k1, j2=k1+n1;
      this->random_shuffle(rnd,v,k1,j2);
      this->random_shuffle(rnd,v,j2,k2);
      vector<int> w;
      while (n1 || n2) {
        int choose1 = int(rnd.rand()%(n1+n2))<n1;
        if (choose1) { w.push_back(v[j1++]); n1--; }
        else { w.push_back(v[j2++]); n2--; }
      }
      for (int j=0; j<n; j++) v[k1+j] = w[j];
    }

    void random_shuffle(randomg_t &rnd,vector<int> &v) {
      this->random_shuffle(rnd,v,0,v.size());
    }

    void l2v(const list<int> &L,vector<int> &v) {
      v.clear();
      list<int>::const_iterator p = L.begin();
      while (p!=L.end()) v.push_back(*p++);
    }

    void v2l(const vector<int> &v, list<int> &L) {
      L.clear();
      int N = v.size();
      for (int j=0; j<N; j++) L.push_back(v[j]);
    }
    
    void random_shuffle(randomg_t &rnd,list<int> &L) {
      vector<int> v;
      l2v(L,v);
      random_shuffle(rnd,v);
      v2l(v,L);
    }
  };
  double eval_base_t::BGDUMMY=0.0;

}
#undef CSTR


template<int N, typename... Ts>  class var_eval_t;

template<int N> class var_eval_t<N> {
protected:
  static constexpr int level=N+1;
public:
  void eval() { }
  int evalr() { return -1; }
};

template<int N,typename class_t, typename func_t, typename... Ts> 
class var_eval_t<N, class_t,func_t,Ts...> : public var_eval_t<N+1,Ts...> {
  class_t ev;
 protected:
  static constexpr int level = var_eval_t<N+1,Ts...>::level-1;
 public:
	
  using var_eval_t<N+1,Ts...>::eval;
  using var_eval_t<N+1,Ts...>::evalr;
	
  template<int M>
    void eval(typename enable_if<M==level,func_t>::type F,
              int vrbs,int ucase=-1) {
    ev.F = F;
    ev.evfun(vrbs,ucase);
  }
  template<int M>
    int evalr(typename enable_if<M==level,func_t>::type F,
              int vrbs,int ucase=-1,int hardness=0) {
    ev.F = F;
    return ev.evrandom(vrbs,ucase,hardness);
  }
	
};

template<typename... Ts> using eval_t = var_eval_t<0,Ts...>;

#endif
