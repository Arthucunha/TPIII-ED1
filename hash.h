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

