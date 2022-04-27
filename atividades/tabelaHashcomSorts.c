#include<stdlib.h>
#include<stdio.h>
#include<time.h>

typedef struct no{
    int valor;
    int colisoes;
}NO;

typedef struct no{
    int valor;
    int quantia;
    NO2 *prox;
}NO2;

int tam  = 0;

//parteSort-----------------------------------------------------------------
void troca(int*a,int*b)
{
    int aux=*a;
    *a=*b;
    *b=aux;
}

void subir(int i, int vetor[]){
    int j= i/2;

    if(j>0){

        if(vetor[i]>vetor[j]){

            int aux= vetor[i];
            vetor[i]= vetor[j];
            vetor[j]= aux;

            subir(j,vetor);
        }
    }
}

void descer(int i, int vetor[],int n){
    int esq= 2*i+1;
    int dir= 2*i+2;
    int maior=i;
    
    if(esq<n && vetor[esq]>vetor[maior])    maior=esq;
    if(dir<n && vetor[dir]>vetor[maior])    maior=dir;
    
    if(i!=maior)
    {
        troca(&vetor[i],&vetor[maior]);
        descer(maior,vetor,n);
    }
}

void inserir(int novo, int vetor[]){
    int aux= tam;
    tam++;

    vetor[aux+1]= novo;
    subir(tam, vetor);
}

void remover(int vetor[]){

    if(tam>0){

        vetor[0]= vetor[tam];
        vetor[tam]= 0;
        tam--;

        descer(0,vetor,tam);
    }
    else printf("lista vazia");
}

void construir(int vetor[]){
    int i;

    for (i=(tam/2); i>=0; i--){
        descer(i,vetor,tam);
    }
}

void heapsort(int vetor[]){
    int i=tam-1, aux=tam;
    construir(vetor);

    while(i>0)
    {
        troca(&vetor[0],&vetor[i]);
        i--;  aux--;
        descer(0,vetor,aux);
    }
}

void insertionsort(int vetor[]){
    int i;
    for(i=1;i<=tam;i++){
        int aux= vetor[i];
        int j= i-1;

        while (vetor[j]>aux && j>=0)
        {
            vetor[j+1]= vetor[j];
            j--;
        }
        vetor[j+1]= aux;
    }
}

//parteHash------------------------------------------------------------------
void adiciona(int chave, NO tabela[], int no){
    if(tabela[no].valor==0) tabela[no].valor= chave;
    else tabela[no].colisoes++;
}

void divisao(int chave, NO tabela[]){
    int bloco= chave%10001;

    adiciona(chave,tabela,bloco);
}

void dobra(int chave, NO tabela[]){
    int aux, vetor[6], resp; //chaves com ate 6 casas decimais

    for(int i=0;i<6;i++) vetor[i]= 0;
    
    aux= chave;
    aux= aux/100000;
    vetor[0]= aux;
    aux= chave;
    aux= aux/10000-((chave/100000)*10);
    vetor[1]= aux;
    aux= chave;
    aux= aux/1000-((chave/10000)*10);
    vetor[2]= aux;
    aux= chave;
    aux= aux/100-((chave/1000)*10);
    vetor[3]= aux;
    aux= chave;
    aux= aux/10-((chave/100)*10);
    vetor[4]= aux;
    aux= chave;
    aux= aux/1-((chave/10)*10);
    vetor[5]= aux;

    aux=0;
    aux=vetor[0]+vetor[3]+vetor[4];
    if(aux>9&&aux<100) aux= aux%10;

    resp= aux*10;

    aux=0;
    aux=vetor[1]+vetor[2]+vetor[5];
    if(aux>9&&aux<100) aux= aux%10;
    
    resp= resp+aux;

    adiciona(resp,tabela,resp); //pelo q entendi da aula adiciona no nó com valor da chave (isso criou um grande numero de colisoes ...
                                //...pois na tabela da dobra os números só são inseridos de 0 a 99 mesmo com tamanho de chaves diferentes)
}

void multiplicacao (int chave,NO tabela[]){
    chave*= chave;
    while(chave>9999) chave/= 10; //pega o digito da frente ao invés do do meio (ampliei para os primeiros 4 digitos pra dar mais dispersão)

    adiciona(chave,tabela,chave);
}

void add(int chave,NO2 numeros[],int no){

    if(numeros[no].valor==0) numeros[no].valor= chave;
    else{
        NO2 *aux = &numeros[no];
        NO2 *novo = malloc(sizeof(NO2));
        novo->valor = chave;
        novo->prox = NULL;

        for(int i=0; i<numeros[no].quantia; i++){
            aux = aux->prox;
        }
        aux->prox = novo;
    }
    numeros[no].quantia++;
}

void auxDispersao(int chaves[],int tam){
    NO2 numeros[6]; //até 6 casas decimais de chaves
    int i,j,casa_dec=0, aux;
    

    for(i=0;i<tam;i++){ //poe mais nós com os numeros nas suas casas decimais ex: 41, poe o 4 em numeros[0].valor e 1 em numeros[1.valor]

        aux= chaves[i];
        while(aux!=0){
            casa_dec++;
            aux/=10;
        }

        aux= chaves[i];
        for(j=0;j<casa_dec;j++){
            add(aux%10,numeros,j);
            aux/10;
        }
    }
}



int main(){
  int i,j;

  int vetor[300000]; //sort
  NO tabela1[10000],tabela2[10000],tabela3[10000],tabela4[10000],tabela5[10000]; //hash

  int chaves[20000];

  double time_spent= 0.0; //clock
  clock_t begin = clock();

  for(i=0;i<20000;i++) chaves[i]= rand()%1000000; //cria vetor de chaves aleatórias

  //auxDispersao(chaves,20000); minha dispersão não funcionou de nenhum jeito que tentei

  for(i=0;i<20000;i++){ //poe as chaves na tabela
    //divisao(chaves[i],tabela1);
    //dobra(chaves[i], tabela2);
    //multiplicacao(chaves[i],tabela3);
  }

  j=0;
  for(i=0;i<10000;i++){ //mostra as colisões da tabela
    //j+=  tabela1[i].colisoes;
    //j+=  tabela2[i].colisoes;
    //j+=  tabela3[i].colisoes;
    //j+=  tabela4[i].colisoes;
    //j+=  tabela5[i].colisoes;
  }
  //printf("%d colisoes",j);

  j=300000;
  for(i=0;i<300000;i++){ //não tão aleatório no sort né mas é pra n repetir números no vetor ent puis pior caso :/
    vetor[i]= j;
    j--;
  }
  tam= 300000;

  //heapsort(vetor);
  //insertionsort(vetor);

  clock_t end = clock();
  time_spent += (double)(end - begin) / CLOCKS_PER_SEC;

  printf("programa chegou ao fim com %f",time_spent);
}
