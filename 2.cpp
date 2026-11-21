#include <iostream>

using namespace std;

class Navegador {
private:
    int cols; // Necesario para saber cuánto saltar verticalmente
public:
    Navegador(int c) : cols(c) {}

    int* Arriba(int* p)    { return p - cols; }
    int* Abajo(int* p)     { return p + cols; }
    int* Izquierda(int* p) { return p - 1; }
    int* Derecha(int* p)   { return p + 1; }
};

void imprimirMatriz(int* mat, int filas, int cols) {
    for (int f = 0; f < filas; f++) {
        for (int c = 0; c < cols; c++) {
            cout << *(mat + f * cols + c) << "\t"; // Fórmula 2D sin []
        }
        cout << endl;
    }
    cout << endl;
}

int main() {
    int FILAS = 4, COLS = 5;
    
    // 1. Matriz 2D dinámica en 1 solo bloque (1ra forma)
    int* matriz = new int[FILAS * COLS];
    for (int i = 0; i < FILAS * COLS; i++) {
        *(matriz + i) = i + 1; // Llenamos del 1 al 20
    }

    cout << "Matriz Original:\n";
    imprimirMatriz(matriz, FILAS, COLS);

    // 2. Declaramos el array de punteros a métodos de la clase Navegador
    // Índices: 0:Arriba, 1:Abajo, 2:Izquierda, 3:Derecha
    int* (Navegador::*acciones[4])(int*) = {
        &Navegador::Arriba,
        &Navegador::Abajo,
        &Navegador::Izquierda,
        &Navegador::Derecha
    };

    // 3. Array de configuración (ej. Derecha, Derecha, Abajo, Abajo, Izquierda)
    int ruta[] = { 3, 3, 1, 1, 2 };
    int pasos = 5;

    Navegador nav(COLS);
    int* actual = matriz; // Empezamos en la celda 1 (esquina superior izquierda)
    *actual = 0;          // Marcamos la celda inicial

    // 4. Recorrido automático SIN if/switch y SIN corchetes []
    for (int* pRuta = ruta; pRuta < ruta + pasos; pRuta++) {
        int codigo = *pRuta;
        
        // Obtenemos el puntero al método usando aritmética de punteros
        int* (Navegador::*metodoElegido)(int*) = *(acciones + codigo);
        
        // Ejecutamos el método sobre el objeto 'nav' (¡Ojo a los paréntesis!)
        actual = (nav.*metodoElegido)(actual);
        *actual = 0;
    }

    cout << "Matriz con Recorrido (0s):\n";
    imprimirMatriz(matriz, FILAS, COLS);

    delete[] matriz; // Siempre liberar memoria dinámica
    return 0;
}
