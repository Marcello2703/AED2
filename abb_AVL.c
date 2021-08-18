//Marcello Fonseca de Oliveira
//RA: 140664

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
 
typedef struct arv
{
    int chave;
    struct arv *esq;
    struct arv *dir;
    int balanco;
} tArv;
 
typedef tArv *pArv; //ponteiro do tipo arvore

int maior(int x, int y){
  return (x > y)? x : y;
}

pArv menorNo(pArv a){ //retorna o menor no a esquerda
  pArv aux = a;
  while(aux->esq != NULL){
    aux = aux->esq;
  }
  return aux;
}

int balancoNo(pArv a){ //retorna o balanco de dado no
  if(a==NULL)
    return 0;
  return a->balanco;
}

int getBalanco(pArv a){ //faz o calculo do balanco de um nó pai
  if(a==NULL)
    return 0;
  return balancoNo(a->esq) - balancoNo(a->dir);
}

pArv rotacaoDireita(pArv a){
  pArv x = a->esq;
  pArv t2 = x->dir;

  x->dir = a;
  a->esq = t2; 

  a->balanco = maior(balancoNo(a->esq), balancoNo(a->dir))+1; 
  x->balanco =  maior(balancoNo(x->esq), balancoNo(x->dir))+1;

  return x;
}

pArv rotacaoEsquerda(pArv a){
  pArv y = a->dir;
  pArv t2 = y->esq;

  y->esq = a;
  a->dir = t2;

  a->balanco = maior(balancoNo(a->esq), balancoNo(a->dir))+1;
  y->balanco = maior(balancoNo(y->esq), balancoNo(y->dir))+1;

  return y;
}

pArv insere(pArv a, int valor)
{
    
    if (a == NULL)
    {
        pArv novo = (pArv)malloc(sizeof(tArv));
        novo->chave = valor;
        novo->esq = NULL;
        novo->dir = NULL;
        novo->balanco = 1;
        return novo;
    }
    if (valor < a->chave)
    {
        a->esq = insere(a->esq, valor);
    }
    else if(valor > a->chave)
    {
        a->dir = insere(a->dir, valor);
    }else{
      return a;
    }

    a->balanco = 1 + maior(balancoNo(a->esq), balancoNo(a->dir));

    int balanco = getBalanco(a);


    if(balanco > 1 && valor < a->esq->chave){
      return rotacaoDireita(a);
    }
    if(balanco < -1 && valor > a->dir->chave){
      return rotacaoEsquerda(a);
    }
    if(balanco > 1 && valor > a->esq->chave){
      a->esq = rotacaoEsquerda(a->esq);
      return rotacaoDireita(a);
    }
    if(balanco < -1 && valor < a->dir->chave){
      a->dir = rotacaoDireita(a->dir);
      return rotacaoEsquerda(a);
    }
    return a;
}
 
pArv removeNo(pArv a, int valor)
{
    if (a == NULL)
    {
        return a;
    }

    if (valor < a->chave)
    {
        a->esq = removeNo(a->esq, valor);
    }
    else if (valor > a->chave)
    {
        a->dir = removeNo(a->dir, valor);
    }
    else
    { //achou nó
        if (a->esq == NULL || a->dir == NULL)
        {
            pArv temp = a->esq ? a->esq : a->dir;

            if(temp == NULL){
              temp = a;
              a = NULL;
            }else{
              a = temp;
              free(temp);
            }
        }else{
          pArv temp = menorNo(a->dir);
          a->chave = temp->chave;
          a->dir = removeNo(a->dir, temp->chave);
        }
    }
    if(a == NULL)
      return a;

    a->balanco = 1 + maior(balancoNo(a->esq), balancoNo(a->dir));
    int balanco = getBalanco(a);

    if (balanco > 1 && getBalanco(a->esq) >= 0)
        return rotacaoDireita(a);

    if (balanco > 1 && getBalanco(a->esq) < 0)
    {
        a->esq = rotacaoEsquerda(a->esq);
        return rotacaoDireita(a);
    }

    if (balanco < -1 && getBalanco(a->dir) <= 0)
        return rotacaoEsquerda(a);
 
    if (balanco < -1 && getBalanco(a->dir) > 0)
    {
        a->dir = rotacaoDireita(a->dir);
        return rotacaoEsquerda(a);
    }
 
    return a;

}
 
int descobreAltura(pArv a)
{
    if (a == NULL)
    {
        return -1;
    }
    else
    {
        int he = descobreAltura(a->esq) + 1;
        int hd = descobreAltura(a->dir) + 1;
        if (he < hd)
            return hd;
        else
            return he;
    }
}
 
pArv buscaChave(pArv a, int c)
{
    pArv p;
    p = a;
    while (p != NULL)
    {
        if (p->chave == c)
            return p;
        else
        {
            if (c > p->chave)
                p = p->dir;
            else
                p = p->esq;
        }
    }
    return p;
}

void imprimePrefixa(pArv a)
{
  if(a!=NULL)
  {
    printf("%d", a->chave);
    imprimePrefixa(a->esq);
    imprimePrefixa(a->dir);
  }
}

pArv libera(pArv a)
{
    if (a != NULL)
    {
        libera(a->esq);
        libera(a->dir);
        free(a);
    }
    return NULL;
}

int main(void)
{
    int infoInsercao[1000];
    int buscaRemocao[1000];
    int busca, cont = 0, i, alt1 = 0, altDireita1 = 0, altEsquerda1 = 0, alt2 = 0, altDireita2 = 0, altEsquerda2 = 0;
    pArv resultBusca;
 
    do
    {
        scanf("%d", &infoInsercao[cont]);
        cont++;
    } while (infoInsercao[cont - 1] >= 0);
 
    pArv raiz = NULL;
 
    for (i = 0; i < cont - 1; i++)
    { //percorre o vetor de chave, inserindo os valores na arvore
        
        raiz = insere(raiz, infoInsercao[i]);
    }

    alt1 = descobreAltura(raiz);
    altDireita1 = descobreAltura(raiz->dir) + 1;
    altEsquerda1 = descobreAltura(raiz->esq) + 1;

    cont = 0;
    do
    { //segundo input
        scanf("%d", &buscaRemocao[cont]);
        cont++;
    } while (buscaRemocao[cont - 1] >= 0);
 
    for (i = 0; i < cont - 1; i++)
    {
        if (buscaChave(raiz, buscaRemocao[i]) != NULL)
        { //array que insere ou remove os valores inseridos.
            raiz = removeNo(raiz, buscaRemocao[i]);
        }
        else
        {
            raiz = insere(raiz, buscaRemocao[i]);
        }
    }
 
    bool flag = true;
 
    scanf("%d", &busca); //terceiro input
    resultBusca = buscaChave(raiz, busca);
    if (resultBusca == NULL)
    {
        flag = false;
    }
    else
    {
        alt2 = descobreAltura(resultBusca);
        altDireita2 = descobreAltura(resultBusca->dir)+1;
        altEsquerda2 = descobreAltura(resultBusca->esq)+1;
    }
 
    printf("%d, %d, %d\n", alt1, altEsquerda1, altDireita1);
    if (flag == false)
    {
        printf("Valor nao encontrado\n");
    }
    else
    {
        printf("%d, %d, %d\n", alt2, altEsquerda2, altDireita2);
    }

 
    libera(raiz); // desaloca arvore
    return 0;
}
