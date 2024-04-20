#include <stdio.h>
#include <stdlib.h>

#define alto 50

int top = -1;

void push(char arr[alto], char y) {
	if (top == alto - 1) {
		printf("Imposible, la pila está llena\n");
		return;
	}
	top++;
	arr[top] = y;
}

void pop(char arr[alto]) {
	if (top == -1) {
		printf("Imposible, la pila esta vacia\n");
		return;
	}
	arr[alto] = '0';
	top--;
}

void peak(char arr[alto]) {
	printf("%c", arr[alto]);
}


int main(void) {
	char arr[alto], dato;
	int i;

	while(1) {
		printf("\n-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
		printf("                  LA PILA\n");
		printf("-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n\n");

		printf("Que quieres hacer?\n");
		printf("1.- Agregar elemento\n");
		printf("2.- Quitar elemento\n");
		printf("3.- Ver ultimo elemento\n");
		printf("4.- Ver toda la pila\n");
		printf("5.- Salir\n");
		printf("Opcion: ");
		scanf("%i", &i);
		printf("\n");

		if(i==1) {
			printf("Ingrese el dato nuevo\n");
			scanf(" %c", &dato);
			push(arr,dato);
			printf("Tu pila actualmente es: \n");
			for(i=top ; i >= 0 ; i--) {
				printf("%c\n", arr[i]);
			}
		}
		if(i==2) {
			pop(arr);
			printf("Tu pila quedo asi:\n ");
			for(i=top ; i >= 0 ; i--) {
				printf("%c\n", arr[i]);
			}
		}
		if(i==3) {
			peak(arr);
		}
		if(i==4) {
			printf("Su pila es la siguiente");
			for(i=top ; i >= 0 ; i--) {
				printf("%c\n", arr[i]);
			}
		}
		if(i==5) {
			break;
		}
		if(i!=2) {
			printf("Seas mamon, ahi esta el perro menu\n");
			printf("BURRO\n\n");
		}
	}
	return 0;
}
