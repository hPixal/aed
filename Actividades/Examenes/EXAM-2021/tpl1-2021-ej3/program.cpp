#define USECHRONO
#undef HAVE_MPI
#include "eval.hpp"
#include <cassert>
#include <climits>
#include <cstdlib>
#include <stack>
using namespace aed;
using namespace std;

// COMPLETAR DNI y NOMBRE AQUI:
// Nombre: Gareis Nahuel Julian
int DNI= 43538493;

void llenavector(list<int> &au,list<int> &l){
    list<int>::iterator it = l.begin();
    int aux = *l.begin();
    auto auxit= l.begin();

    while (it != l.end())
    {
        if (aux > *it)
        {
            aux = *it;
            auxit = it;
        }
        ++it;
    }

    au.push_back(aux);
    l.erase(auxit);

    if (l.size() == 0)
    { return; } else
    { llenavector(au,l); }
    
}

void ordenar(list<int> &l){
    list<int> auxlist;
    llenavector(auxlist,l);
    l.swap(auxlist);
}


bool es_primo(int numero){
  numero = abs(numero);
  if( numero == 0 || numero == 1)
   { return false; }
  if( numero == 2 )
   { return true; }
  for (int i = 2; i < numero-1; i++)
  {
    if(numero%i == 0)
      return false;
  }
  return true;
  
}


  void primos(list<int> &L,stack<int> &P){
    auto it = L.begin();
    list<int> aux;
    while(it != L.end()){
      if (es_primo(*it))
      {
          aux.push_back(*it);
      }
      ++it;
    }
    ordenar(aux);
    it = aux.begin();
    while(it != aux.end()){
      P.push(*it);
      ++it;
    }
  }

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int main() {
  Eval ev;
  int vrbs = 0;
  ev.eval<1>(primos,vrbs);

  return 0;
}
