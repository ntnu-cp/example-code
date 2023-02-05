#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define _min(a, b) ((a) < (b) ? (a) : (b))
#define _max(a, b) ((a) > (b) ? (a) : (b))

int min(int a, int b, int c)
{
    int d = _min(b, c);
    return _min(a, d);
}

int max(int a, int b, int c)
{
    int d = _max(b, c);
    return _max(a, d);
}

void fill_3d(int *ptr1, int x1, int x2, int x3,
             int *ptr2, int y1, int y2, int y3,
             int *ptr3, int z1, int z2, int z3)
{
    if (ptr1 > ptr2)
    {
        fill_3d(ptr2, y1, y2, y3,
                ptr1, x1, x2, x3,
                ptr3, z1, z2, z3);
        return;
    }
    else if (ptr1 > ptr3)
    {
        fill_3d(ptr3, z1, z2, z3,
                ptr2, y1, y2, y3,
                ptr1, x1, x2, x3);
        return;
    }
    else if (ptr2 > ptr3)
    {
        fill_3d(ptr1, x1, x2, x3,
                ptr3, z1, z2, z3,
                ptr2, y1, y2, y3);
        return;
    }

    int dl = max(x1, y1, z1) - min(x1, y1, z1);
    int dr = max(x2, y2, z2) - min(x2, y2, z2);
    int dc = max(x3, y3, z3) - min(x3, y3, z3);
    //	printf("%d %d %d\n", dl,dr,dc);

    int C = 0, R = 0;
    if (x1 == y1 && x1 == z1)
    {
        if (z3 == x3)
        {
            C = (ptr3 - ptr1) / dr;
        }
        else
        {
            C = (ptr3 - ptr1 - (z3 - x3)) / dr;
        }
    }
    else
    {
        double xy1 = x1 - y1,
               xy2 = x2 - y2,
               xy3 = x3 - y3,
               xyptr = ptr1 - ptr2;
        printf("%lf %lf %lf\n", xy1, xy2, xyptr - xy3);
        double xz1 = x1 - z1,
               xz2 = x2 - z2,
               xz3 = x3 - z3,
               xzptr = ptr1 - ptr3;
        printf("%lf %lf %lf\n", xz1, xz2, xzptr - xz3);
        if (xy1 == 0)
            xy1 = z1 - y1,
            xy2 = z2 - y2,
            xy3 = z3 - y3,
            xyptr = ptr3 - ptr2;
        {
            double yz1 = z1 - y1,
                   yz2 = z2 - y2,
                   yz3 = z3 - y3,
                   yzptr = ptr3 - ptr2;
            printf("%lf %lf %lf\n", yz1, yz2, yzptr - yz3);
        }

        double t = xz1 / xy1;
        double c = (xzptr - t * xyptr - (xz3 - t * xy3)) / (xz2 - t * xy2);
        double r = 0;
        if (xy1 != 0)
            r = (xyptr - xy3 - c * xy2) / (xy1 * c);
        else if (xz1 != 0)
            r = (xzptr - xz3 - c * xz2) / (xz1 * c);
        C = (int)(0.5 + c), R = (int)(0.5 + r);
    }
    //	printf("%d %d %lf\n",R,C,c);

    int *start = ptr1;
    if (x2 != min(x2, y2, z2))
        start -= (x2 - min(x2, y2, z2)) * C;
    if (x3 != min(x3, y3, z3))
        start -= (x3 - min(x3, y3, z3));

    for (int k = 0; k <= dl; k++)
    {
        for (int i = 0; i <= dr; i++)
        {
            for (int j = 0; j <= dc; j++)
            {
                *(start + k * R * C + i * C + j) = 1;
            }
        }
    }
}

int main()
{
    int x1, x2, x3, y1, y2, y3, z1, z2, z3;
    scanf("%d%d%d%d%d%d%d%d%d", &x1, &x2, &x3, &y1, &y2, &y3, &z1, &z2, &z3);

    // init 3d array & set array to zeros
    int r, c, l;
    scanf("%d%d%d", &l, &r, &c);
    int arr[l][r][c];
    memset(arr, 0, l * r * c * sizeof(int));

    fill_3d(&arr[x1][x2][x3], x1, x2, x3,
            &arr[y1][y2][y3], y1, y2, y3,
            &arr[z1][z2][z3], z1, z2, z3);

    int ll = min(x1, y1, z1), hl = max(x1, y1, z1);
    int lr = min(x2, y2, z2), hr = max(x2, y2, z2);
    int lc = min(x3, y3, z3), hc = max(x3, y3, z3);

    // output XY
    for (int k = 0; k < l; k++)
    {
        for (int i = 0; i < r; i++)
        {
            for (int j = 0; j < c; j++)
            {
                if (k >= ll && k <= hl && i >= lr && i <= hr && j >= lc && j <= hc)
                {
                    assert(arr[k][i][j] == 1);
                }
                else
                {
                    assert(arr[k][i][j] == 0);
                }
                // printf("%d", arr[k][i][j]);
            }
            // printf("\n");
        }
        // printf("\n");
    }

    return 0;
}
