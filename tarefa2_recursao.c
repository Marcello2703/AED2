#include <stdio.h>

int vale_livros(int n, int v)
{
    if (n / v == 0)
    {
        return 0;
    }
    return n / v + vale_livros(n / v + n % v, v);
}

int main()
{
    int i, n, d, p, v, ans;
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        scanf("%d %d %d", &d, &p, &v);
        ans = d / p + vale_livros(d / p, v);
        printf("%d\n", ans);
    }
}