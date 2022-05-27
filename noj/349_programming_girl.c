// Problem link: https://noj.tw/problem/349

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#define MAXN 16

int dfs(unsigned int acc, int acc_cost, int start_idx, unsigned int target, int len, unsigned int vals[MAXN], unsigned int costs[MAXN])
{
    if (acc == target)
    {
        return acc_cost;
    }

    int min_cost = INT32_MAX;
    for (int i = start_idx; i < len; i++)
    {
        if ((acc | vals[i]) > acc)
        {
            int cost = dfs(acc | vals[i], acc_cost + costs[i], i + 1, target, len, vals, costs);
            min_cost = (cost < min_cost) ? cost : min_cost;
        }
    }

    return min_cost;
}

int main()
{
    int n, k;
    unsigned int vals[MAXN] = {},
                 costs[MAXN] = {},
                 target = 0;
    scanf("%d%d", &n, &k);
    for (size_t i = 0; i < k; i++)
    {
        target = (target << 1) | 1;
    }
    for (size_t i = 0; i < n; i++)
    {
        scanf("%u %u", &costs[i], &vals[i]);
    }

    printf("%d\n", dfs(0, 0, 0, target, n, vals, costs));

    return 0;
}
