#include "indiceInvertido.h"
#include "hash.h"

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main() {

    IndiceInvertido indiceInvertido;
    Chave* chaves;
    Chave* chavesPesquisa[NN];
    NomeDocumento nomeDocsPesquisa[ND];
    char nomeDocumento[D];
    int n, nChaves, nChavesPesquisa;
    char opcao;

    inicia(indiceInvertido);

    scanf("%d", &n); // entrada numero de docs

    for(int i = 0; i < n; i++){
        scanf("%s", nomeDocumento);
        nChaves = pegarChaves(chaves);
        for(int j = 0; j < nChaves; j++){
            insereDocumento(indiceInvertido, chaves[j], nomeDocumento);
        }
    }

    scanf("%c", opcao);
    if(opcao == "B"){
        nChavesPesquisa = pegarChaves(chavesPesquisa);
        consulta(indiceInvertido, chavesPesquisa, nChavesPesquisa, nomeDocsPesquisa);
    }
    else if(opcao == "I"){
        imprime(indiceInvertido);
    }
    else{
        printf("\nOpção invalida, reinicie o programa e digite uma opção valida\n");
    }

    return 0;
}
