#include <stdio.h>
#include <stdlib.h>
// exercício e análise de complexidade ListaDuplamenteEncadeada

typedef struct no{
    int valor;
    struct no *prox;
    struct no *ant;
}NO;

NO *inicio = NULL;
NO *fim = NULL;
int tam = 0;

void adicionar(int valor, int pos){
        NO *novo = (NO*) malloc (sizeof (NO));
        novo->valor = valor;
        novo->prox = NULL;
        novo->ant = NULL;
    
        if(inicio == NULL){ //lista vazia :D
            inicio = novo;
            fim = novo;
        }else if(pos == 0){ //inicio - CONSTANTE <3
            novo->prox = inicio;
            inicio->ant = novo; //novidade
            inicio = novo;
        }else if(pos == tam){ //fim - CONSTANTE <3
            fim->prox = novo;
            novo->ant = fim; //novidade
            fim = novo;
        }else{ // "no meio" - busca :/ - LINEAR
            NO *aux = inicio;
            for(int i=0; i<pos; i++){
                aux = aux->prox;
            }
            novo->prox = aux;
            aux->ant->prox = novo;
            novo->ant = aux->ant;
            aux->ant = novo;
        }
        tam++;
    
}



void remover(int pos){
    
  if(pos >=0 && pos < tam){
    
    if(tam == 1){//1 elemento - CONSTANTE
        NO* lixo = inicio;
        inicio = NULL;
        fim= NULL;
        free(lixo);
    }else if(pos == 0){ //inicio - CONSTANTE
            NO* lixo = inicio;
            inicio = inicio->prox;
            inicio->ant = NULL; //novidade
            free(lixo);
    }else if(pos == tam -1){ //fim :o -> CONSTANTE <3 <3 <3
            NO *lixo = fim;
            fim->ant->prox = NULL;
            fim = fim->ant;
            free(lixo);
    }else{
            NO *aux = inicio;
            for(int i=0; i<pos; i++){
                aux = aux->prox;
            }
            aux->ant->prox = aux->prox;
            aux->prox->ant = aux->ant;
            free(aux);
    }
      tam--;
  }
}

void imprimir(){
    NO* aux = inicio;
    for(int i=0; i<tam; i++){
        printf("%d ", aux->valor);
        aux = aux->prox;
    }
}


int main(){
    adicionar(8,0);
    adicionar(2,0);
    adicionar(5,1);
    adicionar(4,3);
    adicionar(7,4);
    remover(4);
    imprimir();
    return 0;
}



