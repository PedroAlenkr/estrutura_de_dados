#include <stdio.h>
#include <stdlib.h>
//exercício sobre árvore binária sem balanceamento

typedef struct no{
    int chave;
    //...
    struct no *esq;
    struct no *dir;
}NO;

NO* raiz = NULL;

NO* busca(int x, NO *aux){
    
    //1 - caso: arvore esta vazia
    if(aux == NULL){
        return NULL;
    //2 - caso: encontrei a chave
    }else if(x == aux->chave){
        return aux;
    //3 - caso: não encontrei preciso buscar no resto da arvore
    }else if(x < aux->chave){ //busca na subarvore esq
        
        if(aux->esq != NULL){
            return busca(x, aux->esq);
        }else{
            return aux; //nao encontrei, mas ele deveria estar no lado esq do aux
        }
    }else{//busca na subarvore dir
        
        if(aux->dir != NULL){
            return busca(x, aux->dir);
        }else{
            return aux; //nao encontrei, mas ele deveria estar no lado dir do aux
        }
    }
}


NO* busca_arvore(x){
    NO *resp = busca(x, raiz);
    if(resp->chave != x){
        return NULL;
    }else{
        return resp;
    }
}

void add(int x){
    
    if(raiz == NULL){
        NO* novo = malloc (sizeof(NO*));
        novo->chave = x;
        novo->esq = NULL;
        novo->dir = NULL;
        raiz = novo;
    }else{
        NO *resp = busca(x, raiz);
        if(resp->chave != x){ // eu posso adicionar - resp pai do NO novo
            NO* novo = malloc (sizeof(NO*));
            novo->chave = x;
            novo->esq = NULL;
            novo->dir = NULL;
            if(x < resp->chave){
                resp->esq = novo;
            }else{
                resp->dir = novo;
            }
        }else{ //eu nao posso adicionar - resp ja tem a chave que eu gostaria de
              //adicionar - chave duplicada
              printf("Adição não permitada. Chave duplicada.");
           
          }
    }
}

void in_ordem(NO* aux){
    if(aux->esq != NULL){
        in_ordem(aux->esq);
    }
    printf("%d ", aux->chave);
    if(aux->dir != NULL){
        in_ordem(aux->dir);
    }
}


int main(){
    add(9);
    add(7);
    //add(5);
    //add(14);
    //add(11);
    //add(2);
    in_ordem(raiz);
}

