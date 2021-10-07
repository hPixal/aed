#include <iostream>
#include <map>
#include <list>
using namespace std;
typedef map<int,list<int>> graph;

/*
isHamilt. Dado un grafomap<int, list<int> >Gy una lista de v ́ertices
list<int> L determinar si L es un camino hamiltoniano en G
*/
bool isThere(list<int> l, int f){
    for(auto x = l.begin(); x!=l.end() ; ++x){
        if(*x == f)
            return true;
    }
    return false;
}

bool isPath(graph &g, list<int> &l,list<int>::iterator it){

    auto retrieve = g.find(*it);

    if (retrieve != g.end() && it != l.end())
    {
        auto aux = it; ++aux;
        if( aux == l.end())
            return true;
        if(isThere(retrieve->second,*(aux)))
            return isPath(g,l,++it);

    }
    return false;
}

bool isPath(graph &g, list<int> &l){
    auto it = l.begin();
    if (g.find(*it) != g.end())
    {
        return isPath(g,l,++it);
    }
    return false;
}

bool isHamilt(graph &g, list<int> &l){
    if(l.size() > g.size()){
        return false;
    }
    for(auto x : l){
        int repcount = 0;
        for(auto y : l){
            if(x == y)
                repcount++;
            if(repcount == 2)
                return false;
        }
    }
    
    return isPath(g,l);
}

int main(){
    graph G={
		{0,{1}},
	{1,{0,3,4}},
		{2,{3,4}},
	{3,{1,2}},
		{4,{1,2}}
	};

    list<int> c1 = { 0 , 1 , 3 , 2 , 4 };
    list<int> c2 = { 0 , 1 , 3 , 2 , 4 , 1};
    list<int> c3 = { 0 , 1 , 2 , 3 , 4 };
    if(isHamilt(G,c1))
        cout << "todo piola con el c1" << endl;
    if(isHamilt(G,c2))
        cout << "todo piola con el c2" << endl;
    if(isHamilt(G,c3))
        cout << "todo piola con el c3" << endl;
    return 0;
}