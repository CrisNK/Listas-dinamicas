#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define MAX_containers 12
#define MAX_pilas 7
#define true 1
#define false 0

typedef struct
{
    int id;
    char empresa[100];
} CONTAINER;
typedef struct
{
    CONTAINER container[MAX_containers];
    int tope;
} PILA;

void clean()
{
    system("clear");
    ////system("cls");
}
void pause()
{
    fflush(stdin);
    getchar();
    ////system("pause");
}
// Protipos de funciones
void agregarContainer(PILA pila[]);
void eliminarContainer(PILA pila[]);
void mostrarContainers(PILA pila[]);
void imprimir_infoPilas(PILA pila[]);
void menu();

int main()
{
    srand(time(NULL));
    PILA pila[MAX_pilas];
    int i, opcion;
    for (i = 0; i < MAX_pilas; i++)
        pila[i].tope = -1;
    do
    {
        menu();
        scanf("%d", &opcion);
        switch (opcion)
        {
        case 1:
            clean();
            agregarContainer(pila);
            imprimir_infoPilas(pila);
            break;
        case 2:
            eliminarContainer(pila);
            break;
        case 3:
            // PEEK de la pila que el usuario escoja
            break;
        case 4:
            mostrarContainers(pila);
            pause();
            break;
        case 5:
            printf("Saliendo del programa");
            break;
        default:
            printf("Opcion no valida, intente nuevamente");
            break;
        }
    } while (opcion != 5);
    return 0;
}

