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
    int n = indice[posicao].n;

    

    int indiceChave = busca(indice, chave);

    if(indiceChave == -1){ //caso a chave nao exista na tabela, adicionar ela a tabela
        if (indice[posicao].chave == VAZIO)
        {
            strcpy(indice[posicao].chave, chave);
            strcpy(indice[posicao].documentos[n], nomeDocumento);
            indice[posicao].n++;
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
                strcpy(indice[posicao].documentos[n], nomeDocumento);
            }
            else{
                return false; //tabela cheia
            }
        }
    }
    else{
        strcpy(indice[posicao].documentos[n], nomeDocumento);
        indice[posicao].n++;
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
    return -1;
}

int consulta(IndiceInvertido indice, Chave* chaves, int nChaves, NomeDocumento* documentos){

    int cont = 0; //contador de documentos encontrados
    int indices[nChaves];//Vetor para armazenar os indices de cada chave
    bool encontrou;

    for(int i = 0; i < nChaves; i++){
        indices[i] = -1;
    }

    for (int i = 0; i < nChaves; i++){
        encontrou = false;
        for(int j = 0; j < M; j++){
            if(strcmp(indice[j].chave, chaves[j]) == 0){
                encontrou = true;
                indices[i] = j;
                break;
            }
        }
        if(!encontrou){
            return 0; //retorna 0 documentos encontrados
        }
    }

    for(int i = 0; i < indice[indices[0]].n; i++){
        //verifica se o documento contem a primeira chave
        if(strcmp(indice[indices[0]].documentos[i], documentos[0]) == 0){
            //verifica se o documento contem as demais chaves
            for(int j = 1; j < nChaves; j++){
                encontrou = false;
                for(int k = 0; k < indice[indices[j]].n; k++){
                    if(strcmp(indice[indices[j]].documentos[k], documentos[j]) == 0){
                        encontrou = true;
                        break;
                    }
                }
                if(!encontrou){
                    break;
                }
            }
            if(encontrou){
                //se o documento contem todas as chaves, adiciona ao vetor de documentos encontrados
                strcpy(documentos[cont], indice[indices[0]].documentos[i]);
                cont++;
            }
        }
    }

    return cont; //retorna o numero de documentos encontrados

    /*
    int main(){
    IndiceInvertido indice;
    Chave chaves[2] = {"chave1", "chave2"};
    NomeDocumento documentos[ND];
    int num_documentos_encontrados;
    
    */
}