#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    int edad;
    char prop[50];
    char especie[20];
    char nombre[50];
}animal;

int main(){
    /*
        * El asterisco es para determinar el apuntador
        * EL ampersant es para asignar valores al apuntador
    */

    animal *datos = malloc(sizeof(animal)); //! Aqui se asigna la memoria al puntero de datos

    /*
        ! Para capturar strings es importante usar fgets
        ! Con fgets, puedes leer una línea completa de entrada, 
        ! incluidos los espacios en blanco. La función fgets toma tres argumentos: 
        ! el buffer donde se almacenará la cadena de caracteres, el tamaño máximo del buffer y el flujo de entrada 
        ! stdin en este caso. 
        ? Incluye salto de linea
    */
    printf("Nombre del propietario del animal: ");
    fgets(datos->prop, sizeof(datos->prop), stdin); //? No es necesario el Ampersant ni el Asterisco
    printf("Que especie animal es: ");
    fgets(datos->especie, sizeof(datos->especie), stdin);//? No es necesario el Ampersant ni el Asterisco
    printf("Nombre del animal: ");
    fgets(datos->nombre, sizeof(datos->nombre), stdin);//? No es necesario el Ampersant ni el Asterisco
    printf("Edad del animal: ");
    scanf("%i", &datos->edad);//? No es necesario el Asterisco
    //? Impresion de los datos
    printf("Datos del animal ingresado: \n");
    printf("Pripietario: %s", datos->prop);
    printf("Especie: %s", datos->especie);
    printf("Nombre: %s", datos->nombre);
    printf("Edad: %i", datos->edad);

    free(datos); //! Se libera la memoria que utiliza la variable
    return 0;
}