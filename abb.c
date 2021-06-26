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
} tArv;
 
typedef tArv *pArv; //ponteiro do tipo arvore
 
pArv insere(pArv a, pArv new)
{
    if (a == NULL)
    {
        return new;
    }
    if (a->chave > new->chave)
    {
        a->esq = insere(a->esq, new);
    }
    else
    {
        a->dir = insere(a->dir, new);
    }
    return a;
}
 
pArv removeNo(pArv a, int v)
{
    if (a == NULL)
    {
        return NULL;
    }
    else if (a->chave > v)
    {
        a->esq = removeNo(a->esq, v);
    }
    else if (a->chave < v)
    {
        a->dir = removeNo(a->dir, v);
    }
    else
    { //achou nó
        if (a->esq == NULL && a->dir == NULL)
        {
            free(a);
            a = NULL;
        }
        else if (a->esq == NULL)
        { //apenas filho a direita
            pArv t = a;
            a = a->dir;
            free(t);
        }
        else if (a->dir == NULL)
        { //apenas filho a esquerda
            pArv t = a;
            a = a->esq;
            free(t);
        }
        else
        {
            pArv f = a->dir;
            while (f->esq != NULL)
            {
                f = f->esq;
            }
            a->chave = f->chave;
            f->chave = v;
            a->dir = removeNo(a->dir, v);
        }
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
        int he = descobreAltura(a->esq);
        int hd = descobreAltura(a->dir);
        if (he < hd)
            return hd + 1;
        else
            return he + 1;
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
 
    pArv raiz = (pArv)malloc(sizeof(tArv)); //aloca raiz
    raiz->chave = infoInsercao[0];
    raiz->esq = NULL;
    raiz->dir = NULL;
 
    for (i = 1; i < cont - 1; i++)
    { //percorre o vetor de chave, inserindo os valores na arvore
        pArv novo;
        novo = (pArv)malloc(sizeof(tArv));
        novo->chave = infoInsercao[i];
        novo->dir = NULL;
        novo->esq = NULL;
        insere(raiz, novo);
    }
    //imprimePrefixa(raiz);
    //printf("\n");
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
            removeNo(raiz, buscaRemocao[i]);
        }
        else
        {
            pArv novo;
            novo = (pArv)malloc(sizeof(tArv));
            novo->chave = buscaRemocao[i];
            novo->dir = NULL;
            novo->esq = NULL;
            insere(raiz, novo);
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
 
    libera(raiz);
    return 0;
}
