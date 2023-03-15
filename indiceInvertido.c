#include "indiceInvertido.h"

#include <string.h>
#include <stdio.h>

void inicia(IndiceInvertido indiceInvertido)
{
    for (int i = 0; i < M; i++)
    {
        indiceInvertido[i].n = 0;
        strcpy(indiceInvertido[i].chave, VAZIO);
        /*if(strcmp(indiceInvertido[i].chave, VAZIO) == 0){
            printf("Chave na inicia: %s -> ", indiceInvertido[i].chave);
        }*/

        for (int j = 0; j < ND; j++)
        {
            strcpy(indiceInvertido[i].documentos[j], VAZIO);
        }
    }
}

bool insereDocumento(IndiceInvertido indice, Chave chave, NomeDocumento nomeDocumento)
{
    int posicao = 0;
    int n = indice[posicao].n;

    int indiceChave = busca(indice, chave);

    if (indiceChave == -1)
    { // caso a chave nao exista na tabela, adicionar ela a tabela

        if (strcmp(indice[posicao].chave, VAZIO) == 0)
        {
            strcpy(indice[posicao].chave, chave);
            strcpy(indice[posicao].documentos[n], nomeDocumento);
            indice[posicao].n++;
        }
        else
        {

            int novaPosicao = posicao + 1;
            while (indice[novaPosicao].chave != VAZIO && novaPosicao != posicao)
            {
                novaPosicao = novaPosicao + 1;
                if (novaPosicao == 999)
                {
                    novaPosicao = 0;
                }
                if (strcmp(indice[novaPosicao].chave, VAZIO) == 0)
                {
                    n = indice[novaPosicao].n;
                    strcpy(indice[novaPosicao].chave, chave);
                    strcpy(indice[novaPosicao].documentos[n], nomeDocumento);
                    indice[novaPosicao].n++;
                    break;
                }
                else
                {
                    //return false; // tabela cheia
                }
            }
        }
    }
    else
    {
        n = indice[indiceChave].n;
        strcpy(indice[indiceChave].documentos[n], nomeDocumento);
        indice[indiceChave].n++;
    }

    return true; // sucesso
}

int busca(IndiceInvertido indice, Chave chave)
{
    int posicao = h(chave, 1000);
    int tentativas = 0;

    while (tentativas < M)
    {
        if (posicao == 999)
        {
            posicao = 0;
        }
        // printf("\n\nposicao: %d\n\n", posicao);
        if (strcmp(indice[posicao].chave, chave) == 0)
        {
            // printf("\n\nValor função busca: %d\n\n", indiceChave);
            return posicao;
        }
        posicao++;
        tentativas++;
    }
    return -1;
}

int consulta(IndiceInvertido indice, Chave *chaves, int numChaves, NomeDocumento *documentos)
{
    
    // Inicializa a lista de documentos com o primeiro elemento da primeira chave
    int posicao = busca(indice, chaves[0]);
    if (posicao == -1){
        
        return 0; // Chave não existe no índice
    }
    int numDocumentos = indice[posicao].n;
    for (int i = 0; i < numDocumentos; i++)
    {
        strcpy(documentos[i], indice[posicao].documentos[i]);
    }

    // Itera sobre as demais chaves
    for (int i = 1; i < numChaves; i++)
    {
        posicao = busca(indice, chaves[i]);
        if (posicao == -1)
            return 0; // Chave não existe no índice

        // Verifica se o documento está presente na lista de documentos da chave atual
        int j = 0;
        while (j < numDocumentos)
        {
            bool encontrado = false;
            for (int k = 0; k < indice[posicao].n; k++)
            {
                if (strcmp(documentos[j], indice[posicao].documentos[k]) == 0)
                {
                    encontrado = true;
                    break;
                }
            }
            if (!encontrado)
            {
                // Remove o documento da lista de documentos
                numDocumentos--;
                strcpy(documentos[j], documentos[numDocumentos]);
            }
            else
            {
                j++;
            }
        }
    }

    return numDocumentos;
}

void imprime(IndiceInvertido indice)
{
    printf("Indice Invertido:\n");

    for (int i = 0; i < M; i++)
    {
        if (strcmp(indice[i].chave, VAZIO) != 0)
        {
            printf("\n%s -", indice[i].chave);
            for (int j = 0; j < indice[i].n; j++)
            {
                if(strcmp(indice[j].chave, VAZIO) != 0){
                    printf(" %s", indice[i].documentos[j]);
                }
                
            }
            printf("\n");
        }
    }
}

void quicksort(NomeDocumento *lista, int esq, int dir)
{
    int i = esq, j = dir;
    NomeDocumento pivo;
    strcpy(pivo, lista[(esq + dir) / 2]);
    while (i <= j)
    {
        while (strcmp(lista[i], pivo) < 0)
        {
            i++;
        }
        while (strcmp(lista[j], pivo) > 0)
        {
            j--;
        }
        if (i <= j)
        {
            NomeDocumento tmp;
            strcpy(tmp, lista[i]);
            strcpy(lista[i], lista[j]);
            strcpy(lista[j], tmp);
            i++;
            j--;
        }
    }
    if (esq < j)
    {
        quicksort(lista, esq, j);
    }
    if (i < dir)
    {
        quicksort(lista, i, dir);
    }
}

void sort(NomeDocumento *lista, int n)
{
    quicksort(lista, 0, n - 1);
}
