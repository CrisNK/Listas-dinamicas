#include <stdio.h>
#include <stdlib.h>
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
void showMessageError(int errorCodeID)
{
    clean();
    if (errorCodeID == 1)
        printf("Error: La opcion ingresada no es valida.\n");
    if (errorCodeID == 2)
        printf("Error: La cola esta llena.\n");
    if (errorCodeID == 3)
        printf("Error: La cola esta vacia.\n")
            pause();
    clean();
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
               "| 2. Cancelar turno        |\n"
               "| 3. Salir                 |\n"
               "*--------------------------*\n"
               " Seleccione una opcion: ");
        scanf("%d", &option);
        if (option < 1 || option > 3)
            showMessageError(1);
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
            showMessageError(1);
    } while (option < 1 || option > 6);
    return option;
}
void makeTramit(node **head, int qRear, int tramitTime)
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
    } while (i < qRear);
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
                showMessageError(2);
            else
            {
                node *tramits = NULL;
                int tramit;
                printf("Ingrese su nombre: ");
                scanf("%s", queue[qRear].name);
                do
                {
                    clean();
                    tramit = selectTramit();
                    switch (tramit)
                    {
                    case 1: // Retiro        = 5 min
                        makeTramit(&tramits, qRear, 5);
                        break;
                    case 2: // Deposito      = 2 min
                        makeTramit(&tramits, qRear, 2);
                        break;
                    case 3: // Consulta      = 4 min
                        makeTramit(&tramits, qRear, 4);
                        break;
                    case 4: // Actualizacion = 5 min
                        makeTramit(&tramits, qRear, 5);
                        break;
                    case 5: // Pagos         = 6 min
                        makeTramit(&tramits, qRear, 6);
                        break;
                    case 6: // Finalizar tramites
                        break;
                    }
                } while (tramit != 6);

                queue[qRear].tramits = tramits;
                qRear++;

                clean();
                if (qRear == 1)
                    printf("Sus tramites tienen un tiempo estimado de %d minutos.\n", waitingTime(qRear));
                else
                    printf("Su tiempo de espera es: %d minutos.\n", waitingTime(qRear));
            }
        }
        if (option == removeClient)
        {

        }
    } while (option != 3);
    return 0;
}