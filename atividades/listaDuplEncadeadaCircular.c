#include <stdio.h>
#include <stdlib.h>
// exercício sobre lista duplamente encadeada circular com operação para calcular os filhotes da lista

typedef struct no
{
	int id;           //para o identificador dos cangurus
	int sexo;         //para distinguir macho e fêmea com 0 e 1
	int num_filhotes; //para fornecer a quantia de filhotes de cada canguru sendo 0 para machos

	struct no *prox;
	struct no *ant;   //como é duplamente encadeada precisa de ponteiro ant

    //nomes usados são assim para serem iguais os usados no código e na questão da prova
} NO;
//observação: tive que por o typedef desse jeito pois meu compilador tava dando warning do jeito igual da prova

NO *inicio;
int tam =0;

void add(int id, int sexo, int num_filhotes)
{
    NO *novo = (NO*) malloc (sizeof (NO));

    novo->id= id;                      //coloca as informações que precisam estar na lista vvv
    novo->sexo= sexo;
    novo->num_filhotes= num_filhotes;


    if(tam == 0)                       //<-lista vazia
    {
        novo->prox= novo;
        novo->ant= novo;
        inicio= novo;
    }
    else                               //<-lista já com um inicio
    {
        inicio->ant ->prox= novo;   //aqui faz o prox do ultimo elemento da lista (mais conhecido como inicio->ant) aponta pro novo
        novo->prox= inicio;         //agora podemos fazer o prox do novo (que agora é o ultimo elemento da lista pelos ponteiros prox) aponta pro inicio

        novo->ant= inicio->ant;     //para os ponteiros ant, fazemos o ant do novo elemento apontar para o elemento anterior a inicio (que ainda é o ultimo elemento da lista pelos ponteiros ant)
        inicio->ant= novo;          //agora fazemos o ant do inicio que estava apontando para o antigo ultimo elemento apontar para o novo ultimo elemento
    }
    //uma lista circular facilitou o trabalho de adicionar no fim com só o ponteiro inicio, que agora tem complexidade constante :D
    tam++;
}

int soma(NO *inicio)
{
    int soma=0,i;
    NO *aux = inicio;               //<-aqui cria um ponteiro aux que aponta para o inicio da lista

    for(i=0; i<tam; i++)            //<-então movemos o aux até o valor tam mas ao invés de só passa aux pro endereço do...
    {                               //...proximo nó ele também soma os valores de num_filhotes e guarda em soma
        soma+= aux->num_filhotes;
        aux = aux->prox;            //<-poderia ter feito com os ponteiros ant também nesse caso já que é lista circular
    }
return soma;
}

int main()
{
    int som;

    add(1,1,2);
    add(2,1,1);
    add(3,0,0);
    add(4,1,2);
    add(5,0,0);

    som= soma(inicio); //muita criatividade pra nomea variável soma e funcao soma
    printf("soma dos filhotes: %d", som);
}
