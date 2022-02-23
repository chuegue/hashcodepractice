#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "DynVec.h"

#define MAX_SIZE 512

typedef struct _Node
{
    char *name;
    int score;
    struct _Node *next;
} Node;

Node *InitList()
{
    return NULL;
}

Node *Comp_Update(Node *lista, char *name, int delta)
{
    Node *ptr = lista;
    int found = 0;
    while (ptr)
    {
        if (strcmp(name, ptr->name) == 0)
        {
            found = 1;
            ptr->score += delta;
            break;
        }
        ptr = ptr->next;
    }
    if (!found)
    {
        Node *new = (Node *)malloc(sizeof(Node));
        new->name = (char *)malloc((strlen(name) + 1) * sizeof(char));
        strcpy(new->name, name);
        new->score = delta;
        new->next = lista;
        lista = new;
    }
    return lista;
}

void Print_List(Node *lista)
{
    Node *ptr = lista;
    while (ptr)
    {
        printf("Name: %s\nScore: %i\n\n", ptr->name, ptr->score);
        ptr = ptr->next;
    }
}

void Free_List(Node *lista)
{
    Node *ptr = lista;
    while (lista)
    {
        ptr = lista;
        lista = lista->next;
        free(ptr->name);
        free(ptr);
    }
}

int main(int argc, char *argv[])
{
    char delim[2] = " ";
    FILE *fp = fopen(argv[1], "r");
    char line1[MAX_SIZE];
    int n_clients = atoi(fgets(line1, MAX_SIZE, fp));
    Clientes *clientes = Init_Clientes(n_clients);
    Node *Lista = InitList();

    for (int i = 0; i < n_clients; i++)
    {
        Pessoa *new = Init_Pessoa(i/*"nome" da pessoa. Nome é o index pelo qual aparecem no ficheiro*/);
        char likes[MAX_SIZE];
        char hates[MAX_SIZE];
        if (fgets(likes, MAX_SIZE, fp) && fgets(hates, MAX_SIZE, fp))
        {
            //LIKES
            int n = atoi(strtok(likes, delim));
            new = Set_N_Likes(new, n);
            for (int p = 0; p < n; p++)
            {
                char *ingredient = strtok(NULL, delim);
                if (strchr(ingredient, '\n'))
                {
                    ingredient[strlen(ingredient) - 1] = '\0';
                }
                // INGREDIENTE GOSTADO ESTA AQUI
                new = Add_Like(new, ingredient, p);
                Lista = Comp_Update(Lista, ingredient, 1);
            }
            //DISLIKES
            n = atoi(strtok(hates, delim));
            new = Set_N_Dislikes(new, n);
            for (int p = 0; p < n; p++)
            {
                char *ingredient = strtok(NULL, delim);
                if (strchr(ingredient, '\n'))
                {
                    ingredient[strlen(ingredient) - 1] = '\0';
                }
                // INGREDIENTES NAO GOSTADOS AQUI
                new = Add_Dislike(new, ingredient, p);
                Lista = Comp_Update(Lista, ingredient, -1);
            }
            clientes = Add_Cliente(clientes, new, i);
        }
        else
        {
            printf("ERRO\n");
            exit(1);
        }
    }
    Free_List(Lista);
    fclose(fp);
    return 0;
}