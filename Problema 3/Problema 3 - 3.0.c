#include <stdio.h>
#include <stdlib.h>
#define true 1
#define false 0
#define queueSize 10

typedef struct node
{
    char name[15];
    int time;
    struct node *next;
} node;
typedef struct
{
    char name[20];
    int tramit[5];
    node *pointer;
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
void showMessageError(int errorCodeID)
{
    clean();
    if (errorCodeID == 1)
        printf("Error: La opcion ingresada no es valida.\n");
    if (errorCodeID == 2)
        printf("Error: La cola está llena.\n");
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
void withdraw()
{

}
int main()
{
    int option, qFront = 0, qRear = 0;
    do
    {
        option = getMenuOption();
        switch (option)
        {
        case 1: // Añadir persona a la cola:
            if (checkIfQueueIsFull(qRear) == true)
                showMessageError(2);
            else
            {
                int tramit;
                printf("Ingrese su nombre: ");
                scanf("%s", queue[qFront].name);
                do
                {
                    tramit = selectTramit();
                    switch (tramit)
                    {
                    case 1: // Retiro = 5 min
                        withdraw();
                    case 2: // Deposito = 2 min
                    case 3: // Consulta = 4 min
                    case 4: // Actualizacion = 5 min
                    case 5: // Pagos = 6 min
                    case 6: // Finalizar tramites
                    }
                } while (tramit != 6);
            }
        case 2:
        case 3:
        }
    } while (option != 3);
    return 0;
}