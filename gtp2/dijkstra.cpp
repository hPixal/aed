#include <iostream>
#include <map>
#include <list>

/*
Dijkstra. Programefloat Dijkstra(graphW& G, int u, int v, list<int>&path)
que dado elgrafo ponderadoGdefinido como typedef map<int,map<int,float>> graphW;, 
implemente elalgoritmo de Dijkstra para retornar el costo del camino m ́as corto
entre el v ́ertice de partida u y elv ́ertice de llegadav. Adem ́as debe devolver
en path uno de los posibles caminos. Si no hay camino posible, 
retornar un n ́umero muy grande (infinito).
*/

using namespace std;
typedef map<int,list<int>> graph;
typedef map<int,map<int,float>> graphW;









/*
int Dijkstra(graphW& G, 
			 char ini, 
			 char fin, 
			 list<char>& path){

	map<char,bool> visitados;
	map<char,pair<int,char>> acum;
	
	for(auto node:G){
		acum[node.first] = {inf,'-'};
	}
	acum[ini] = {0,'-'};
	char currentnode = ini;
	
	while(currentnode!=fin){
		visitados[currentnode];
		map<char,int>& adyacentes = G[currentnode];
		
		int w = acum[currentnode].first;
		///actualizar la tabla de los vecinos
		for(auto vecino:adyacentes){
			char label = vecino.first;
			if(visitados.find(label)==visitados.end()){
				int new_w = w + vecino.second; 
				if(new_w < acum[label].first){
					acum[label].first = new_w;
					acum[label].second = currentnode;
				}				
			}
		}
		///seleccionar el siguiente nodo a evaluar
		///entre los no visitados
		///buscar el de menor peso en la tabla acum
		int minw = inf;
		for(auto columna:acum){
			if(visitados.find(columna.first)==visitados.end()){
				if(columna.second.first < minw){
					minw = columna.second.first;
					currentnode = columna.first;
				}
			}
		}
		
	}
	///generar la lista 'hacia atras'
	while(currentnode!=ini){
		path.push_front(currentnode);
		currentnode = acum[currentnode].second;
	}
	path.push_front(currentnode);
	
	return acum[fin].first;
	
}
*/


const bool checkIfVisited(map<int,bool> &vis,int chk){
    return (vis.find(chk)->second == true); 
}

int getCheaper(graphW::iterator &it,map<int,bool> vis){
    auto compare = -1;
    for(auto x = it->second.begin(); x != it->second.end() ; ++x){
        if(compare > x->second && checkIfVisited(vis,x->first)){
            compare = x->second;
            vis[x->first] = false;
        }
    }
    return compare;
}

void getMinWeights(graphW& G,map<int,float> &weight,map<int,bool> vis, graphW::iterator mother){
    auto it = mother->second.begin();
    while(it != mother->second.end()){
        if(!checkIfVisited(vis,it->first)){
            
        }
    }
}

float Dijkstra(graphW& G, int u, int v, list<int>&path){
    map<int,bool> vis; map<int,float> weight;
}