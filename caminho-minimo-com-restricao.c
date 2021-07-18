#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define INF INT_MAX
#define MAX 1024

typedef struct Titem{
    int dado;
    struct Titem *prox;
}Titem;

typedef struct Tpilha{
    Titem *topo;
}Tpilha;

void InicializaPilha(Tpilha *pilha){
    pilha->topo = NULL;
}

void InserePilha(Tpilha *pilha, int dado){
    Titem *aux = malloc(sizeof(Titem));
    aux->dado = dado;
    aux->prox = pilha->topo;
    pilha->topo = aux;
}

int RemovePilha(Tpilha *pilha){
    int removido;
    removido = pilha->topo->dado;
    pilha->topo = pilha->topo->prox;

    return removido;
}

typedef struct Tfila{
    Titem *inicio, *fim;
} Tfila;

void InicializaFila(Tfila *fila){
    fila->inicio = NULL;
    fila->fim = NULL;
}

void InsereFila(Tfila *fila, int novo){
    Titem *aux = malloc(sizeof(Titem));
    aux->prox = NULL;
    aux->dado = novo;

    if(fila->inicio = NULL) fila->inicio = aux;
    else{
        fila->fim->prox = aux;
        fila->fim = aux;
    }
}

int RemoveFila(Tfila *fila){
    int removido = fila->inicio->dado;
    fila->inicio = fila->inicio->prox;

    return removido;
}

typedef struct Tvertice{
    int dado;
    int peso;
    struct Tvertice *prox;
}Tvertice;

typedef struct TlistaAdj{
    int tamanho;
    Tvertice **adj;
}TlistaAdj;

void InicializaLista(TlistaAdj *lista, int N){
    lista->adj = malloc(N*sizeof(Tvertice*));
    lista->tamanho = N;

    int i;
    for(i=0; i<N; i++){
        lista->adj[i] = NULL;
    }
}

void InsereLista(TlistaAdj *lista, int v1, int v2, int P){
    Tvertice *aux = malloc(sizeof(Tvertice));
    aux->dado = v2;
    aux->peso = P;
    aux->prox = NULL;

    if (lista->adj[v1] == NULL) lista->adj[v1] = aux;

    else if(lista->adj[v1] != NULL){
        if(aux->dado < lista->adj[v1]->dado){
            aux->prox = lista->adj[v1];
            lista->adj[v1] = aux;
        }
        else{
            Tvertice *percorre = lista->adj[v1];
            while (percorre->prox != NULL && aux->dado > percorre->prox->dado){
            percorre = percorre->prox;
            }
            aux->prox = percorre->prox;
            percorre->prox = aux;
        }
    }
}

void OrdenacaoTopologica(TlistaAdj *lista, int v, int *visitados, Tpilha *pilha){
        visitados[v] = 1;

        Tvertice *percorre = lista->adj[v];
        while(percorre != NULL){
            if(visitados[percorre->dado] == 0) OrdenacaoTopologica(lista, percorre->dado, visitados, pilha);

            percorre = percorre->prox;
        }

        InserePilha(pilha, v);
}

void Relax(int removido, int dado, int peso, int *dist, int R){
    if(dist[dado] > dist[removido] + peso && peso <= R) dist[dado] = dist[removido] + peso;
}

void DistanciaMinima(TlistaAdj *lista, int V, int N, int R){
    Tpilha pilha;
    InicializaPilha(&pilha);

    int *dist = malloc(N*sizeof(int));
    int *visitados = malloc(N*sizeof(int));
    int i;

    for(i=0; i<N; i++){
        visitados[i] = 0;
        dist[i] = INF;
    }
    dist[V] = 0; // distancia entre o busca e ele mesmo

    for(i=V; i<N; i++){
        if(visitados[i] == 0) OrdenacaoTopologica(lista, i, visitados, &pilha);
    }

    Tvertice *percorre;

    while(pilha.topo != NULL){
        int removido = RemovePilha(&pilha);
        percorre = lista->adj[removido];

        if(dist[ xc removido] != INF){
            while(percorre != NULL){
                Relax(removido, percorre->dado, percorre->peso, dist, R);
                percorre = percorre->prox;
            }
        }
    }

    for(i=0; i<N; i++){
        if(dist[i] == INF) printf("INF ");
        else printf("%d ", dist[i]);
    }
    printf("\n");
}

void buscaProfundidade(TlistaAdj *lista, int busca, int *visitados){
    visitados[busca] = 1;
    printf("%d ", busca);

    Tvertice *p;
    p = lista->adj[busca];
    while(p != NULL){
        if(visitados[p->dado] == 0) buscaProfundidade(lista, p->dado, visitados);
        p = p->prox;
    }
}

void IniciaBP(TlistaAdj *lista, int busca){
    int *visitados = malloc(lista->tamanho*sizeof(int));
    int i;
    for(i=0; i<lista->tamanho; i++) visitados[i] = 0;

    buscaProfundidade(lista, busca, visitados);

}

void BuscaLargura(TlistaAdj *lista, int busca){
    int *visitados = malloc(lista->tamanho*sizeof(int));
    int i;
    for(i=0; i<lista->tamanho; i++) visitados[i] = 0;

    Tfila *fila;
    InicializaFila(fila);

    visitados[busca] =1;
    InsereFila(fila, busca);

    while(fila->inicio != NULL){
        int removido = RemoveFila(fila);
        printf("%d", removido);
        Tvertice *p = lista->adj[removido];
        while(p != NULL){
            if(visitados[p->dado] == 0){
                visitados[p->dado] = 1;
                InsereFila(fila, p->dado);
             }
            p = p->prox;
        }

    }
}

int main(){

    int busca;
    scanf("%d", &busca);

    int R;
    scanf("%d", &R);

    int N, M;
    scanf("%d %d", &N, &M);

    TlistaAdj lista;
    InicializaLista(&lista, N);

    int P, v1, v2, i;

    for(i=0; i<M; i++){
        scanf("%d %d %d", &v1, &v2, &P);
        InsereLista(&lista, v1, v2, P);
    }

    DistanciaMinima(&lista, busca, N, R);
    IniciaBP(&lista, busca);
    BuscaLargura(&lista, busca);

   return 0;
}
