#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define MAX_containers 12
#define MAX_pilas 7
#define true 1
#define false 0

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

// Estrucutra que guarda los valores que tengo en cada container
typedef struct nodo
{
    int id;
    char empresa[100];
} CONTAINER;

// Estructura que almacena cuantos containers maximo puedo guardar en cada pila
typedef struct pila
{
    CONTAINER nodos[MAX_containers];
    int tope;
} PILA;

// Protipos de funciones
void agregar_nodo(PILA pila[]);
void eliminar_container(PILA pila[]);
void imprimir_infoPilas(PILA pila[]);
void mostrar_matriz(PILA pila[]);
void menu();

int main()
{
    srand(time(NULL));
    PILA pila[MAX_pilas];
    for (int i = 0; i < MAX_pilas; i++)
    {
        pila[i].tope = -1; // inicializar el ejerccio full vacio
    }

    int opcion;
    do
    {
        menu();
        scanf("%d", &opcion);
        switch (opcion)
        {
        case 1:
            // Agregar containers
            clean();
            agregar_nodo(pila);
            imprimir_infoPilas(pila);
            fflush(stdin);
            getchar();
            break;
        case 2:
            // Eliminar continers
            eliminar_container(pila);
            break;
        case 3:
            // PEEK de la pila que el usuario escoja
            break;
        case 4:
            // Imprimir pilas de containers
            mostrar_matriz(pila);
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

void agregar_nodo(PILA pila[])
{
    // Comprobar de que las pilas estén libres para ingresar un nuevo container.
    mostrar_matriz(pila);
    int i, isFull[MAX_pilas];
    for (i = 0; i < MAX_pilas; i++)
    {
        if (pila[i].tope == (MAX_containers - 1))
            isFull[i] = true;
        else
            isFull[i] = false;
    }

    // Agrega el container.
    int posicionPila;
    char empresa[100];
    printf("A que pila deseas ingresarle un container? ");
    scanf("%d", &posicionPila);
    posicionPila--;

    if (pila[posicionPila].tope == 6) //? El 6 deberia ser 'MAX_containers'
    {
        while (pila[posicionPila].tope == 6)
        {
            printf("Pila de containers llena, ingrese otra posicion: ");
            scanf("%d", &posicionPila);
            posicionPila--;
        }
    }
    printf("Ingresa el nombre de la empresa propietaria del container: ");
    scanf("%s", empresa);
    pila[posicionPila].tope++;
    pila[posicionPila].nodos[pila[posicionPila].tope].id = 1000 + rand() % 8999;
    strcpy(pila[posicionPila].nodos[pila[posicionPila].tope].empresa, empresa);
}

void eliminar_container(PILA pila[])
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
            if (pila[i].nodos[posicionActualContainer + 1].id == id)
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
                        containerAux[topeAux].id = pila[i].nodos[topeDelContainer].id;
                        strcpy(containerAux[topeAux].empresa, pila[i].nodos[topeDelContainer].empresa);
                        topeAux++;
                        topeDelContainer--;
                        if (topeDelContainer == posicionActualContainer + 1)
                        {
                            isFounded = true;
                            pila[i].tope = topeDelContainer;
                            int j;
                            for (j = topeAux; j > 0; j--)
                            {
                                pila[i].nodos[topeDelContainer].id = containerAux[j - 1].id;
                                strcpy(pila[i].nodos[topeDelContainer].empresa, containerAux[j - 1].empresa);
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

void mostrar_matriz(PILA pila[])
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
                    matriz[k][j] = pila[0].nodos[cantidadContainers].id;
                    k--;
                }
            }
            else if (i == 12 && j == 2) // 2da pila de containers
            {
                int k = i;
                while (pila[1].tope != cantidadContainers)
                {
                    cantidadContainers++;
                    matriz[k][j] = pila[1].nodos[cantidadContainers].id;
                    k--;
                }
            }
            else if (i == 11 && j == 4) // 3ra pila de containers
            {
                int k = i;
                while (pila[2].tope != cantidadContainers)
                {
                    cantidadContainers++;
                    matriz[k][j] = pila[2].nodos[cantidadContainers].id;
                    k--;
                }
            }
            else if (i == 11 && j == 6)
            { // 4ta pila de contenedores
                int k = i;
                while (pila[3].tope != cantidadContainers)
                {
                    cantidadContainers++;
                    matriz[k][j] = pila[3].nodos[cantidadContainers].id;
                    k--;
                }
            }
            else if (i == 11 && j == 8)
            { // 5ta pila de contenedores
                int k = i;
                while (pila[4].tope != cantidadContainers)
                {
                    cantidadContainers++;
                    matriz[k][j] = pila[4].nodos[cantidadContainers].id;
                    k--;
                }
            }
            else if (i == 12 && j == 10)
            { // 6ta pila de contenedores
                int k = i;
                while (pila[5].tope != cantidadContainers)
                {
                    cantidadContainers++;
                    matriz[k][j] = pila[5].nodos[cantidadContainers].id;
                    k--;
                }
            }
            else if (i == 13 && j == 12)
            { // 7ma pila de contenedores
                int k = i;
                while (pila[6].tope != cantidadContainers)
                {
                    cantidadContainers++;
                    matriz[k][j] = pila[6].nodos[cantidadContainers].id;
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