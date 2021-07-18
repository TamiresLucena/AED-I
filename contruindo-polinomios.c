                                                                                                    v#include <stdio.h>
#include <stdlib.h>

typedef struct Titem{ // monomio
    int coef;
    int exp;
}Titem;

typedef struct Tlista{ // lista de mononio = polinomio
    Titem *item;
    int tamanho;
}Tlista;

int InicializaLista(Tlista *lista, int N){
    lista->item = malloc(N * sizeof(Titem));
    lista->tamanho = 0;
return 0;
}

void LerInfo(Tlista *lista, int N){
    int i;
    Titem novo;
    for(i=0; i<N; i++){
        scanf("%d %d", &novo.coef, &novo.exp);
        Inserir(lista, novo);
    }
}

void Inserir(Tlista *lista, Titem item){
    int i, e;

    e = Buscar(lista, item);

    if (e == -1){
        lista->item[lista->tamanho] = item;
        lista->tamanho++;
    }
    else{
        if (lista->item[e].coef + item.coef == 0){
            Remover(lista, e);
        }
        else{
            lista->item[e].coef += item.coef;
        }
    }
}

int Buscar(Tlista *lista, Titem novo){
    int e = -1, i;
    for (i = 0; i < lista->tamanho; i++){
        if (novo.exp == lista->item[i].exp)
            e = i;
    }
    return e;
}

void Remover(Tlista *lista, int posicao)
{
    int i;
    Titem aux = lista->item[posicao];
    for (i = posicao; i < lista->tamanho-1; i++)
        lista->item[i] = lista->item[i+1];

    lista->tamanho--;
}

void Ordena(Tlista *lista){
    int i, j;
    Titem aux;
        for(i=0; i< lista->tamanho; i++){
            for (j=i+1; j<lista->tamanho; j++){
                if(lista->item[j].exp > lista->item[i].exp){
                    aux = lista->item[j];
                    lista->item[j] = lista->item[i];
                    lista->item[i] = aux;
                }
            }
        }
}


int Imprime(Tlista *lista){
    if(lista->tamanho == 0) printf("nulo");
     int i;
     for(i=0; i<lista->tamanho; i++)
        printf("%d %d ", lista->item[i].coef,lista->item[i].exp);

    printf("\n%d", lista->tamanho);
 return 0;
}

int main(){

    int N;
    scanf("%d", &N);


    Tlista lista;
    Titem item;

    InicializaLista(&lista, N);
    LerInfo(&lista, N);
    Ordena(&lista);
    Imprime(&lista);

return 0;
}
