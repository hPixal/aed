#include <iostream>
#include <map> 
#include <list>
using namespace std;
typedef map<int,list<int>> graph;

/*
CompConexa. Dado un grafo como map<int,list<int>> Gencontrar los 
subconjuntos del mismolist<list<int>> Dque est ́an desconectados, es decir, 
los conjuntos de v ́ertices de cada una de lascomponentes conexas. 
Por ejemplo, siG={1->{2},2->{1},3->{4},4->{3}}, entonces 
deberetornarD=({1,2},{3,4}). La signatura de la funci ́on a implementar es
void comp_conexas(map<int,list<int>> &G, list<list<int>> &D)
*/

/*
void genCompConexa(graph& G, map<int,bool>& visitados, int label, list<int>& cc) {
	visitados[label];
	cc.push_back(label);
	list<int>& adyacentes = G[label];
	for(auto vecino:adyacentes){
		if(visitados.find(vecino)==visitados.end()){
			genCompConexa(G,visitados,vecino,cc);
		}
	}
}

list<list<int>> compConexas(graph& G){
	list<list<int>> CC;
	map<int,bool> visitados;
	
	while(visitados.size()<G.size()){
		int label;
		///busco algun vertice que no haya sido visitado
		for(auto vertice:G){
			if(visitados.find(vertice.first)==visitados.end()){
				label = vertice.first;
				break;
			}
		}
		///generar su componente conexa
		list<int> cc;
		genCompConexa(G,visitados,label,cc);
		
		CC.push_back(cc);
	}
	
	return CC;
}
*/

list<int> getConnections(graph &G, int mother, map<int,bool> &vis){
    list<int> rtrn;
    auto it = G[mother].begin();
    while(it != G[mother].end()){
        if(vis.find(*it) == vis.end()){
            vis[*it] = true;
            rtrn.push_back(*it);
            list<int> aux = getConnections(G,*it,vis);
            aux.sort();
            rtrn.sort();
            rtrn.merge(aux);
        }
        ++it;
    }
    return rtrn;
}

void comp_conexas(graph &G, list<list<int>> &D){
    auto it = G.begin();
    D.empty();
    map<int,bool> visited;
    while(visited.size() != G.size()){
        auto aux = it->first;
        if(visited.find(aux) == visited.end()){
            D.push_back(getConnections(G,it->first,visited));
        }
		++it;
    }
}

int main() {
	graph G={
		{0,{1}},
	{1,{0,3,4}},
		{2,{3}},
	{3,{1,2}},
		{4,{1}},
	{5,{6}},
		{6,{5,7}},
	{7,{6}}
	};
	list<list<int>> CC;
    comp_conexas(G,CC);
	
	cout<<"Componentes conexas: "<<endl;
	for(auto cc : CC){
		cout<<"( ";
		for(auto x : cc){
			cout<<x<<" ";
		}
		cout<<")"<<endl;
	}
	return 0;
}


