#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef char Chave[21];
typedef char NomeDocumento[51];

typedef struct
{
    Chave chave;
    NomeDocumento nomeDocumento;

}TItem;
typedef TItem Hash[1000];

int h(char * chave, int m) {
    float p[] = {0.8326030060567271, 0.3224428884580177, 
                 0.6964223353369197, 0.1966079596929834, 
                 0.8949283476433433, 0.4587297824155836, 
                 0.5100785238948532, 0.05356055934904358, 
                 0.9157270141062215, 0.7278472432221632};
    int tamP = 10;
    unsigned int soma = 0;
    for (int i=0;i<strlen ( chave );i++){
        soma += (unsigned int) chave [i] * p[i % tamP];
    }
    return soma % m;
}

void imprimirChaves(Chave* chaves, int tamanho) {
    printf("Chaves: ");
    for (int i = 0; i < tamanho; i++) {
        printf("%s ", chaves[i]);
    }
    printf("\n");
}

int pegarChaves(Chave* chaves) {
    int i = 0;
    char* token;
    char str[20001];
    int posicao;
    
    // tokenizacao da string original, divide em strings delimitadas por espaco em branco
    fgets (str, 20001, stdin);
    str[strcspn(str, "\n")] = 0; //remove o \n do final da string e substitui por 0

    token = strtok(str, " "); // a funçao strtok aponta para a string que esta a frente da atual separadas por um espaco em brancp

    while (token != NULL) {
        strcpy(chaves[i++], token); //strcpy pega o que contem na segunda string e copia pra primeira
        //inserir o item na lista adequada

        //mudei
        posicao = h(chaves[i-1], i);//olhando onde ficara a string na tabela

        token = strtok(NULL, " "); //obtendo o proximo token na string original
    }
    return i;
}

int main() {

    int i = 0;
    char* token;
    char str[20001];
    int posicao;
    char nomeDocumento[51];

    Chave* chaves = malloc(100 * sizeof(Chave));
    
    
    
    scanf("%s", nomeDocumento);
    pegarChaves(chaves);
    
    printf("\nnome: %s\n", nomeDocumento);
    printf("\nChave: %s\n", chaves[0]);

    /*while (token != NULL) {
        strcpy(chaves[i++], token);

        //inserir o item na lista adequada
        posicao = h(chaves[i-1], i);
        printf("\nPosição: %d\n", posicao);

        token = strtok(NULL, " ");
        //printf("\n%c\n", str[i]);
        //printf("\n%d\n", i);
        //i++;
    }*/

    //printf("\n%s\n", chaves[1]);

    //imprimirChaves(chaves, i);
    
    free(chaves);
    
    

    return 0;
}
