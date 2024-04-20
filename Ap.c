#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>

/*
    ? Para moverse por el puntero es necesario sumar o restar a la variable dentro de parentesis
    ! *(Variable+1);
    ! *(Variable-1);
    ? Se puede comparar dos punteros, esto es para evaluar a donde apuntan
    ! *Varibale1==Variable2, entonces apuntan al mismo coso
    ? Para asignar cosas al puntero se hace mediante una variable y con el ampersant
    ! float ns= 3.1416;
    ! float *decimal= &ns;
*/

/*
    ? Las variables fuera del main son variables globales
    ? Ayudan bastante
*/

/*
    ? Glosario memoria dinamica
    ! malloc() Reserva la memoria dinamica
    * Su sintaxis es: Variable = malloc(sizeof(Dato));
    ! free() Libera memoria dinamica
    * Su sintaxis es: free(Variable);
    ! calloc() Similar a malloc pero inicia su valor en 0
    * Variable = (tipo de dato *)calloc(numero de elementos a asignar, sizeof(Tipo de dato de nuevo))
    ! realloc() Aumenta el tamaño en caso de necesitarse
    * Variable = (tipo de dato *)calloc(Variable a aumentar,cantidad de espacios a aumentar * sizeof(Tipo de dato de nuevo))
*/

int main (void){
    /* Para los apuntadores: 
    ! Operar la diereccion & Ampersant
    ! Operar el contenido del apuntador * Asterisco 
    */
    float ns= 3.1416;
    float *decimal= &ns;
    ns=2.1; // ?Si el valor cambia hara que el lugar en el que esta tambien cambies

    int ent=5;
    int *entero=&ent;// ?Para poder modificar cosas dentro primero debe de tener algo dentro 
    *entero = 15; // ?El valor dentro del apuntador cambia al nuevo asignado

    //! Si el apuntador recibe otro tipo de dato al que esta declarado, arojara basura
    //! La basura es algun valor que no tiene sentido alguno o que no esta de acuerdo a su funcion

    int *entetero = &*entero; //? Asi se apunta a un apuntador

    printf("El valor del apuntador decimal es: %f \n", *decimal);
    printf("El valor del apuntador entero es: %d \n", *entero);
    printf("El valor del apuntador del apuntador del entero es: %d\n ", *entetero);


    return 0;
}