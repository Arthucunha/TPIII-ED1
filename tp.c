#include "indiceInvertido.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main()
{
    double tempoGasto = 0.0;

    clock_t begin = clock();

    IndiceInvertido indiceInvertido;
    Chave chavesPesquisa[NN];
    Chave chavesEntrada[NN];
    NomeDocumento documentos[ND];
    char nomeDocumento[D];
    int n, nChaves, nChavesPesquisa, nDocumentos, colisoes = 0;
    char opcao;



    inicia(indiceInvertido);

    scanf("%d", &n); // entrada numero de docs

    for (int i = 0; i < n; i++)
    {
        scanf("%s", nomeDocumento);
        nChaves = pegarChaves(chavesEntrada);
        for (int j = 0; j < nChaves; j++)
        {
            insereDocumento(indiceInvertido, chavesEntrada[j], nomeDocumento, &colisoes);
        }
    }

    scanf("%c", &opcao);
    if (opcao == 'B')
    {
        nChavesPesquisa = pegarChaves(chavesPesquisa);
        nDocumentos = consulta(indiceInvertido, chavesPesquisa, nChavesPesquisa, documentos);
        if (nDocumentos == 0)
        {
            printf("none\n");
            return 0;
        }
        else
        {
            sort(documentos, nDocumentos);
            for (int i = 0; i < nDocumentos; i++)
            {
                printf("%s ", documentos[i]);
                printf("\n");
            }
        }
        printf("\n");
    }
    else if (opcao == 'I')
    {
        imprime(indiceInvertido);
    }
    else
    {
        printf("\nOpção invalida, reinicie o programa e digite uma opção valida\n");
    }

    clock_t end = clock();
    tempoGasto += (double)(end - begin) / CLOCKS_PER_SEC;

    return 0;
}
