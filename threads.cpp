#include <iostream>
#include <memory>
#include <thread>

using namespace std;

// --- <A Completar 1> ---
// Recorre las celdas desde 'ini' hasta 'fin' y guarda en 'resultado'
// cuántos elementos son divisibles exactamente entre 'divisor' (sin usar if).
void contarMultiplos(int* ini, int* fin, int divisor, int& resultado) {
    while(ini<fin){
        while(*ini%divisor==0){
            resultado++;break;
        }
        ini++;
        
    }

}
// --- Fin <A Completar 1> ---

int main() {
    const int FILAS = 4;
    const int COLS = 6;
    const int K = 2;
    int filas_por_hilo = FILAS / K; // 2 filas por hilo
    int divisor = 3;

    // Matriz 4x6 en heap (24 elementos)
    unique_ptr<int[]> matriz(new int[FILAS * COLS]{
         3,  4,  6,  7,  9, 10,   // Fila 0 -> 3 múltiplos (3, 6, 9)
        12, 14, 15, 16, 18, 20,   // Fila 1 -> 3 múltiplos (12, 15, 18)
         1,  2,  3,  5,  6,  8,   // Fila 2 -> 2 múltiplos (3, 6)
        21, 22, 24, 25, 27, 30    // Fila 3 -> 4 múltiplos (21, 24, 27, 30)
    });
    int* ptr_mat = matriz.get();

    unique_ptr<int[]> conteos_parciales(new int[K]{0});
    int* ptr_conteos = conteos_parciales.get();

    unique_ptr<thread[]> hilos(new thread[K]);
    thread* ptr_hilos = hilos.get();

    // --- <A Completar 2> ---
    // Lanza los K hilos usando ptr_hilos y ref(...) para pasar cada casilla de ptr_conteos,
    // y luego haz .join() a todos los hilos.
    thread t1(contarMultiplos,ptr_mat,ptr_mat+(FILAS*COLS)/2,divisor,ref(*ptr_conteos));
    thread t2(contarMultiplos,ptr_mat+(FILAS*COLS)/2,ptr_mat+(FILAS*COLS),divisor,ref(*(ptr_conteos+1)));
    t1.join();
    t2.join();
 

    // --- Fin <A Completar 2> ---

    // Verificación (debe imprimir 12)
    int total = 0;
    for (int* p = ptr_conteos; p < ptr_conteos + K; p++) {
        total += *p;
    }
    cout << "Total de multiplos de " << divisor << ": " << total << endl;

    return 0;
}
