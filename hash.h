#ifndef HASH
#define HASH

#define N 21 // tamanho da chave ( string )
#define D 51 // tamanho do nome do documento ( string )
#define ND 100 // numero maximo de documentos
#define NN 1000 // numero maximo de chaves por documentos
#define M 1000 // tamanho da tabela
#define MAX_STR 20001

typedef char Chave[N]; // Essas linhas de código definem dois novos tipos de dados, Chave e NomeDocumento, que são arrays de caracteres.
typedef char NomeDocumento[D];

typedef struct
{
    Chave chave;
    NomeDocumento nomeDocumento;
}TItem;


int h(char* chave, int m);
int pegarChaves(Chave* chaves);


#endif // !HASH

/*
hash.h

Definir as constantes necessárias
Implementar a função hash
Implementar a função para pegar as palavras de cada documento na linha
hash.c

Implementar as funções definidas em hash.h

indiceInvertido.h

Definir as estruturas de dados necessárias
Implementar as funções para manipulação dessas estruturas de dados:
aloca
libera
insereDocumento
busca
consulta
imprime
indiceInvertido.c

Implementar as funções definidas em indiceInvertido.h

tp.c

Implementar a função principal main, que deve:
Ler o número N de documentos a serem inseridos
Ler os N documentos
Construir o índice invertido utilizando as funções do TAD IndiceInvertido
Imprimir o índice invertido, se a opção for "I"
Realizar consultas com um ou mais termos, se a opção for "B"

*/