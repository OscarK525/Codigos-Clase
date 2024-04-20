#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int hanoiRecursivo(int n, char origen, char auxiliar, char destino){
    if(n == 1){
        printf("Mover disco 1 de %c a %c\n", origen, destino);
        return 0;
    }
    hanoiRecursivo(n-1, origen, destino, auxiliar);
    printf("Mover disco %d de %c a %c\n", n, origen, destino);
    hanoiRecursivo(n-1, auxiliar, origen, destino);
    return 0;
}

int hanoiIterativo(int n, char origen, char auxiliar, char destino){
    int i, total = 1;
    char *pila = (char *)malloc(n * sizeof(char));
    pila[0] = origen;
    pila[1] = auxiliar;
    pila[2] = destino;
    for(i = 1; i < (1 << n); i++){
        if(i & 1){
            printf("Mover disco 1 de %c a %c\n", pila[0], pila[2]);
        }
        else{
            printf("Mover disco 1 de %c a %c\n", pila[2], pila[0]);
        }
        total++;
        if(i & (i - 1)){
            if((i & 3) == 1){
                printf("Mover disco 2 de %c a %c\n", pila[0], pila[1]);
            }
            else{
                printf("Mover disco 2 de %c a %c\n", pila[1], pila[0]);
            }
            total++;
        }
        else{
            printf("Mover disco 2 de %c a %c\n", pila[0], pila[2]);
            total++;
        }
        if(i & (i - 1)){
            if((i & 3) == 1){
                printf("Mover disco 3 de %c a %c\n", pila[1], pila[2]);
            }
            else{
                printf("Mover disco 3 de %c a %c\n", pila[2], pila[1]);
            }
            total++;
        }
        else{
            printf("Mover disco 3 de %c a %c\n", pila[0], pila[2]);
            total++;
        }
    }
    free(pila);
    return total;
}

int main(){
    int n;
    clock_t ini, fin;
    double secs;
    printf("Cuantos discos quieres en la torre de Hanoi? ");
    scanf("%d", &n);
    //? Recursivo
    ini = clock();
    hanoiRecursivo(n, 'A', 'B', 'C');
    fin = clock();
    secs = (double)(fin - ini) / CLOCKS_PER_SEC;
    printf("\nTiempo de ejecucion: %.16g milisegundos\n\n", secs * 1000.0);
    //? Iterativo
    ini = clock();
    printf("\nTotal de movimientos: %d\n", hanoiIterativo(n, 'A', 'B', 'C'));
    fin = clock();
    secs = (double)(fin - ini) / CLOCKS_PER_SEC;
    printf("\nTiempo de ejecucion: %.16g milisegundos\n\n", secs * 1000.0);
    
    return 0;
}