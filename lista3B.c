//Marcello Fonseca de Oliveira 140664
#include <stdio.h>
#include <stdlib.h>
void imprime(int *v, int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        printf("%d ", v[i]);
    }
}
void insertionSortRecursivo(int *v, int n, int nivel)
{
    if (n <= 1)
        return;

    insertionSortRecursivo(v, n - 1, nivel + 1);

    int chave = v[n - 1];
    int i = n - 2;

    while (i >= 0 && v[i] > chave)
    {
        v[i + 1] = v[i];
        i = i - 1;
    }
    v[i + 1] = chave;
    printf("%d %d %d\n", nivel + 1, chave, i + 1);
}
int main()
{
    int n, i, nivel = 0, *vet;
    scanf("%d", &n);
    vet = (int *)malloc(n * sizeof(int));

    for (i = 0; i < n; i++)
        scanf("%d", &vet[i]);

    insertionSortRecursivo(vet, n, nivel);
    imprime(vet, n);
    free(vet);
}