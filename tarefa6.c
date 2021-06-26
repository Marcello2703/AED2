#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void max_heapify(int *vet, int n, int index)
{
    int aux;
    int left = 2 * index;
    int right = 2 * index + 1;
    int max;
    if ((left <= n) && (vet[left] > vet[index]))
    {
        max = left;
    }
    else
    {
        max = index;
    }
    if ((right <= n) && (vet[right] > vet[index]))
    {
        max = right;
    }
    if (max != index)
    {
        aux = vet[index];
        vet[index] = vet[max];
        vet[max] = aux;
        max_heapify(vet, n, max);
    }
}
int heap_extract_max(int *vet, int n)
{
    if (n >= 1)
    {
        int max = vet[0];
        int last = n;
        vet[0] = vet[last];
        n--;
        max_heapify(vet, n, 0);
        return max;
    }
}
void heapsort(int *vet, int n)
{
    build_max_heap(vet, n);
    int V[n];
    while (n > 0)
    {
        V[n] = heap_extract_max(vet, n);
    }
}
void build_max_heap(int *vet, int n)
{
    int i;
    for (i = n / 2; i >= 1; i--)
    {
        max_heapify(vet, n, i);
    }
}
int main()
{
    int n;
    scanf("%d", &n);
    //char palavras[n][20];
}