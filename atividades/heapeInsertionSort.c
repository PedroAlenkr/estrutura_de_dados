#include<stdlib.h>
#include<stdio.h>
// exercísio sobre algoritmos de ordenação HeapSort e InsertionSort

int tam = 0;

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
    int j= 2*i;

    if(j<=n){

        if(j<n){

            if(vetor[j+1]>vetor[j]){
                j++;
            }
        }

        if(vetor[i]<vetor[j]){

            int aux= vetor[i];
            vetor[i]= vetor[j];
            vetor[j]= aux;

            descer(j,vetor,n);
        }
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
    int i;
    construir(vetor);

    for(i= tam; i>0; i--){
        vetor[0]= vetor[i];

        descer(0,vetor,i);
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

int main(){
  int i,j;
  int vetor[10000];
  j=10000;

  for(i=0;i<10000;i++){ //não tão aleatório né mas é pq n dá pra repetir números no vetor ent foi nisso q pensei :/
    vetor[i]=j;        
    j--;
  }
  tam= 10000;

  //heapsort(vetor); //heap sort está com problema, em todos os testes ele foi bem mais rápido mas não ordenou e criou novos valores no vetor (geralmente zeros)
  insertionsort(vetor);
  printf("fim");

}
