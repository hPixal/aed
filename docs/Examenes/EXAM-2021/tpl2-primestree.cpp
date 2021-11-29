#include <iostream>
#include <version>
#include <vector>
#include <map>
#include <list>
#include <set>
#include <math.h>
#include "tree.hpp"
//#include "btree.hpp"
#include "util_tree.hpp"
//#include "str_convs.hpp"
using namespace aed;
using namespace std;

//typedef btree<int>::iterator bnode;


 void countheight(tree<int> &tr,tree<int>::iterator itr,map<int,int> &count,int level){
    if(itr == tr.end()) return; 
    if(count.find(level) == count.end()) count[level] = 0;
    count[level] = count[level]+1;
    auto child = itr.lchild();
    while (child != tr.end())
    {
        countheight(tr,child,count,level+1);
        child = child.right();
    }
    
 }

 void countheight(tree<int> &tr,map<int,int> &count){
    count.empty();
    if (tr.empty())
    {
        count[0] = 0;
        return;
    }
    countheight(tr,tr.begin(),count,0);
 }

void decomp(int it, int &comp1, int &comp2){
	
	comp1=sqrt(it);
	
	while(comp1!=1){
		
		if (it%comp1==0){
			comp2=it/comp1;
			return;
		}
		--comp1;
	}
	if (comp1==1){
    comp2=it;
    return;
  }

	
}

void primestree(tree<int> &tr, tree<int>::iterator it, int num) {

int comp1,comp2;
decomp(num,comp1,comp2);
  
if (comp1==1) return;

auto child = it.lchild();

child = tr.insert(child,comp1);
primestree(tr,child,comp1);

++child;
child=tr.insert(child,comp2);
primestree(tr,child,comp2);
  
}

void primestree(tree<int> &tr, int num) {
  tr.clear();
  tr.insert(tr.begin(),num);
  primestree(tr,tr.begin(),num);
  
}


/*
    Este archivo es solo de ejemplo. Usalo para resolver los ejercicios, ya que este
    en esta carpeta especifica y con este nombre especifico, es el unico con el que 
    funciona la utilería de la catedra. Se puede usar como plantilla para luego cam
    biarle el nombre a uno más apropiado y entregarlo como resolción.
*/


int main(){
    tree<int> tr;
    primestree(tr,315);
    print_tree(tr);
    return 0;
}