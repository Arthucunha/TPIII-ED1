#ifndef HASH_ABERTO
#define HASH_ABERTO

#include "hash.h"
#include <stdbool.h>

/* Os cabeçalhos de todas as funções e os TADs podem ser alterados */

#define VAZIO "!!!!!!!!!!!!!!!!!!!!\0 "

typedef struct {
    int n; // numero de documentos
    Chave chave;
    NomeDocumento documentos[ND];
} Item;

typedef Item IndiceInvertido[M]; // criacao do indice invertido

/* Funções */

void inicia(IndiceInvertido);
bool insereDocumento(IndiceInvertido indice, Chave chave, NomeDocumento nomeDocumento, int *contadorColisoes);
int busca(IndiceInvertido, Chave);
int consulta(IndiceInvertido, Chave*, int, NomeDocumento*);
void imprime(IndiceInvertido);
void quicksort(NomeDocumento* lista, int esq, int dir);
void sort(NomeDocumento*, int);

#endif // !HASH_ABERTO