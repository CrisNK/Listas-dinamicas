#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define true 1
#define false 0
#define queueSize 10

typedef struct node
{
    int time;
    struct node *next;
} node;
typedef struct
{
    char name[20];
    int waitingTime;
    node *tramits;
} person;

person queue[queueSize];

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

// Funciones secundarias:
int checkIfQueueIsFull(int qRear)
{
    return (qRear + 1) == queueSize ? true : false;
}
int checkIfQueueIsEmpty(int qRear)
{
    return qRear == 0 ? true : false;
}
void displayMessageError(int errorCodeID)
{
    clean();
    if (errorCodeID == 1)
        printf("Error: La opcion ingresada no es valida.\n");
    if (errorCodeID == 2)
        printf("Error: La cola esta llena.\n");
    if (errorCodeID == 3)
        printf("Error: La cola esta vacia.\n");
    if (errorCodeID == 4)
        printf("Error: No se ha seleccionado ningun tramite.\n");
    pause();
    clean();
}
int userWaitingTime(node *head)
{
    node *aux = head;
    int time = 0;
    while (aux != NULL)
    {
        time += aux->time;
        aux = aux->next;
    }
    return time;
}

// Funciones principales:
int getMenuOption()
{
    int option;
    do
    {
        printf("*--------------------------*\n"
               "|      Menu principal      |\n"
               "*--------------------------|\n"
               "| 1. Realizar tramite      |\n"
               "| 2. Abandonar cola        |\n"
               "| 3. Salir                 |\n"
               "*--------------------------*\n"
               " Seleccione una opcion: ");
        scanf("%d", &option);
        if (option < 1 || option > 3)
            displayMessageError(1);
    } while (option < 1 || option > 3);
    clean();
    return option;
}
int selectTramit()
{
    int option;
    do
    {
        printf("*-----------------------*\n"
               "|        Tramites       |\n"
               "*-----------------------*\n"
               "| 1. Retiro             |\n" // 5 min
               "| 2. Deposito           |\n" // 2 min
               "| 3. Consulta           |\n" // 4 min
               "| 4. Actualizacion      |\n" // 5 min
               "| 5. Pagos              |\n" // 6 min
               "| 6. Finalizar tramites |\n"
               "*-----------------------*\n"
               " Seleccione una opcion: ");
        scanf("%d", &option);
        if (option < 1 || option > 6)
            displayMessageError(1);
    } while (option < 1 || option > 6);
    return option;
}
void makeTramit(node **head, int tramitTime)
{
    if (*head == NULL)
    {
        node *new = (node *)malloc(sizeof(node));
        new->time = tramitTime;
        new->next = NULL;
        *head = new;
    }
    else
    {
        node *aux = *head;
        while (aux->next != NULL)
            aux = aux->next;
        node *new = (node *)malloc(sizeof(node));
        new->time = tramitTime;
        new->next = NULL;
        aux->next = new;
    }
}
int waitingTime(int qRear)
{
    int i = 0, suma = 0;
    node *aux;
    do
    {
        aux = queue[i].tramits;
        while (aux != NULL)
        {
            suma += aux->time;
            aux = aux->next;
        }
        i++;
    } while (i < (qRear - 1));
    return suma;
}

int main()
{
    int option, qFront = 0, qRear = 0, addClient = 1, removeClient = 2;
    do
    {
        option = getMenuOption();
        if (option == addClient)
        {
            if (checkIfQueueIsFull(qRear) == true)
                displayMessageError(2);
            else
            {
                node *tramits = NULL;
                int tramit, customerPerformedTramit = false;
                printf("Ingrese su nombre: ");
                scanf("%s", queue[qRear].name);
                do
                {
                    clean();
                    tramit = selectTramit();
                    switch (tramit)
                    {
                    case 1: // Retiro        = 5 min
                        makeTramit(&tramits, 5);
                        customerPerformedTramit = true;
                        break;
                    case 2: // Deposito      = 2 min
                        makeTramit(&tramits, 2);
                        customerPerformedTramit = true;
                        break;
                    case 3: // Consulta      = 4 min
                        makeTramit(&tramits, 4);
                        customerPerformedTramit = true;
                        break;
                    case 4: // Actualizacion = 5 min
                        makeTramit(&tramits, 5);
                        customerPerformedTramit = true;
                        break;
                    case 5: // Pagos         = 6 min
                        makeTramit(&tramits, 6);
                        customerPerformedTramit = true;
                        break;
                    case 6: // Finalizar tramites
                        if (customerPerformedTramit == false)
                            displayMessageError(4);
                        break;
                    }
                } while (tramit != 6 || customerPerformedTramit == false);

                queue[qRear].tramits = tramits;
                queue[qRear].waitingTime = userWaitingTime(tramits);
                qRear++;

                clean();
                if (qRear == 1)
                    printf("Sus tramites tienen un tiempo estimado de %d minutos.\n", waitingTime(qRear));
                else
                    printf("Su tiempo de espera es de: %d minutos.\n", waitingTime(qRear));
            }
        }
        if (option == removeClient)
        {
            if (checkIfQueueIsEmpty(qRear) == true)
                displayMessageError(3);
            else
            {
                if (qRear == 1)
                {
                    printf("Se acaba de atender al ultimo cliente de la cola.\n");
                    qRear = 0;
                }
                else
                {
                    int i, j = 0, auxTime = queue[qFront].waitingTime;
                    char auxName[20];
                    strcpy(auxName, queue[qFront].name);
                    for (i = 0; i < (qRear - 1); i++)
                    {
                        j++;
                        strcpy(queue[i].name, queue[j].name);
                        queue[i].tramits = queue[j].tramits;
                    }
                    qRear--;
                    printf("Cliente %s ha sido atendido exitosamente.\n"
                           "Se informa a nuestros usuarios que su tiempo\n"
                           "de espera se reduce en %d minutos.\n",
                           auxName, auxTime);
                }
            }
        }
    } while (option != 3);
    return 0;
}