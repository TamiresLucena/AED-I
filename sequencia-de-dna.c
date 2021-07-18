//TAMIRES LUCENA 111866

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Titem{
    char carac;
    struct Titem *proximo;
    struct Titem *anterior;
}Titem;

typedef struct Tlista{
    Titem *inicio;
    Titem *fim;
}Tlista;

void Inicializa(Tlista *lista){
    lista->inicio = NULL;
    lista->fim = NULL;
}

void Insere(Tlista *lista, Titem letra){
    Titem *aux = malloc(sizeof(Titem));
    *aux = letra;

    if(lista->fim == NULL){
        lista->fim = aux;
        lista->inicio = aux;
        aux->anterior = NULL;
        aux->proximo = NULL;
    }
    else{
        lista->fim->proximo = aux;
        aux->anterior = lista->fim;
        lista->fim = aux;
        aux->proximo = NULL;
    }

}

void Imprime(Tlista *lista){
    Titem *percorre;
    percorre = lista->inicio;

    while(percorre != NULL){
        printf("%c", percorre->carac);
        percorre = percorre->proximo;
    }
}

void Remover(Tlista *lista, Titem *percorre, Titem *temporario){
    if(temporario != NULL){
    temporario->anterior = percorre->anterior;
    }
    else{
        lista->fim = percorre->anterior;
    }
    if(percorre != lista->inicio){
        percorre->anterior->proximo = temporario;
    }
    else{
        lista->inicio = temporario;
    }
}

void Encontra(Tlista *lista, char *sub, int tamsub){
    Titem *percorre;
    percorre = lista->inicio;

    Titem *temporario;
    int i;
    int vezes = 0;

    while(percorre != NULL){
        if(percorre->carac == sub[0]){
            int comparacao = 1;
            temporario = percorre->proximo;
            for(i=1; i<tamsub; i++){
               if(temporario != NULL && temporario->carac == sub[i]){
                comparacao ++;
                temporario = temporario->proximo;
               }
               else break;
            }
            if(comparacao == tamsub){
                 vezes ++;
                Remover(lista, percorre, temporario);
                percorre = temporario;
            }
            else{
            percorre = percorre->proximo;
            }
        }
        else{
            percorre = percorre->proximo;
        }
    }
    printf("%d\n", vezes);
}


int main()
{
    Tlista lista;
    char string[1023];

    scanf("%s", string);
    int tamanho = strlen(string);
    Inicializa(&lista);

    Titem letra;

    int i;
    for(i=0; i<tamanho; i++){
        letra.carac = string[i];
        Insere(&lista, letra);
    }

    char sub[1023];
    scanf("%s", sub);
    int tamsub = strlen(sub);

    if(tamsub > tamanho){
        Imprime(&lista);
    }

    else{
    Encontra(&lista, sub, tamsub);
    Imprime(&lista);
    }


    return 0;
}

