//! K
#include <stdlib.h>
#include <stdio.h>

//! Estructura de nodo
typedef struct nodo {
    int numero;
    struct nodo *next;
} nodo;

/*
! Inicia la lista y devuelve un valor NULL al puntero
*/
nodo *listan(nodo *lista) {
    lista = NULL;
    return lista;
}

/*
! Crea un nodo y lo inserta al inicio
! Devuelve la lista actualizada
*/
nodo *insertar(nodo *lista, int numero) {
    nodo *nuevonumero;
    nuevonumero = (nodo *)malloc(sizeof(nodo));
    nuevonumero->numero = numero;
    nuevonumero->next = lista;
    lista = nuevonumero;
    return lista;
}

/*
! Crea un nodo y lo inserta en la lista despues de un valor x
! Si x no se encuentra en la lista devuelve una lista vacia
*/
void insDesp(nodo **lista, int x, int y) {
    nodo *nuevonumero, *aux;
    nuevonumero = (nodo *)malloc(sizeof(nodo));
    nuevonumero->numero = y;
    nuevonumero->next = NULL;

    aux = *lista;
    while (aux != NULL) {
        if (aux->numero == x) {
            nuevonumero->next = aux->next;
            aux->next = nuevonumero;
            return;
        }
        aux = aux->next;
    }
    printf("El valor %d no se encuentra en la lista \n", x);
}


/*
! Elimina el primer nodo y libera la memoria
! Da error si esta vacia la lista
*/
void borrarPrimero(nodo **lista) {
    if (*lista == NULL) {
        printf("La lista se encuentra vacia\n");
        return;
    }
    nodo *temp = *lista;
    *lista = (*lista)->next;
    free(temp);
}

/*
! Elimina el ultimo nodo de la lista y libera la memoria
! Si solo hay un solo nodo, regresa la lista como NULL
! Y si esta vacia, da error
*/
void borrarUltimo(nodo **lista) {
    if (*lista == NULL) {
        printf("La lista se encuentra vacia\n");
        return;
    }
    if ((*lista)->next == NULL) {
        free(*lista);
        *lista = NULL;
        return;
    }
    nodo *prev = NULL;
    nodo *current = *lista;
    while (current->next != NULL) {
        prev = current;
        current = current->next;
    }
    free(current);
    prev->next = NULL;
}

/*
! Elimina un nodo despues de otro y se libera la memoria
! Si el nodo con valor x no tiene siguiente da error
! Si esta vacia tambien da error
*/
void borrarDesp(nodo **lista, int x) {
    nodo *temp, *prev;
    temp = *lista;
    prev = NULL;

    //? Mientras sea diferente a null
    while (temp != NULL) {
        //? Si temporal es igual a x
        if (temp->numero == x) {
            //? Si temporal es igual a NULL no hay nada que borrar
            if (temp->next == NULL) {
                printf("No hay nodo después de %d para borrarlo\n", x);
                return;
            }
            //? De lo contrario elimina el nodo siguiente y recorre el apuntador
            prev = temp;
            temp = temp->next;
            prev->next = temp->next;
            //? Libera la memoria
            free(temp);
            return;
        }
        prev = temp;
        temp = temp->next;
    }
    printf("El valor %d no se encuentra en la lista \n", x);
}

/*
! Imprime la lista
*/
void imp_cola(nodo *lista) {
    printf("Lista: ");
    while (lista != NULL) {
        printf("%d ", lista->numero);
        lista = lista->next;
    }
    printf("\n");
}

//! Main
int main() {
    nodo *lista = listan(lista);
    int opc, num, desp, x;
    while (1) {
        printf("                      Menu de Lista   \n");
        printf("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-");
        printf("\nQue desea hacer?\n");
        printf("1. Insertar al inicio\n");
        printf("2. Insertar después de un número\n");
        printf("3. Borrar primer numero\n");
        printf("4. Borrar ultimo numero\n");
        printf("5. Borrar un numero después de otro\n");
        printf("6. Imprimir lista\n");
        printf("7. Salir\n");
        scanf("%d", &opc);
        //? Switch del menu
        switch (opc) {
        case 1:
            printf("Ingrese el número a insertar: ");
            scanf("%d", &num);
            lista = insertar(lista, num);
            break;
        case 2:
            printf("Después de qué número desea insertar: ");
            scanf("%d", &x);
            printf("Ingrese el número a insertar: ");
            scanf("%d", &num);
            insDesp(&lista, x, num);
            imp_cola(lista);
            break;
        case 3:
            borrarPrimero(&lista);
            imp_cola(lista);
            break;
        case 4:
            borrarUltimo(&lista);
            imp_cola(lista);
            break;
        case 5:
            printf("Después de qué número desea borrar: ");
            scanf("%d", &x);
            borrarDesp(&lista, x);
            break;
        case 6:
            imp_cola(lista);
            break;
        case 7:
            printf("Saliendo...\n");
            return 0;
        default:
            printf("Tas bien? Esa no es opcion BURRO\n");
            break;
        }
    }
}
