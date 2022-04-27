#include<stdlib.h>
#include<stdio.h>

typedef struct no{
    int valor, alt, bal;
    struct no *dir,*esq;
}NO;

int maiorAlt(int x, int y){
    if(x>y) return x;
    return y;
}

int altura(NO *raiz){
    if (raiz == NULL) return -1;
    return raiz->alt;
}

int bal(NO *no){
    if(no == NULL) return 0;
    return altura(no->esq) - altura(no->dir);
}

int quantiaNos(NO *raiz){
    if(raiz == NULL) return 0;
    return (quantiaNos(raiz->esq) + quantiaNos(raiz->dir))+1;
}

NO *rotDir(NO *antPai){ //pt
    NO *novoPai, *filho;//ptu ptv
    novoPai= antPai->esq;
    filho= novoPai->dir;

    novoPai->dir= antPai;
    antPai->esq= filho;

    antPai->alt= maiorAlt(altura(antPai->dir), altura(antPai->esq))+1;
    novoPai->alt= maiorAlt(altura(novoPai->dir), altura(novoPai->esq))+1;

    return novoPai;
}

NO *rotEsq(NO *antPai){ 
    NO *novoPai, *filho;
    novoPai= antPai->dir;
    filho= novoPai->esq;

    novoPai->esq= antPai;
    antPai->dir= filho;

    antPai->alt= maiorAlt(altura(antPai->dir), altura(antPai->esq))+1;
    novoPai->alt= maiorAlt(altura(novoPai->dir), altura(novoPai->esq))+1;

    return novoPai;
}

NO *rotDE(NO *no){
    no->dir= rotDir(no->dir);
    return rotEsq(no);
}

NO *rotED(NO *no){
    no->esq= rotEsq(no->esq);
    return rotDir(no);
}

NO *balancear(NO *raiz){
    int Bal= bal(raiz);

    if(Bal>1 && bal(raiz->esq)>=0)  raiz= rotDir(raiz); 
    if(Bal<-1 && bal(raiz->dir)<=0) raiz= rotEsq(raiz);

    if(Bal>1 && bal(raiz->esq)<0)  raiz= rotED(raiz);
    if(Bal<-1 && bal(raiz->dir)>0) raiz= rotDE(raiz); 

    return raiz;
}

NO *inserir(NO *raiz,int x){
    if(raiz== NULL){ //achou espaco
        NO *novo = malloc(sizeof(NO));
    
        novo->valor= x;
        novo->dir= NULL;
        novo->esq= NULL;
        novo->alt= 0;
        novo->bal= 0;

        return novo;
    }
    else{ //checa para onde ir a ab caso não tenha achado espaco vazio
        if(x<raiz->valor) raiz->esq= inserir(raiz->esq,x);
        if(x>raiz->valor) raiz->dir= inserir(raiz->dir,x);
    }

    raiz->alt= maiorAlt(altura(raiz->dir),altura(raiz->esq))+1;
    raiz= balancear(raiz); //se a ab perdeu sua propriedade de AVL é necessário checar pra ver se tem que balancear 

    return raiz;
}

NO *remover (NO *raiz,int chave){
    if(raiz== NULL) return NULL;
    else{
    if(raiz->valor == chave) { // achou o valor
        if(raiz->esq == NULL && raiz->dir == NULL) {free(raiz); return NULL;} // não tem filhos
        else {
            if(raiz->esq!= NULL && raiz->dir!= NULL){// tem 2 filhos
                NO *aux= raiz->esq;

                while(raiz->dir!= NULL) aux= aux->dir;

                raiz->valor= aux->valor;
                aux->valor= chave;
                raiz->esq= remover(raiz->esq,chave);

                return raiz;
            }
            else{ // tem algum filho
                NO *aux;
                if(raiz->esq!= NULL) aux= raiz->esq;
                else aux= raiz->dir;

                free(raiz);
                return aux;
            }
        }
    }
    else{
        if(chave<raiz->valor) raiz->esq= remover(raiz->esq,chave);
        else raiz->dir= remover(raiz->dir,chave);
    }

    raiz->alt= maiorAlt(altura(raiz->esq),altura(raiz->dir))+1;
    raiz= balancear(raiz);

    return raiz;
    }
}

int main(){
    NO *raiz= NULL; //raiz da avl para fazer teste e achar a fonte dos bugs (teste manual)
    int i,j, verifica, nos;

    NO *avls[10]; //diminui a quantia de avls e de nós porque o pc ficava travando (teste automatico)
    for(i=0;i<10;i++) avls[i]= NULL;

    for(i=0;i<10;i++){ //testes automaticos, todos deram certo 
        for(j=0;j<100;j++){
            avls[i]= inserir(avls[i],rand()% 100000); 
        }
        verifica= bal(avls[i]); //cada avl criada a raiz vai pro avls e já confere se é ou não avl e a quantia de nos
        if(verifica==0||verifica==-1||verifica==1) printf("eh AVL");
        else printf("nao eh AVL");

        nos= quantiaNos(avls[i]);
        printf("%d",nos);

        //for(j=0;j<10;j++){ 
            //avls[j]= remover(avls[j],avls[j]->valor);
        //}
        

        //verifica= bal(avls[i]);
        //if(verifica==0||verifica==-1||verifica==1) printf("eh AVL");
        //else printf("nao eh AVL");

        //nos= quantiaNos(avls[i]);
        //printf("%d",nos);
    }

    raiz= inserir(raiz,1); //testes manuais pois estava com problemas 
    raiz= inserir(raiz,2);
    raiz= inserir(raiz,3);
    raiz= inserir(raiz,4);
    raiz= inserir(raiz,5);
    raiz= inserir(raiz,6);

    raiz= remover(raiz,5);

    verifica= bal(raiz);
    if(verifica==0||verifica==-1||verifica==1) printf("eh AVL");
    else printf("nao eh AVL");

    nos= quantiaNos(raiz);
    printf("%d",nos);
}