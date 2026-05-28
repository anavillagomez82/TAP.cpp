#include <iostream>
using namespace std;

// Comparador menor
template <class T>
struct CLess {
	bool operator()(T a, T b) { return a < b; }
};

// Clase Pivot universal: cambia este return por el número que quieras (0, n/2, n-1, etc.)
template <class T>
struct XPivot {
	inline unsigned long operator()(T* arr, unsigned long n) {
		return 0; // Funciona con 0, n/2, n-1 o cualquier índice válido
	}
};

// QuickSort robusto y universal usando la partición original de Hoare
template <class T, class C, class P>
void qs(T* arr, unsigned long n, C cmp, P piv) {
	// Caso base fundamental
	if (n <= 1)
		return;
	
	// 1. Obtener el valor del pivote desde el índice elegido
	unsigned long pi = piv(arr, n);
	T pivot = arr[pi];
	
	// 2. Inicializar índices (esquema Hoare puro adaptado a unsigned long)
	long i = -1;
	long j = n;
	
	// 3. Proceso de partición
	while (true) {
		// Avanzar i mientras el elemento sea menor que el pivote
		do {
			i++;
		} while (cmp(arr[i], pivot));
		
		// Retroceder j mientras el elemento sea mayor que el pivote
		do {
			j--;
		} while (cmp(pivot, arr[j]));
		
		// Si los índices se cruzaron o se encontraron, terminamos la partición
		if (i >= j)
			break;
		
		// Intercambiar los elementos desordenados
		swap(arr[i], arr[j]);
	}
	
	// 4. Corrección crítica para evitar bucles infinitos cuando el pivote es el peor posible
	// Si la partición divide el arreglo de forma totalmente desequilibrada (j == n - 1),
	// forzamos el corte reduciendo el tamaño en 1 para que la recursión no se cicle.
	unsigned long corte = j;
	if (corte == n - 1) {
		corte--;
	}
	
	// 5. Llamadas recursivas seguras utilizando el punto de corte
	qs(arr, corte + 1, cmp, piv);
	qs(arr + corte + 1, n - (corte + 1), cmp, piv);
}

template <class T>
	void print(T* arr, unsigned long n) {
	for (unsigned long i = 0; i < n; i++)
		cout << arr[i] << " ";
	cout << endl;
}
	
	int main() {
		// Arreglo de prueba difícil (con números repetidos y desordenados)
		int arr[] = {5, 5, 9, 1, 4, 7, 1, 2, 8, 1, 5, 3, 6, 9, 1};
		unsigned long n = sizeof(arr) / sizeof(arr[0]);
		
		CLess<int> less;
		XPivot<int> piv;
		
		cout << "Original: ";
		print(arr, n);
		
		qs(arr, n, less, piv);
		
		cout << "Ordenado: ";
		print(arr, n);
		
		return 0;
	}
	
