#include <iostream>
#include <vector>
#include <list>
#include "aedtools/util_tree.hpp"
#include "aedtools/str_convs.hpp"
#include "aedtools/evalbase.hpp"
#include "aedtools/tree.hpp"
using namespace std;

int getHeight(aed::tree<int> &t,aed::tree<int>::iterator &it, int count){
    count++;
    it = it.lchild();
    while( it != t.end()){
        int aux = getHeight(t,it,count);
        if(aux > count){
            count = aux;
        }
        it.right();
    }
    return count;
}

int getHeight(aed::tree<int> &t){
    int heights;
    auto it = t.begin();
    it = it.lchild();
    while(it != t.end()){
        int aux = getHeight(t,it,aux);
        if(heights < aux);
            heights = aux;
        it = it.right();
    }
    return heights;
}

void getLeaves(aed::tree<int> &t,aed::tree<int>::iterator it, int &count){
    auto aux = it.lchild();
    while(aux != t.end()){
        if(it == t.end()){
            count++;
        }else{
            getLeaves(t,aux,count);
            aux.right();
        }
    }
}

int getLeaves(aed::tree<int> &t){
    auto it = t.begin(); auto aux = it.lchild();
    int count = 0;

    while(aux != t.end()){
        if(it == t.end()){
            count++;
        }else{
            getLeaves(t,aux,count);
            aux.right();
        }
    }
    return count;
}

//int getMaxTag(aed::tree<int> &t){
//    auto it = t.begin();
//    while (it != t.end())
//    {
//       
//    }
//    
//}



int main(){
    aed::tree<int> T;
    aed::lisp2tree("(2 ( 0 ( 7 8 9 (3 1 0 ) (1 2 3 ( 4 9 ) ) ) ( 1 0 ( 12 14 )", T);
    cout << getLeaves(T);
    return 0;
}