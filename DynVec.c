#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "DynVec.h"

Clientes *Init_Clientes(int n_clientes)
{
    Clientes *new = (Clientes *)malloc(sizeof(Clientes));
    new->n_clientes = n_clientes;
    new->clientes = (Pessoa *)malloc(n_clientes * sizeof(Pessoa));
    return new;
}

Clientes *Add_Cliente(Clientes *clientes, Pessoa *cliente, int index)
{
    clientes->clientes[index] = *cliente;
    free(cliente);
    return clientes;
}

void Free_Clientes(Clientes *clientes)
{
    for (int i = 0; i < clientes->n_clientes; i++)
    {
        for (int j = 0; j < clientes->clientes[i].n_likes; j++)
        {
            free(clientes->clientes[i].likes[j]);
            
        }
        free(clientes->clientes[i].likes);
        for (int j = 0; j < clientes->clientes[i].n_dislikes; j++)
        {
            free(clientes->clientes[i].dislikes[j]);
            
        }
        free(clientes->clientes[i].dislikes);
    }
    free(clientes->clientes);
    free(clientes);
    
}

Pessoa *Init_Pessoa(int nome)
{
    Pessoa *new = (Pessoa *)malloc(sizeof(Pessoa));
    new->nome = nome;
    return new;
}

Pessoa *Set_N_Likes(Pessoa *pessoa, int likes)
{
    pessoa->n_likes = likes;
    pessoa->likes = (char **)malloc(likes * sizeof(char *));
    return pessoa;
}

Pessoa *Set_N_Dislikes(Pessoa *pessoa, int dislikes)
{
    pessoa->n_dislikes = dislikes;
    pessoa->dislikes = (char **)malloc(dislikes * sizeof(char *));
    return pessoa;
}

Pessoa *Add_Like(Pessoa *pessoa, const char *ingrediente, int index)
{
    pessoa->likes[index] = (char *)malloc((strlen(ingrediente) + 1) * sizeof(char));
    strcpy(pessoa->likes[index], ingrediente);
    return pessoa;
}

Pessoa *Add_Dislike(Pessoa *pessoa, const char *ingrediente, int index)
{
    pessoa->dislikes[index] = (char *)malloc((strlen(ingrediente) + 1) * sizeof(char));
    strcpy(pessoa->dislikes[index], ingrediente);
    return pessoa;
}
