#include <iostream>
#include <memory>
#include <thread>

using namespace std;

class Cuenta {
public:
    int saldo;
    Cuenta() : saldo(100) {}

    // --- <A Completar 1>: Implementa los 3 métodos ---
    void depositar50() {
        saldo+=50;
    }
    void retirar20(){ 
    saldo-=20;
        
    }
    void duplicar() {
        saldo=saldo*2;
    }
    // --- Fin <A Completar 1> ---
};

// --- <A Completar 2>: Función que ejecutará cada hilo ---
// Debe recorrer las cuentas desde 'ini' hasta 'fin', y a cada cuenta
// aplicarle todas las operaciones del arreglo 'codigos' (de tamaño 'n_codigos')
// usando el arreglo de punteros a métodos 'ops'.
void procesarCuentas(Cuenta* ini, Cuenta* fin, int* codigos, int n_codigos, void (Cuenta::**ops)()) {
    while(ini<fin){
        int*p=codigos;
        while(p<codigos+n_codigos){
            (ini->*(*(ops+*p)))();
            p++;
    }
    ini++;
}}
// --- Fin <A Completar 2> ---

int main() {
    const int N = 6;
    const int K = 2;
    int bloque = N / K;

    unique_ptr<Cuenta[]> cuentas(new Cuenta[N]);
    Cuenta* ptr_cuentas = cuentas.get();

    // Operaciones a aplicar a cada cuenta: depositar50 (0), duplicar (2), retirar20 (1)
    // Saldo esperado por cuenta: ((100 + 50) * 2) - 20 = 280
    int n_codigos = 3;
    unique_ptr<int[]> codigos(new int[n_codigos]{0, 2, 1});
    int* ptr_codigos = codigos.get();

    // --- <A Completar 3>: Arreglo de punteros a métodos de Cuenta ---
    void(Cuenta::*pm[])()={&Cuenta::depositar50,&Cuenta::retirar20,&Cuenta::duplicar};
    

    // --- Fin <A Completar 3> ---

    unique_ptr<thread[]> hilos(new thread[K]);
    thread* ptr_hilos = hilos.get();

    // --- <A Completar 4>: Lanzar los K hilos y luego hacer .join() ---
    thread t1(procesarCuentas,ptr_cuentas,ptr_cuentas+3,ptr_codigos,n_codigos,pm);
    thread t2(procesarCuentas,ptr_cuentas+3,ptr_cuentas+N,ptr_codigos,n_codigos,pm);
    t1.join();
    t2.join();

    // --- Fin <A Completar 4> ---

    // Verificación
    for (Cuenta* c = ptr_cuentas; c < ptr_cuentas + N; c++) {
        cout << "Saldo final: " << c->saldo << endl; // Debe imprimir 280 en las 6 cuentas
    }

    return 0;
}
