#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define N 21    // tamanho da chave ( string )
#define D 51    // tamanho do nome do documento ( string )
#define ND 100  // numero maximo de documentos
#define NN 1000 // numero maximo de chaves por documentos
#define M 1000  // tamanho da tabela
#define MAX_STR 20001

#define VAZIO "!!!!!!!!!!!!!!!!!!!!\0"

typedef char Chave[21];
typedef char NomeDocumento[51];

typedef struct
{
    int n; // numero de documentos
    Chave chave;
    NomeDocumento documentos[ND];
} Item;

typedef Item IndiceInvertido[M];

int h(char *chave, int m)
{
    float p[] = {0.8326030060567271, 0.3224428884580177,
                 0.6964223353369197, 0.1966079596929834,
                 0.8949283476433433, 0.4587297824155836,
                 0.5100785238948532, 0.05356055934904358,
                 0.9157270141062215, 0.7278472432221632};
    int tamP = 10;
    unsigned int soma = 0;
    for (int i = 0; i < strlen(chave); i++)
    {
        soma += (unsigned int)chave[i] * p[i % tamP];
    }
    return soma % m;
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
        //printf("\n\nposicao: %d\n\n", posicao);
        if (strcmp(indice[posicao].chave, chave) == 0)
        {
            //printf("\n\nValor função busca: %d\n\n", indiceChave);
            return posicao;
        }
        posicao++;
        tentativas++;
    }
    return -1;
}

void imprimirChaves(Chave *chaves, int tamanho)
{
    printf("Chaves: ");
    for (int i = 0; i < tamanho; i++)
    {
        printf("%s ", chaves[i]);
    }
    printf("\n");
}

int pegarChaves(Chave *chaves)
{
    int i = 0;
    char *token;
    char str[20001];
    int posicao;

    // tokenizacao da string original, divide em strings delimitadas por espaco em branco
    fgets(str, 20001, stdin);
    str[strcspn(str, "\n")] = 0; // remove o \n do final da string e substitui por 0

    token = strtok(str, " "); // a funçao strtok aponta para a string que esta a frente da atual separadas por um espaco em brancp

    while (token != NULL)
    {
        strcpy(chaves[i++], token); // strcpy pega o que contem na segunda string e copia pra primeira
        // inserir o item na lista adequada

        // mudei
        posicao = h(chaves[i - 1], i); // olhando onde ficara a string na tabela

        token = strtok(NULL, " "); // obtendo o proximo token na string original
    }
    return i;
}
bool insereDocumento(IndiceInvertido indice, Chave chave, NomeDocumento nomeDocumento)
{
    //int posicao = h(chave, 1000);

    int posicao = 0;
    int n = indice[posicao].n;

    int indiceChave = busca(indice, chave);

    //printf("\n\n chegou \n\n");
    //printf("\n\nValor função busca: %d\n\n", indiceChave);
    //printf("\n\nValor função busca: %s\n\n", indice[indiceChave].chave);

    if (indiceChave == -1)
    { // caso a chave nao exista na tabela, adicionar ela a tabela

        //printf("\n\ncondicao do if: %s\n\n", indice[posicao].chave);
        if (strcmp(indice[posicao].chave, VAZIO) == 0)
        {

            
            strcpy(indice[posicao].chave, chave);
            printf("\n\n Entrou 2 com a chave %s\n\n", chave);
            //printf("\n\n novo indice primeiro if = %s \n\n", indice[posicao].chave);
            //printf("\n\n Inserido na posicao: %d \n\n", posicao);
            strcpy(indice[posicao].documentos[n], nomeDocumento);
            indice[posicao].n++;
        }
        else
        {
            printf("\n\n Entrou 3 com a chave %s\n\n", chave);
            // tratamento por colisao por sondagem linear
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
                    //printf("\n\n Entrou 4 \n\n");
                    strcpy(indice[novaPosicao].chave, chave);
                    //printf("\n\n novo indice = %s \n\n", indice[posicao].chave);
                    strcpy(indice[novaPosicao].documentos[n], nomeDocumento);
                    indice[novaPosicao].n++;
                    break;
                }
                else
                {
                    // return false; // tabela cheia
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

int consulta(IndiceInvertido indice, Chave *chaves, int numChaves, NomeDocumento *documentos)
{
    // Inicializa a lista de documentos com o primeiro elemento da primeira chave
    int posicao = busca(indice, chaves[0]);
    if (posicao == -1)
        return 0; // Chave não existe no índice
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
void imprimeIndice(IndiceInvertido indice, int tamanho)
{
    printf("Indice Invertido:\n");

    for (int i = 0; i < tamanho; i++)
    {
        if (strcmp(indice[i].chave, VAZIO) != 0)
        {
            printf("Chave: %s \n", indice[i].chave);
            for (int j = 0; j < 51; j++)
            {
                printf("Documentos: %s \n", indice[i].documentos[j]);
            }
            printf("\n");
        }
    }
}

void quicksort(NomeDocumento* lista, int esq, int dir){
    int i = esq, j = dir;
    NomeDocumento pivo;
    strcpy(pivo, lista[(esq + dir) / 2]);
    while (i <= j) {
        while (strcmp(lista[i], pivo) < 0) {
            i++;
        }
        while (strcmp(lista[j], pivo) > 0) {
            j--;
        }
        if (i <= j) {
            NomeDocumento tmp;
            strcpy(tmp, lista[i]);
            strcpy(lista[i], lista[j]);
            strcpy(lista[j], tmp);
            i++;
            j--;
        }
    }
    if (esq < j) {
        quicksort(lista, esq, j);
    }
    if (i < dir) {
        quicksort(lista, i, dir);
    }
}

void sort(NomeDocumento* lista, int n){
    quicksort(lista, 0, n-1);
}



int main()
{

    /*IndiceInvertido indice;

    inicia(indice);

    int tamanho = strlen(indice[0].chave);

    printf("\n\nTamanho = %d\n\n", tamanho);
    printf("Chave na inicia: %s -> ", indice[0].documentos[0]);

    insereDocumento(indice, "chave1", "doc1");
    insereDocumento(indice, "chave2", "doc1");
    insereDocumento(indice, "chave2", "doc2");
    insereDocumento(indice, "chave3", "doc1");
    insereDocumento(indice, "chave3", "doc2");
    insereDocumento(indice, "chave3", "doc3");
    //imprimeIndice(indice, 5);

    // Teste da função consulta()
    Chave chaves[2] = {"chave2", "chave3"};
    NomeDocumento documentos[ND];
    int num_documentos = consulta(indice, chaves, 2, documentos);

    // Impressão dos documentos encontrados
    printf("Documentos encontrados:\n");
    for (int i = 0; i < num_documentos; i++) {
        printf("%s\n", documentos[i]);
    }

    */

    NomeDocumento lista[100] = {"Beta", "Zeta", "Delta", "Alfa", "Epsilon"};
    int n = 5;

    sort(lista, n);

    for (int i = 0; i < n; i++) {
        printf("%s\n", lista[i]);
    }

    return 0;
}
