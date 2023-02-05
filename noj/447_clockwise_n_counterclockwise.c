#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>
#define MAXN 100

int arr[MAXN];
int grid[MAXN][MAXN];

int main()
{
    const int EMPTY = -1;
    int n, k;
    scanf("%d%d", &n, &k);
    assert(n >= 1 && n <= 100);
    assert(k >= 1 && k <= 20);

    for (size_t i = 0; i < n; i++)
    {
        scanf("%d", arr + i);
        assert(arr[i] >= 0 && arr[i] <= 10000);
    }

    for (int r, c, d, i = 0; i < k; i++)
    {
        scanf("%d%d%d", &r, &c, &d);
        assert(r * c == n);
        assert(d == 0 || d == 1);

        size_t ia = 0;
        memset(grid, -1, sizeof(grid));
        for (size_t rr = 0; rr < r; rr++)
        {
            for (size_t cc = 0; cc < c; cc++)
            {
                grid[rr][cc] = arr[ia++];
            }
        }

        int dr[] = {0, 1, 0, -1};
        int dc[] = {1, 0, -1, 0};
        ia = 0;
        int ir = 0, ic = 0;

        if (d == 0)
            d++;
        else
            d = -1;
        int id = d > 0 ? 0 : 1;

        while (1)
        {
            arr[ia++] = grid[ir][ic];
            grid[ir][ic] = EMPTY;

            int t = 0;
            for (; t < 2; t++)
            {
                int nr = ir + dr[id];
                int nc = ic + dc[id];

                if (nr < 0 || nr >= r || nc < 0 || nc >= c || grid[nr][nc] == EMPTY)
                {
                    id = ((id + d) + 4) % 4;
                    continue;
                }

                ir = nr;
                ic = nc;
                break;
            }

            if (t == 2)
                break;
        }
    }

    for (size_t i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
