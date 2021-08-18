//MARCELLO FONSECA DE OLIVEIRA 
//RA: 140664

#include <stdio.h>
#include<stdlib.h>

typedef struct celula{
  int conteudo;
  struct celula* prox;
}Celula;

typedef Celula *pCelula; //ponteiro p celula

typedef struct{
  Celula *comeco;
}Lista;

typedef Lista *pLista; //ponteiro p lista

void criaLista(pLista l){
  l->comeco = NULL;
}

void insereLista(pLista l, int val){ //insere no inicio
  pCelula novo = (pCelula)malloc(sizeof(Celula));
  pCelula aux = l->comeco;
  if(novo){
    novo->conteudo = val;
    if(l->comeco == NULL){
      l->comeco = novo;
    }else{
      while(aux->prox != NULL){
        aux = aux->prox;
      }
      aux->prox = novo;
    }
    novo->prox = NULL;
  }else{
    printf("\tErro ao alocar\n");
  }
}

void removeLista(pLista l, int val){
  pCelula atual, proximo, anterior;
  atual = l->comeco;
  proximo = l->comeco->prox;
  while(atual->prox != NULL && atual->conteudo != val){
    anterior = atual;
    atual = atual->prox;
    proximo = proximo->prox;
  }
  if(atual == l->comeco){
    l->comeco = proximo;
    free(atual);
  }else{
    anterior->prox = atual->prox;
    free(atual);
  }
}

pCelula buscaChave(pLista l, int chave){
  pCelula aux = l->comeco;
  while(aux != NULL && aux->conteudo != chave)
    aux = aux->prox;
  if(aux)
    return aux;
  return NULL;
}

void imprimeLista(pLista l){
  pCelula aux = l->comeco;
  while(aux){
    printf("%d ", aux->conteudo);
    aux = aux->prox;
  }
}

void inicializaTabela(Lista tab[], int tam){
  int i;
  for(i=0; i<tam; i++){
    criaLista(&tab[i]);
  }
}

int funcaoHash(int chave, int tam){
  return chave % tam;
}

void insereHash(Lista tab[], int val, int tam){
  int id = funcaoHash(val, tam);
  insereLista(&tab[id], val);
}

void removeHash(Lista tab[], int val, int tam){
  int id = funcaoHash(val, tam);
  removeLista(&tab[id], val);
}

pCelula buscaHash(Lista tab[], int val, int tam){
  int id = funcaoHash(val, tam);
  pCelula aux = buscaChave(&tab[id], val);
  return aux;
}

void imprimeHash(Lista t[], int tam){
  int i;
  for(i=0; i<tam; i++){
    printf("%d = ", i);
    imprimeLista(&t[i]);
    printf("\n");
  }
}

void imprimeLinha(Lista tab[], int linha){
  pCelula aux = tab[linha].comeco;
  if(aux == NULL){
    printf("[%d]\n", linha);
  }else{
    printf("[%d] ", linha);
    while(aux != NULL){
      printf("%d ", aux->conteudo);
      aux = aux->prox;
    }
  }
}


int main(void) {
  int tableTam, cont = 0, i;
  
  scanf("%d", &tableTam);
  Lista tabela[tableTam];

  inicializaTabela(tabela, tableTam);

  int insertValues[1000];

  do{
    scanf("%d", &insertValues[cont]);
    cont++;
  }while(insertValues[cont-1] >= 0);

  for(i=0; i<cont-1; i++){
    //printf("%d ", insertValues[i]);
    insereHash(tabela, insertValues[i], tableTam);
  }
   
  int buscaRetirada; 
  scanf("%d", &buscaRetirada);
  struct celula *aux = buscaHash(tabela, buscaRetirada, tableTam);
  if(aux){
    removeHash(tabela, aux->conteudo, tableTam);
  }else{
    printf("Valor não encontrado\n");
  }

  int printaLinha;
  scanf("%d", &printaLinha);

  //imprimeHash(tabela, tableTam);
  imprimeLinha(tabela, printaLinha);


  return 0;
}