#include <stdio.h>
#include <math.h>

int main() {
    double numero, resultado;

    // Solicitar al usuario que ingrese un número
    printf("Ingrese un número: ");
    scanf("%lf", &numero);

    // Calcular el cuadrado utilizando la función pow() de la librería math
    resultado = pow(numero, 2);

    // Mostrar el resultadoa
    printf("El cuadrado de %.2lf es %.2lf.\n", numero, resultado);

    return 0;
}
 