#include "indiceInvertido.h"
#include "hash.h"

int main() {

    Tabela tabela;
    IndiceInvertido indiceInvertido;
    inicializarTabela(tabela);
    inicializarIndiceInvertido(indiceInvertido);
    Chave* chaves;
    char nomeDocumento[51];
    int n, nChaves;

    scanf("%d", &n);

    for(int i = 0; i < n; i++){
        scanf("%s", nomeDocumento);
        nChaves = pegarChaves(chaves);
        for(int j = 0; j < nChaves; j++){
            inserir(tabela, chaves, nomeDocumento);
        }
    }


    return 0;
}
