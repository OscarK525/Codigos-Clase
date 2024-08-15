// Oscar Morales
// Librerias
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <limits.h>
#include <math.h>

// Constantes del programa
const int fil = 20;  // Numero de filas del mapa
const int col = 20;  // Numero de columnas del mapa
const float prob_mut = 0.1;  // Probabilidad de mutacion
const int num_genes = 1000;  // Numero de genes en el genoma de un robot
const int num_robs = 100;  // Numero de robots en la poblacion
const int vida_inicial = 50;  // Vida inicial de los robots
const int num_entradas = 12;  // Numero de entradas
const int num_ocultas = 5;  // Numero de neuronas en la capa oculta
const int num_salidas = 4;  // Numero de salidas
const int num_generaciones = 1000;  // Numero de generaciones a simular
const int torneo_size = 5;  // Tamaño del torneo para la selección de padres

// Estructura del Robot
struct robot
{
    int x;  // Posicion x del robot en el mapa
    int y;  // Posicion y del robot en el mapa
    int fitness;  // Valor que mide el rendimiento del robot
    int vida;  // Vida restante del robot
    float pesos_eo[12][5];  // Pesos de las conexiones entre la capa de entrada y la capa oculta
    float pesos_os[5][4];  // Pesos de las conexiones entre la capa oculta y la capa de salida
    int rec[100][2];  // Registro de las posiciones recorridas por el robot
};

// Alias para la estructura del robot
typedef struct robot raspi;

// Funcion para generar el mapa
void generarMapa(char mapa[fil][col], int *luz_x, int *luz_y)
{
    char obstaculo = 'X';  // Obstaculo en el mapa
    char luz = 'L';  // Luz en el mapa
    char espacio = ' ';  // Espacio libre en el mapa

    // Llenar el mapa con Obstaculos y espacios libres
    for (int i = 0; i < fil; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if (i == 0 || i == fil - 1 || j == 0 || j == col - 1)
            {
                mapa[i][j] = obstaculo;  // Bordes del mapa como obstaculo
            }
            else
            {
                int random = rand() % 100;
                if (random < 10)
                {
                    mapa[i][j] = obstaculo;  // 10% de probabilidad de obstaculo
                }
                else
                {
                    mapa[i][j] = espacio;  // 90% de probabilidad de espacio libre
                }
            }
        }
    }

    // Colocar la luz en una posicion aleatoria del mapa
    *luz_x = rand() % (fil - 2) + 1;
    *luz_y = rand() % (col - 2) + 1;
    mapa[*luz_x][*luz_y] = luz;
}

// Funcion para imprimir el mapa
void imprimirMapa(char mapa[fil][col])
{
    for (int i = 0; i < fil; i++)
    {
        for (int j = 0; j < col; j++)
        {
            printf("%c", mapa[i][j]);  // Imprimir cada celda del mapa
        }
        printf("\n");
    }
}

// Funcion para imprimir la informacion de un robot
void imprimirRobot(raspi *robot)
{
    printf("Posicion: (%d, %d)\n", robot->x, robot->y);
    printf("Fitness: %d\n", robot->fitness);
    printf("Vida: %d\n", robot->vida);
    printf("Pesos eo:\n");
    for (int i = 0; i < num_entradas; i++)
    {
        for (int j = 0; j < num_ocultas; j++)
        {
            printf("%f ", robot->pesos_eo[i][j]);  // Imprimir los pesos de entrada a oculta
        }
        printf("\n");
    }
    printf("Pesos os:\n");
    for (int i = 0; i < num_ocultas; i++)
    {
        for (int j = 0; j < num_salidas; j++)
        {
            printf("%f ", robot->pesos_os[i][j]);  // Imprimir los pesos de oculta a salida
        }
        printf("\n");
    }
}

// Sensores del robot

