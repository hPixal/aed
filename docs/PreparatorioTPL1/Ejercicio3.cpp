#include <iostream>
#include <stack>
using namespace std;

/*
is-balanced] (stack)Dado un stringexpr, implementar una funciónbool 
is_balanced(string &expr);que determine si el par y orden 
de{,},(,),[,]estábalanceado.Ejemplos:[ ( ) ] { } { [ ( ) ( ) ] ( ) }
estábalanceado[ ( ] )no estábalanceado.Ayuda:Se propone el siguiente 
algoritmo:Declarar una pila dechar S.Recorrer el stringexpr.Si el 
caracter actual es un símbolo de apertura, entonces apilarlo.Si el 
caracter actual es un símbolo de cierre y matchea con su símbolo de apertura, entoncesquitarlo de la pila. Si no retornar falso. Atención: Chequear que la pila no esté vacía.Una vez recorrido todo el string, si la pila está vacía, entonces la expresión está balanceada.
*/

bool is_balanced(string &expr);

int main(){

    return 0;
}

bool is_balanced(string &expr){
    stack<char> S;
    
    auto it = expr.begin();
    
    while(it != expr.end()){
        if(*it == '{' || *it == '[' || *it == '(' ){
            S.push(*it);
        }else if((*it == '}' && S.top() == '{')|| 
                 (*it == ']' && S.top() == '[')||
                 (*it == '(' && S.top() == '{')){
                    S.pop();
                }
    }
    if(S.empty()){
        return true;
    }else{
        return false;
    }
}