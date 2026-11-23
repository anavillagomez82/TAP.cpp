#include <iostream>
#include <memory>
using namespace std;
//Se guarda en una variable con auto (porque es un objeto de un struct sin nombre).
//Se invoca poniéndole paréntesis al lado: fc(*inicio) (porque llama a su operator()).
//Cuando una función la recibe por parámetro, se usa template <typename Func> y Func fc (exactamente igual que cuando recibes un functor).
//Y si la lambda tiene captura vacía [] (sin atributos), el compilador también te regala una conversión automática a puntero a función clásico (void (*ptr)(int&)).

template <class T,class F>
void aplicarOperacion(T* inicio,T*fin,F funcion) {

    while(inicio<fin){
        funcion(*inicio);
        inicio++;
    }
}


int main() {
    int n = 5;
    unique_ptr<int[]> datos(new int[n]{10, 20, 30, 40, 50});
    int* inicio = datos.get();
    int* fin = inicio + n;

    int incremento = 5;
    int umbral = 30;

    aplicarOperacion(inicio,fin,[incremento](int& w){w=w+incremento;});
    
    aplicarOperacion(inicio,fin,[umbral](int i){if(i>umbral){cout<<i;}});


    return 0;
}
