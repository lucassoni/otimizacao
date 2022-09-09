#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "bblib.h"
#include <stdbool.h>

valor melhor;
int l, m, n;

// L = Quantidade de Grupos Sociais
// M = Atores
// N = Personagens

// retorna o custo dos atores escolhidos
int calculaCusto(ator *atores)
{
    int custo = 0;
    for (int i = 0; i < m; i++)
    {
        if (atores[i].escolhido == 1)
        {
            custo += atores[i].custo;
        }
    }
}

int calculaCustoRestantes(ator *atores)
{
    int custo = 0;
    for (int i = 0; i < m; i++)
    {
        if (atores[i].escolhido == 0)
        {
            custo += atores[i].custo;
        }
    }
}

int limitante(ator *atores)
{
    int custo1, custo2, custores;
    custo1 = calculaCusto(atores);
    custo2 = calculaCustoRestantes(atores);
    custores = custo1 + custo2 * x;
}

// retorna a quantidade de grupos distintos entre os atores escolhidos
int quantGrupos(ator *atores)
{
    int *grupos = calloc(l, sizeof(int));
    int quantGrupos = 0;
    for (int i = 0; i < m; i++)
    {
        if (atores[i].escolhido == 1)
        {
            for (int j = 0; j < atores[i].grupos; j++)
            {
                if (grupos[atores[i].idGrupos[j]] == 0)
                {
                    quantGrupos++;
                    grupos[atores[i].idGrupos[j]] = 1;
                }
            }
        }
    }

    return quantGrupos;
}

// retorna a quantidade de atores escolhidos
int quantEscolhidos(ator *atores)
{
    int escolhidos = 0;
    for (int i = 0; i < m; i++)
    {
        if (atores[i].escolhido == 1)
        {
            escolhidos++;
        }
    }
    return escolhidos;
}

// funcao para inicializar a variavel melhor
void inicializaMelhor()
{
    melhor.custo = INFINITY;
    melhor.atores = malloc(sizeof(int) * m);
    for (int i = 0; i < m; i++)
    {
        melhor.atores[i] = 1;
    }
}

ator *leAtores()
{
    ator *atores = malloc(sizeof(ator) * m);
    int *grupos = calloc(l, sizeof(int));
    int quantGrupos = 0;
    for (int i = 0; i < m; i++)
    {
        scanf("%d %d", &atores[i].custo, &atores[i].grupos);
        atores[i].idGrupos = malloc(sizeof(int) * atores[i].grupos);
        for (int j = 0; j < atores[i].grupos; j++)
        {
            scanf("%d", &atores[i].idGrupos[j]);
            if (grupos[atores[i].idGrupos[j]] == 0)
            {
                quantGrupos++;
                grupos[atores[i].idGrupos[j]] = 1;
            }
        }
        atores[i].escolhido = 1;
    }

    if (quantGrupos < l)
    {
        printf("Inviavel\n");
        exit(0);
    }

    free(grupos);

    return atores;
}

void printaAtores(ator *atores)
{
    for (int i = 0; i < m; i++)
    {
        printf("ator %d\n", i);
        printf("custo: %d grupos: %d\n", atores[i].custo, atores[i].grupos);
        for (int j = 0; j < atores[i].grupos; j++)
        {
            printf("grupo: %d\n", atores[i].idGrupos[j]);
        }
        printf("\n");
    }
}

bool factivel(int i, ator *atores)
{
    if (quantGrupos(atores) < l)
        return false;

    if (quantEscolhidos(atores) < n)
        return false;

    return true;
}

void Soluciona(int i, ator *atores)
{
    if (i > 3)
        return;
    if (factivel(i, atores))
    {
        return;
    }

    if (m == n)
    {
    }

    // ramifica para esquerda
    atores[i].escolhido = 0;
    Soluciona(i + 1, atores);

    // ramifica para direita
    atores[i].escolhido = 1;
    Soluciona(i + 1, atores);
}