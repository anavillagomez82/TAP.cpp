#include<iostream>
#include <memory>
using namespace std;
//smartpointers
int main() {
    int N = 5;
    // 1. Reserva un arreglo dinámico de 'N' enteros usando unique_ptr llamado 'arr':
    unique_ptr<int[]>arr(new int[N]);

    // 2. Saca el puntero crudo 'ptr' con .get():
    int*p=arr.get();

    // 3. Guarda el número 99 en la posición 2 SIN usar corchetes []:
    *(p+2)=99;
}
