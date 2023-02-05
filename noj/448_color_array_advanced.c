#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

void color_array(int **reg[], int n, int c[])
{
    assert(n > 0 && n <= 300);

    int lens[100] = {};
    for (size_t i = 0; i < n; i++)
    {
        int **r = reg[i];
        while (*r != NULL)
        {
            lens[i]++;
            r++;
        }
    }

    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = i + 1; j < n; j++)
        {
            assert(lens[i] != lens[j]);
        }
    }

    for (int i = 0; i < n; i++)
    {
        // Find max
        int max = INT32_MIN;
        int min_j = -1;
        for (int j = 0; j < n; j++)
        {
            if (reg[j] == NULL)
                continue;

            if (max < lens[j])
            {
                max = lens[j];
                min_j = j;
            }
        }

        assert(min_j != -1);

        int **r = reg[min_j];
        while (*r != NULL)
        {
            **r = c[min_j];
            r++;
        }
        reg[min_j] = NULL;
    }
}

int main()
{
    int R = 5, C = 4;
    int arr[R][C];
    memset(arr, -1, R * C * sizeof(int));

    int *r[2][5] = {{&arr[2][0], &arr[2][1], &arr[2][2], NULL},
                    {&arr[1][2], &arr[2][2], &arr[3][2], &arr[4][2], NULL}};

    int **reg[2] = {r[0], r[1]};
    int c[2] = {1, 2};

    color_array(reg, 2, c);

    for (int i = 0; i < R; i++)
    {
        for (int j = 0; j < C; j++)
            printf("%d ", arr[i][j]);
        printf("\n");
    }

    return 0;
}