#include <stdio.h>
#include <stdlib.h>
//exercício sobre pilha com operação de soma dos números da pilha

typedef struct no
{
    int id;
    struct no *prox;
}NO;


NO* inicio= NULL;
int tam= 0;
int soma= 0;

void adicionar(int id)
{
    
    NO *novo = malloc (sizeof(NO));
    novo->id = id;
    novo->prox = NULL;
    
    if(tam == 0)
    {
        inicio = novo;
    }
    else
    {
        novo->prox= inicio;
        inicio= novo;
    }
    tam++;
}

int remover()
{
    if(tam > 0)
    {
        NO *lixo = inicio;
        if(tam == 1)
        {
            inicio = NULL;
        }
        else
        {
            inicio = inicio->prox;
        }
        int aux = inicio->id;
        free(lixo);
        tam--;
        return aux;
    }
    else
    {
        printf("pilha esta vazia :/\n");
        return -1;
    }
}
    
int imprimir(NO *aux)
{
    if(aux!=NULL) 
    {
        soma+= aux->id;
        imprimir(aux->prox);
    }

return soma;
}

int main()
{
    adicionar(10);
    adicionar(7);
    adicionar(5);
    adicionar(3);
    remover();
    remover();
    adicionar(8);
    printf("soma: %d",imprimir(inicio));
 
}



