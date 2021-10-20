#include <iostream>
#include <map>
#include <list>

/*
ColoreadoGrafos. Partiendo del modelado de los problemas de coloraci ́on de
 grafos de la Gu ́ıa 1,implementar funciones que reciban como par ́ametro el 
 grafo (map<int,list<int>>) que modelacada problema y encuentre, mediante una 
 estrategia de coloreo heur ́ıstica, una soluci ́on posible.
*/

using namespace std;
typedef map<int,list<int>> graph;

bool checkAmoutOfColors(graph g, int size){
    auto it = g.begin(); int cont; int acum;
    while(it != g.end()){
        cont++;
        acum+= static_cast<int>(it->second.size());
        it++;
    }
    if ((acum/cont)>size)
        return false;
    return true;
}

list<int> getNeighbours()

void getColors(graph &g, map<int,string> &colours, map<int,int> &colored, graph::iterator mother){
    auto it = mother->second.begin(); auto cl = colours.begin();
    while(it != mother->second.end()){
        bool colored = false;
        while(colored){
            
        }
        it++;
    }
}

map<int,int> colourGraph(graph &g, map<int,string> c){
    auto mother = g.begin(); map<int,int> colored;
    colored[mother->first] = c.begin()->first;

    if(checkAmoutOfColors(g,c.size())){

    }
}

int main(){

    return 0; 
}