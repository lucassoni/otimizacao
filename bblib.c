#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "bblib.h"
#include <stdbool.h>

valor melhor;
int l, m, n, quantNos;
bool otimilidade, viabilidade, bound;

// L = Quantidade de Grupos Sociais
// M = Atores
// N = Personagens

void printaMelhor(ator *atores)
{
    // if (quantEscolhidos(melhor.atores) != n || quantGrupos(melhor.atores) != l)
    // {
    //     printf("Inviavel\n");
    //     exit(0);
    // }
    for (int i = 0; i < m; i++)
    {
        if (melhor.atores[i].escolhido)
        {
            printf("%d ", i + 1);
        }
    }
    printf("\n");
    printf("%.2f\n", melhor.custo);
    // printaAtores(atores);
    // printf("--------------\n");
    // printaAtores(melhor.atores);
}
// retorna o custo dos atores escolhidos
float calculaCusto(ator *atores)
{
    int custo = 0;
    for (int i = 0; i < m; i++)
    {
        if (atores[i].escolhido == 1)
        {
            custo += atores[i].custo;
        }
    }
    return custo;
}

int compare(const void *num1, const void *num2)
{
    if (*(int *)num1 > *(int *)num2)
        return 1;
    else
        return -1;
}

// Bound proprio
float Bound(int i, ator *atores)
{
    float custo = 0;
    if (m > i)
    {
        float *atoresRestantes = malloc(sizeof(float) * (m - i));
        int k = 0;
        for (int j = i; j < m; j++)
        {
            atoresRestantes[k] = atores[j].custo;
            k++;
        }

        qsort(atoresRestantes, m - i, sizeof(float), compare);

        int quantJaEscolhidos = quantEscolhidos(atores) - (m - i);
        for (int j = 0; j < n - quantJaEscolhidos; j++)
        {
            custo += atoresRestantes[j];
        }
        free(atoresRestantes);
    }

    for (int j = 0; j < i; j++)
    {
        if (atores[j].escolhido)
            custo += atores[j].custo;
    }

    return custo;
}

// Bound professor
float Bound2(int i, ator *atores)
{
    float custo = 0;
    if (m > i)
    {

        float *atoresRestantes = malloc(sizeof(float) * (m - i));
        int k = 0;
        for (int j = i; j < m; j++)
        {
            atoresRestantes[k] = atores[j].custo;
            k++;
        }

        qsort(atoresRestantes, m - i, sizeof(float), compare);

        int quantJaEscolhidos = quantEscolhidos(atores) - (m - i);
        for (int j = 0; j < n - quantJaEscolhidos; j++)
        {
            custo += atoresRestantes[0];
        }
        free(atoresRestantes);
    }

    for (int j = 0; j < i; j++)
    {
        if (atores[j].escolhido)
            custo += atores[j].custo;
    }

    return custo;
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
    free(grupos);

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

void trocaMelhor(int custo, ator *atores)
{
    melhor.custo = custo;
    for (int i = 0; i < m; i++)
    {
        melhor.atores[i] = atores[i];
    }
}

// funcao para inicializar a variavel melhor
void inicializaMelhor()
{
    melhor.custo = INFINITY;
    melhor.atores = malloc(sizeof(ator) * m);
    for (int i = 0; i < m; i++)
    {
        melhor.atores[i].escolhido = 1;
    }
}

ator *leAtores()
{
    ator *atores = malloc(sizeof(ator) * m);
    for (int i = 0; i < m; i++)
    {
        scanf("%f %d", &atores[i].custo, &atores[i].grupos);
        atores[i].idGrupos = malloc(sizeof(int) * atores[i].grupos);
        for (int j = 0; j < atores[i].grupos; j++)
        {
            scanf("%d", &atores[i].idGrupos[j]);
        }
        atores[i].escolhido = 1;
    }

    return atores;
}

void printaAtores(ator *atores)
{
    for (int i = 0; i < m; i++)
    {
        printf("ator %d\n", i);
        printf("custo: %f grupos: %d\n", atores[i].custo, atores[i].grupos);
        for (int j = 0; j < atores[i].grupos; j++)
        {
            printf("grupo: %d\n", atores[i].idGrupos[j]);
        }
        printf("escolhido: %d\n", atores[i].escolhido);
        printf("\n");
    }
}

bool factivel(int i, ator *atores)
{
    if (m < n)
    {
        return false;
    }

    if (quantGrupos(atores) < l)
        return false;

    if (quantEscolhidos(atores) < n)
        return false;

    return true;
}

static float menor(float a, float b)
{
    if (a < b)
        return a;
    else
        return b;
}

void Soluciona(int i, ator *atores)
{
    if (otimilidade)
    {
        if (viabilidade)
        {
            if (!factivel(i, atores))
            {
                return;
            }
        }
        if (i > m)
        {
            return;
        }

        quantNos++;

        if (quantEscolhidos(atores) == n && quantGrupos(atores) == l)
        {
            int custo_atual = calculaCusto(atores);
            if (melhor.custo > custo_atual)
            {
                trocaMelhor(custo_atual, atores);
            }
        }
        // bound pick
        float escolhe_limitante;
        if (!bound)
            escolhe_limitante = Bound(i + 1, atores);
        else
            escolhe_limitante = Bound2(i + 1, atores);

        // bound skip
        atores[i].escolhido = 0;
        float pula_limitante;
        if (!bound)
            pula_limitante = Bound(i + 1, atores);
        else
            pula_limitante = Bound2(i + 1, atores);
        atores[i].escolhido = 1;

        if (menor(escolhe_limitante, pula_limitante) >= melhor.custo)
            return;

        if (escolhe_limitante < pula_limitante)
        {

            Soluciona(i + 1, atores);
            if (pula_limitante < melhor.custo)
            {
                // ramifica para esquerda
                atores[i].escolhido = 0;
                Soluciona(i + 1, atores);
                // ramifica para direita
                atores[i].escolhido = 1;
            }
        }
        else
        {
            // ramifica para esquerda
            atores[i].escolhido = 0;
            Soluciona(i + 1, atores);
            // ramifica para direita
            atores[i].escolhido = 1;
            if (pula_limitante < melhor.custo)
            {
                Soluciona(i + 1, atores);
            }
        }
    }

    else
    {
        if (i > m)
        {
            return;
        }

        quantNos++;

        if (quantEscolhidos(atores) == n && quantGrupos(atores) == l)
        {
            float custo_atual = calculaCusto(atores);
            if (melhor.custo > custo_atual)
            {
                trocaMelhor(custo_atual, atores);
            }
        }

        // ramifica para esquerda
        atores[i].escolhido = 0;
        Soluciona(i + 1, atores);

        // ramifica para direita
        atores[i].escolhido = 1;
        Soluciona(i + 1, atores);
    }
}