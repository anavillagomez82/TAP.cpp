#include <iostream>
#include <memory>

using namespace std;

class Robot {
public:
    int f, c;
    Robot() : f(0), c(0) {}

    // --- <A Completar 1>: Implementa los 4 movimientos ---
    void moverArriba() {
        f--;
    }

    void moverAbajo() {
        f++;
    }

    void moverDerecha() {
        c++;
    }

    void moverIzquierda() {
        c--;
    }
    // --- Fin <A Completar 1> ---
};

int main() {
    const int FILAS = 4;
    const int COLS = 4;

    // Matriz 4x4 en heap (un solo bloque continuo de 16 ceros)
    unique_ptr<int[]> mapa(new int[FILAS * COLS]{0});
    int* ptr_mapa = mapa.get();

    Robot r;
    *ptr_mapa = 1; // Marcamos la celda inicial (0, 0) con 1

    // 5 órdenes: Abajo(1), Abajo(1), Derecha(2), Arriba(0), Derecha(2)
    int n_ordenes = 5;
    unique_ptr<int[]> ordenes(new int[n_ordenes]{1, 1, 2, 0, 2});
    int* p = ordenes.get();
    void(Robot::*s[])()={&Robot::moverArriba,&Robot::moverAbajo,&Robot::moverDerecha,&Robot::moverIzquierda};
    while(p<ordenes.get()+n_ordenes){
        (r.*(*(s+*p)))();
        *(ptr_mapa+r.f*COLS+r.c)=1;
        
        p++;
    }

    // Impresión del mapa (ya hecha para verificar tu resultado)
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLS; j++) {
            cout << *(ptr_mapa + i * COLS + j) << " ";
        }
        cout << endl;
    }

    return 0;
}
