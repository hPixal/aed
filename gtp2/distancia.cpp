#include <iostream>
#include <map>
#include <list>
using namespace std;
typedef map<int,list<int>> graph;

/*
Distancia. Dado un grafo map<int,list<int>> G y un vértice de partida x se desea 
determinar la distancia este al resto de los vértices en G. Se solicita 
retornar una estructura de capas de vecinosde G al rededor de x definida de la 
siguiente forma: la capa 0 es{x}, la capa 1 son los vecinos de x.
A partir de allí la capan >= 2 está formada por los vecinos de los vértices de 
la capa n−1 (esdecir la adyacencia de la capa) pero que no están en las capas 
anteriores (en realidad basta converificar que no estén en las capas n−1 ni n−2). Notar que los v ́ertices en la capanseencuentran a una distanciandel v ́ertices de partida 
*/
void getTags(graph::iterator &mother,map<int,bool> &visited, map<int,int> &tags,int &tagcost){
    auto it = mother->second.begin();

    while(it != mother->second.end()){
        if (visited.find(*it) != visited.end())
        {
            visited[*it] = true;
            tags[*it] = tagcost;
        }
    }
    tagcost++;
}

map<int,int> fetchDistance(graph g, int mother){
    map<int,bool> visited; map<int,int> tags;
    int tagcost = 1;

    
}

int main(){

    return 0;
}