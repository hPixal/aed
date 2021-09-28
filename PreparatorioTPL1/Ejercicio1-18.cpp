#include <iostream>
#include <list>
#include <vector>

using namespace std;

void sign_split(list<int> &L,vector< list<int> > &VL);

int main(){


    return 0;
}

void sign_split(list<int> &L,vector< list<int> > &VL){
    auto it = L.begin();
    int aux = *it;
    list<int> auxlist;

    while (it != L.end())
    {
        if (aux<0 && *it < 0 || aux>=0 && *it >= 0)
        {
            auxlist.push_back(*it);
            aux = *it;
        }else{
            VL.push_back(auxlist);
            auxlist.clear();
        }
    }
}