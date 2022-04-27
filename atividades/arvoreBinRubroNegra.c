#include <stdio.h>
#include <stdlib.h>

enum cor {R, N};

typedef struct NO {
  int valor;
  struct NO *dir,*esq,*pai;
  enum cor cor;
}NO;

typedef struct RB {
  NO *raiz;
  NO *externo;
}RB;

NO*sucessor(RB *t, NO *x) {
  while(x->esq != t->externo)
    x= x->esq;
return x;
}

NO* new_NO(int valor) {
  NO* n= malloc(sizeof(NO));
  n->esq= NULL;
  n->dir= NULL;
  n->pai= NULL;
  n->valor= valor;
  n->cor= R;

return n;
}

RB* new_RB() {
  RB *t= malloc(sizeof(RB));
  NO *novo= malloc(sizeof(NO));
  novo->esq= NULL;
  novo->dir= NULL;
  novo->pai= NULL;
  novo->cor= N;
  novo->valor= 0;
  t->externo= novo;
  t->raiz= t->externo;

return t;
}

void MoverPai(RB *t, NO *u, NO *v) {
  if(u->pai == t->externo) t->raiz= v;
  else {
    if(u == u->pai->esq) u->pai->esq= v;
    else u->pai->dir= v;
  }
  v->pai= u->pai;
}

void RotacaoE(RB *t, NO *x) {
  NO *y= x->dir;
  x->dir= y->esq;
  if(y->esq != t->externo) {
    y->esq->pai= x;
  }
  y->pai= x->pai;
  if(x->pai == t->externo) t->raiz= y;
  else if(x == x->pai->esq) x->pai->esq= y;
  else x->pai->dir= y;

  y->esq= x;
  x->pai= y;
}

void RotacaoD(RB *t, NO *x) {
  NO *y= x->esq;
  x->esq= y->dir;
  if(y->dir != t->externo) {
    y->dir->pai= x;
  }
  y->pai = x->pai;
  if(x->pai == t->externo) t->raiz= y;
  else if(x == x->pai->dir) x->pai->dir= y;
  else x->pai->esq= y;

  y->dir= x;
  x->pai= y;
}

void RotaRN(RB *t, NO *z) {
  while(z->pai->cor == R) {
    if(z->pai == z->pai->pai->esq) { 
      NO *y= z->pai->pai->dir; 

      if(y->cor == R) {
        z->pai->cor= N;
        y->cor= N;
        z->pai->pai->cor= R;
        z= z->pai->pai;
      }
      else { 
        if(z == z->pai->dir) {
          z= z->pai;
          RotacaoE(t, z);
        }
      
        z->pai->cor= N; 
        z->pai->pai->cor= R; 
        RotacaoD(t, z->pai->pai);
      }
    }
    else { //parte analoga trocada do rotarn
      NO *y= z->pai->pai->esq;

      if(y->cor == R) {
        z->pai->cor= N;
        y->cor= N;
        z->pai->pai->cor= R;
        z= z->pai->pai;
      }
      else {
        if(z == z->pai->esq) {
          z= z->pai;
          RotacaoD(t, z);
        }
        z->pai->cor= N;
        z->pai->pai->cor= R;
        RotacaoE(t, z->pai->pai);
      }
    }
  }
  t->raiz->cor = N;
}

void RotaRemoverRN(RB *t, NO *x) {
  while(x != t->raiz && x->cor == N) {
    if(x == x->pai->esq) {
      NO *w= x->pai->dir;

      if(w->cor == R) {
        x->pai->cor= R;
        w->cor= N;
        RotacaoE(t, x->pai);
        w= x->pai->dir;
      }
      if(w->dir->cor == N && w->esq->cor == N) {
        w->cor= R;
        x= x->pai;
      }
      else {
        if(w->dir->cor == N) {
          w->esq->cor= N;
          w->cor= R;
          RotacaoD(t, w);
          w= x->pai->dir;
        }
        w->cor= x->pai->cor;
        x->pai->cor= N;
        w->dir->cor= N;
        RotacaoE(t, x->pai);
        x= t->raiz;
      }
    }
    else { //parte analoga trocada do rotaremoverrn
      NO *w= x->pai->esq;

      if(w->cor == R) {
        x->pai->cor= R;
        w->cor= N;
        RotacaoD(t, x->pai);
        w= x->pai->esq;
      }
      if(w->dir->cor == N && w->esq->cor == N) {
        w->cor= R;
        x= x->pai;
      }
      else {
        if(w->esq->cor == N) {
          w->dir->cor= N;
          w->cor= R;
          RotacaoE(t, w);
          w= x->pai->esq;
        }
        w->cor= x->pai->cor;
        x->pai->cor= N;
        w->esq->cor= N;
        RotacaoD(t, x->pai);
        x= t->raiz;
      }
    }
  }
  x->cor= N;
}

