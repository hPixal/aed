#include <iostream>
#include <list>
#include <queue>
using namespace std;

/*
Implementar una función voidmerge_kway(vector< queue<int> > &qords
,queue<int> &merged)que dado un vector de colas ordenadasordqs, 
obtener la colamergedresultante de la fusión de todaslas colas en una 
sola, de forma de que los elementos siguen ordenadas. 
Por ejemplo siordqs=((1,3,5,6),(0,3,5,8),(6,9,10))entonces debe 
darmerged=(0,1,3,3,5,5,6,6,8,9,10). Elalgoritmo puede ser 
destructivo sobreordqs.
*/

void merge_kway(vector< queue<int> > &qords,queue<int> &merged);


int main(){

    return 0;
}


void merge_kway(vector< queue<int> > &qords,queue<int> &merged){
    auto it = qords.begin();
    vector<int> aux;

    while(it != qords.end()){
        aux.push_back(it->front());
        ++it;
    }

    for (size_t i = 0; i < aux.size(); i++)
    {
        for (size_t j = 0; j < aux.size(); j++)
        {
            if (aux[i]<aux[j])
            {
                int auxi = aux[i];
                aux[i] = auxi;
            }
        }
    }
}