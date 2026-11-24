#include <iostream>
using namespace std;

// --- PASO 1: Rellena qué hace cada función (el profe te da los nombres) ---
void descuento(int& precio) {
    precio=precio-20;
}

void impuesto(int& precio) {
    precio=precio+10;
}

void duplicar(int& precio) {
    precio=precio*2;
}
// -------------------------------------------------------------------------

int main() {
    int precio = 100;

    // Lista de cupones a aplicar en orden: primero impuesto(1), luego descuento(0), luego duplicar(2)
    int cupones[3] = {1, 0, 2};
    int* ptr_cupones = cupones;

    // --- PASO 2: <A Completar 4> (Sin usar [] ni if/switch) ---
    void(*botones[])(int&)={descuento,impuesto,duplicar};
    int* p=ptr_cupones;
    while(p<ptr_cupones+3){
        (*(botones+*p))(precio);
        p++;
    }

    cout << "Precio final: " << precio << endl; // Debe salir: 180
    return 0;
}
