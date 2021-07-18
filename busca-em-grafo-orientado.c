// Tamires Lucena 111866

#include <stdio.h>
#include <stdlib.h>

typedef struct Titem{
    int dado;
    struct Titem *proximo;
}Titem;

typedef struct Tfila{
    Titem *inicio;
    Titem *fim;
    int tamanho;
}Tfila;

void InicializaFila(Tfila *fila){
    fila->inicio = NULL;
    fila->fim = NULL;
    fila->tamanho = 0;
}

void InsereFila(Tfila *fila, Titem item){
    Titem *aux = malloc(sizeof(Titem));
    *aux = item;
    aux->proximo = NULL;

    if(fila->inicio == NULL){
        fila->inicio = aux;
        fila->fim = aux;
        fila->tamanho ++;
    }
    else{
        fila->fim->proximo = aux;
        fila->fim = aux;
        fila->tamanho ++;
    }
}

Titem RemoverFila(Tfila *fila){

    Titem item = (*fila->inicio);
    Titem *aux = fila->inicio->proximo;

    free(fila->inicio);
    fila->tamanho --;
    fila->inicio = aux;

    return item;
}


typedef struct Tvertice{
    int dado;
    struct Tvertice *proximo;
}Tvertice;

typedef struct TlistaAdj{
    int tamanho;
    Tvertice **adjacente;
}TlistaAdj;

void Inicializa(TlistaAdj *lista, int N){
    lista->adjacente = malloc(N*sizeof(Tvertice*));
    lista->tamanho = N;

    int i;
    for(i=0;i<N; i++){
        lista->adjacente[i] = NULL;
    }
}

void Insere(TlistaAdj *lista, int vertice, int info){
    Tvertice *aux = malloc(sizeof(Tvertice));
    aux->dado = info;
    aux->proximo = NULL;

    if(lista->adjacente[vertice] == NULL) lista->adjacente[vertice] = aux;

    else if(lista->adjacente[vertice] != NULL){
        if(lista->adjacente[vertice]->dado > aux->dado){
            aux->proximo = lista->adjacente[vertice];
            lista->adjacente[vertice] = aux;
        }
        else{
            Tvertice *percorre = lista->adjacente[vertice];
            while (percorre->proximo != NULL && percorre->proximo->dado < aux->dado){//enquanto acontece, só percorre ainda
            percorre = percorre->proximo;
            }
            aux->proximo = percorre->proximo;
            percorre->proximo = aux;
        }
    }
}

void BuscaLargura(TlistaAdj *lista, int V){
    int *visitado = malloc(lista->tamanho*sizeof(int)); // tenho duvida aqui
    int i;
    for(i=0; i<lista->tamanho; i++){
        visitado[i] = 0;
    }

    int total = 0;

    Tfila fila;
    InicializaFila(&fila);

    visitado[V] = 1;


    Titem item;

    item.dado = V;
    InsereFila(&fila, item);

    Titem removido;
    Tvertice *percorre;

    while (fila.inicio != NULL){
        removido = RemoverFila(&fila);
        printf("%d ", removido.dado);

        percorre = lista->adjacente[removido.dado];
        while (percorre != NULL){
            if(!visitado[percorre->dado]){
                visitado[percorre->dado] = 1;
                item.dado = percorre->dado;
                InsereFila(&fila, item);
            }
            percorre = percorre->proximo;
        }
    }
    printf("\n");
}

void BP(TlistaAdj *lista, int V, int *visitado){

    visitado[V] = 1;
    printf("%d ", V);
    Tvertice *percorre = lista->adjacente[V];
    while (percorre != NULL) {
        if (! visitado [percorre->dado]){
            BP(lista, percorre->dado, visitado);
        }
        percorre= percorre->proximo;
    }
}

void BuscaProfundidade(TlistaAdj *lista, int V){

    int *visitado = malloc(lista->tamanho*sizeof(int));
    int i;
    for(i=0; i<lista->tamanho; i++) visitado[i] = 0;
    BP(lista, V, visitado);
    printf("\n");
}



int main(){
    int V;
    scanf("%d", &V);

    int N, M;
    scanf("%d %d", &N, &M);

    TlistaAdj lista;
    Inicializa(&lista, N);

    int i;
    int vertice, info;
    for(i=0; i<M; i++){
        scanf("%d %d", &vertice, &info);
        Insere(&lista, vertice, info);
    }

    BuscaLargura(&lista, V);
    BuscaProfundidade(&lista, V);



    return 0;
}
