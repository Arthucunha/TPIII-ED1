#include "indiceInvertido.h"

#include <string.h>
/*
indiceInvertido.c

Implementar as funções definidas em indiceInvertido.h
*/

void inicia(IndiceInvertido indiceInvertido)
{
    for (int i = 0; i < M; i++)
    {
        indiceInvertido[i].n = 0;
        strcpy(indiceInvertido[i].chave, VAZIO);
        for (int j = 0; j < ND; j++)
        {
            strcpy(indiceInvertido[i].documentos[j], VAZIO);
        }
    }
}

bool insereDocumento(IndiceInvertido indice, Chave chave, NomeDocumento nomeDocumento)
{
    int posicao = h(chave, 1000);

    if (indice[posicao].chave == VAZIO)
    {
        strcpy(indice[posicao].chave, chave);
        strcpy(indice[posicao].documentos[(indice[posicao].n + 1)], nomeDocumento);
        if (indice[posicao].n != 0)
        {
            indice[posicao].n += 1;
        }
    }
    else
    {
        // tratamento por colisao por sondagem linear
        int novaPosicao = posicao + 1;
        while (indice[novaPosicao].chave != VAZIO && novaPosicao != posicao)
        {
            novaPosicao = novaPosicao + 1;
        }
        if (indice[novaPosicao].chave == VAZIO)
        {
            strcpy(indice[posicao].chave, chave);
            strcpy(indice[posicao].documentos[(indice[posicao].n + 1)], nomeDocumento);
        }
        else{
            return false; //tabela cheia
        }
    }
    return true; //sucesso
}

int busca(IndiceInvertido indice, Chave chave){
    int posicao = h(chave, 1000);
    int tentativas = 0;

    while(tentativas < M){
        if(strcmp(indice[posicao].chave,chave)){
            return posicao;
        }
        posicao++;
        tentativas++;
    }

}