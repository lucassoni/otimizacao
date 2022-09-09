#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct ator
{
    int custo;
    int grupos;
    int *idGrupos;
    int escolhido;
} ator;

typedef struct valor
{
    int custo;
    int *atores;
} valor;

extern int l, m, n;

int calculaCusto(ator *atores);

int quantGrupos(ator *atores);

int quantEscolhidos(ator *atores);

void inicializaMelhor();

ator *leAtores();

void printaAtores(ator *atores);

bool factivel(int i, ator *atores);

void Soluciona(int i, ator *atores);
