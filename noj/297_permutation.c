// Problem link: https://noj.tw/problem/297

#include <stdio.h>
#define N 11

// n = 4, k = 2, num = {3, 1, 4, 5}
// result:
// 1, 3 | 1, 4 | 1, 5
// 3, 1 | 3, 4 | 3, 5
// 4, 1 | 4, 3 | 4, 5
// 5, 1 | 5, 3 | 5, 4

int find(int num[], int n, int r)
{
    // find the rth element in num[] (0 <= r <= n-1)
    //  return the index of it.
    int *ptr[N] = {};
    for (int i = 0; i < n; i++)
        ptr[i] = &(num[i]);

    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - 1 - i; j++)
        {
            if (*ptr[j] > *ptr[j + 1])
            {
                int *tmp = ptr[j];
                ptr[j] = ptr[j + 1];
                ptr[j + 1] = tmp;
            }
        }
    return (ptr[r] - &(num[0]));
}

void swap(int num[], int x, int y)
{
    int tmp = num[x];
    num[x] = num[y];
    num[y] = tmp;
    return;
}

void print_sol(int ans[], int m)
{
    for (int i = 0; i < m; i++)
        printf("%d ", ans[i]);
    printf("\n");
    return;
}

void permute(int n, int k, int num[], int ans[], int x)
{
    // choose k numbers out of num[];
    // put the resulting k-permutation into ans[]
    // ans[] contains x elements

    // terminal condition
    if (k == 0)
    {
        print_sol(ans, x);
        return;
    }

    // recursive formula
    //   choose an element from num[] (in order)
    //   put it into ans[x]
    //   recursively choose k-1 elements from the remaining n-1 numbers.
    for (int i = 0; i < n; i++)
    {
        int j = find(num, n, i);
        swap(num, 0, j);
        // e.g. n = 4, k = 2, num = {3, 1, 4, 5}
        // i=0 --> choose 1
        //  remain: {3, 4, 5} --> choose 1 number from this array.
        ans[x] = num[0];
        permute(n - 1, k - 1, num + 1, ans, x + 1);
    }
    return;
}

int main()
{
    int n, k;
    scanf("%d%d", &n, &k);

    int num[N] = {};
    for (int i = 0; i < n; i++)
        scanf("%d", &num[i]);

    int ans[N] = {};
    permute(n, k, num, ans, 0);

    return 0;
}
