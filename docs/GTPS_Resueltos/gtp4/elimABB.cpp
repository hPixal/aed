#include <iostream>
#include <version>
#include <vector>
#include <map>
#include <list>
#include <set>
//#include "tree.hpp"
#include "btree.hpp"
//#include "util_btree.hpp"
//#include "str_convs.hpp"
using namespace aed;
using namespace std;

//typedef btree<int>::iterator bnode;

/*
    Este archivo es solo de ejemplo. Usalo para resolver los ejercicios, ya que este
    en esta carpeta especifica y con este nombre especifico, es el unico con el que 
    funciona la utilería de la catedra. Se puede usar como plantilla para luego cam
    biarle el nombre a uno más apropiado y entregarlo como resolción.
*/

template<typename T>
    typename btree<T>::iterator findVal(btree<T> &BT, T v, typename btree<T>::iterator pos){
        return BT.end();
    }

btree<int>::iterator findVal(btree<int> &BT, int v){
    auto pos = BT.begin();
    while (true)
    { 
        if(pos == BT.end()) return pos;
        if(*pos > v){
            pos = pos.left(); 
        } else if (*pos < v){
            pos = pos.right();
        } else if( *pos == v){
            return pos;
        }
    }
    
}

void elimina_ABB(btree<int> &BT, int v) {
	btree<int>::iterator pos = findVal(BT, v);
	
	/// Si el valor v no esta en el arbol, no hace nada
	/// Si el valor v esta en el arbol, dependera de la cantidad de hijos que tenga
	/// - Si tiene un solo hijo, "subir" todo el subarbol de dicho hijo a la posicion del padre
	/// - Si tiene dos hijos, se busca un valor cualquiera de las ramas para eliminarlo,
	/// y reemplazar por la posicion del valor v
	/// Tiene que ser el minimo valor de la rama derecha, o el maximo valor de la rama izquierda
	if(pos != BT.end()) {
		/// Si no tiene hijos, elimina el nodo
		if(pos.left() == BT.end() && pos.right() == BT.end()) /// No tiene hijos
			BT.erase(pos);
		else if(pos.right() == BT.end()) { /// Solo tiene hijo izquierdo
			btree<int> temp; auto beg = temp.begin();
            auto p = pos; p.left();

			temp.splice(beg,p);
			pos = BT.erase(pos); 
			BT.splice(pos, beg);
		} else if(pos.left() == BT.end()) { /// Solo tiene hijo derecho
			btree<int> temp; auto beg = temp.begin();
            auto p = pos; p.right();

			temp.splice(beg, p);
			pos = BT.erase(pos);
			BT.splice(pos, beg);
		} else { /// Si tiene ambos hijos, elegir una estrategia ("minimo de los maximos")
			btree<int>::iterator minR = pos.right();
			while(minR.left() != BT.end()) {
				minR = minR.left();
			}

			int valorTemp = *minR;
			/// NOTA: en lugar de eliminar la hoja con el "minimo de los maximos":
			/// BT.erase(minR);
			/// utilizar el splice para que "suba" el subarbol del hijo derecho
			/// de minR a la posicion de minR
            auto minrr = minR; minrr.right();

			BT.splice(minR, minrr);
			*pos = valorTemp;
		}
	}
}

////////////////////////////////////////////////////////////////////////////
/*Extra: listar un arbol binario */
////////////////////////////////////////////////////////////////////////////

template<typename T>
    int getLevelCount(btree<T> &tr,typename btree<T>::iterator pos, int count){
        if(pos == tr.end()) return count; count++;

        int r = getLevelCount(tr,pos.right(),count);
        int l = getLevelCount(tr,pos.left(),count);

        if(r>l) return r;
        return l;
    }

template<typename T>
    int getLevelCount(btree<T> &tr){
        if(tr.size() == 0) return 0;
        int count = 0;
        getLevelCount(tr,tr.begin(),count);
    }

template<typename T>
    void getLevels(btree<T> &BT,vector<vector<T>> &levels, 
         typename btree<T>::iterator pos, int count ){
        if(pos == BT.end()) return; 
        levels[count].push_back(*pos);
        getLevels(BT,levels,pos.right(),count+1);
        getLevels(BT,levels,pos.left(),count+1);
    }

template<typename T>
    void listar_ABB(btree<T> &BT){
        vector<vector<T>> levels;
        levels.resize(getLevelCount(BT));

        //auto lvl = levels.begin();
        getLevels(BT,levels,BT.begin(),0);

        int spacecount = levels.size(); int level = 0;
        for(auto itv = levels.begin() ; itv != levels.end() ; itv++ ){
            cout << "[ " << level << " ] ";
            for (int i = 0; i < spacecount; i++)
            {
                cout << "        ";
            }
            
            for(auto its = itv->begin() ; its != itv->end() ; its++ ){
                cout << " ( " << *its << " ) "; 
            }
            level++; spacecount--;
            cout << endl;
        }

    }

////////////////////////////////////////////////////////////////////////////
/*Extra: crear un arbol binario */
////////////////////////////////////////////////////////////////////////////

void create_btree(btree<int> &tr,btree<int>::iterator it,int level,int count){
    if(count > level) return;
    it = tr.insert(it,int(rand()%40));

    btree<int>::iterator nextr = it.right();
    btree<int>::iterator nextl = it.left();

    create_btree(tr,nextr,level,count+1);
    create_btree(tr,nextl,level,count+1);
}


void create_btree(btree<int> &tr,int level){
    tr.clear();
    create_btree(tr,tr.begin(),level,0);
}

////////////////////////////////////////////////////////////////////////////
/*Extra: crear un set aleatorio */
////////////////////////////////////////////////////////////////////////////

set<int> create_set(int elem){
    set<int> rtrn;
    while ( int(rtrn.size()) != elem)
    {
        int aux = rand() % (elem+2);
        if (rtrn.find(aux) == rtrn.end())
        {
            rtrn.insert(aux);
        }
    }
    return rtrn;
}

int main(){
    btree<int> example;
    create_btree(example,4);

    set<int> test = create_set(5);
    set<int> test2 = create_set(5);
    set<int> test3 = create_set(5);
    vector<set<int>> bigtest;
    bigtest.push_back(test);
    bigtest.push_back(test2);
    bigtest.push_back(test3);

    listar_ABB(example);

    // if(balanced(tr)) cout << "funciona" << endl;
    return 0;
}
