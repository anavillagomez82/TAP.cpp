#include <iostream>
using namespace std;
//puntero a funcion
int sumar(int a, int b) {
    return a + b;
}

int main() {
    // 1. Declara un puntero a función llamado 'pf' y apúntalo a 'sumar':
    int(*pf)(int,int)=&sumar;

    // 2. Llama a 'pf' pasándole 4 y 5, y guarda el resultado en 'res':
    int res = pf(4,5);
}
