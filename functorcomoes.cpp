#include <iostream>
using namespace std;
//Functor

struct Multiplicador {
    int factor;
    Multiplicador(int f) : factor(f) {}
    int operator()(int x){
        return x*factor;
    }

    // 1. Sobrecarga operator() para que reciba 'int x' y devuelva 'x * factor':
    
};

int main() {
    // 2. Crea un objeto 'por3' de tipo Multiplicador con factor = 3:
    Multiplicador por3=3;
    
    // 3. Úsalo como función pasándole el número 10 y guarda el resultado en 'r':
    int r = por3(10);
}

    
