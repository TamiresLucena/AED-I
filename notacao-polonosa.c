                      #include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

typedef struct Tpilha{
    char item[MAX];
    int topo;
}Tpilha;

void Inicializar(Tpilha *pilha){
    pilha->topo = -1;
}

int PilhaVazia(Tpilha *pilha){
    if(pilha->topo == -1)
        return 1;
    return 0;
}

void Empilhar(Tpilha *pilha, char novoitem){
    pilha->topo ++;
    pilha->item[pilha->topo] = novoitem;
}

char Desempilhar(Tpilha *pilha){
    char valor;
    valor = pilha->item[pilha->topo];
    pilha->topo --;
    return valor;
}

void PreencheExpressao(char expressao[]){
    scanf("%s", expressao);
}

char topoDaPilha(Tpilha *pilha){  // Retorna o topo da pilha sem retirar o elemento do topo. (lê)
    return pilha->item[pilha->topo];
}

int precedenciaNivel(char topo2){
    if (topo2=='+'||topo2=='-')
        return 2;
    else if (topo2 =='*'|| topo2 == '/')
        return 1;
    else
        return 3;
}

int ConverteExpressao(char expressao[], char expressaoRPN[]){
    int i, tamanho;
    int j=0;
    char topo2=0;
    Tpilha pilha;
   int pabre=0, pfecha=0;

    Inicializar(&pilha);
    PreencheExpressao(expressao);
    tamanho = strlen(expressao);

    if(expressao[0] == ')'){
        printf("Invalid Expression\n");
    }

    else{
    for (i=0;i<tamanho;i++){
        if (expressao[i]>47 && expressao[i]<58){ // se for numero
            expressaoRPN[j] = expressao[i];
            j++;
        }

        else if (expressao[i]=='('){
            pabre ++;
            Empilhar(&pilha,'(');
        }

        else if (expressao[i] == '+' || expressao[i] == '-' || expressao[i] == '*' || expressao[i] == '/' ){
            if (!PilhaVazia(&pilha))
            {
                topo2 = topoDaPilha(&pilha);//ve o topo atual sem tirar

                if (precedenciaNivel(topo2)>=precedenciaNivel(expressao[i])){ // compara o topo antigo com o que vai ser inserido
                    if(topo2 == '('){
                        Desempilhar(&pilha);
                        Empilhar(&pilha, expressao[i]);
                    }
                    else{
                    expressaoRPN[j] = Desempilhar(&pilha);
                    j++;
                    Empilhar(&pilha, expressao[i]);
                    } // se for parenteses
                }
                else
                    Empilhar(&pilha, expressao[i]);
            }
            else
                Empilhar(&pilha, expressao[i]); // se a pilha for vazia
        }

        else if(expressao[i]==')'){
            pfecha++;
            topo2 = topoDaPilha(&pilha);
            if (topo2!='('){
                expressaoRPN[j] = Desempilhar(&pilha);
                j++;
            }
            else{
                Desempilhar(&pilha);

            }
        } // fim do else if
    } // fim do for
    expressaoRPN[j] = Desempilhar(&pilha);
    expressaoRPN[j+1] = '\0';
    if(pabre != pfecha){
        return 1;
    }// n balenceado
    }//ELSE
    return 0;
} // fim da conversão

void imprimeResultado(char expressaoRPN[]){
    int i;
    for (i = 0; i<strlen(expressaoRPN); i++){
        //if (expressaoRPN[i] != '(' && expressaoRPN[i] != ')') //não printa parenteses NAO PRECISA
            printf("%c", expressaoRPN[i]);
    }
    printf("\n");
}



typedef struct Tintpilha{
    int item[MAX];
    int topo;
}Tintpilha; // 2 pilha

void InicializarInt(Tintpilha *intpilha){
    intpilha->topo = -1;
}// 2 pilha

int PilhaVaziaint(Tintpilha *pilha){
    if(pilha->topo == -1)
        return 1;
    return 0;
}

void EmpilharInt(Tintpilha *intpilha, int novoitem){
    intpilha->topo ++;
    intpilha->item[intpilha->topo] = novoitem;
} // 2pilha

int DesempilharInt(Tintpilha *intpilha){
    int valor; // a ser desempilhado
    valor = intpilha->item[intpilha->topo];
    intpilha->topo --;
    return valor;
}// 2 pilha


int main(){

    char expressao[MAX];
    char expressaoRPN[MAX];

    if(ConverteExpressao(expressao, expressaoRPN) == 1){
        printf("Unbalanced Parenthesis\n");
    }

    else{



        Tintpilha intpilha;

        int i;
        InicializarInt(&intpilha);

        int tam = strlen(expressaoRPN);
        int numeroprapilha[tam];
        int erro = 0;

        for(i=0; i<tam; i++)
        {
            if (expressaoRPN[i] >= '0' && expressaoRPN[i] <= '9')
                EmpilharInt(&intpilha, expressaoRPN[i]-48);
            else
            {
                int a, b, resultado;
                if (!PilhaVaziaint(&intpilha))
                    b = DesempilharInt(&intpilha);
                else
                {
                    printf("Invalid Expression\n");
                    erro = 1;
                    break;
                }
                if (!PilhaVaziaint(&intpilha))
                    a = DesempilharInt(&intpilha);
                else
                {
                    printf("Invalid Expression\n");
                    erro = 1;
                    break;
                }

                switch (expressaoRPN[i])
                {
                    case '+':
                        EmpilharInt(&intpilha, (a+b));
                    break;

                    case '-':
                        EmpilharInt(&intpilha, (a-b));
                    break;

                    case '*':
                        EmpilharInt(&intpilha, (a*b));
                    break;

                    case '/':
                        EmpilharInt(&intpilha, (int)(a/b));
                    break;
                }
            }
        } // converti pra int com tabela ASCII

        if (!erro && intpilha.topo == 0)
        {
            imprimeResultado(expressaoRPN);
            printf("%d", intpilha.item[intpilha.topo]);
        }
        else
            if (erro == 0)
                printf("Invalid Expression\n");
    }

    return 0;
}
