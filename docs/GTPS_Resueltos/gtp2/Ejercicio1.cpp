#include <iostream>
#include <map>
#include <list> 
using namespace std;

/*
map2list. Escribir una funci ́on que dado un mapMretorna las listas de 
claves y valores, utilice lasignaturavoid map2list(map<int,int> &M, 
list<int> &Keys, list<int> &Vals). Ejemplo:siM={1->2, 3->5, 8->20}, 
entonces debe retornarKeys = (1,3,8)yVals = (2,5,20)
*/

void map2list(map<int,int> &M,list<int> &Keys, list<int> &Vals){
    auto it= M.begin();
    while (!M.empty())
    {
        Keys.push_back(it->first);
        Vals.push_back(it->second);
        ++it;
    }
    cout << "se termino" << endl;
}

void show(const list<int> )

int main(){
    list<int> ejKey;
    list<int> ejVals;
    map<int,int> ejMap;
    
    ejMap[999] = 404;
    ejMap[3312] = 666;

    map2list(ejMap,ejKey,ejVals);
    

    return 0;
}