#include <iostream>
#include <version>
#include <vector>
#include <map>
#include <list>
#include "btree.hpp"
using namespace aed;
using namespace std;

typedef btree<int>::iterator bnode;

void preorder(const btree<int> &t, list<int> &l, btree<int>::iterator it){
    if(it == t.end()) return;
    l.push_back(*it);
    preorder(t,l,it.right());
    preorder(t,l,it.left());
}


list<int> preorder(const btree<int> &t){
    auto it = t.begin(); list<int> rtrn;
    while(rtrn.size() != t.size()){
        preorder(t,rtrn,it);
    }

    return rtrn;
}

void posorder(const btree<int> &t, list<int> &l, btree<int>::iterator it){
    if(it == t.end()) return;

    posorder(t,l,it.right());
    posorder(t,l,it.left());

    l.push_back(*it);
}


list<int> posorder(const btree<int> &t){
    auto it = t.begin(); list<int> rtrn;
    while(rtrn.size() != t.size()){
        posorder(t,rtrn,it);
    }

    return rtrn;
}

void inorder(const btree<int> &t, list<int> &l, btree<int>::iterator it){
    if(it == t.end()) return;

    inorder(t,l,it.right());
    l.push_back(*it);
    inorder(t,l,it.left());
}

list<int> inorder(const btree<int> &t){
    auto it = t.begin(); list<int> rtrn;
    while(rtrn.size() != t.size()){
        inorder(t,rtrn,it);
    }

    return rtrn;
}

/*Extra: crear un arbol binario */

void create_btree(btree<int> &tr,bnode it,int level,int count){
    if(count > level) return;
    it = tr.insert(it,count/*int(rand()%40)*/);

    bnode nextr = it.right();
    bnode nextl = it.left();

    create_btree(tr,nextr,level,count+1);
    create_btree(tr,nextl,level,count+1);
}

void create_btree(btree<int> &tr,int level){
    tr.clear();
    create_btree(tr,tr.begin(),level,0);
}

int main(){
    btree<int> tr;
    create_btree(tr,2);
    auto l = inorder(tr);

    cout << "{ ";
    for(auto x : l){
        cout << x << " ";
    }
    cout << " }" << endl;

    
    return 0;
}