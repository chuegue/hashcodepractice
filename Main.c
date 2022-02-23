#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "DynVec.h"
#include "Graph.h"

#define MAX_SIZE 512

typedef struct _Node
{
    char *name;
    struct _Node *next;
} Node;

int n_ingredientes = 0;

Node *InitList()
{
    return NULL;
}

Node *Comp_Update(Node *lista, char *name)
{
    Node *ptr = lista;
    int found = 0;
    while (ptr)
    {
        if (strcmp(name, ptr->name) == 0)
        {
            found = 1;
            break;
        }
        ptr = ptr->next;
    }
    if (!found)
    {
        n_ingredientes++;
        Node *new = (Node *)malloc(sizeof(Node));
        new->name = (char *)malloc((strlen(name) + 1) * sizeof(char));
        strcpy(new->name, name);
        new->next = lista;
        lista = new;
    }
    return lista;
}

int Element_Index(Node *lista, const char *ingredient)
{
    int i = 0;
    Node *ptr = lista;
    while (ptr)
    {
        if (strcmp(ptr->name, ingredient) == 0)
            return i;
        i++;
        ptr = ptr->next;
    }
}

void Print_List(Node *lista)
{
    Node *ptr = lista;
    while (ptr)
    {
        printf("Name: %s\n\n", ptr->name);
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
        Pessoa *new = Init_Pessoa(i /*"nome" da pessoa. Nome é o index pelo qual aparecem no ficheiro*/);
        char likes[MAX_SIZE];
        char hates[MAX_SIZE];
        if (fgets(likes, MAX_SIZE, fp) && fgets(hates, MAX_SIZE, fp))
        {
            // LIKES
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
                Lista = Comp_Update(Lista, ingredient);
            }
            // DISLIKES
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
                Lista = Comp_Update(Lista, ingredient);
            }
            clientes = Add_Cliente(clientes, new, i);
        }
        else
        {
            printf("ERRO\n");
            exit(1);
        }
    }
    Graph *G = Init_Graph(n_clients + n_ingredientes + 2);

    for (int i = 0; i < n_clients; i++)
    {
        G = Add_Edge(G, 0, i + 1, n_ingredientes);
    }

    for (int i = 0; i < clientes->n_clientes; i++)
    {
        for (int l = 0; l < clientes->clientes[i].n_likes; l++)
        {
            G = Add_Edge(G, i + 1, 1 + clientes->n_clientes + Element_Index(Lista, clientes->clientes[i].likes[l]), 1);
        }
        for (int d = 0; d < clientes->clientes[i].n_dislikes; d++)
        {
            G = Add_Edge(G, 1 + clientes->n_clientes + Element_Index(Lista, clientes->clientes[i].dislikes[d]), i + 1, 1);
        }
    }

    for (int i = 1 + clientes->n_clientes; i < clientes->n_clientes + n_ingredientes + 1; i++)
    {
        G = Add_Edge(G, i, clientes->n_clientes + n_ingredientes + 1, 1);
    }
    Print_List(Lista);
    for (int i = 0; i < clientes->n_clientes + n_ingredientes + 2; i++)
    {
        Edge *ptr = G->u[i];
        while(ptr){
            printf("%d -> %d\t", i,ptr->v);
            ptr = ptr->next;
        }
        printf("\n");
    }
    Free_Graph(G, n_clients + n_ingredientes + 2);
    Free_Clientes(clientes);
    Free_List(Lista);
    fclose(fp);
    return 0;
}