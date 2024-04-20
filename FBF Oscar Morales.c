#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

// Estructura para los nodos del árbol sintáctico
typedef struct Nodo {
    char valor;
    struct Nodo *izquierda;
    struct Nodo *derecha;
} Nodo;


bool detectFBF(char *formula);
Nodo* construir_arbol(char *formula, int *indice);
Nodo* crear_nodo(char valor);
void imprimir_arbol(Nodo* raiz);

bool detectFBF(char *formula) {
    int pares = 0; //Variable para mantener los pares de parentesis

    //Iterar sobre la cadena de la fórmula
    for (int i = 0; formula[i] != '\0'; i++) {
        if (formula[i] == '(') {
            pares++; // Incrementar el pares si encontramos un paréntesis izquierdo
        } else if (formula[i] == ')') {
            pares--; // Decrementar el pares si encontramos un paréntesis derecho
        }

        //Si se detecta que el pares es negativo, osea que hay mas parendesis cerrados que abiertos
        //automaticamente se considera una formula no FBF
        if (pares < 0) {
            return false;
        }

        //Se verifica si hay signos no validos en la formula
        if (!isalpha(formula[i]) && formula[i] != '(' && formula[i] != ')' 
		&& formula[i] != '~' && formula[i] != '*' 
		&& formula[i] != '+' && formula[i] != '-') {
            return false;
        }

        //Se verifica que no haya operadores consecutivos sin un atomo entre ellos o un parentesis
        if (i > 0 && (formula[i] == '*' || formula[i] == '+' || formula[i] == '-') 
		&& (formula[i - 1] == '*' || formula[i - 1] == '+' || formula[i - 1] == '-')) {
            return false;
        }

        //Verifica que no haya mas de un atomo consecutivo
        if (i > 0 && isalpha(formula[i]) && isalpha(formula[i - 1])) {
            return false;
        }
    }

    //Si se llega a que el pares no es 0, significa que no es una FBF
    return pares == 0;
}

//Construccion del arbol sintactico
Nodo* construir_arbol(char *formula, int *indice) {
    //Verificar si el carácter actual es un átomo
    if (isalpha(formula[*indice])) {
        return crear_nodo(formula[(*indice)++]);
    } else if (formula[*indice] == '(') {
        //Si es un paréntesis izquierdo, avanza en el índice
        (*indice)++;
        //Construir el subárbol izquierdo
        Nodo* izquierda = construir_arbol(formula, indice);
        //El siguiente carácter debería ser un operador
        char operador = formula[(*indice)++];
        //Construir el subárbol derecho
        Nodo* derecha = construir_arbol(formula, indice);
        //Avanzar para saltar el paréntesis derecho
        (*indice)++;
        //Crear un nodo para el operador y conectar los subárboles
        Nodo* nodo_operador = crear_nodo(operador);
        nodo_operador->izquierda = izquierda;
        nodo_operador->derecha = derecha;
        return nodo_operador;
    } else {
        //Si el carácter actual no es un átomo ni un paréntesis izquierdo,
        //puede ser un espacio en blanco o un operador, así que avanzamos el índice.
        (*indice)++;
        return NULL;
    }
}

//Función para crear un nuevo nodo del árbol
Nodo* crear_nodo(char valor) {
    Nodo* nuevo_nodo = (Nodo*)malloc(sizeof(Nodo));
    nuevo_nodo->valor = valor;
    nuevo_nodo->izquierda = NULL;
    nuevo_nodo->derecha = NULL;
    return nuevo_nodo;
}

//Función para imprimir el árbol sintáctico en orden
void imprimir_arbol(Nodo* raiz) {
    if (raiz == NULL)
        return;

    //Recorrer el subárbol izquierdo
    imprimir_arbol(raiz->izquierda);

    //Imprimir el valor del nodo actual
    printf("%c ", raiz->valor);

    //Recorrer el subárbol derecho
    imprimir_arbol(raiz->derecha);
}

//Inicio del programa
int main() {
	//Cadena de caracteres para la formula
	printf("-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n ");
	printf("         Es una FBF?\n");
	printf("-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n\n");
    char formula[100];
    printf("Introduce una formula proposicional: ");
    fgets(formula, sizeof(formula), stdin);

    //Elimina el salto de linea de la entrada
    if (formula[strlen(formula) - 1] == '\n')
        formula[strlen(formula) - 1] = '\0';

	//Detecta si es una FBF con la funcion detectFBF
    if (detectFBF(formula)) {
        printf("Excelente, la formula si es una FBF\n");
        int indice = 0;
        Nodo* arbol = construir_arbol(formula, &indice);

        //Si es una FBF genera un arbol sintactico simple y en orden
        printf("EL arbol sintáctico en orden: ");
        //Funcion de impresion del arbol sintactico
        imprimir_arbol(arbol);
        printf("\n");
    //En caso de que no sea un FBF
    } else {
        printf("Lo siento, no es una FBF\n");
    }

    return 0;
}