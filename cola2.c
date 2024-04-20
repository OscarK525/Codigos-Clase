#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

//? Estructuras
typedef struct {
    int frente;
    int atras;
} Indice;

typedef struct {
    bool uso;
    int turnos;
} Cajero;

typedef struct {
    int clientes[10];
    int frente;
    int atras;
} Cola;

//? Aqui es donde se agregan a la cola
void mascola(Cola *c, int cliente) {
    if ((c->atras + 1) % 10 != c->frente) {
        c->clientes[c->atras] = cliente;
        c->atras = (c->atras + 1) % 10;
    } else {
        printf("La cola está llena.\n");
    }
    if (c->frente == c->atras) {
        printf("La cola está llena.\n");
        return;
    }
}

//? Uso y desuso del cajeros
void avanzar_cajero(Cajero *c) {
    if (c->uso) {
        c->turnos--;
        if (c->turnos == 0) {
            c->uso = false;
            printf("El cajero ha terminado de atender a un cliente.\n");
        }
    }
}

//? Clientes nuevos y sus turnos
void nuevo_cliente(Cola *c) {
    int tik;
    int nv_c = rand() % 5;
    if (nv_c == 0) {
        printf("No llegó ningún cliente nuevo.\n");
    } else {
        tik = rand() % 10 + 1;
        printf("Nuevo cliente a la fila.\n");
        printf("Sus turnos necesarios son: %d\n", tik);
        mascola(c, tik); // Add new client to the queue
    }
}


//? Imprimir el estado actual de la cola
void imprimir_cola(Cola *c) {
    printf("Cola de clientes:\n");
    int i = c->frente;
    while (i != c->atras) {
        printf("%d ", c->clientes[i]);
        i = (i + 1) % 10;
    }
    printf("\n");
}

int main() {
    srand(time(NULL));

    Cola cola;
    cola.frente = 0;
    cola.atras = 0;

    Cajero cajeros[3]; // Assuming 3 cashiers
    for (int i = 0; i < 3; i++) {
        cajeros[i].uso = false;
    }

    char tecla;

    while (1) {
        printf("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*");
        printf("                          ColaDos");
        printf("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*");
        nuevo_cliente(&cola);
        for (int i = 0; i < 3; i++) {
            if (!cajeros[i].uso && cola.frente != cola.atras) {
                cajeros[i].uso = true;
                cajeros[i].turnos = cola.clientes[cola.frente];
                cola.frente = (cola.frente + 1) % 10;
                printf("El cliente está siendo atendido por el cajero %d.\n", i+1);
            }
            avanzar_cajero(&cajeros[i]);
        }
        imprimir_cola(&cola);
        printf("Presione Enter para continuar.\n");
        scanf("%c", &tecla); 
        system("cls");
    }

    return 0;
}
