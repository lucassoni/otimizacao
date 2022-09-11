#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define BOUND2 true
#define BOUND1 false

typedef struct ator
{
    float custo;
    int grupos;
    int *idGrupos;
    int escolhido;
} ator;

typedef struct valor
{
    float custo;
    ator *atores;
} valor;

extern int l, m, n, quantNos;

extern bool otimilidade, viabilidade, bound;

void printaMelhor();

float calculaCusto(ator *atores);

int compare(const void *num1, const void *num2);

float Bound(int i, ator *atores);

float Bound2(int i, ator *atores);

int quantGrupos(ator *atores);

int quantEscolhidos(ator *atores);

void inicializaMelhor();

ator *leAtores();

void printaAtores(ator *atores);

bool factivel(int i, ator *atores);

void Soluciona(int i, ator *atores);
