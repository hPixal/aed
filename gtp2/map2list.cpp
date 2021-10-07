#include <iostream>
#include <map>
#include <list>
using namespace std;

/*
1)map2list. Escribir una funci ́on que dado un mapMretorna las listas de 
claves y valores, utilice lasignaturavoid map2list(map<int,int> &M, 
list<int> &Keys, list<int> &Vals). Ejemplo:siM={1->2, 3->5, 8->20}, 
entonces debe retornarKeys = (1,3,8)yVals = (2,5,20)
*/

void map2list(map<int,int> &M, list<int> &Keys, list<int> &Vals);

int main(){
    map<int,int> test;
    test[1] = 40;
    test[2] = 50;
    test[3] = 60;
    test[4] = 70;

    /*
    for(auto it = test.begin(); it != test.end(); ++it){
        cout << it->first << " " <<  it->second << endl;
    }
    */

   list<int> keys;
   list<int> vals;

    map2list(test,keys,vals);
    auto itv = vals.begin();
    auto itk = keys.begin();

    while (itk != keys.end())
    {
        cout << *itk << " " << *itv << endl;
        ++itk; ++itv;
    }
    

    return 0;
}

void map2list(map<int,int> &M, list<int> &Keys, list<int> &Vals){
    auto it = M.begin();
    Keys.clear(); Vals.clear();

    while (it != M.end())
    {
        Keys.push_back(it->first);
        Vals.push_back(it->second);
        ++it;
    }
    
}