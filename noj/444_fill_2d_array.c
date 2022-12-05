#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void fill_2d(int *ptr1, int r1, int c1, int *ptr2, int r2, int c2)
{
    // Ensure that x <= y
    if (ptr1 > ptr2)
    {
        fill_2d(ptr2, r2, c2, ptr1, r1, c1);
        return;
    }

    if (r1 == r2)
    {
        while (ptr1 <= ptr2)
        {
            *ptr1 = 1;
            ptr1++;
        }
        return;
    }

    int c = ((ptr2 - ptr1) - (c2 - c1)) / (r2 - r1);
    int lc = c1 < c2 ? c1 : c2;
    int rc = c1 > c2 ? c1 : c2;
    int *ptr = ptr1 - c1;
    for (int i = r1; i <= r2; i++)
    {
        for (int j = lc; j <= rc; j++)
        {
            ptr[j] = 1;
        }
        ptr += c;
    }
}

// int main()
// {
//     int r1, c1, r2, c2;
//     scanf("%d%d%d%d", &r1, &c1, &r2, &c2);

//     // init 2d array
//     int r = 10, c = 10;
//     int arr[r][c];

//     // set array to zeros
//     memset(arr, 0, r * c * sizeof(int));

//     fill_2d(&arr[r1][c1], r1, c1, &arr[r2][c2], r2, c2);

//     // output XY
//     for (int i = 0; i < r; i++)
//     {
//         for (int j = 0; j < c; j++)
//         {
//             printf("%d ", arr[i][j]);
//         }
//         printf("\n");
//     }

//     return 0;
// }
