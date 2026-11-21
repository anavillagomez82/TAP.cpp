#include <iostream>
#include <memory>

using namespace std;

void eliminarYCompactar(int* inicio, int n, int x) {
    int* fin = inicio + n;
    int* lector = inicio;
    int* escritor = inicio;

    // 1. Copiamos hacia la izquierda todo lo que NO sea 'x'
    while (lector < fin) {
        if (*lector != x) {
            *escritor = *lector;
            escritor++;
        }
        lector++;
    }

    // 2. Rellenamos con ceros lo que sobró a la derecha
    while (escritor < fin) {
        *escritor = 0;
        escritor++;
    }
}

void imprimir(int* inicio, int n) {
    for (int* p = inicio; p < inicio + n; p++) {
        cout << *p << " ";
    }
    cout << endl;
}

int main() {
    int n = 8;
    // Reservamos en heap con unique_ptr (1ra forma)[cite: 6]
    unique_ptr<int[]> datos(new int[n]{4, 2, 7, 2, 9, 2, 1, 5});

    // Sacamos el raw pointer con .get() para no usar corchetes []
    int* ptr = datos.get();

    cout << "Original:   ";
    imprimir(ptr, n);

    eliminarYCompactar(ptr, n, 2); // Eliminamos el 2

    cout << "Resultante: ";
    imprimir(ptr, n);

    return 0;
}
