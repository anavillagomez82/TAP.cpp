#include <iostream>
#include <thread>
using namespace std;

template<class T>
struct Cgreater {
	inline bool operator()(T a, T b) { return a > b; }
};

template<class T>
struct Cless {
	inline bool operator()(T a, T b) { return a < b; }
};

// 1. MEZCLAR: Aquí adentro se crea y se destruye un arreglo temporal NUEVO cada vez
template<class T, class C>
void mezclar(T arr[], int inicio, int medio, int fin, C comparador) {
	int tam_temporal = fin - inicio + 1;
	T* temp = new T[tam_temporal]; // <-- Arreglo temporal local para ESTA mezcla

	int i = inicio;
	int j = medio + 1;
	int k = 0; // Arranca en 0 porque 'temp' mide exactamente lo necesario para este bloque

	while (i <= medio && j <= fin) {
		if (comparador(arr[i], arr[j]) || arr[i] == arr[j]) {
			temp[k] = arr[i]; i++;
		} else {
			temp[k] = arr[j]; j++;
		}
		k++;
	}

	while (i <= medio) { temp[k] = arr[i]; i++; k++; }
	while (j <= fin) { temp[k] = arr[j]; j++; k++; }

	// Copiamos de vuelta al arreglo original
	// Como 'temp' empieza en 0, arr[inicio + l] se alinea con temp[l]
	for (int l = 0; l < tam_temporal; l++) {
		arr[inicio + l] = temp[l];
	}

	delete[] temp; // <-- Lo borramos inmediatamente aquí adentro
}

// 2. MERGESORT: Ya no crea memoria, solo calcula los bloques
template <class T, class C> 
void mergesort(T arr[], int size, C comparador) {
	for (int bloque = 1; bloque < size; bloque = 2 * bloque) {
		for (int inicio = 0; inicio < size - 1; inicio += 2 * bloque) {
			int calcmedio = inicio + bloque - 1;
			int medio = (calcmedio < size - 1) ? calcmedio : size - 1;
			
			int calcfin = inicio + 2 * bloque - 1;
			int fin = (calcfin < size - 1) ? calcfin : size - 1;
			
			// Llamamos a mezclar sin pasarle un temporal externo
			mezclar<T, C>(arr, inicio, medio, fin, comparador);
		}
	}
}

int main() {
	int arr[] = { 10, 7, 3, 5, 2, 8, 9, 4, 3, 1, 6 };
	int size = sizeof(arr) / sizeof(arr[0]);
	Cless<int> l;

	const int nh = 2; 
	thread hilos[nh];
	int tpt = size / nh;
	
	// Lanzar hilos por secciones con aritmética de punteros
	for (int i = 0; i < nh; i++) {
		hilos[i] = thread(mergesort<int, Cless<int>>, arr + (i * tpt), tpt, l);
	}
	for (int i = 0; i < nh; i++) {
		hilos[i].join();
	}
	
	// Mezcla final en el main usando la función que crea su propio temporal
	int medio_global = tpt - 1;
	mezclar<int, Cless<int>>(arr, 0, medio_global, size - 1, l);

	// Imprimir resultado
	for (int x : arr) cout << x << " ";
	cout << "\n";

	return 0;
}
