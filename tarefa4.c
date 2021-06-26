#include <stdio.h>
#include <stdlib.h>
int mergeSort(int v[], int tamanho, int kont);
int _mergeSort(int v[], int temp[], int inicio, int final, int kont);
int merge(int v[], int temp[], int inicio, int meio,
          int final, int kont);

int mergeSort(int v[], int tamanho, int kont) //funcao aux que cria um vet temporario e chama a merge sort
{
    int *temp = (int *)malloc(tamanho * sizeof(int)); //vet temporario auxiliar na ordenacao
    return _mergeSort(v, temp, 0,
                      tamanho - 1, kont);
}

int _mergeSort(int v[], int temp[], int inicio, int final, int kont)
{
    int meio, cont = 0;
    if (final > inicio)
    {
        meio = (final + inicio) / 2;

        cont += _mergeSort(v, temp, inicio, meio, kont);
        cont += _mergeSort(v, temp, meio + 1, final, kont);
        cont += merge(v, temp, inicio, meio + 1, final, kont);
    }
    return cont; //carregará o contador de pares para a função auxiliar e main
}

int merge(int v[], int temp[], int inicio, int meio, //func de ordenacao e contagem
          int final, int kont)
{
    int i = inicio, j = meio, k = inicio;
    int cont = 0;
    //primeiro laço: ira percorrer o vetor recebido como parametro em duas partes comparando as posições e contando os pares que satisfazem a condição
    while ((i <= meio - 1) && (j <= final))
    {
        if (v[i] <= kont * v[j])
        {
            k++;
            i++;
        }
        else
        {
            k++;
            j++;
            cont = cont + (meio - i);
        }
    }
    //restaura os valores dos contadores pra percorrer ordenando
    i = inicio;
    j = meio;
    k = inicio;
    //percorre o vetor parametro, inserindo de forma ordenada os valores no vetor temporario
    while ((i <= meio - 1) && (j <= final))
    {
        if (v[i] <= v[j])
        {
            temp[k++] = v[i++];
        }
        else
        {
            temp[k++] = v[j++];
        }
    }
    //caso i passe do meio ou j chegue ao final, os valores restantes do vetor seram alocados ao vetor temporario
    while (i <= meio - 1)
        temp[k++] = v[i++];

    while (j <= final)
        temp[k++] = v[j++];
    //passa os valores do vetor temp para o vetor original
    for (i = inicio; i <= final; i++)
        v[i] = temp[i];

    return cont; //retorna o numero de pares contados
}

int main()
{
    int i, n, k;
    scanf("%d", &n);
    scanf("%d", &k);

    int v[n];

    for (i = 0; i < n; i++)
    {
        scanf("%d", &v[i]);
    }
    printf("%d\n", mergeSort(v, n, k)); //chama a função auxiliar e printa o resultado
    return 0;
}
×