// Funcion para detectar obstaculos en una dirección
float sensorObstaculo(char mapa[fil][col], int x, int y, int dx, int dy)
{
    int alcance = 4;  // Alcance del sensor
    for (int i = 1; i < alcance; i++)
    {
        int nx = x + dx * i;
        int ny = y + dy * i;
        if (nx < 0 || ny < 0 || nx >= fil || ny >= col)
            break;
        if (mapa[nx][ny] == 'X')
        {
            return 1.0 / i;  // Retorna la distancia inversa al obstáculo
        }
    }
    return 0;
}

// Funcion para detectar la luz en una dirección específica
float sensorLuz(char mapa[fil][col], int x, int y, int dx, int dy)
{
    int alcance = 4;  // Alcance del sensor
    for (int i = 1; i < alcance; i++)
    {
        int nx = x + dx * i;
        int ny = y + dy * i;
        if (nx < 0 || ny < 0 || nx >= fil || ny >= col)
            break;
        if (mapa[nx][ny] == 'L')
        {
            return 1.0 / i;  // Retorna la distancia inversa a la luz
        }
    }
    return 0;
}

// Funcion para detectar espacio libre en una direccion especifica
float sensorEspacio(char mapa[fil][col], int x, int y, int dx, int dy)
{
    int alcance = 4;  // Alcance del sensor
    for (int i = 1; i < alcance; i++)
    {
        int nx = x + dx * i;
        int ny = y + dy * i;

        if (nx >= 0 && nx < fil && ny >= 0 && ny < col)
        {
            if (mapa[nx][ny] == ' ')
            {
                return 1.0 / i;  // Retorna la distancia inversa al espacio libre
            }
        }
        else
        {
            return 0;
        }
    }
    return 0;
}

// Funcion para obtener las entradas (valores de los sensores) del robot
void obtenerEntradas(float entradas[], char mapa[fil][col], int x, int y)
{
    entradas[0] = sensorObstaculo(mapa, x, y, -1, 0); // Sensor de obstaculos hacia arriba
    entradas[1] = sensorObstaculo(mapa, x, y, 1, 0);  // Sensor de obstaculos hacia abajo
    entradas[2] = sensorObstaculo(mapa, x, y, 0, -1); // Sensor de obstaculos hacia la izquierda
    entradas[3] = sensorObstaculo(mapa, x, y, 0, 1);  // Sensor de obstaculos hacia la derecha
    entradas[4] = sensorLuz(mapa, x, y, -1, 0);       // Sensor de luz hacia arriba
    entradas[5] = sensorLuz(mapa, x, y, 1, 0);        // Sensor de luz hacia abajo
    entradas[6] = sensorLuz(mapa, x, y, 0, -1);       // Sensor de luz hacia la izquierda
    entradas[7] = sensorLuz(mapa, x, y, 0, 1);        // Sensor de luz hacia la derecha
    entradas[8] = sensorEspacio(mapa, x, y, -1, 0);   // Sensor de espacio libre hacia arriba
    entradas[9] = sensorEspacio(mapa, x, y, 1, 0);    // Sensor de espacio libre hacia abajo
    entradas[10] = sensorEspacio(mapa, x, y, 0, -1);  // Sensor de espacio libre hacia la izquierda
    entradas[11] = sensorEspacio(mapa, x, y, 0, 1);   // Sensor de espacio libre hacia la derecha
}

// Funcion para evaluar el estado del robot
void evaluar(raspi *robot, char mapa[fil][col])
{
    if (robot->vida == 0)
    {
        robot->fitness = 0;  // Si el robot no tiene vida, su fitness es 0
        return;
    }
    if (mapa[robot->x][robot->y] == 'X')
    {
        robot->fitness -= 10;  // Penalizacion por chocar con un obstáculo
        robot->vida = 0;
        return;
    }
    if (mapa[robot->x][robot->y] == 'L')
    {
        robot->fitness += 1000 / (vida_inicial - robot->vida + 1);  // Recompensa por encontrar la luz
        robot->vida = 0;
        return;
    }
    if (robot->x != robot->rec[robot->vida - 1][0] || robot->y != robot->rec[robot->vida - 1][1])
    {
        robot->fitness += 1;  // Incremento del fitness por moverse a una nueva posición
    }
}

