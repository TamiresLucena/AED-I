// Tamires Lucena 111866

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Tno{
    char string[1024];
    struct Tno *filho;
    struct Tno *irmao;
}Tno;

typedef struct Tarvore{
    Tno *raiz;
}Tarvore;

void Inicializa(Tarvore *arvore){
    arvore->raiz = NULL;
}

void Insere(Tno *raiz, Tno *aux, char *pai){
    if(strcmp(pai, raiz->string) == 0){
        aux->irmao = raiz->filho;
        raiz->filho = aux;
        //printf("inseriu\n");
        return;
    }
    //printf("tamo procurano\n");
    Tno *procura;
    procura = raiz->filho;
    while(procura != NULL){
        Insere(procura, aux, pai);
        procura = procura->irmao;
    }
}

void CriaNo(Tarvore *arvore, char *arquivo, char *pai){
    Tno *aux = malloc(sizeof(Tno));
    strcpy(aux->string, arquivo);
    aux->filho = NULL;
    aux->irmao = NULL;

    //printf("alocou\n");
    if(arvore->raiz == NULL) arvore->raiz = aux;
    else Insere(arvore->raiz, aux, pai);
}

void Mover(Tarvore *arvore, Tno *raiz, char *arquivo, char *pai){
    if(raiz->filho != NULL && strcmp(arquivo, raiz->filho->string) == 0){
        Tno *muda = raiz->filho;
        raiz->filho = raiz->filho->irmao;
        muda->irmao = NULL;
        Insere(arvore->raiz, muda, pai);
        //printf("moveu\n");
        return;
    }

     if(raiz->irmao != NULL && strcmp(arquivo, raiz->irmao->string) == 0){
        Tno *muda = raiz->irmao;
        raiz->irmao = raiz->irmao->irmao;
        muda->irmao = NULL;
        Insere(arvore->raiz, muda, pai);
        //printf("moveu\n");
        return;
    }

    Tno *procura;
    procura = raiz->filho;
    while(procura != NULL){
        Mover(arvore, procura, arquivo, pai);
        procura = procura->irmao;
    }
}

void Remover(Tno *raiz, char *arquivo){
    if(raiz->filho != NULL && strcmp(arquivo, raiz->filho->string) == 0){
        Tno *excluir = raiz->filho;
        raiz->filho = raiz->filho->irmao;
        free(excluir);
        //printf("removeu\n");
        return;
    }

    if(raiz->irmao != NULL && strcmp(arquivo, raiz->irmao->string) == 0){
        Tno *excluir = raiz->irmao;
        raiz->irmao = raiz->irmao->irmao;
        free(excluir);
        return;
    }

    Tno *procura;
    procura = raiz->filho;
    while(procura != NULL){
        Remover(procura, arquivo);
        procura = procura->irmao;
    }

}

int Imprime(Tno *raiz, char *string){
    int achou;
    if(strcmp(string, raiz->string) == 0){
        printf("%s ", raiz->string);
        return 1;
    }

    Tno *procura;
        procura = raiz->filho;
        while(procura != NULL){
            achou = Imprime(procura, string);
            if(achou == 1){
                printf("%s ",raiz->string);
                return 1;
            }
            procura = procura->irmao;
        }
    return 0;
}



int main(){

    int N;
    scanf("%d", &N);

    char string[1024];
    scanf("%s", string);

    Tarvore arvore;
    Inicializa(&arvore);

    CriaNo(&arvore, "\\root", "\0");

    int i;
    char funcao[3];
    char pai[1024];
    char arquivo[1024];

    for(i=0; i<N; i++){

        scanf("%s %s", funcao, arquivo);
        if(funcao[1] == 'a' || funcao[1] == 'm') scanf("%s", pai);

        if(funcao[1] == 'a') CriaNo(&arvore, arquivo, pai);
        else if (funcao[1] == 'm') Mover(&arvore, arvore.raiz, arquivo, pai);
        else if (funcao[1] == 'r') Remover(arvore.raiz, arquivo);


    }

    int a = Imprime(arvore.raiz, string);
    if(a == 0) printf("Arquivo nao encontrado!\n");


 return 0;
}
