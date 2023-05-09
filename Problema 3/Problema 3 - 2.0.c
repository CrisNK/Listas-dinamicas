#include <stdio.h>
#include <stdlib.h>
#define true 1, false 0
#define sizeQueue 10

typedef struct node
{
    int time;
    struct node *next;
} node;
typedef struct person
{
    char nombre[20];
    int waitingTime;
    struct node *tramites;
} person;

node *head = NULL;
person queue[sizeQueue];
int first = NULL, last = NULL, peopleInTheQueue = 0;

// Funciones utilitarias:
void clean()
{
    // Support for MacOS.
    //// system("clear");
    // Support for Windows.
    system("cls");
}
void pause()
{
    // Support for MacOS.
    //// fflush(stdin);
    //// getchar();
    // Support for Windows.
    system("pause");
}

// Impresion de errores:
void errorMessageFullQueue()
{
    printf("Error: La cola está llena.\n");
    clean();
    pause();
}

// Funciones principales del programa:
int getCase()
{
    int option;

    do
    {
        printf("*--------------------------*\n"
               "|      Menu principal      |\n"
               "*--------------------------|\n"
               "| 1. Realizar tramite      |\n"
               "| 2. Cancelar turno        |\n"
               "| 3. Salir                 |\n"
               "*--------------------------*\n"
               " Seleccione una opcion: ");
        scanf("%d", &option);
        if (option < 1 || option > 3)
        {
            clean();
            printf("Error: La opcion ingresada no es valida.\n");
        }
    } while (option < 1 || option > 3);
    clean();
    return option;
}
void requestTramits()
{
    char option;
    do
    {
        printf("Desea realizar un retiro (S/N):");
        scanf("%c", &option);
    } while (option != 'S' || option != 'N');
    if (option == 'S')
    {
        if (head == NULL)
        {
            node *new = (node *)malloc(sizeof(node));
            new->time = 5;
            new->next = NULL;
            head = new;
            queue[peopleInTheQueue].tramites = head;
        }
    }
}

int main()
{
    while (1)
    {
        switch (getCase())
        {
        case 1: // Agregar persona a la cola
            if (peopleInTheQueue == sizeQueue)
                errorMessageFullQueue();
            else
            {
                printf("Ingrese su nombre: ");
                scanf("%s", queue[peopleInTheQueue].nombre);
                requestTramits();
                pause();
            }
            break;
        case 2:
            break;
        case 3:
            return 0;
        }
    }
}