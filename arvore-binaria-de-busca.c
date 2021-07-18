// Tamires Lucena 111866

#include <stdio.h>
#include <stdlib.h>

typedef struct Tno{
    int num;
    struct Tno *esquerda;
    struct Tno *direita;
}Tno;

typedef struct Tarvore{
    Tno *raiz;
}Tarvore;

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

    if(arvore->raiz == NULL) arvore->raiz = aux;
    else Verifica(arvore->raiz, aux);
}

void ImprimePRE(Tno *existente){
    if(existente == NULL) return;
    printf("%d ", existente->num);
    ImprimePRE(existente->esquerda);
    ImprimePRE(existente->direita); // depois do return
}

void ImprimeEM(Tno *existente){
    if(existente == NULL) return;
    ImprimeEM(existente->esquerda);
    printf("%d ", existente->num);
    ImprimeEM(existente->direita);
}

void ImprimePOS(Tno *existente){
    if(existente == NULL) return;
    ImprimePOS(existente->esquerda);
    ImprimePOS(existente->direita);
    printf("%d ", existente->num);
}

void ImprimeBusca(Tno *existente, int V){
    printf("%d ", existente->num);
    if(existente->num == V) return;
    else if(V < existente->num) ImprimeBusca(existente->esquerda, V);
    else if(V > existente->num) ImprimeBusca(existente->direita, V);
}

int Altura(Tno *existente){
   if(existente == NULL)
      return -1;
   else {
      int esq = Altura(existente->esquerda);
      int dir = Altura(existente->direita);
      if (esq < dir) return dir + 1;
      else return esq + 1;
   }
}

int main()
{
    int N, V;
    scanf("%d", &N);
    scanf("%d", &V);

    int i;
    Tno no;
    Tarvore arvore;
    Inicializa(&arvore);
    int vesetem = 0;

    for(i=0; i<N; i++){
        scanf("%d", &no.num);
        Insere(&arvore, no);
        if(V == no.num) vesetem ++;
    }

    ImprimePRE(arvore.raiz);
    printf("\n");
    ImprimeEM(arvore.raiz);
    printf("\n");
    ImprimePOS(arvore.raiz);
    printf("\n");

    if(vesetem == 0) printf("-1");
    else ImprimeBusca(arvore.raiz, V);
    printf("\n");

    int altura = Altura(arvore.raiz);
    printf("%d", altura);

    return 0;
}
