#include <stdio.h>
#include <stdlib.h> // system("cls")
#include <conio.h>  // getch()
#include <ctype.h>  // toupper()
#include <stdbool.h>
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
    struct node *tramits;
} person;

person persons[10];

// Funciones utilitarias
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
void moveUpMenu(int IDMenu, int height, int width, char menu[height][width], int *arrowPosition)
{
    if (IDMenu == 0)
    {
        menu[*arrowPosition][6] = ' ';
        (*arrowPosition)--;
        menu[*arrowPosition][6] = '>';
    }
    if (IDMenu == 1)
    {
        if (*arrowPosition == 9)
        {
            menu[*arrowPosition][8] = ' ';
            (*arrowPosition) -= 2;
            menu[*arrowPosition][2] = '>';
        }
        else
        {
            menu[*arrowPosition][2] = ' ';
            (*arrowPosition)--;
            menu[*arrowPosition][2] = '>';
        }
    }
    showMenu(height, width, menu);
}
void moveDownMenu(int IDMenu, int height, int width, char menu[height][width], int *arrowPosition)
{
    if (IDMenu == 0)
    {
        menu[*arrowPosition][6] = ' ';
        (*arrowPosition)++;
        menu[*arrowPosition][6] = '>';
    }
    if (IDMenu == 1)
    {
        if (*arrowPosition == 7)
        {
            menu[*arrowPosition][2] = ' ';
            (*arrowPosition) += 2;
            menu[*arrowPosition][8] = '>';
        }
        else
        {
            menu[*arrowPosition][2] = ' ';
            (*arrowPosition)++;
            menu[*arrowPosition][2] = '>';
        }
    }
    showMenu(height, width, menu);
}
//! OPTIMIZAR URGENTEMENTE ESTA FUNCION
void markX(int arrowPosition, char menu[11][34])
{
    int retiro = 3, deposito = 4, consulta = 5, actualizacion = 6, pagos = 7;
    if (arrowPosition == retiro) // 5 min
    {
        if (menu[arrowPosition][25] == 'X')
            menu[arrowPosition][25] = ' ';
        else
            menu[arrowPosition][25] = 'X';
    }
    if (arrowPosition == deposito) // 2 min
    {
        if (menu[arrowPosition][25] == 'X')
            menu[arrowPosition][25] = ' ';
        else
            menu[arrowPosition][25] = 'X';
    }
    if (arrowPosition == consulta) // 4 min
    {
        if (menu[arrowPosition][25] == 'X')
            menu[arrowPosition][25] = ' ';
        else
            menu[arrowPosition][25] = 'X';
    }
    if (arrowPosition == actualizacion) // 5 min
    {
        if (menu[arrowPosition][25] == 'X')
            menu[arrowPosition][25] = ' ';
        else
            menu[arrowPosition][25] = 'X';
    }
    if (arrowPosition == pagos) // 6 min
    {
        if (menu[arrowPosition][25] == 'X')
            menu[arrowPosition][25] = ' ';
        else
            menu[arrowPosition][25] = 'X';
    }
    showMenu(11, 34, menu);
}

// Funciones principales
int setCase()
{
    int arrowPosition = 3;
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
        if (key == 'W' && arrowPosition > 3)
            moveUpMenu(0, 7, 31, menu, &arrowPosition);
        if (key == 'S' && arrowPosition < 5)
            moveDownMenu(0, 7, 31, menu, &arrowPosition);
    } while (key != ENTER);
    if (arrowPosition == 3)
        return 1;
    if (arrowPosition == 4)
        return 2;
    if (arrowPosition == 5)
        return 3;
}
void makeTramits(int *first, int *last)
{
    system("cls");
    bool isConfirm = false;
    int arrowPosition = 3, enviar = 9;
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
    printf("Ingrese su nombre: ");
    fgets(persons[0].name, 20, stdin);
    showMenu(11, 34, menuMakeTramits);
    do
    {
        key = toupper(getch());
        if (key == 'W' && arrowPosition > 3)
            moveUpMenu(1, 11, 34, menuMakeTramits, &arrowPosition);
        if (key == 'S' && arrowPosition < 9)
            moveDownMenu(1, 11, 34, menuMakeTramits, &arrowPosition);
        if (key == ENTER)
        {
            markX(arrowPosition, menuMakeTramits);
            if (arrowPosition == enviar)
                isConfirm = true;
        }
    } while (isConfirm == false);

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