// Funcion para activar la red neuronal del robot y obtener las salidas
void activar(float entradas[], float *salidas, raspi *robot)
{
    float ocultas[5] = {0};

    // Calcular las activaciones de la capa oculta
    for (int i = 0; i < num_ocultas; i++)
    {
        for (int j = 0; j < num_entradas; j++)
        {
            ocultas[i] += entradas[j] * robot->pesos_eo[j][i];
        }
        ocultas[i] = 1 / (1 + exp(-ocultas[i]));  // Funcion de activacion sigmoide
    }

    // Calcular las activaciones de la capa de salida
    for (int i = 0; i < num_salidas; i++)
    {
        salidas[i] = 0;
        for (int j = 0; j < num_ocultas; j++)
        {
            salidas[i] += ocultas[j] * robot->pesos_os[j][i];
        }
        salidas[i] = 1 / (1 + exp(-salidas[i]));  // Funcion de activacion sigmoide
    }
}

// Funcion para mover el robot segun las salidas de la red neuronal
void mover(raspi *robot, char mapa[fil][col])
{
    float entradas[num_entradas];
    obtenerEntradas(entradas, mapa, robot->x, robot->y);  // Obtener las entradas del robot

    float salidas[num_salidas];
    activar(entradas, salidas, robot);  // Activar la red neuronal del robot

    int max_index = 0;
    for (int i = 1; i < num_salidas; i++)
    {
        if (salidas[i] > salidas[max_index])
        {
            max_index = i;  // Determinar la salida con mayor valor
        }
    }

    robot->rec[robot->vida][0] = robot->x;
    robot->rec[robot->vida][1] = robot->y;

    // Mover el robot segun la salida con mayor valor
    switch (max_index)
    {
    case 0:
        if (mapa[robot->x - 1][robot->y] != 'X')
        {
            robot->x -= 1;  // Mover hacia arriba
        }
        break;
    case 1:
        if (mapa[robot->x + 1][robot->y] != 'X')
        {
            robot->x += 1;  // Mover hacia abajo
        }
        break;
    case 2:
        if (mapa[robot->x][robot->y - 1] != 'X')
        {
            robot->y -= 1;  // Mover hacia la izquierda
        }
        break;
    case 3:
        if (mapa[robot->x][robot->y + 1] != 'X')
        {
            robot->y += 1;  // Mover hacia la derecha
        }
        break;
    }
    robot->vida--;  // Reducir la vida del robot en cada movimiento
}

// Funcion para mutar los pesos de la red neuronal del robot
void mutar(raspi *robot)
{
    for (int i = 0; i < num_entradas; i++)
    {
        for (int j = 0; j < num_ocultas; j++)
        {
            if (rand() / (float)RAND_MAX < prob_mut)
            {
                robot->pesos_eo[i][j] += ((rand() / (float)RAND_MAX) - 0.5) * 2;  // Mutacion en los pesos de entrada a oculta
            }
        }
    }
    for (int i = 0; i < num_ocultas; i++)
    {
        for (int j = 0; j < num_salidas; j++)
        {
            if (rand() / (float)RAND_MAX < prob_mut)
            {
                robot->pesos_os[i][j] += ((rand() / (float)RAND_MAX) - 0.5) * 2;  // Mutacion en los pesos de oculta a salida
            }
        }
    }
}

// Funcion para cruzar los genes de dos robots padres y crear un hijo
void cruzar(raspi *padre, raspi *madre, raspi *hijo)
{
    for (int i = 0; i < num_entradas; i++)
    {
        for (int j = 0; j < num_ocultas; j++)
        {
            hijo->pesos_eo[i][j] = (rand() % 2 == 0) ? padre->pesos_eo[i][j] : madre->pesos_eo[i][j];  // Cruce de pesos de entrada a oculta
        }
    }
    for (int i = 0; i < num_ocultas; i++)
    {
        for (int j = 0; j < num_salidas; j++)
        {
            hijo->pesos_os[i][j] = (rand() % 2 == 0) ? padre->pesos_os[i][j] : madre->pesos_os[i][j];  // Cruce de pesos de oculta a salida
        }
    }
    mutar(hijo);  // Mutacion del hijo
}

