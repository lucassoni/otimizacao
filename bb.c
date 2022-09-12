#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bblib.h"
#include <stdbool.h>
#include <time.h>

int main(int argc, char *argv[])
{
    otimilidade = true;
    viabilidade = true;
    bound = BOUND1;
    clock_t start = clock();
    for (int i = 0; i < argc; i++)
    {
        if (!strcmp(argv[i], "-a"))
        {
            bound = BOUND2;
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

    // int l, m, n;
    scanf("%d %d %d", &l, &m, &n);

    ator *atores = leAtores();
    if (quantGrupos(atores) < l || m < n)
    {
        printf("Inviavel\n");
        exit(0);
    }

    inicializaMelhor();

    quantNos = 0;
    Soluciona(0, atores);
    printaMelhor(atores);
    clock_t end = clock();

    float time_spent = 0.0;
    time_spent += (float)(end - start) / CLOCKS_PER_SEC;
    fprintf(stderr, "A arvore teve %d nos\n", quantNos);
    fprintf(stderr, "Tempo: %f segundos\n", time_spent);
}
