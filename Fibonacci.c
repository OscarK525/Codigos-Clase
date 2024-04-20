#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//? Funcion recursiva para obtener el numero de Fibonacci
int fibonacciRecursiva(int n){
    if(n == 0){
        return 0;
    }
    else if(n == 1){
        return 1;
    }
    else{
        return fibonacciRecursiva(n-1) + fibonacciRecursiva(n-2);
    }
}

//? Funcion iterativa para obtener el numero de Fibonacci
int fibonacciIterativo(int n){
    int a = 0, b = 1, c;
    if(n == 0){
        return a;
    }
    for(int i = 2; i <= n; i++){
        c = a + b;
        a = b;
        b = c;
    }
    return b;
}

//? Funcion principal
int main(){
    int n;
    clock_t ini, fin;
    double secs;
    printf("Cuantos numeros de Fibonacci deseas? ");
    scanf("%d", &n);
    ini = clock();
    for(int i = 0; i < n; i++){
        printf("%d ", fibonacciRecursiva(i));
    }
    fin = clock();
    secs = (double)(fin - ini) / CLOCKS_PER_SEC;
    printf("\nTiempo de ejecucion: %.16g milisegundos\n\n", secs * 1000.0);
    //? Iterativo
    ini = clock();
    for(int i = 0; i < n; i++){
        printf("%d ", fibonacciIterativo(i));
    }
    fin = clock();
    secs = (double)(fin - ini) / CLOCKS_PER_SEC;
    printf("\nTiempo de ejecucion: %.16g milisegundos\n\n", secs * 1000.0);
    return 0;
}