#ifndef HASH_ABERTO
#define HASH_ABERTO

#include "hash.h"
#include <stdbool.h>

/* Os cabeçalhos de todas as funções e os TADs podem ser alterados */

#define VAZIO " !!!!!!!!!!!!!!!!!!!!\0 "

typedef struct {
    int n; // numero de documentos
    Chave chave;
    NomeDocumento documentos[ND];
} Item;

typedef Item IndiceInvertido[M]; // criacao do indice invertido

/* Funções */

void inicia(IndiceInvertido);
bool insereDocumento(IndiceInvertido, Chave, NomeDocumento);
int busca(IndiceInvertido, Chave);
int consulta(IndiceInvertido, Chave*, int, NomeDocumento*);
void imprime(IndiceInvertido);
void sort(NomeDocumento*, int);

#endif // !HASH_ABERTO

/*
indiceInvertido.h

Definir as estruturas de dados necessárias
Implementar as funções para manipulação dessas estruturas de dados:
aloca
libera
insereDocumento
busca
consulta
imprime
*/