#include "indiceInvertido.h"
#include "hash.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{

    IndiceInvertido indiceInvertido;
    Chave chavesPesquisa[NN];
    Chave chavesEntrada[NN];
    NomeDocumento documentos[ND];
    char nomeDocumento[D];
    int n, nChaves, nChavesPesquisa, nDocumentos;
    char opcao;

    inicia(indiceInvertido);

    scanf("%d", &n); // entrada numero de docs

    for (int i = 0; i < n; i++)
    {
        scanf("%s", nomeDocumento);
        nChaves = pegarChaves(chavesEntrada);
        for (int j = 0; j < nChaves; j++)
        {
            insereDocumento(indiceInvertido, chavesEntrada[j], nomeDocumento);
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

    return 0;
}