void agregarContainer(PILA pila[])
{
    // Comprobar de que las pilas estén libres para ingresar un nuevo container.
    int i, pilasLlenas = 0;
    for (i = 0; i < MAX_pilas; i++)
    {
        if (pila[i].tope == (MAX_containers - 1))
            pilasLlenas++;
    }
    if (pilasLlenas == MAX_pilas)
    {
        printf("Error: No hay espacio para ingresar otro container.\n");
        return;
    }

    int posicionPila;
    char empresa[100];
    mostrarContainers(pila);
    do
    {
        printf("A que pila deseas ingresarle un container? ");
        scanf("%d", &posicionPila);
        if (pila[posicionPila].tope == MAX_containers)
        {
            clean();
            printf("Error: Pila de containers llena.\n");
        }
    } while (posicionPila < 1 || posicionPila > 8);

    posicionPila--;
    printf("Ingresa el nombre de la empresa propietaria del container: ");
    scanf("%s", empresa);
    pila[posicionPila].tope++;
    pila[posicionPila].container[pila[posicionPila].tope].id = 1000 + rand() % 8999;
    strcpy(pila[posicionPila].container[pila[posicionPila].tope].empresa, empresa);
}
void eliminarContainer(PILA pila[])
{
    int id, i, isFounded = false;
    int bandera = 0;
    int posicionActualContainer = -1;
    printf("Ingrese el ID del container que desea eliminar: ");
    scanf("%d", &id);
    if (id > 9999 || id < 1000)
    {
        while (id > 9999 || id < 1000)
        {
            printf("Los codigos unicos de cada container son de 4 digitos, ingrese nuevamente: ");
            scanf("%d", &id);
        }
    }
    for (i = 0; i < MAX_pilas; i++)
    {
        while (posicionActualContainer < pila[i].tope)
        {
            // Aqui encuentro la posicion del elemento que quiero eliminar.
            if (pila[i].container[posicionActualContainer + 1].id == id)
            {
                bandera = 1;
                // Aqui consulto si es que la posicion que quiero borrar esta en el tope.
                if (pila[i].tope == posicionActualContainer + 1)
                {
                    pila[i].tope--;
                    // Se agrega un break para indicar que ya se elimino el id que era igual a el tope de alguna pila
                    printf("Producto eliminado\n");
                    break;
                }
                else // Se encontro el id del container a borrar, pero no esta en el tope
                {
                    CONTAINER containerAux[12]; // se crea una pila auxiliar para apilar y desapilar
                    int topeAux = 0, topeDelContainer = pila[i].tope;
                    // Se pasan los containers que estan encima del que se quiere eliminar a la pila auxiliar.
                    while (topeDelContainer > posicionActualContainer + 1)
                    {
                        containerAux[topeAux].id = pila[i].container[topeDelContainer].id;
                        strcpy(containerAux[topeAux].empresa, pila[i].container[topeDelContainer].empresa);
                        topeAux++;
                        topeDelContainer--;
                        if (topeDelContainer == posicionActualContainer + 1)
                        {
                            isFounded = true;
                            pila[i].tope = topeDelContainer;
                            int j;
                            for (j = topeAux; j > 0; j--)
                            {
                                pila[i].container[topeDelContainer].id = containerAux[j - 1].id;
                                strcpy(pila[i].container[topeDelContainer].empresa, containerAux[j - 1].empresa);
                                topeDelContainer++;
                            }
                            pila[i].tope = topeDelContainer - 1;
                        }
                        if (isFounded == true)
                            break;
                    }
                    clean();
                    printf("Pila auxiliar: \n");
                    for (int k = topeAux - 1; k >= 0; k--)
                    {
                        printf("ID [%d] : Empresa: %s\n", containerAux[k].id, containerAux[k].empresa);
                    }
                    pause();
                }
            }
            posicionActualContainer++;
        }
        posicionActualContainer = -1;
    }
    if (bandera == 0)
    {
        printf("El id ingresado no existe \n");
        pause();
    }
}
void mostrarContainers(PILA pila[])
{
    int matriz[14][13];
    int cantidadContainers = -1;

    for (int l = 0; l < 14; l++)
    {
        for (int h = 0; h < 13; h++)
        {
            matriz[l][h] = 0;
        }
    }

    for (int i = 0; i < 14; i++)
    {
        for (int j = 0; j < 13; j++)
        {
            if (i == 13 && j == 0) // 1era pila de containers
            {
                int k = i;
                while (pila[0].tope != cantidadContainers)
                {
                    cantidadContainers++;
                    matriz[k][j] = pila[0].container[cantidadContainers].id;
                    k--;
                }
            }
            else if (i == 12 && j == 2) // 2da pila de containers
            {
                int k = i;
                while (pila[1].tope != cantidadContainers)
                {
                    cantidadContainers++;
                    matriz[k][j] = pila[1].container[cantidadContainers].id;
                    k--;
                }
            }
            else if (i == 11 && j == 4) // 3ra pila de containers
            {
                int k = i;
                while (pila[2].tope != cantidadContainers)
                {
                    cantidadContainers++;
                    matriz[k][j] = pila[2].container[cantidadContainers].id;
                    k--;
                }
            }
            else if (i == 11 && j == 6)
            { // 4ta pila de contenedores
                int k = i;
                while (pila[3].tope != cantidadContainers)
                {
                    cantidadContainers++;
                    matriz[k][j] = pila[3].container[cantidadContainers].id;
                    k--;
                }
            }
            else if (i == 11 && j == 8)
            { // 5ta pila de contenedores
                int k = i;
                while (pila[4].tope != cantidadContainers)
                {
                    cantidadContainers++;
                    matriz[k][j] = pila[4].container[cantidadContainers].id;
                    k--;
                }
            }
            else if (i == 12 && j == 10)
            { // 6ta pila de contenedores
                int k = i;
                while (pila[5].tope != cantidadContainers)
                {
                    cantidadContainers++;
                    matriz[k][j] = pila[5].container[cantidadContainers].id;
                    k--;
                }
            }
            else if (i == 13 && j == 12)
            { // 7ma pila de contenedores
                int k = i;
                while (pila[6].tope != cantidadContainers)
                {
                    cantidadContainers++;
                    matriz[k][j] = pila[6].container[cantidadContainers].id;
                    k--;
                }
            }
            cantidadContainers = -1;
        }
    }

    for (int q = 0; q < 14; q++)
    {
        for (int w = 0; w < 13; w++)
        {
            if (matriz[q][w] == 0)
            {
                printf("[    ]");
            }
            else
            {
                printf("[%d]", matriz[q][w]);
            }
        }
        printf("\n");
    }
}
void imprimir_infoPilas(PILA pila[])
{
    int i, contador = -1;
    for (i = 0; i < MAX_pilas; i++)
    {
        printf("\n\nPila %d de containers:\n", i + 1);
        // 0
        while (pila[i].tope != contador)
        {
            printf("ID: %d\nEmpresa: %s\n", pila[i].nodos[contador + 1].id, pila[i].nodos[contador + 1].empresa);
            contador++;
        }
        contador = -1;
    }
}
void menu()
{
    clean();
    printf("\033[0;32m");
    printf("Que deseas hacer?\n");
    printf("\033[0m");
    printf("\n1. Agregar un container a una pila en especifico");
    printf("\n2. Eliminar un container segun su ID");
    printf("\n3. Consultar el valor del tope de una pila");
    printf("\n4. Mostrar en pantalla los containers que hay actualmente");
    printf("\n5. Salir del programa \n");
    printf("\033[0;32m");
    printf(">> ");
    printf("\033[0m");
}