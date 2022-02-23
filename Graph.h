#ifndef GRAPH
#define GRAPH

typedef struct _Edge
{
    int v;
    int flow;
    int capacity;
    struct _Edge *next;
} Edge;

typedef struct
{
    Edge **u;
} Graph;

Graph *Init_Graph(int);
Graph *Add_Edge(Graph *, int, int, int);
void Free_Graph(Graph *, int);
#endif