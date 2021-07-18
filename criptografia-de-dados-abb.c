//Tamires Lucena 111866

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Tno{
    char letra;
    int num;
    struct Tno *esquerda;
    struct Tno *direita;
} Tno;

typedef struct Tarvore{
    Tno *raiz;
} Tarvore;

void Inicializa(Tarvore *arvore){
    arvore->raiz = NULL;
}

void Verifica(Tno *existente, Tno *aux){

    if(aux->num < existente->num){
        if(existente->esquerda == NULL) existente->esquerda = aux;
        else Verifica(existente->esquerda, aux);
    }
    else{
        if(existente->direita == NULL) existente->direita = aux;
        else Verifica(existente->direita, aux);
    }
}

void Insere(Tarvore *arvore, Tno novono){
    Tno *aux = malloc(sizeof(Tno));
    *aux = novono;

    aux->direita = NULL;
    aux->esquerda = NULL;

    if(arvore->raiz == NULL) arvore->raiz = aux; // insere o primeiro
    else Verifica(arvore->raiz, aux);
}

Tno* Remover(Tno *remover){
    Tno *aux, *retornar;
    aux = remover;

    if(remover->direita == NULL && remover->esquerda == NULL) return NULL;
    else if(remover->direita == NULL /*&& remover->esquerda != NULL*/) return remover->esquerda;
    else if(remover->esquerda == NULL /*&& remover->direita != NULL*/) return remover->direita;
    else{
        aux = remover->direita;
        while(aux->esquerda != NULL && aux->esquerda->esquerda !=NULL){
            aux = aux->esquerda;
        }
        if(aux->esquerda != NULL){
            if(aux->esquerda->direita == NULL && aux->esquerda->esquerda == NULL){
                retornar = aux->esquerda;
                retornar->direita = remover->direita;
                retornar->esquerda = remover->esquerda;
                aux->esquerda = NULL;
            }
            else if(aux->esquerda->direita != NULL){ //mais a esquerda tem filho a direita
                retornar = aux->esquerda;
                aux->esquerda = retornar->direita;
                retornar->direita = remover->direita;
                retornar->esquerda = remover->esquerda;
            }
        free(remover);
        return retornar;
        }
        else{
            aux->esquerda = remover->esquerda;
            free(remover);
            return aux;
        }
    }
    return NULL;
}

void Busca(Tno *raiz, char excluir, int fexcluir){
    Tno *anterior, *remover;
    anterior = NULL;
    remover = raiz;

    while(remover != NULL){
        if(remover->letra == excluir){
            if(remover == raiz){
                raiz = Remover(remover);
                return;
            }
            else{
                if(remover == anterior->direita){
                    anterior->direita = Remover(remover);
                    return;
                    }
                if(remover == anterior->esquerda){
                    anterior->esquerda = Remover(remover);
                    return;
                }
            }
        }
        anterior = remover;
        if(fexcluir < remover->num) remover = remover->esquerda;
        else if(fexcluir >= remover->num) remover = remover->direita;
    }
}

void ImprimeEM(Tno *existente){
    if(existente == NULL) return;
    ImprimeEM(existente->esquerda);
    printf("%c", existente->letra);
    ImprimeEM(existente->direita);
}


int main(){

    Tarvore arvore;
    Inicializa(&arvore);

    Tno no;

    char um, dois;
    scanf("%c %c", &um, &dois);



    char string[1025];
    scanf("%s", string);

    int tamanho = strlen(string);
    int i, j, fum, fdois;
    int cont[26];


    for(i=0; i<26; i++) cont[i] = 0; // inicializa contador

    for(i=0; i<tamanho; i++){
        j=toupper(string[i]);
        if (j>=65 && j<=90) cont[j-65]++;
    }

    for(i=0; i<26; i++){
        if (cont[i]>0){
            char c = i+65;
            no.letra = c;
            no.num = cont[i];
            Insere(&arvore, no);
            if(no.letra == um) fum = no.num;
            if(no.letra == dois) fdois = no.num;
        }
    }

    Busca(arvore.raiz, um, fum);
    Busca(arvore.raiz, dois, fdois);
    ImprimeEM(arvore.raiz);



    return 0;
}