// Funcion para seleccionar un robot padre usando el metodo del torneo
raspi seleccionarPadre(raspi poblacion[])
{
    raspi mejor = poblacion[rand() % num_robs];
    for (int i = 1; i < torneo_size; i++)
    {
        raspi candidato = poblacion[rand() % num_robs];
        if (candidato.fitness > mejor.fitness)
        {
            mejor = candidato;  // Seleccionar el mejor robot del torneo
        }
    }
    return mejor;
}

// Funcion para inicializar un robot con valores aleatorios
void inicializarRobot(raspi *robot)
{
    robot->x = rand() % (fil - 2) + 1;
    robot->y = rand() % (col - 2) + 1;
    robot->vida = vida_inicial;
    robot->fitness = 0;
    for (int i = 0; i < num_entradas; i++)
    {
        for (int j = 0; j < num_ocultas; j++)
        {
            robot->pesos_eo[i][j] = ((rand() / (float)RAND_MAX) - 0.5) * 2;  // Inicializar pesos de entrada a oculta
        }
    }
    for (int i = 0; i < num_ocultas; i++)
    {
        for (int j = 0; j < num_salidas; j++)
        {
            robot->pesos_os[i][j] = ((rand() / (float)RAND_MAX) - 0.5) * 2;  // Inicializar pesos de oculta a salida
        }
    }
}

// Funcion para inicializar la población de robots
void inicializarPoblacion(raspi poblacion[])
{
    for (int i = 0; i < num_robs; i++)
    {
        inicializarRobot(&poblacion[i]);  // Inicializar cada robot en la población
    }
}

// Funcion principal para ejecutar la simulación
void ejecutarSimulacion(char mapa[fil][col])
{
    raspi poblacion[num_robs];
    inicializarPoblacion(poblacion);  // Inicializar la población

    for (int generacion = 0; generacion < num_generaciones; generacion++)
    {
        printf("Generacion %d\n", generacion);

        // Evaluar cada robot en la población
        int fitness_total = 0;
        raspi mejor_robot = poblacion[0];

        for (int i = 0; i < num_robs; i++)
        {
            raspi *robot = &poblacion[i];
            robot->vida = vida_inicial;
            robot->fitness = 0;
            while (robot->vida > 0)
            {
                mover(robot, mapa);  // Mover el robot
                evaluar(robot, mapa);  // Evaluar el robot
            }
            fitness_total += robot->fitness;
            if (robot->fitness > mejor_robot.fitness)
            {
                mejor_robot = *robot;  // Encontrar el mejor robot de la generación
            }
        }

        // Imprimir resultados de la generación
        printf("Fitness promedio: %f\n", (float)fitness_total / num_robs);
        printf("Mejor robot - Fitness: %d\n", mejor_robot.fitness, mejor_robot.x, mejor_robot.y);

        // Crear nueva población a través de cruces y mutaciones
        raspi nueva_poblacion[num_robs];
        for (int i = 0; i < num_robs; i++)
        {
            raspi padre = seleccionarPadre(poblacion);
            raspi madre = seleccionarPadre(poblacion);
            raspi hijo;
            inicializarRobot(&hijo);  // Inicializar el hijo antes de cruzar
            cruzar(&padre, &madre, &hijo);
            nueva_poblacion[i] = hijo;  // Agregar el hijo a la nueva población
        }

        // Reemplazar la población antigua con la nueva población
        for (int i = 0; i < num_robs; i++)
        {
            poblacion[i] = nueva_poblacion[i];
        }
    }
}

// Funcion principal del programa
int main()
{
    srand(time(NULL));  // Inicializar la semilla de números aleatorios

    char mapa[fil][col];
    int luz_x, luz_y;
    generarMapa(mapa, &luz_x, &luz_y);  // Generar el mapa
    imprimirMapa(mapa);  // Imprimir el mapa

    ejecutarSimulacion(mapa);  // Ejecutar la simulación

    return 0;
}
