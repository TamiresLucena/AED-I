// Tamires Lucena 111866

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Titem{
    char carac;
    int quantidade;
    struct Titem *anterior;
    struct Titem *proximo;
}Titem;

typedef struct Tlista{
    Titem *inicio;
    Titem *fim;
    int tamanho;
}Tlista;

void Inicializa(Tlista *lista){
    lista->inicio = NULL;
    lista->fim = NULL;
    lista->tamanho = 0;
}

void Inserir(Tlista *lista, Titem letra){
    Titem *aux = malloc(sizeof(Titem));
    *aux = letra;

    if(lista->inicio == NULL){
        lista->inicio = aux;
        lista->fim = aux;
        aux->anterior = NULL;
        aux->proximo = NULL;
    }
    else{
        lista->fim->proximo = aux;
        aux->anterior = lista->fim;
        lista->fim = aux;
        aux->proximo = NULL;
    }
    lista->tamanho ++;
}

void Imprimir(Tlista *lista){
    Titem *percorre;
    percorre = lista->inicio;

    printf("%d\n", lista->tamanho*2);
    while(percorre != NULL){
        printf("%d%c", percorre->quantidade, percorre->carac);
        percorre = percorre->proximo;
    }
    return;
}

void Remover(Tlista *lista, Titem *percorre){
    Titem *remove;
    remove = percorre;

    // no inicio
    if(percorre == lista->inicio){
        lista->inicio = percorre->proximo;
        lista->inicio->anterior = NULL;
    }
    // no fim
    else if(percorre == lista->fim){
        lista->fim = percorre->anterior;
        lista->fim->proximo = NULL;
    }
    // no meio ta certo
    else{
        percorre->anterior->proximo = percorre->proximo;
        percorre->proximo->anterior = percorre->anterior;
    }

    percorre = percorre->proximo;
    free(remove);
    lista->tamanho --;
}

void Encontra(Tlista *lista){
    Titem *percorre;
    percorre = lista->inicio;

    while(percorre!= NULL){

        if(percorre->quantidade != 1) percorre = percorre->proximo;

        else{ // =1
            if(percorre == lista->inicio && percorre->proximo != NULL && percorre->proximo->quantidade != 1){ //inicio
                percorre->proximo->quantidade ++;
                Remover(lista, percorre);
            }
            else if(percorre == lista->fim && percorre->anterior != NULL && percorre->anterior->quantidade != 1){ //fim
                percorre->anterior->quantidade++;
                Remover(lista, percorre);
            }
            else if(percorre->anterior != NULL && percorre->anterior->quantidade != 1 && percorre->proximo != NULL && percorre->proximo->quantidade != 1){ //meio
                if(percorre->anterior->quantidade > percorre->proximo->quantidade) percorre->anterior->quantidade ++;
                else if(percorre->proximo->quantidade > percorre->anterior->quantidade) percorre->proximo->quantidade ++;
                else if(percorre->anterior->quantidade == percorre->proximo->quantidade) percorre->anterior->quantidade ++;
                Remover(lista, percorre);
            }
            else percorre = percorre->proximo;
        }
    }
}



int main()
{
    char string[1024];
    scanf("%s", string);
    int tamanho = strlen(string);

    int i=0, j=0;
    int contador = 1;

    Tlista lista;
    Inicializa(&lista);

    Titem letra;

    for(j=1; j<tamanho; j++){
        if(string[i] == string[j])
            contador ++;
        else{
            letra.carac = string[i];
            letra.quantidade = contador;
            Inserir(&lista, letra);
            contador = 1;
            i = j;
        }
    }

    if(j == tamanho){ // ultimos que não entram no "for"
        letra.carac = string[i];
        letra.quantidade = contador;
        Inserir(&lista, letra);
    }


    Imprimir(&lista);
    printf("\n");
    Encontra(&lista);
    Imprimir(&lista);

    return 0;
}
