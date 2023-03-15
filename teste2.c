#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TAMANHO_CHAVE 21
#define TAMANHO_DOCUMENTO 51
#define TAMANHO_TABELA 1000
#define MAX_CHAVES_DOCUMENTO 1000
#define MAX_DOCUMENTOS 100

typedef char Chave[TAMANHO_CHAVE];
typedef char NomeDocumento[TAMANHO_DOCUMENTO];

typedef struct {
    Chave chave;
    NomeDocumento nomeDocumento;
} TItem;

typedef TItem* Tabela[TAMANHO_TABELA];

typedef struct {
    Chave chave;
    int documentos[MAX_CHAVES_DOCUMENTO];
    int qtdDocumentos;
} TIndiceInvertido;

typedef TIndiceInvertido* IndiceInvertido[TAMANHO_TABELA];

void inicializarTabela(Tabela tabela) {
    for (int i = 0; i < TAMANHO_TABELA; i++) {
        tabela[i] = NULL;
    }
}

void inicializarIndiceInvertido(IndiceInvertido indiceInvertido) {
    for (int i = 0; i < TAMANHO_TABELA; i++) {
        indiceInvertido[i] = NULL;
    }
}

int funcaoHash(Chave chave) {
    int soma = 0;
    for (int i = 0; i < strlen(chave); i++) {
        soma += (int) chave[i];
    }
    return soma % TAMANHO_TABELA;
}


int inserir(Tabela tabela, Chave chave, NomeDocumento nomeDocumento, IndiceInvertido indiceInvertido) {
    int posicao = funcaoHash(chave);
    TItem* novoItem = (TItem*) malloc(sizeof(TItem));
    if (novoItem == NULL) {
        return 0; // falha na alocação de memória
    }
    strcpy(novoItem->chave, chave);
    strcpy(novoItem->nomeDocumento, nomeDocumento);

    if (tabela[posicao] == NULL) {
        tabela[posicao] = novoItem;
    } else {
        // tratamento de colisão por sondagem linear
        int novaPosicao = (posicao + 1) % TAMANHO_TABELA;
        while (tabela[novaPosicao] != NULL && novaPosicao != posicao) {
            novaPosicao = (novaPosicao + 1) % TAMANHO_TABELA;
        }
        if (tabela[novaPosicao] == NULL) {
            tabela[novaPosicao] = novoItem;
        } else {
            free(novoItem);
            return 0; // tabela cheia
        }
    }

    // índice invertido
    int i;
    for (i = 0; i < MAX_CHAVES_DOCUMENTO; i++) {
        if (indiceInvertido[i] == NULL) {
            indiceInvertido[i] = novoItem;
            break;
        }
    }
    if (i == MAX_CHAVES_DOCUMENTO) {
        free(novoItem);
        return 0; // índice invertido cheio
    }

    return 1; // sucesso
}

void imprimirChaves(Tabela tabela) {
    printf("Chaves: ");
    for (int i = 0; i < TAMANHO_TABELA; i++) {
        if (tabela[i] != NULL) {
            printf("%s ", tabela[i]->chave);
        }
    }
    printf("\n");
}

void imprimirIndiceInvertido(IndiceInvertido indiceInvertido) {
    printf("Índice invertido:\n");
    for (int i = 0; i < MAX_CHAVES_DOCUMENTO; i++) {
        if (indiceInvertido[i] != NULL) {
            printf("%s: ", indiceInvertido[i]->chave);
            for (int j = 0; j < MAX_DOCUMENTOS; j++) {
                if (indiceInvertido[i][j].nomeDocumento[0] != '\0') {
                    printf("%s ", indiceInvertido[i][j].nomeDocumento);
                }
            }
            printf("\n");
        }
    }
}

int main() {
    Tabela tabela;
    IndiceInvertido indiceInvertido;
    inicializarTabela(tabela);
    inicializarIndiceInvertido(indiceInvertido);

    // exemplo de uso
    inserir(tabela, "chave1", "documento1", indiceInvertido);
    inserir(tabela, "chave2", "documento1", indiceInvertido);
    inserir(tabela, "chave3", "documento2", indiceInvertido);
    inserir(tabela, "chave4", "documento3", indiceInvertido);

    imprimirChaves(tabela);
    imprimirIndiceInvertido(indiceInvertido);

    return 0;
}
