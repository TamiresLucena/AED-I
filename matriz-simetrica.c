#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//i linhas, j colunas

int **CriaMatriz (int N){

    int i,j;

    int **ponteiroMatriz;
    ponteiroMatriz = malloc(N*sizeof(int*));

    for(i=0; i<N; i++){
        ponteiroMatriz[i] = malloc(i*sizeof(int));
    }

    for(i=0; i<N; i++){
        for(j=i; j<N; j++){
            ponteiroMatriz[i][j] = rand() %100;
        }
    }
    return ponteiroMatriz;
}


int LerElemento(int i, int j, int N, int **matriz)
{
    int aux;
    if(i>=N || j>=N){
        return 0;
    }

    else if(i>j){
        aux = i;
        i = j;
        j = aux;
    }
    return matriz[i][j];
}


int AlteraValor(int i, int j, int N, int **matriz)
{
    int valor, aux;
    if(i>=N || j>=N){
        return 0;
    }

    else if(i>j){
        aux = i;
        i = j;
        j = aux;
    }
    printf("Insira o novo valor para posicao [%d][%d] da matriz: \n", j, i);
    scanf("%d", &valor);

    matriz[i][j] = valor;
    return valor;
}



int main(){

    int N, i, j;

    printf("Quantidade de linhas/colunas da matriz: ");
    scanf("%d", &N);

    int **matriz;
    matriz = CriaMatriz(N);

    for(i=0; i<N; i++){
        for(j=0; j<N; j++){
            if(i>j) printf("%d ", matriz[j][i]);
            else printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }


    printf("Insira a posicao [i][j] da matriz para leitura: ");
    scanf("%d %d", &i, &j);

    int leitura;
    leitura = LerElemento(i, j, N, matriz);
    if(leitura==0) printf("Posicao Invalida!\n");
    else printf("O valor acessado e: %d\n", leitura);


    printf("Insira a posicao [i][j] da matriz para alteracao: ");
    scanf("%d %d", &i, &j);

    int alteracao;
    alteracao = AlteraValor(i, j, N, matriz);
    if(alteracao==0) printf("Posicao Invalida!\n");
    else printf("O valor %d foi inserido na posicao [%d][%d]\n", alteracao, i, j);


    printf("Nova Matriz:\n");

    for(i=0; i<N; i++){
        for(j=0; j<N; j++){
            if(i>j) printf("%d ", matriz[j][i]);
            else printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
    return 0;
}
