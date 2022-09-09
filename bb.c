#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bblib.h"
#include <stdbool.h>

int main(int argc, char *argv[])
{
    bool otimilidade = true, viabilidade = true, limitanteAlt = false;
    for (int i = 0; i < argc; i++)
    {
        if (!strcmp(argv[i], "-a"))
        {
            limitanteAlt = true;
        }
        if (!strcmp(argv[i], "-o"))
        {
            otimilidade = false;
        }
        if (!strcmp(argv[i], "-f"))
        {
            viabilidade = false;
        }
    }
    if (otimilidade || viabilidade || limitanteAlt)
    {
        printf("\n");
    }

    // int l, m, n;
    scanf("%d %d %d", &l, &m, &n);

    if (m < n)
    {
        printf("Inviavel\n");
        exit(0);
    }

    ator *atores = leAtores();
    printaAtores(atores);
    inicializaMelhor();
    Soluciona(0, atores);
    // branchAndBound();
}
