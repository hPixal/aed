#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
using namespace std;
/*
[Pareto] (lista)Se dice que un puntox= (x1, x2, .., xn)n-dimensional domina
 a otro puntoy= (y1, y2, .., yn)si secumple que:∀k∈[1, n] :xk≤yk,y∃k0∈[1, n]
 / xk0< yk0(1)Por ejemplox=[2,1,5]domina ay=[2,2,5], pero dadoz=[1,2,5]no es
  cierto ni quexdomina aznizdomina ax.Entonces, dada una lista de puntos de
  coordenadas enteras positivaslist<vector<int>> L,implemente una 
  funciónlist<vector<int>> Pareto(list<vector<int>>&L);que retorne la lista
  depuntos no-dominados (aquellos que no son dominados por ningún otro
  punto). Se garantiza que cadavector<int>tienencoordenadas. La lista de
  retorno debe devolver los vectores en el mismo orden enque se encontraban
  enL.Nota:Formalmente, lo que se solicita es que retorne los puntos que 
  pertenecen a la frontera de Pareto,muy utilizada en problemas de 
  optimización con múltiples objetivos.Ejemplo:SiL=[[2,1,5],[2,2,5],
  [1,2,5]]en toncespareto(L)debe retornar[[2,1,5],[1,2,5]],ya que[2,2,5]
  es dominado por[2,1,5]pero[2,1,5]y +[1,2,5]+ no se dominan entre sí.
  Ayuda:Se sugiere implementar una función auxiliar
  bool domina(vector<int> x, vector<int> y);
  que reciba dos puntosn-dimensionales y que retorne verdadero en caso 
  de quexdomine ay
*/

template<typename T> 
    T getSum(vector<T> a){
        auto acum = *a.begin();
        if(!a.empty()){
            for(auto x : a)
                acum+=*x;
        }
        return 0;
    }

list<vector<int>> Pareto(list<vector<int>>&L);

int main(){


}

list<vector<int>> Pareto(list<vector<int>>&L){
    auto it = L.begin();
    auto aux = *L.begin();
    list<vector<int>> rtrn;

    while(it != L.end()){
        auto it2 = L.begin();
        bool add = true;
        while (it2 != L.end())
        {
            if (getSum(*it)>getSum(*it2))
            {
                add = false;
            }
            ++it2;
        }
        if(add)
            rtrn.push_back(*it);
        ++it;
    }
    return rtrn;
}