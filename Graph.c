#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"

Graph *Init_Graph(int n_vertices)
{
    Graph *new = (Graph *)malloc(sizeof(Graph));
    new->u = (Edge **)malloc(n_vertices * sizeof(Edge *));
    for (int i = 0; i < n_vertices; i++)
    {
        new->u[i] = NULL;
    }
    return new;
}

Graph *Add_Edge(Graph *G, int u, int v, int capacity)
{
    Edge *new = (Edge *)malloc(sizeof(Edge));
    new->capacity = capacity;
    new->flow = 0;
    new->v = v;
    new->next = G->u[u];
    G->u[u] = new;
    return G;
}

void Free_Graph(Graph *G, int n_vertices)
{
    for (int i = 0; i < n_vertices; i++)
    {
        Edge *ptr = G->u[i];

        while(ptr){
            Edge *next = ptr->next;
            free(ptr);
            ptr = next;
        }
    }
    free(G->u);
    free(G);
}