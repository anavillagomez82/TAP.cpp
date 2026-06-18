#include <iostream>
#include <thread>
using namespace std;

template<class T>
struct Cgreater {
	inline bool operator()(T a, T b) {
		return a > b;
	}
};

template<class T>
struct Cless {
	inline bool operator()(T a, T b) {
		return a < b;
	}
};

template<class T, class C>
void mezclar(T arr[], T temp[], int inicio, int medio, int fin, C comparador) {
	int i = inicio;
	int j = medio + 1;
	int k = inicio;
	while (i <= medio && j <= fin) {
		if (comparador(arr[i], arr[j]) || arr[i] == arr[j]) {
			temp[k] = arr[i];
			i++;
		}
		else {
			temp[k] = arr[j];
			j++;
		}
		k++;
	}
	while (i <= medio) {
		temp[k] = arr[i];
		i++;
		k++;
	}
	while (j <= fin) {
		temp[k] = arr[j];
		j++;
		k++;
	}
    // CORRECCIÓN 1: l <= fin (para no comerse el último elemento)
	for (int l = inicio; l <= fin; l++) {
		arr[l] = temp[l];
	}
}

template <class T, class C> 
void mergesort(T arr[], int size, C comparador) {
	T* tp = new T[size]; // Usamos 'tp'
	for (int bloque = 1; bloque < size; bloque = 2 * bloque) {
		for (int inicio = 0; inicio < size - 1; inicio += 2 * bloque) {
			int calcmedio = inicio + bloque - 1;
            // CORRECCIÓN 2: size - 1 (cambiado el < por -)
			int medio = (calcmedio < size - 1) ? calcmedio : size - 1;
			
			int calcfin = inicio + 2 * bloque - 1;
            // CORRECCIÓN 2: size - 1
			int fin = (calcfin < size - 1) ? calcfin : size - 1;
			
            // CORRECCIÓN 3: Se usan las variables correctas (tp, comparador, T, C)
			mezclar<T, C>(arr, tp, inicio, medio, fin, comparador);
		}
	}
	delete[] tp; // Se borra 'tp'
}

int main() {
    // Tu arreglo tiene 11 elementos (impar) ¡Excelente para probar los ternarios!
	int arr[] = { 10,7,3,5,2,8,9,4,3,1,6 };
	int size = sizeof(arr) / sizeof(arr[0]);
	Cless<int> l;
	Cgreater<int> g;

	const int nh = 2; // Ojo: Para 11 elementos, 2 hilos es mejor que 8 para que tpt no de 1 o 0
	thread hilos[nh];
	int tpt = size / nh;
	
	for (int i = 0; i < nh; i++) {
        // CORRECCIÓN 4: Cerrado el template de mergesort e introducido bien Cless<int>
		hilos[i] = thread(mergesort<int, Cless<int>>, arr + (i * tpt), tpt, l);
	}
	for (int i = 0; i < nh; i++) {
		hilos[i].join();
	}
	
	int* temporal = new int[size];
    // CORRECCIÓN 5: Especificado Cless<int> en el template
	mezclar<int, Cless<int>>(arr, temporal, 0, tpt - 1, size - 1, l);
	delete[] temporal;

	// Imprimir para verificar que funcionó
	for (int x : arr) cout << x << " ";
	cout << "\n";

	return 0;
}
