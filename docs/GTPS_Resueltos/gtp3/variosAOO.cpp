#include <iostream>
#include <version>
#include <map>
#include <list>
#include "tree.hpp"
#include "str_convs.hpp"
#include "util_tree.hpp"
//#include "str_convs.hpp"
using namespace aed;
using namespace std;

/*
    Este archivo es solo de ejemplo. Usalo para resolver los ejercicios, ya que este
    en esta carpeta especifica y con este nombre especifico, es el unico con el que 
    funciona la utilería de la catedra. Se puede usar como plantilla para luego cam
    biarle el nombre a uno más apropiado y entregarlo como resolción.
*/

void getHeight(tree<int> &arbol, tree<int>::iterator pos,
            int &count, int &maxcount){

    if (pos == arbol.end()) return;

    auto c = pos.lchild();

    while (c != arbol.end()){ getHeight(arbol,c++,++count,maxcount); }

    if (count > maxcount){ maxcount = count;}
    --count;
}

int getHeight(tree<int> &arbol){
    int count = 0; int maxcount = 0; auto pos = arbol.begin();
    getHeight(arbol,pos,count,maxcount);
    return maxcount;
}

/////////////////////////////////////////////////////////////////////////////

void getLeaves(tree<int> &t,tree<int>::iterator it, int &count){

    if (it == t.end()) return;

    auto child = it.lchild();
    if (child == t.end()) ++count;

    while (child != t.end()) getLeaves(t,child++,count);
}

int getLeaves(tree<int> &t){
    auto beg = t.begin();
    int count = 0;
    getLeaves(t,beg,count);
    return count;
}


/////////////////////////////////////////////////////////////////////////////

void getMaxTag(tree<int> &tr,tree<int>::iterator pos, int &mxTAG){
    if (pos == tr.end()) return;

    auto child = pos.lchild();
    
    while(child != tr.end()){
        if(*child > mxTAG){ mxTAG=*child; }
        getMaxTag(tr,child++,mxTAG);
    }

}

int getMaxTag(tree<int> &tr){
    auto pos = tr.begin(); int mxTAG = *pos;
    getMaxTag(tr,pos,mxTAG);
    return mxTAG;
}

/////////////////////////////////////////////////////////////////////////////

bool isLeaf(tree<int>::iterator node, const tree<int>::iterator end){
    return (node.lchild() == end);
}

void getMaxTagLeafs(tree<int> &tr,tree<int>::iterator pos, int &mxTAG){
    if (pos == tr.end()) return;

    auto child = pos.lchild();
    
    while(child != tr.end()){
        if(*child > mxTAG && isLeaf(child,tr.end())){ mxTAG=*child; }
        getMaxTagLeafs(tr,child++,mxTAG);
    }
}

int getMaxTagLeafs(tree<int> &tr){
    auto pos = tr.begin(); int mxTAG = *pos;
    getMaxTagLeafs(tr,pos,mxTAG);
    return mxTAG;
}

/////////////////////////////////////////////////////////////////////////////

void getSum(tree<int> &tr,tree<int>::iterator pos, int &TAGsum){
    if (pos == tr.end()) return;
    auto child = pos.lchild();
    while(child != tr.end()){
        TAGsum+= *child;
        getSum(tr,child,TAGsum);
        child = child.right();
    }
}
int getSum(tree<int> &tr){
    auto pos = tr.begin(); int TAGsum = *pos;
    getSum(tr,pos,TAGsum);
    return TAGsum;
}

/////////////////////////////////////////////////////////////////////////////
/*
tree<int>::iterator removeCell(tree<int> &tr,tree<int>::iterator pos){
    if(pos == tr.end()) return tr.end();
    auto child = pos.lchild();


    while(child != tr.end()){
        child = removeCell(tr,child);
    }

    return tr.erase(pos);
}
*/
void removeUneven(tree<int> &tr,tree<int>::iterator pos){
    if (pos == tr.end()) return;
    auto child = pos.lchild();
    while(child != tr.end()){
        if(*child%2 != 0){
            child = tr.erase(child);
        }else{
            removeUneven(tr,child);
            child = child.right();
        }
    }
}

void removeUneven(tree<int> &tr){
    auto pos = tr.begin(); int TAGsum = *pos;
    removeUneven(tr,pos);
}

int main(){
    tree<int> tr;
    make_random_tree(tr,10,3);
    list<int> pre;

    print_tree(tr);
    removeUneven(tr);
    print_tree(tr);
    //int h = getHeight(tr);
    //int l = getLeaves(tr);
    //int t = getSum(tr);
    //cout << " " << t;
    /*    
    print_tree(t);
    for(auto x : pre){
        cout << x << " ";
    }
    */
    return 0;
}