void InserirRN(RB *t, NO *z) {
  NO* y= t->externo;
  NO* pt= t->raiz;

  while(pt != t->externo) {
    y= pt;
    if(z->valor == pt->valor) y= NULL;
    if(z->valor < pt->valor) pt= pt->esq;
    else pt= pt->dir;
  }

  if(y != NULL){
    z->pai= y;

    if(y == t->externo) t->raiz= z;
    else {
      if(z->valor < y->valor) y->esq= z;
      else y->dir= z;
    }

  z->dir= t->externo;
  z->esq= t->externo;
  z->cor= R;

  RotaRN(t, z);
  }
}

void removerRN(RB *t, NO *z) {
  NO *y= z;
  NO *x;
  enum cor corOriginal= y->cor;
  if(z->esq == t->externo) {
    x= z->dir;
    MoverPai(t, z, z->dir);
  }
  else{ 
    if(z->dir == t->externo) {
      x= z->esq;
      MoverPai(t, z, z->esq);
    }
    else {
      y= sucessor(t, z->dir);
      corOriginal= y->cor;
      x= y->dir;
      if(y->pai == z) x->pai= z;
      else {
        MoverPai(t, y, x);
        y->dir= z->dir;
        y->dir->pai= y;
      }
      MoverPai(t, z, y);
      y->esq= z->esq;
      y->esq->pai= y;
      y->cor= z->cor;
    }
  }
  if(corOriginal == N) RotaRemoverRN(t, x);
}

int quantiaNos(NO *raiz){
    if(raiz->valor == 0) return 0;
    else return (quantiaNos(raiz->esq) + quantiaNos(raiz->dir))+1;
}

int calculaN(NO *raiz){
  int n=0;
    if(raiz->valor == 0) return 0;
    else {
      if(raiz->cor == N) n=1;
      return (calculaN(raiz->esq) + calculaN(raiz->dir))+n;
    }
}

int confereN(NO *raiz){
  int bal1=0,bal2=0;
  if(raiz->dir->valor!=0) bal1= calculaN(raiz->dir);
  if(raiz->esq->valor!=0) bal2= calculaN(raiz->esq);
  if(bal1!=bal2) return 1;

  if(raiz->esq->valor!=0) confereN(raiz->esq);
  if(raiz->dir->valor!=0) confereN(raiz->dir);
  
}

int main() {
  int nos, verifica,i,j;
  int valores[11]={17,22,16,29,7,4,32,2,3,34,33};

  RB *t = new_RB();
  NO *no[11];
  RB *arvores[10]; //diminui a quantia de arvores e nós como no programa anterior
  for(i=0;i<9;i++) arvores[i]= new_RB();
  //NO *novo;

  for(i=0;i<11;i++){ //teste manual
    no[i]= new_NO(valores[i]);
    InserirRN(t,no[i]);
  }

  //no[0]->dir->cor= N; //desbalanceia se quiser, pra conferi o confereN()
  nos= quantiaNos(t->raiz); //não sei se é pra contar os últimos nós negros também, eu puis pra só mostra os inseridos mesmo, acho que era essa a intenção
  verifica= confereN(t->raiz);

  for(i=0;i<10;i++){ //teste automatico: 10 arvores 100 nos de 0 a 100.000 com remocao de 10 nós depois
    for(j=0;j<100;j++){
      NO *novo;
      novo= new_NO(rand()%100000);
      InserirRN(arvores[i],novo);
    }
    verifica= confereN(arvores[i]->raiz); //mesmo comportamento do programa anterior, aqui confere a arvore recem criada e inserida
    if (verifica==0) printf("eh Rubro-Negra");
    else printf("nao eh Rubro-negra");

    nos= quantiaNos(arvores[i]->raiz);
    printf("%d",nos);

    for(j=0;j<10;j++){ //notei o erro do programa da at2 que fazia a remoção automática falhar, esse for tbm tava com i variando ao inves de j
      removerRN(arvores[i],arvores[i]->raiz);
    }
    verifica= confereN(arvores[i]->raiz);
    if (verifica==0) printf("eh Rubro-Negra");
    else printf("nao eh Rubro-negra");

    nos= quantiaNos(arvores[i]->raiz);
    printf("%d",nos);
  }

return 0;
}