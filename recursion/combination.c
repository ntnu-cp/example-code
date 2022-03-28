// by hlwang
// Recursively generate all k-combinations of {1, ..., n}

#include <stdio.h>
#define N 20 // Note: n < N

void print_combination(int ans[], int k)
{
    for (int i = 0; i < k; i++)
        printf("%d ", ans[i]);
    printf("\n");
    return;
}

void choose(int n, int k, int p[], int ans[], int pos)
{
    // apply the identity C(n, k) = C(n-1, k-1) + C(n-1, k)

    // terminal condition
    if (n < k)
        return;

    if (k == 0)
    {
        print_combination(ans, pos);
        return;
    }

    // recursively formula
    ans[pos] = p[0];
    choose(n - 1, k - 1, p + 1, ans, pos + 1);
    choose(n - 1, k, p + 1, ans, pos);

    return;
}

int main()
{
    int n, k, p[N], ans[N];

    scanf("%d%d", &n, &k);

    for (int i = 0; i < n; i++)
        p[i] = i + 1;

    choose(n, k, p, ans, 0);

    return 0;
}
