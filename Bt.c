#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define tam 11
#ifdef _WIN32
  #include<windows.h>
#endif  

typedef struct {
    int x;
    int y;
} coords;

void limp(){
  #ifdef _WIN32
    system("cls");
  #else
    system("clear");
  #endif
}

int colocar(int tab[tam][tam]), iniciar(int tab[tam][tam]), tablero(int tab[tam][tam]), disparar(int tab2[tam][tam]);
int initab(int tab2[tam][tam]), tablerom(int tab2[tam][tam]), colocartab(int tab2[tam][tam]), disptab(int tab[tam][tam]);

int main() {
	printf("=============================================\n");
	printf("-----------------Battleship------------------\n");
	printf("=============================================\n");
    int tab[tam][tam], tab2[tam][tam];
    coords b1;
    srand(time(NULL));
	//jugador
    iniciar(tab);
    colocar(tab);
	//IA
    initab(tab2);
    colocartab(tab2);
	//ciclo de juego
    while(1) {
    	printf("=============================================\n");
		printf("-----------------Battleship------------------\n");
		printf("=============================================\n\n");
        disparar(tab2);
        printf("Es turno de la IA. Presiona enter para continuar.\n");
        getchar(); // Presiona Enter para continuar
        disptab(tab);
    }

    return 0;
}

int iniciar(int tab[tam][tam]) {
    for (int i = 0; i < tam; i++) {
        for (int j = 0; j < tam; j++) {
            tab[i][j] = 0;
        }
    }
}

int initab(int tab2[tam][tam]) {
    for (int i = 0; i < tam; i++) {
        for (int j = 0; j < tam; j++) {
            tab2[i][j] = 0;
        }
    }
}

int colocar(int tab[tam][tam]) {
    coords b1;
    int ori;
	limp();
    for (int k = 5; k > 3; k--) {
        printf("Ingresa la coordenada en X y Y del barco de longitud %d:\n", k);
        scanf("%d %d", &b1.y, &b1.x);
        printf("Ingresa 0 para colocarlo vertical y 1 para horizontal: ");
        scanf("%d", &ori);

        if (ori == 0) {
            for (int i = b1.x; i < (b1.x + k); i++) {
                tab[i][b1.y] = k;
            }
        } else if (ori == 1) {
            for (int j = b1.y; j < (b1.y + k); j++) {
                tab[b1.x][j] = k;
            }
        }
        tablero(tab);
    }
}

int tablero(int tab[tam][tam]) {
    printf("==================================\n");
    printf("           Tu tablero\n");
    printf("==================================\n");
    for (int i = 0; i < tam; i++) {
        for (int j = 0; j < tam; j++) {
            if ((i == 0 && (j == 0))) {
                printf("  ");
            } else if (i == 0) {
            	//Arriba
                printf("  |%d", j);
            } else if (j == 0) {
            	//lateral
                printf("|%d|", i);
            } else if (tab[i][j] == -1) {
                printf("|x|");
            } else if (tab[i][j] == -2) {
                printf("|X|");
            } else {
                printf(" |%d|", tab[i][j]);
            }
        }
        printf("\n");
    }
}

int colocartab(int tab[tam][tam]) {
    coords bm1;
    int r = 0, r1 = 0, orim = 0, cont = 0;

    srand(time(NULL));

    for (int k = 5; k > 3; k--) {
        do {
            cont = 0;
            srand(time(NULL));
            while (orim < 1) {
                orim = rand() % 3;
            }
            do {
                r = rand() % 11;
                bm1.y = r;
            } while ((r == 0) || ((r + k) > 10));

            do {
                r1 = rand() % tam;
                bm1.x = r1;
            } while ((r1 == 0) || ((r1 + k) > 10));

            if (orim == 1) {
                for (int i = bm1.x; i < (bm1.x + k); i++) {
                    if (tab[i][bm1.y] != 0) {
                        cont = cont + 1;
                    }
                }

                if (cont == 0) {
                    for (int i = bm1.x; i < (bm1.x + k); i++) {
                        tab[i][bm1.y] = k;
                    }
                }
            } else if (orim == 2) {
                for (int j = bm1.y; j < (bm1.y + k); j++) {
                    if (tab[bm1.x][j] != 0) {
                        cont = cont + 1;
                    }
                }
                if (cont == 0) {
                    for (int j = bm1.y; j < (bm1.y + k); j++) {
                        tab[bm1.x][j] = k;
                    }
                }
            }
        } while (cont >= 1);
    }

    tablerom(tab);
}

int tablerom(int tab2[tam][tam]) {
    printf("==================================\n");
    printf("           Tablero IA\n");
    printf("==================================\n");
    for (int i = 0; i < 11; i++) {
        for (int j = 0; j < 11; j++) {
            if ((i == 0 && (j == 0))) {
                printf("  ");
            } else if (i == 0) {
                //Arriba
                printf("  |%d", j);
            } else if (j == 0) {
                //lateral
                printf("|%d|", i);
            } else if (tab2[i][j] == -1) {
                printf("x ");
            } else if (tab2[i][j] == -2) {
                printf("X ");
            } else {
                printf(" |%d|", tab2[i][j]);
            }
        }
        printf("\n");
    }
}

int disptab(int tab[tam][tam]) {
    int dx = 0, dy = 0, d = -1, cont = 0;

    while (d < 1) {
        srand(time(NULL));
        while (dx < 3) {
            dx = rand() % tam;
        }
        while (dy < 1) {
            dy = rand() % tam;
        }

        if ((tab[dy][dx] == 0)) {
            printf("Eso estuvo cerca\n");
            tab[dy][dx] = d;
            dx = 0;
            dy = 0;
            d = 0;

        }
        if (tab[dy][dx] == -1) {
            dx = 0;
            dy = 0;
            d = 0;
        } else {
            tab[dy][dx] = -2;
            d = 2;
        }
    }

    tablero(tab);
}

int disparar(int tab2[tam][tam]) {
    int dx, dy;
    printf("Ingresa la coordenada en X y Y donde quieres disparar:\n");
    scanf("%d %d", &dx, &dy);

    if (tab2[dy][dx] == 0) {
        tab2[dy][dx] = -1;
        printf("Por porco\n");
    }
    if (tab2[dy][dx] > 0) {
        tab2[dy][dx] = -2;
        printf("Buen tiro\n");
    }

    tablerom(tab2);
}



