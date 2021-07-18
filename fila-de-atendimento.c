#include <stdio.h>
#include <stdlib.h>

typedef struct Titem{
    int id;
    int tempo;
    struct Titem *prox;
}Titem;

typedef struct Tfila{
    Titem *inicio;
    Titem *fim;
    int tempo;
    int tamanho;
}Tfila;

void InicializaFila(Tfila *fila, int A){
    int i;
    for(i=0; i<A; i++){
        fila[i].inicio = NULL;
        fila[i].fim = NULL;
        fila[i].tempo = 0;
        fila[i].tamanho = 0;
    }
}


void InserePrimeiros(Tfila *fila, Titem novocliente, int i){
    Titem *aux = malloc(sizeof(Titem));
    *aux = novocliente;

        if(fila[i].fim == NULL){
            fila[i].fim = aux;
            fila[i].inicio = aux;
            fila[i].tempo = aux->tempo;
            fila[i].tamanho ++;
        } //coloca os primeiros de cada fila
}

int Menor(Tfila *fila, int A){

    int j=0;
    int menor = fila[j].tempo;
    int idmenor = j;

    for(j=1; j<A; j++){
        if(fila[j].tempo < menor){
            menor = fila[j].tempo;
            idmenor = j;
        }
    }
    return idmenor;
}



void InserirFila(Tfila *fila, Titem novocliente, int A){

    Titem *aux = malloc(sizeof(Titem));
    *aux = novocliente;

    int i = Menor(fila, A);

            fila[i].fim->prox = aux;
            fila[i].fim = aux;
            fila[i].tempo += aux->tempo;
            fila[i].tamanho ++;
}


Titem RemoverFila(Tfila *fila, int j){

    Titem item = (*fila[j].inicio);
    Titem *aux = fila[j].inicio->prox;

    free(fila[j].inicio);
    fila[j].tamanho --;
    fila[j].inicio = aux;

    return item;
}


int main(){
    int N;
    scanf("%d", &N); // clientes

    int A;
    scanf("%d", &A); // atendentes

    Tfila fila[A];
    InicializaFila(fila, A);

    Titem cliente;

    int i;

    for(i=0; i<A; i++){
        cliente.id = i+1;
        scanf("%d", &cliente.tempo);
        InserePrimeiros(fila, cliente, i);
    } // le primeiros cliente e ja insere

    for(i=A; i<N; i++){
        cliente.id = i+1;
        scanf("%d", &cliente.tempo);
        InserirFila(fila, cliente, A);
    } // le e insere o restante


    int j;
    Titem recebe;
    for(j=0; j<A; j++){
        int at = j+1;
        printf("%d: ", at);
        int tam;
        tam = fila[j].tamanho;
        for(i=0; i<tam; i++){
            recebe = RemoverFila(fila, j);
            printf("%d ", recebe.id);

        }
        printf("\n");
    }







    return 0;
}
