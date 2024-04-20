#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Inicia el metodo de ordenamiento COCKATILSORT
void cocks(int arr[], int n) {
	//Variables de ordenamiento
	int inte = 1;
	int ini = 0;
	int fin = n-1;
	//Variables de control
	int i;
	while(inte) {
		//Se cambia inte para que entre al while
		inte = 0;

		//Mover el mas grande al final
		for(i=ini; i<fin; i++) {
			if(arr[i]>arr[i+1]) {
				int temp=arr[i];
				arr[i]=arr[i+1];
				arr[i+1]=temp;
				inte=1;
			}
		}
		//Si ya esta todo en orden sale
		if(!inte) {
			break;
		}
		//Reduce la cantidad de movimiento en 1
		inte=0;
		fin--;

		//Mueve el elemento mas pequeño al inicio
		for(i=fin-1; i>=ini; i--) {
			if(arr[i]>arr[i+1]) {
				int temp=arr[i];
				arr[i]=arr[i+1];
				arr[i+1]=temp;
				inte=1;
			}
		}

		ini++;
	}
}
//Main
int main() {
	int n;
	printf("Ingrese la cantidad de elemententos: ");
	scanf("%d", &n);

	//Generador de datos
	int arr[n];
	srand(time(NULL)); // Semilla para la generación de números aleatorios
	for (int i = 0; i < n; ++i) {
		arr[i] = rand() % (n+1); // Generar números aleatorios dentro del rango especificado
	}
	printf("\n");

	clock_t begin = clock();
	cocks(arr, n);
	clock_t end = clock();

	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

	printf("Arreglo ordenado:\n");
	for (int i = 0; i < n; ++i) {
		printf("%d ", arr[i]);
	}
	printf("\n");

	printf("Tiempo transcurrido: %f segundos\n", time_spent);

	return 0;
}




