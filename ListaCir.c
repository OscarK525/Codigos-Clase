#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Nodo {
    int movimiento;
    int direccion;
    struct Nodo *sig;
    struct Nodo *ant;
} Nodo;

Nodo* crearNodo() {
    Nodo *nuevo = (Nodo *)malloc(sizeof(Nodo));
    nuevo->movimiento = rand() % 5 + 1;
    nuevo->direccion = rand() % 2;
    nuevo->sig = NULL;
    nuevo->ant = NULL;
    return nuevo;
}

void insertarFinal(Nodo **head, Nodo *nuevoNodo) {
    if (*head == NULL) {
        *head = nuevoNodo;
        nuevoNodo->sig = nuevoNodo;
        nuevoNodo->ant = nuevoNodo;
    } else {
        Nodo *ultimo = (*head)->ant;
        ultimo->sig = nuevoNodo;
        nuevoNodo->ant = ultimo;
        nuevoNodo->sig = *head;
        (*head)->ant = nuevoNodo;
    }
}

void eliminarNodo(Nodo **head, Nodo *nodoEliminar) {
    if (*head == nodoEliminar) {
        *head = nodoEliminar->sig;
    }
    nodoEliminar->ant->sig = nodoEliminar->sig;
    nodoEliminar->sig->ant = nodoEliminar->ant;
    free(nodoEliminar);
}

void imprimirNodos(Nodo *head) {
    Nodo *temp = head;
    do {
        printf("Nodo con movimiento %d y direccion %d\n", temp->movimiento, temp->direccion);
        temp = temp->sig;
    } while (temp != head);
}

int main() {
    srand(time(0));
    Nodo *head = NULL;
    for (int i = 0; i < 10; i++) {
        insertarFinal(&head, crearNodo());
    }
    Nodo *actual = head;
    while (head->sig != head) {
        printf("Presiona enter para continuar\n");
        getchar(); // Espera la inserción de un enter para continuar
        for (int i = 0; i < actual->movimiento; i++) {
            actual = (actual->direccion == 0) ? actual->sig : actual->ant;
        }
        Nodo *siguiente = (actual->direccion == 0) ? actual->sig : actual->ant;
        printf("Moviendo en direccion %s\n", actual->direccion == 0 ? "horaria" : "antihoraria");
        printf("Eliminando nodo con movimiento %d y direccion %d\n", actual->movimiento, actual->direccion);
        eliminarNodo(&head, actual);
        actual = siguiente;
        imprimirNodos(head); // Imprime todos los nodos después de cada ciclo
    }
    printf("El ganador es el nodo con movimiento %d y direccion %d\n", head->movimiento, head->direccion);
    free(head);
    return 0;
}