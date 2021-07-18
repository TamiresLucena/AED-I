#include <stdio.h>
#include <stdlib.h>


int ContaString(char *string){
    int i=0;
    while(string[i]!='\0') i++;

    return i
}

int main()
{
    int X, Y, i;
    char C;
    char *stringum, *stringdois;

    scanf("%d %d %c", &X, &Y, &C);

    stringum = malloc(X*sizeof(char));
    stringdois = malloc(Y*sizeof(char));

    scanf(" %s %s", stringum, stringdois);

    int tamanhoum = ContaString(stringum);
    int tamanhodois = ContaString(stringdois);
    int tamanhototal = tamanhoum + tamanhodois;

    char *stringtotal;
    stringtotal = malloc(tamanhototal*sizeof(char));


    for(i=0; i<=tamanhoum; i++){
        stringtotal[i] = stringum[i];
    }
    for(i=0; i<=tamanhodois; i++){
        stringtotal[tamanhoum+i] = stringdois[i];
    }


    int quantidadeCarac=0;
    for(i=0;i<tamanhototal;i++){
        if(stringtotal[i]==C)
            quantidadeCarac ++;
    }

    printf("%s\n", stringtotal);
    printf("%d\n", tamanhototal);
    printf("%d", quantidadeCarac);


    return 0;
}
