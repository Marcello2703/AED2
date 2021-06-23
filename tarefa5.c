//MARCELLO FONSECA DE OLIVEIRA
//RA: 140664
#include <stdio.h>
#include <stdlib.h>

int particao(int V[], int inicio, int fim)
{
    int pivo = V[fim];
    int aux, j, i = inicio;
    for (j = inicio; j < fim; j++)
    {
        if (V[j] <= pivo)
        {
            if (V[j] != V[i])
            {
                aux = V[j];
                V[j] = V[i];
                V[i] = aux;
            }
            i++;
        }
    }
    aux = V[fim];
    V[fim] = V[i];
    V[i] = aux;
    return (i);
}

int quicksort(int V[], int inicio, int fim, int k)
{
    if (inicio <= fim)
    {
        int index = particao(V, inicio, fim);
        if (index == k - 1)
        {
            return V[index];
        }
        else
        {
            if (index < k - 1)
            {
                return quicksort(V, index + 1, fim, k);
            }
            else
            {
                return quicksort(V, inicio, index - 1, k);
            }
        }
    }
}

void imprime(int V[], int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        printf("%d ", V[i]);
    }
}
int main()
{
    int k, n, i;
    scanf("%d", &k);
    do
    {
        scanf("%d", &n);
    } while ((n < k) || (n > 1000 && n < 0));

    int vet[n];
    for (i = 0; i < n; i++)
    {
        scanf("%d", &vet[i]);
    }

    printf("%do menor elemento eh o %d\n", k, quicksort(vet, 0, n - 1, k));

    imprime(vet, n);
}