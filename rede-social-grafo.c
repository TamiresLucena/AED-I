// Tamires Lucena 111866

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Tno{
    char nome[17];
    int indice;
    struct Tno *proximo;
}Tno;

typedef struct Tlista{
    Tno *inicio, *fim;
    int quantidade;
}Tlista;

void inicializaLista(Tlista *lista){
    lista->quantidade = 0;
    lista->inicio = NULL;
    lista->fim = NULL;
}

int Insere(Tlista *lista, char *pessoa){
    Tno *aux = malloc(sizeof(Tno));
    strcpy(aux->nome, pessoa);
    aux->proximo = NULL;

    if(lista->inicio == NULL){
        lista->inicio = aux;
        lista->fim = aux;
    }
    else{
        lista->fim->proximo = aux;
        lista->fim = aux;
    }
    lista->fim->indice = lista->quantidade;
    lista->quantidade++;

    return lista->fim->indice;
}

int Verifica(Tlista *lista, char *pessoa){
    int indice;
    if(lista->inicio == NULL) indice = Insere(lista, pessoa);
    else{
        Tno *percorre = lista->inicio;
        while(percorre != NULL){
            if(!strcmp(percorre->nome, pessoa)) return percorre->indice;
            percorre = percorre->proximo;
        }
        indice = Insere(lista, pessoa);
    }
    return indice;
}

void InsereInt(Tlista *lista, int indice){
    Tno *aux = malloc(sizeof(Tno));
    aux->proximo = NULL;
    aux->indice = indice;

    if(lista->inicio == NULL){
        lista->inicio = aux;
        lista->fim = aux;
    }
    else{
        lista->fim->proximo = aux;
        lista->fim = aux;
    }
    lista->quantidade++;

    return;
}


void VerificaInt(Tlista *lista, int indice){

    if(lista->inicio == NULL) InsereInt(lista, indice);
    else{
        Tno *percorre = lista->inicio;
        while(percorre != NULL){
            if(indice == percorre->indice) return;
            percorre = percorre->proximo;
        }
        InsereInt(lista, indice);
    }
    return;
}



int main(){

    char pessoaprincipal[17];
    scanf("%s", pessoaprincipal);

    int N, M;
    scanf("%d %d", &N, &M);

    Tlista lista;
    inicializaLista(&lista);

    int i, j, indice1, indice2;

    char pessoa1[17], pessoa2[17];

    int matriz[N][N];
    for(i=0; i<N; i++){
        for(j=0; j<N; j++){
            matriz[i][j] = 0;
        }
    }

    for(i=0; i<M; i++){
        scanf("%s %s", pessoa1, pessoa2);
        indice1 = Verifica(&lista, pessoa1);
        indice2 = Verifica(&lista, pessoa2);
        matriz[indice1][indice2] = 1;
        matriz[indice2][indice1] = 1;
    }

    int pp = Verifica(&lista, pessoaprincipal);

    Tlista segundograu;
    inicializaLista(&segundograu);

    for(i=0; i<N; i++){
        if(i != pp && matriz[pp][i] == 1){
            for(j=0; j<N; j++){
                if(j != pp && matriz[i][j] == 1){
                    if(pp != j && matriz[pp][j] == 0){
                       VerificaInt(&segundograu, j);
                    }
                }
            }
        }
    }

    printf("%d\n", segundograu.quantidade);
    return 0;
}
