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
node *head = NULL;
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
    ////getchar();
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
               "| 2. Generar lista dinamica y mostrar su frecuencia.           |\n"
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
void getFrequency()
{
    clean();
    node *aux = head;
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

// Funciones principales
void readTextFile()
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
void createLinkedList()
{
    node *aux;
    if (strcmp(fileName, "Ningun archivo seleccionado.") == 0)
    {
        printf("Error: Se debe leer un archivo antes de ejecutar este comando.\n");
        pause();
        clean();
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
            if (character != EOF)
            {
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
    }
    // Leer los nodos creados:
    getFrequency();
}
void sortAscending()
{
    node *aux, *aux2;
    if (strcmp(fileName, "Ningun archivo seleccionado.") == 0)
    {
        printf("Error: Se debe leer un archivo antes de ejecutar este comando.\n");
        pause();
        clean();
        return;
    }
    if (head == NULL)
    {
        printf("Error: Se debe generar la lista dinamica antes de ordenarla.\n");
        pause();
        clean();
    }
    else
    {
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
        getFrequency();
    }
}
void sortDescending()
{
    node *aux, *aux2;
    if (strcmp(fileName, "Ningun archivo seleccionado.") == 0)
    {
        printf("Error: Se debe leer un archivo antes de ejecutar este comando.\n");
        pause();
        clean();
        return;
    }
    if (head == NULL)
    {
        printf("Error: Se debe generar la lista dinamica antes de ordenarla.\n");
        pause();
        clean();
    }
    else
    {
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
                if (aux->frequency < aux2->frequency)
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
        getFrequency();
    }
}
void searchCharacter()
{
    if (strcmp(fileName, "Ningun archivo seleccionado.") == 0)
    {
        printf("Se debe leer un archivo antes de ejecutar este comando.\n");
        pause();
        clean();
        return;
    }
    if (head == NULL)
    {
        printf("Error: Se debe generar una lista dinamica antes de buscar un caracter.\n");
        pause();
        clean();
    }
    else
    {
        FILE *file;
        node *aux = head; // Recorrer la lista y buscar el caracter
        char characterToSearch;
        int isFound = false;

        fflush(stdin);
        printf("Ingrese el caracter a buscar: ");
        scanf("%c", &characterToSearch);

        while (aux != NULL)
        {
            if (characterToSearch == aux->character)
            {
                printf("*-----------------------*\n"
                       "| Caracter | Frecuencia |\n"
                       "*-----------------------*\n"
                       "|    %c     |     %2d     |\n"
                       "*-----------------------*\n",
                       aux->character, aux->frequency);
                pause();
                clean();
                isFound = true;
                break;
            }
            aux = aux->next;
        }
        if (isFound == false)
        {
            printf("Error: El caracter ingresado no se encuentra en la lista.\n");
            pause();
            clean();
        }
    }
}
int main()
{
    int option;
    do
    {
        option = setOption();
        switch (option)
        {
        case 1: // Leer un conjunto de caracteres desde un archivo texto de entrada (.txt).
            clean();
            readTextFile();
            break;
        case 2: // Generar una lista dinámicamente enlazada L con los caracteres leídos, indicando para cada carácter cuantas veces se encontraba repetido el mismo en el archivo fuente original.
            clean();
            createLinkedList();
            break;
        case 3: // Ordenar la lista por frecuencia creciente.
            clean();
            sortAscending();
            break;
        case 4: //  Ordenar la lista por frecuencia decreciente.
            clean();
            sortDescending();
            break;
        case 5: // Buscar la presencia de un carácter específico (a leer) e indicar su frecuencia.
            clean();
            searchCharacter();
            break;
        case 6: // Salir.
            break;
        }
    } while (option != 6);

    return 0;
}