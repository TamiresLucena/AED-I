#include <stdio.h>
#include <stdlib.h>

int *RetornaPonteiro (int *vetor, int N){
  int i, pares=0;

  int *vetorpar;
   vetorpar = (int*)malloc(sizeof(int));

  for(i=0;i<N;i++){
    if(vetor[i]%2==0)
    {
        vetorpar[pares] = vetor[i];
        pares++;
        vetorpar = (int*)realloc(vetorpar, (pares+1)*sizeof(int));
    }
  }


   printf("numeros pares: %d\n", pares);

   return vetorpar;

  }


int main()
{
    int i, N, pares = 0;
    printf("Quantidade de numeros do vetor: ");
    scanf("%d", &N);
    int vetor[N];

    for(i=0;i<N;i++){
        vetor[i] = rand() % 100;
        if (vetor[i]%2==0) pares++;
    }


    for(i=0;i<N;i++){
        printf("vetor[%d] = %d\n", i, vetor[i]);
    }

    int *retorno;
    retorno = RetornaPonteiro(vetor, N);

    for(i=0;i<pares;i++){
        printf("vetorpar[%d] = %d\n", i, retorno[i]);
    }

    return 0;
}
