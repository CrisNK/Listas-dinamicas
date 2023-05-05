#include <stdio.h>
#include <stdlib.h> // system("cls")
#include <conio.h> // getch()
#include <ctype.h> // toupper()
#define true 1, false 0
#define retiro 5, deposito 2, consulta 4, actualizacion 5, pagos 6
#define ENTER 13

typedef struct node
{
    int tramit;
    struct node *next;
} node;

typedef struct person
{
    char name[20];
    int waitingTime;
    struct node tramits;
} person;

person persons[10];

void showMenu(int height, int width, char menu[height][width])
{
    system("cls");
    int i, j;
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
            printf("%c", menu[i][j]);
        printf("\n");
    }
}
void moveUpMenu(int codeMenu, int height, int width, char menu[height][width], int *arrow)
{
    if (codeMenu == 0)
    {
        menu[*arrow][6] = ' ';
        (*arrow)--;
        menu[*arrow][6] = '>';
    }
    if (codeMenu == 1)
    {
        if (*arrow == 9)
        {
            menu[*arrow][8] = ' ';
            (*arrow)-= 2;
            menu[*arrow][2] = '>';
        }
        else
        {
            menu[*arrow][2] = ' ';
            (*arrow)--;
            menu[*arrow][2] = '>';
        }
    }
    showMenu(height, width, menu);
}
void moveDownMenu(int codeMenu, int height, int width, char menu[height][width], int *arrow)
{
    if (codeMenu == 0)
    {
        menu[*arrow][6] = ' ';
        (*arrow)++;
        menu[*arrow][6] = '>';
    }
    if (codeMenu == 1)
    {
        if (*arrow == 7)
        {
            menu[*arrow][2] = ' ';
            (*arrow)+= 2;
            menu[*arrow][8] = '>';
        }
        else
        {
            menu[*arrow][2] = ' ';
            (*arrow)++;
            menu[*arrow][2] = '>';
        }
    }
    showMenu(height, width, menu);
}

// Funciones principales
int setCase()
{
    int arrow = 3;
    char key;
    char menu[7][31] = {"*-----------------------------*",
                        "|        Menu principal       |",
                        "*-----------------------------|",
                        "|     > Realizar tramite      |",
                        "|       Cancelar turno        |",
                        "|       Salir                 |",
                        "*-----------------------------*"};
    showMenu(7, 31, menu);
    do
    {
        key = toupper(getch());
        fflush(stdin);
        if (key == 'W' && arrow > 3)
            moveUpMenu(0, 7, 31, menu, &arrow);
        if (key == 'S' && arrow < 5)
            moveDownMenu(0, 7, 31, menu, &arrow);
    } while (key != ENTER);
    if (arrow == 3)
        return 1;
    if (arrow == 4)
        return 2;
    if (arrow == 5)
        return 3;
}
void makeTramits(int *first, int *last)
{
    int arrow = 3;
    char key;
    char menuMakeTramits[11][34] = {"*--------------------------------*",
                                    "|     Tramite     | Seleccionado |",
                                    "*--------------------------------|",
                                    "| > Retiro        |              |",
                                    "|   Deposito      |              |",
                                    "|   Consulta      |              |",
                                    "|   Actualizacion |              |",
                                    "|   Pagos         |              |",
                                    "*--------------------------------*",
                                    "|         Enviar tramites        |",
                                    "*--------------------------------*"};
    system("cls");
    if (*first == NULL)
    {
        printf("Ingrese su nombre: ");
        fflush(stdin);
        fgets(persons[0].name, 20, stdin);
        fflush(stdin);
        showMenu(11, 34, menuMakeTramits);
        do
        {
            key = toupper(getch());
            if (key == 'W' && arrow > 3)
                moveUpMenu(1, 11, 34, menuMakeTramits, &arrow);
            if (key == 'S' && arrow < 9)
                moveDownMenu(1, 11, 34, menuMakeTramits, &arrow);
        } while (key != ENTER);
    }
    
}

int main()
{
    int first = NULL, last = NULL;
    while (1)
    {
        switch (setCase())
        {
        case 1:
            makeTramits(&first, &last);
            break;
        case 2:
            break;
        case 3:
            return 0;
        }
    }
}