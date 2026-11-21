#include <iostream>
#include <vector>
//imulacro - Pregunta 3 (Basada en Práctica 8)Enunciado tipo examen:Implemente una función genérica miSort(begin, end, comp) con la misma firma de std::sort que ordene usando Bubble Sort y funcione tanto con punteros clásicos (arrays en stack/heap) como con iteradores de std::vector. Implemente el criterio de comparación (Ascendente y Descendente) como:   Puntero a función.   Function Object (Functor).   Inline Function Object.
//Pruebe todos los casos en el main.
  using namespace std;

// 1. FUNCIÓN LIBRE (para pasar como Puntero a Función)
template <typename T>
bool ascendenteFunc(T a, T b) {
    return a > b; // Si 'a' es mayor que 'b', se intercambian (ordena de menor a mayor)
}

// 2. FUNCTION OBJECT (Functor normal)
template <typename T>
struct AscendenteFunctor {
    bool operator()(T a, T b) {
        return a > b;
    }
};

// 3. INLINE FUNCTION OBJECT (Functor inline)
template <typename T>
struct DescendenteInlineFunctor {
    inline bool operator()(T a, T b) {
        return a < b; // Ordena de mayor a menor
    }
};

// 4. SORT GENÉRICO (Bubble Sort compatible con raw pointers e iteradores STL)
template <typename Iter, typename Comp>
void miSort(Iter begin, Iter end, Comp comp) {
    for (Iter i = begin; i != end; ++i) {
        for (Iter j = begin; j != end - 1; ++j) {
            if (comp(*j, *(j + 1))) { // Funciona igual para puntero a función o functor
                auto temp = *j;
                *j = *(j + 1);
                *(j + 1) = temp;
            }
        }
    }
}

template <typename Iter>
void imprimirRango(Iter begin, Iter end) {
    for (Iter it = begin; it != end; ++it) {
        cout << *it << " ";
    }
    cout << endl;
}

int main() {
    // --- PRUEBA 1: Array en Stack con Puntero a Función ---
    int arr[] = { 45, 12, 89, 3, 27 };
    int n = 5;

    miSort(arr, arr + n, ascendenteFunc<int>); // Se pasa el nombre de la función
    cout << "Array (Puntero a funcion - Asc):  ";
    imprimirRango(arr, arr + n);

    // --- PRUEBA 2: std::vector con Functor (Function Object) ---
    vector<int> vec = { 45, 12, 89, 3, 27 };
    AscendenteFunctor<int> objAsc; // Instanciamos el functor

    miSort(vec.begin(), vec.end(), objAsc);
    cout << "Vector (Functor - Asc):           ";
    imprimirRango(vec.begin(), vec.end());

    // --- PRUEBA 3: std::vector con Inline Functor (objeto temporal) ---
    miSort(vec.begin(), vec.end(), DescendenteInlineFunctor<int>());
    cout << "Vector (Inline Functor - Desc):   ";
    imprimirRango(vec.begin(), vec.end());

    return 0;
}
