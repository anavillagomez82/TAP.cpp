//Situación,Objeto normal (Caja obj;),Puntero a objeto (Caja* ptr;)
//Sabes el nombre (duplicar),obj.duplicar();,ptr->duplicar();
//Está en un puntero (pm),(obj.*pm)();,(ptr->*pm)();

//Cuando es un objeto al que le vas a aplicar el metodo se usa el . 
//Cuando es un puntero a un objeto al que se lo vas a aplicar se usa la ->
#include <iostream>
using namespace std;
//Puntero a metodo
class Caja {
public:
    int valor = 10;
    void duplicar(){
        valor*=2;
    }
};

void procesar(Caja* c) {
    c->duplicar();
}

void procesar(Caja c){
    c.duplicar();
}

int main()
{
   Caja micaja;
   Caja* mc=&micaja;
   void(Caja::*pm)()=&Caja::duplicar;
   (mc->*pm)();//puntero con puntero a metodo
   (micaja.*pm)();//objeto con puntero a metodo
   mc->duplicar();//puntero con metodo
   micaja.duplicar();//objeto con metodo
}
    
