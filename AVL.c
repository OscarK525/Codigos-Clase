#include <stdio.h>
#include <stdlib.h>

//! Estructura del nodo
typedef struct nodo {
    int dato;
    struct nodo *izq;
    struct nodo *der;
    int altura;
} Nodo;

//! Funcion para obtener la altura del nodo
int altura(Nodo *nodo) {
    if (nodo == NULL) {
        return 0;
    }
    return nodo->altura;
}

//! Funcion para pedir números al usuario
int pedirNumero() {
    int numero;
    printf("Ingrese un numero: ");
    scanf("%d", &numero);
    return numero;
}

//! Funcion para obtener el máximo de dos números
int max(int a, int b) {
    return (a > b) ? a : b;
}

//! Funcion para crear un nuevo nodo
Nodo *nuevoNodo(int dato) {
    Nodo *nodo = (Nodo *)malloc(sizeof(Nodo));
    nodo->dato = dato;
    nodo->izq = NULL;
    nodo->der = NULL;
    nodo->altura = 1;
    return nodo;
}

//! Funcion para rotar a la derecha
Nodo *rotarDerecha(Nodo *y) {
    if (y == NULL || y->izq == NULL) {
        printf("No se puede girar a la derecha\n");
        return y;
    }
    
    Nodo *x = y->izq;
    Nodo *T2 = x->der;

    x->der = y;
    y->izq = T2;

    //? Actualizamos la altura de los nodos
    y->altura = max(altura(y->izq), altura(y->der)) + 1;
    if (x != NULL)
        x->altura = max(altura(x->izq), altura(x->der)) + 1;

    //? Imprimir el nodo resultante
    printf("Nodo resultante después de girar a la derecha:\n");
    printf("Dato: %d\n", x->dato);
    printf("Altura: %d\n", x->altura);

    return x;
}

//! Funcion para rotar a la izquierda
Nodo *rotarIzquierda(Nodo *x) {
    if (x == NULL || x->der == NULL) {
        printf("No se puede girar a la izquierda\n");
        return x;
    }
    
    Nodo *y = x->der;
    Nodo *T2 = y->izq;

    y->izq = x;
    x->der = T2;

    //? Actualizamos la altura de los nodos
    x->altura = max(altura(x->izq), altura(x->der)) + 1;
    if (y != NULL)
        y->altura = max(altura(y->izq), altura(y->der)) + 1;

    //? Imprimir el nodo resultante
    printf("Nodo resultante después de girar a la izquierda:\n");
    printf("Dato: %d\n", y->dato);
    printf("Altura: %d\n", y->altura);

    return y;
}

//! Funcion de doble rotacion a la derecha
Nodo *rotarDerechaIzquierda(Nodo *nodo) {
    printf("Realizando doble giro a la derecha-izquierda\n");
    nodo->der = rotarDerecha(nodo->der);
    return rotarIzquierda(nodo);
}

//! Funcion de doble rotacion a la izquierda
Nodo *rotarIzquierdaDerecha(Nodo *nodo) {
    printf("Realizando doble giro a la izquierda-derecha\n");
    nodo->izq = rotarIzquierda(nodo->izq);
    return rotarDerecha(nodo);
}

//! Funcion para obtener el balance del nodo
int obtenerBalance(Nodo *nodo) {
    if (nodo == NULL) {
        return 0;
    }
    return altura(nodo->izq) - altura(nodo->der);
}

//! Funcion para insertar un nodo
Nodo *insertarNodo(Nodo *nodo, int dato) {
    if (nodo == NULL) {
        return nuevoNodo(dato);
    }

    if (dato < nodo->dato) {
        nodo->izq = insertarNodo(nodo->izq, dato);
    } else if (dato > nodo->dato) {
        nodo->der = insertarNodo(nodo->der, dato);
    } else {
        return nodo;
    }

    nodo->altura = 1 + max(altura(nodo->izq), altura(nodo->der));

    int balance = obtenerBalance(nodo);

    if (balance > 1 && dato < nodo->izq->dato) {
        return rotarDerecha(nodo);
    }

    if (balance < -1 && dato > nodo->der->dato) {
        return rotarIzquierda(nodo);
    }

    if (balance > 1 && dato > nodo->izq->dato) {
        nodo->izq = rotarIzquierda(nodo->izq);
        return rotarDerecha(nodo);
    }

    if (balance < -1 && dato < nodo->der->dato) {
        nodo->der = rotarDerecha(nodo->der);
        return rotarIzquierda(nodo);
    }

    return nodo;
}

//! Funcion para recorrer el árbol en orden
void enOrden(Nodo *raiz) {
    if (raiz != NULL) {
        enOrden(raiz->izq);
        printf("%d ", raiz->dato);
        enOrden(raiz->der);
    }
}

//! Funcion para recorrer el árbol en postorden
void postOrden(Nodo *raiz) {
    if (raiz != NULL) {
        postOrden(raiz->izq);
        postOrden(raiz->der);
        printf("%d ", raiz->dato);
    }
}

//! Funcion para recorrer el árbol en preorden
void preOrden(Nodo *raiz) {
    if (raiz != NULL) {
        printf("%d ", raiz->dato);
        preOrden(raiz->izq);
        preOrden(raiz->der);
    }
}

//! Funcion principal
int main() {
    Nodo *raiz = NULL;
    int opcion = 0;
    while (opcion != 9) {
        printf("\n");
        printf("1. Insertar un nodo\n");
        printf("2. Recorrer en orden\n");
        printf("3. Recorrer en preorden\n");
        printf("4. Recorrer en postorden\n");
        printf("5. Girar a la izquierda\n");
        printf("6. Girar a la derecha\n");
        printf("7. Doble giro a la izquierda\n");
        printf("8. Doble giro a la derecha\n");
        printf("9. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        switch (opcion) {
            case 1:
                raiz = insertarNodo(raiz, pedirNumero());
                break;
            case 2:
                enOrden(raiz);
                printf("\n");
                break;
            case 3:
                preOrden(raiz);
                printf("\n");
                break;
            case 4:
                postOrden(raiz);
                printf("\n");
                break;
            case 5:
                raiz = rotarIzquierda(raiz);
                printf("\n");
                break;
            case 6:
                raiz = rotarDerecha(raiz);
                printf("\n");
                break;
            case 7:
                raiz = rotarIzquierdaDerecha(raiz);
                printf("\n");
                break;
            case 8:
                raiz = rotarDerechaIzquierda(raiz);
                printf("\n");
                break;
            case 9:
                break;
            default:
                break;
        } 
    }
    return 0;
}
