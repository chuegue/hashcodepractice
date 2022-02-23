#ifndef DYNVEC
#define DYNVEC

typedef struct
{
    int nome;
    int n_likes;
    int n_dislikes;
    char **likes;
    char **dislikes;
} Pessoa;

typedef struct
{
    Pessoa *clientes;
    int n_clientes;
} Clientes;

Clientes *Init_Clientes(int);
Clientes *Add_Cliente(Clientes *, Pessoa *, int);
void Free_Clientes(Clientes *);
Pessoa *Init_Pessoa(int);
Pessoa *Set_N_Likes(Pessoa *, int);
Pessoa *Set_N_Dislikes(Pessoa *, int);
Pessoa *Add_Like(Pessoa *, const char *, int);
Pessoa *Add_Dislike(Pessoa *, const char *, int);

#endif