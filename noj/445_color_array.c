#include <stdio.h>
#include <stdlib.h>

void color_array(int **reg[], int n, int c[])
{
    for (int i = 0; i < n; i++)
    {
        // Find min
        int **min = NULL;
        int min_j = -1;
        for (int j = 0; j < n; j++)
        {
            if (reg[j] == NULL)
                continue;

            if (min == NULL || reg[j][0] < *min)
            {
                min = reg[j];
                min_j = j;
            }
        }

        if (min == NULL)
            break;

        while (*min != NULL)
        {
            **min = c[min_j];
            min++;
        }

        reg[min_j] = NULL;
    }
}

int main()
{
    int a[6];
    for (int i = 0; i < 6; i++)
        a[i] = -1;

    int *r[3][4] = {{&a[1], &a[2], &a[3]},
                    {&a[3]},
                    {&a[2], &a[3], &a[4]}};

    int **reg[3] = {r[0], r[1], r[2]};
    int c[3] = {3, 1, 0};
    color_array(reg, 3, c);

    for (int i = 0; i < 6; i++)
        printf("%d ", a[i]);
    printf("\n");

    return 0;
}
