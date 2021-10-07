#include <iostream>
#include <map>
#include <list>
using namespace std;

/*
Camino. Implemente la funci ́onbool es_camino(map<int,list<int>> G, 
list<int> &L)querecibe una listaLy determina si es o no camino en el 
grafoG. El grafo se representa como unmapa que relaciona cada v ́ertice 
(clave) con la lista de sus v ́ertices adyacentes (valor)
*/

/* 
   Mirá probablemente existe una implementación menos quilombera, pero
   esta es la que me salió y hasta ahora funciona.
*/

bool es_camino(map<char,list<char>> G,char mother, char child){
    bool cond1 = false; bool cond2 = false;
    for(auto it = G.begin() ; it != G.end() ; ++it ){
        if(it->first == mother)
            { cond1 = true; break; }
    }
    if(cond1 && child != -1){
        for(auto it = G[mother].begin() ;
            it != G[mother].end(); ++it ){
                if(*it == child)
                { cond2 = true; break; }
            }
    }
    if(child == '1'){
        cond2 = true;
    }
    return (cond1 && cond2);
}

bool es_camino(map<char,list<char>> G, list<char> &L){
    
    if(!G.empty() && G.size() > 1){
        auto itfront = L.begin(); itfront++;
        auto itback = L.begin();
        while(true){
            if(es_camino(G,*itback,*itfront) == false){
                return false;
            }
            itback++;
            itfront++;
            if (itfront == L.end())
            {   
                return es_camino(G,*itback,'1');
                break;
            }
        }
    }else if (G.size() == 1 && L.size() == 1)
    {
        es_camino(G,*L.begin(),-1);
    }
    return false;
}

int main(){

    list<char> test = {'a','b','f','m','t'};
    
    map<char,list<char>> G;
    G['a'] = {'b','c','d'};
    G['b'] = {'e','f'};
    G['e'] = {'k'};
    G['k'] = { };
    G['f'] = {'l','m'};
    G['m'] = {'t'};
    G['t'] = { };

    if (es_camino(G,test))
    {
        cout << "no se ni yo como funcionó, pero lo hizo" << endl ;
    } else {
        cout << "no che, ni ahi que es camino" << endl;
    }
    

    return 0;
}