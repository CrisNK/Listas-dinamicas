#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define true 1
#define false 0

typedef struct node
{
    char character;
    int frequency;
    struct node *next;
} node;

// Variable global
char fileName[30] = "Ningun archivo seleccionado.";

// Funciones Windows/MacOS
void clean()
{
    // Support for MacOS.
    ////system("clear");
    // Support for Windows.
    system("cls");
}
void pause()
{
    // Support for MacOS.
    ////fflush(stdin);
    ////getch();
    // Support for Windows.
    system("pause");
}

// Funciones utilitarias
int setOption()
{
    int option;
    do
    {
        clean();
        printf(" Fichero actual: %s\n"
               "*--------------------------------------------------------------*\n"
               "|                       Menu Principal                         |\n"
               "*--------------------------------------------------------------*\n"
               "| 1. Leer archivo de texto.                                    |\n"
               "| 2. Calcular frecuencia de caracteres en un archivo de texto. |\n"
               "| 3. Ordenar lista por frecuencia (ascendente).                |\n"
               "| 4. Ordenar lista por frecuencia (descendente).               |\n"
               "| 5. Buscar caracter.                                          |\n"
               "| 6. Salir.                                                    |\n"
               "*--------------------------------------------------------------*\n"
               " Seleccione una opcion: ",
               fileName);
        scanf("%d", &option);
        if (option < 1 || option > 6)
        {
            clean();
            printf("Error: La opcion ingresada no es valida.\n");
            pause();
        }
    } while (option < 1 || option > 6);
    return option;
}

// Funciones principales
void readTextFile(node *head)
{
    FILE *file;
    char character;
    int isFirstCharacterEOF;
    do
    {
        clean();
        printf("Ingrese el nombre del archivo: ");
        scanf("%s", fileName);
        file = fopen(fileName, "r");

        // Si el archivo no existe:
        if (file == NULL)
        {
            printf("Error: No se ha encontrado el archivo ingresado.\n");
            pause();
            clean();
        }
        else
        {
            isFirstCharacterEOF = true;
            do
            {
                character = fgetc(file);
                if (character == EOF && isFirstCharacterEOF == true)
                {
                    printf("Error: No se han encontrado caracteres en el archivo ingresado.\n");
                    break;
                }
                printf("%c", character);
                isFirstCharacterEOF = false;
            } while (character != EOF);
            printf("\n");
            pause();
        }
        fclose(file);
    } while (file == NULL || isFirstCharacterEOF == true);
    head = NULL;
}
void createLinkedList(node *head)
{
    node *aux;
    if (strcmp(fileName, "Ningun archivo seleccionado.") == 0)
    {
        printf("Error: Se debe leer un archivo antes de ejecutar este comando.\n");
        pause();
        return;
    }
    if (head == NULL)
    {
        FILE *file;
        char character;
        int isFound;

        // Apertura del archivo en modo sólo lectura.
        file = fopen(fileName, "r");

        while (character != EOF)
        {
            isFound = false;
            character = fgetc(file);

            node *new = (node *)malloc(sizeof(node));
            new->character = character;
            new->frequency = 1;
            new->next = NULL;

            aux = head;
            // Cuando la lista está vacía:
            if (aux == NULL)
                head = new;
            else
            {
                // Cuando el caracter ya se encuentra en la lista:
                while (aux != NULL)
                {
                    if (aux->character == character)
                    {
                        aux->frequency++;
                        isFound = true;
                    }
                    aux = aux->next;
                }
                // Cuando el caracter no se encuentra en la lista:
                if (isFound == false)
                {
                    aux = head;
                    while (aux->next != NULL)
                        aux = aux->next;
                    aux->next = new;
                }
            }
        }
    }
    // Leer los nodos creados:
    clean();
    aux = head;
    printf("*-----------------------*\n"
           "| Caracter | Frecuencia |\n"
           "*-----------------------*\n");
    while (aux != NULL)
    {
        printf("|    %c     |     %2d     |\n"
               "*-----------------------*\n",
               aux->character, aux->frequency);
        aux = aux->next;
    }
    pause();
}
void sortAscending(node *head)
{
    node *aux, *aux2;
    if (strcmp(fileName, "Ningun archivo seleccionado.") == 0)
    {
        printf("Error: Se debe leer un archivo antes de ejecutar este comando.\n");
        pause();
        return;
    }

    FILE *file;
    char character;

    // Apertura del archivo en modo sólo lectura.
    file = fopen(fileName, "r");
    aux = head;
    while (aux != NULL)
    {
        aux2 = aux->next;
        while (aux2 != NULL)
        {
            if (aux->frequency > aux2->frequency)
            {
                node *temp = (node *)malloc(sizeof(node));
                temp->character = aux->character;
                temp->frequency = aux->frequency;

                aux->character = aux2->character;
                aux->frequency = aux2->frequency;

                aux2->character = temp->character;
                aux2->frequency = temp->frequency;
            }
            aux2 = aux2->next;
        }
        aux = aux->next;
    }
    // Leer los nodos creados:
    clean();
    aux = head;
    printf("*-----------------------*\n"
           "| Caracter | Frecuencia |\n"
           "*-----------------------*\n");
    while (aux != NULL)
    {
        printf("|    %c     |     %2d     |\n"
               "*-----------------------*\n",
               aux->character, aux->frequency);
        aux = aux->next;
    }
    pause();
}
int main()
{
    int option;
    node *head = NULL;
    do
    {
        option = setOption();
        switch (option)
        {
        case 1: // Leer un conjunto de caracteres desde un archivo texto de entrada (.txt).
            clean();
            readTextFile(head);
            break;
        case 2:
            // Generar una lista dinámicamente enlazada L con los caracteres leídos, indicando para cada carácter cuantas veces se encontraba repetido el mismo en el archivo fuente original.
            clean();
            createLinkedList(head);
            break;
        case 3: // Ordenar la lista por frecuencia creciente.
            clean();
            sortAscending(head);
            break;
        case 4: //  Ordenar la lista por frecuencia decreciente.
            break;
        case 5: // Buscar la presencia de un carácter específico (a leer) e indicar su frecuencia.
            break;
        case 6: // Salir.
            break;
        }
    } while (option != 6);

    return 0;
}